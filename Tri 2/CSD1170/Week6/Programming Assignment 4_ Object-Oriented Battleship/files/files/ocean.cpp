/******************************************************************************/
/*!
\file   ocean.cpp
\author Muhammad Farhan Bin Ahmad
\par    email: b.muhammadfarhan@digipen.edu
\par    DigiPen login: b.muhammadfarhan
\par    Course: CS1170
\par    Section A
\par    Assignment 4: Constructors and Operator Overloading
\date   10/02/2022
\brief
 A script does the following:
  1. CreateOcean -Initialize the starting element for the battleship:
   a. The grid that represent the ocean
   b. The boats that is to be place in the ocean.The actually placing is done in PlaceBoat function. Here we just initializing
  2. DestroyOcean - Delete all dynamically allocated memeory we use
  3. TakeShot - Taking a shot into the grid
    a.Illegal shot - Check if the shot being send it legal(inside the ocean grid)
    b.Miss - The shot fail to hit a boat
    c.Duplicate - Check if the shot hit an already hit grid 
    d.Hit - Hit a boat
    e.Sunk - Has sunk a boat
  4. PlaceBoat - Placing the boat in the ocean. Dictate if the incoming boat placement is legal

*/
/******************************************************************************/


#include <iostream>
#include <iomanip>
#include "ocean.h"

namespace HLP2
{
    namespace WarBoats
    {

        Ocean::Ocean(int num, int x, int y) : num_boats{num}, x_size{x}, y_size{y} //
        {
            int total_size = x * y;
            this->grid = new int[total_size]{DamageType::dtOK};

            this->boats = new Boat[num_boats]{};

            this->stats.duplicates = 0;
            this->stats.hits = 0;
            this->stats.misses = 0;
            this->stats.sunk = 0;

            for (int i = 0; i < num; i++)
            {
                this->boats[i].hits = 0;
                this->boats[i].ID = 0;
            }
        }
        ShotResult Ocean::TakeShot(Point const &coordinate)
        {
            int p = coordinate.y * this->x_size + coordinate.x;
            // Check grid stats
            // THATS ILLEGAL
            if ((coordinate.x < 0) || (coordinate.x > this->x_size - 1) || (coordinate.y < 0) || (coordinate.y > this->y_size - 1))
            {
                return srILLEGAL;
            }

            // MISS ME
            if ((this->grid[p] == dtOK))
            {
                this->stats.misses++;
                this->grid[p] = dtBLOWNUP;
                return srMISS;
            }

            // DUPLICATE
            if (this->grid[p] == dtBLOWNUP || (this->grid[p] >= 1 + HIT_OFFSET && this->grid[p] <= 99 + HIT_OFFSET))
            {
                this->stats.duplicates++;
                return srDUPLICATE;
            }
            // HIT
            this->stats.hits++;
            int c_BoatId = this->grid[p];
            this->boats[c_BoatId - 1].hits++; // Need offset -1 cause array
            this->grid[p] += HIT_OFFSET;
            // SUNK
            if (this->boats[c_BoatId - 1].hits == BOAT_LENGTH)
            {
                this->stats.sunk++;
                return srSUNK;
            }

            return srHIT;
        }
        BoatPlacement Ocean::PlaceBoat(Boat const &boat) const
        {
            // If the boat placement is Horizontal
            if (boat.orientation == oHORIZONTAL)
            {
                // Need check only 1 point in y
                if (boat.position.y >= 0 && boat.position.y <= this->y_size)
                {
                    // Need check 4 points in x
                    if (boat.position.x >= 0 && boat.position.x <= this->x_size - BOAT_LENGTH)
                    {
                        int i = 0;
                        int c_g = 0;
                        while (i < BOAT_LENGTH)
                        {
                            // check each grid in the desire place in the grid to see if its legal to place it in
                            c_g = boat.position.y * this->x_size + (boat.position.x + i);
                            if (this->grid[c_g] != DamageType::dtOK)
                            {
                                return bpREJECTED;
                            }
                            i++;
                        }
                        // If the 4 grid spaces are free
                        i = 0;
                        c_g = 0;
                        while (i < BOAT_LENGTH)
                        {
                            c_g = boat.position.y * this->x_size + (boat.position.x + i);
                            if (this->grid[c_g] == DamageType::dtOK)
                            {
                                this->grid[c_g] = boat.ID; // Allocate grid to boat
                            }
                            i++;
                        }
                        return bpACCEPTED;
                    }
                }
            }
            // If the boat placement is Vertical
            if (boat.orientation == oVERTICAL)
            {
                // Need check only 1 point in x
                if (boat.position.x >= 0 && boat.position.x <= this->x_size)
                {
                    // Need check 4 points in y
                    if (boat.position.y >= 0 && boat.position.y <= this->y_size - BOAT_LENGTH)
                    {
                        int i = 0;
                        int c_g = 0;
                        // check each grid in the desire place in the grid to see if its legal to place it in
                        while (i < BOAT_LENGTH)
                        {
                            c_g = (boat.position.y + i) * this->x_size + boat.position.x;
                            if (this->grid[c_g] != DamageType::dtOK)
                            {
                                return bpREJECTED;
                            }
                            i++;
                        }
                        // If the 4 grid spaces are free
                        i = 0;
                        c_g = 0;
                        while (i < BOAT_LENGTH)
                        {
                            c_g = (boat.position.y + i) * this->x_size + boat.position.x;
                            if (this->grid[c_g] == DamageType::dtOK)
                            {
                                this->grid[c_g] = boat.ID; // Allocate grid to boat
                            }
                            i++;
                        }
                        return bpACCEPTED;
                    }
                }
            }
            // If fail
            return bpREJECTED;
        }
        ShotStats Ocean::GetShotStats() const
        {
            return this->stats; // bruh
        }
        Point Ocean::GetDimensions() const
        {
            Point temp;
            temp.x = x_size;
            temp.y = y_size;
            return temp;
        }
        int* Ocean::GetGrid() const
        {
            return grid;
        }
        Ocean::~Ocean()
        {
            delete[] this->grid;
            delete[] this->boats;
        }
    }
}

#include "ocean.h"
#include <iostream> // std::cout
#include <iomanip>  // std::setw
/******************************************************************************/
/*!
\file   q.cpp
\author Muhammad Farhan Bin Ahmad
\par    email: b.muhammadfarhan@digipen.edu
\par    DigiPen login: b.muhammadfarhan
\par    Course: CS170
\par    Section A
\par    Lab #3 :Lab: Problem Solving with std::strings
\date   21/01/2022
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
namespace HLP2 {


  namespace WarBoats {
    int const BOAT_LENGTH {4};   //!< Length of a boat
    int const HIT_OFFSET  {100}; //!< Add this to the boat ID

   
    Ocean* CreateOcean(int num_boats, int x_size, int y_size)
    {
      Ocean *Oc  =new Ocean;//Create ne ocean

      //Set size of ocean
      int total_size = x_size * y_size;
      Oc->x_size = x_size;
      Oc->y_size = y_size;
      Oc->grid = new int[total_size]{DamageType::dtOK};
      
      //Set total number of boat
      Oc->boats = new Boat[num_boats]{};

      //Reset all stat
      Oc->stats.duplicates = 0;
      Oc->stats.hits = 0;
      Oc->stats.misses = 0;
      Oc->stats.sunk = 0;

      for (int i =0; i < num_boats ;i++)
      {
        Oc->boats[i].hits = 0;
        Oc->boats[i].ID = 0;
      }

      return Oc;
    }
    void DestroyOcean(Ocean *theOcean)
    {
      //Return what was taken
      delete[] theOcean->grid;
      delete[] theOcean->boats;
      delete theOcean;
    }
    ShotResult TakeShot(Ocean& ocean, Point const& coordinate)
    {

      int p = coordinate.y * ocean.x_size + coordinate.x;
      //Check grid stats
      //THATS ILLEGAL
      if ((coordinate.x < 0) || (coordinate.x > ocean.x_size-1) || (coordinate.y < 0) || (coordinate.y > ocean.y_size-1))
      {
        return srILLEGAL;
      }
      
      //MISS ME
      if ((ocean.grid[p] == dtOK) )
      {
        ocean.stats.misses++;
        ocean.grid[p] = dtBLOWNUP;
        return srMISS;
      }

      //DUPLICATE
      if (ocean.grid[p] == dtBLOWNUP || (ocean.grid[p] >= 1+HIT_OFFSET && ocean.grid[p] <= 99+HIT_OFFSET) )
      {
        ocean.stats.duplicates++;
        return srDUPLICATE;
      }
      //HIT
      ocean.stats.hits++;
      int c_BoatId = ocean.grid[p];
      ocean.boats[c_BoatId-1].hits++;//Need offset -1 cause array
      ocean.grid[p] += HIT_OFFSET;
      //SUNK
      if (ocean.boats[c_BoatId-1].hits == BOAT_LENGTH)
      {
        ocean.stats.sunk++;
        return srSUNK;
      }

      return srHIT;

    }
    BoatPlacement PlaceBoat(Ocean& ocean, Boat const& boat)
    {
      //If the boat placement is Horizontal
      if (boat.orientation == oHORIZONTAL)
      {
        //Need check only 1 point in y
        if (boat.position.y >=0 && boat.position.y <= ocean.y_size)
        {
          //Need check 4 points in x
          if (boat.position.x >=0 && boat.position.x <= ocean.x_size-BOAT_LENGTH)
          {
            int i =0;
            int c_g = 0;
            while (i < BOAT_LENGTH)
            {
              //check each grid in the desire place in the grid to see if its legal to place it in
              c_g = boat.position.y * ocean.x_size + (boat.position.x+i);
              if (ocean.grid[c_g] != DamageType::dtOK)
              {
                  return bpREJECTED;
              }
              i++;
            }
            //If the 4 grid spaces are free
            i =0;
            c_g = 0;
            while (i < BOAT_LENGTH)
            {
              c_g = boat.position.y * ocean.x_size + (boat.position.x+i);
              if (ocean.grid[c_g] == DamageType::dtOK)
              {
                ocean.grid[c_g] = boat.ID;//Allocate grid to boat
              }
              i++;
            }
            return bpACCEPTED;
          }
        }
      }
      //If the boat placement is Vertical
      if (boat.orientation == oVERTICAL)
      {
        //Need check only 1 point in x
        if (boat.position.x >=0 && boat.position.x <= ocean.x_size)
        {
          //Need check 4 points in y
          if (boat.position.y >=0 && boat.position.y <= ocean.y_size-BOAT_LENGTH)
          {
            int i =0;
            int c_g = 0;
            //check each grid in the desire place in the grid to see if its legal to place it in
            while (i < BOAT_LENGTH)
            {
              c_g = (boat.position.y+i) * ocean.x_size + boat.position.x;
              if (ocean.grid[c_g] != DamageType::dtOK)
              {
                return bpREJECTED;
              }
              i++;
            }
            //If the 4 grid spaces are free
            i =0;
            c_g = 0;
            while (i < BOAT_LENGTH)
            {
              c_g = (boat.position.y+i) * ocean.x_size + boat.position.x;
              if (ocean.grid[c_g] == DamageType::dtOK)
              {
                ocean.grid[c_g] = boat.ID;//Allocate grid to boat
              }
              i++;
            }
            return bpACCEPTED;
          }
        }
      }
      //If fail 
      return bpREJECTED;
    }
    ShotStats GetShotStats(Ocean const& ocean)
    {
        return ocean.stats;//bruh
    }
    void DumpOcean(const HLP2::WarBoats::Ocean &ocean,
                                    int field_width, 
                                    bool extraline, 
                                    bool showboats) {
      for (int y = 0; y < ocean.y_size; y++) { // For each row
        for (int x = 0; x < ocean.x_size; x++) { // For each column
            // Get value at x/y position
          int value = ocean.grid[y * ocean.x_size + x];
            // Is it a boat that we need to keep hidden?
          value = ( (value > 0) && (value < HIT_OFFSET) && (showboats == false) ) ? 0 : value;
          std::cout << std::setw(field_width) << value;
        }
        std::cout << "\n";
        if (extraline) { std::cout << "\n"; }
      }
    }
  } // namespace WarBoats
} // namespace HLP2

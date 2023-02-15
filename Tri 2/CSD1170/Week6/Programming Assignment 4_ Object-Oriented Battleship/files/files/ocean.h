/******************************************************************************/
/*!
\file   ocean.hpp
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
namespace HLP2
{
    namespace WarBoats
    {
        inline int const BOAT_LENGTH {4}; //!< Length of a boat
        inline int const HIT_OFFSET {100}; //!< Add this to the boat ID
        enum Orientation   { oHORIZONTAL, oVERTICAL };
        enum ShotResult    { srHIT, srMISS, srDUPLICATE, srSUNK, srILLEGAL };
        enum DamageType    { dtOK = 0, dtBLOWNUP = -1 };
        enum BoatPlacement { bpACCEPTED, bpREJECTED };

        struct Point
        {
            int x,y;
        };
        struct Boat
        {
            int hits,ID;
            Orientation orientation;
            Point position;
        };
         struct ShotStats {
            int hits;       //!< The number of boat hits
            int misses;     //!< The number of boat misses
            int duplicates; //!< The number of duplicate (misses/hits)
            int sunk;       //!< The number of boats sunk
        };

        class Ocean
        {
        private:
        int *grid;        //!< The 2D ocean 
        Boat *boats;      //!< The dynamic array of boats
        int num_boats;    //!< Number of boats in the ocean
        int x_size;       //!< Ocean size along x-axis
        int y_size;       //!< Ocean size along y-axis
        ShotStats stats;
        public:
        Ocean (int num_boats, int x_size, int y_size);
        ShotResult TakeShot( Point const& coordinate);
        BoatPlacement PlaceBoat( Boat const& boat) const;
        ShotStats GetShotStats() const;
        Point GetDimensions() const;
        int* GetGrid() const;
        ~Ocean();
        };
        
    }
}
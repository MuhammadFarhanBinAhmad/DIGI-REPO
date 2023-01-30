#include "ocean.h"
#include <iostream> // std::cout
#include <iomanip>  // std::setw

namespace HLP2 {
  namespace WarBoats {
    int const BOAT_LENGTH {4};   //!< Length of a boat
    int const HIT_OFFSET  {100}; //!< Add this to the boat ID

    /*
     * ALL STUDENT IMPLEMENTATION GOES HERE 
    */

    /**************************************************************************/
    /*!
      \brief
        Prints the grid (ocean) to the screen.
      
      \param ocean
        The Ocean to print
      
      \param field_width
        How much space each position takes when printed.
      
      \param extraline
        If true, an extra line is printed after each row. If false, no extra
        line is printed.
        
      \param showboats
        If true, the boats are shown in the output. (Debugging feature)
    */
    /**************************************************************************/
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

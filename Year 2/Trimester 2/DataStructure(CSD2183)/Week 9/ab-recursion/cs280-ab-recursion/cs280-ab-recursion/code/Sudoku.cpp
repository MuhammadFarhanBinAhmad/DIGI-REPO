/******************************************************************************/
/*!
\file:		Sudoku.cpp
\author:  MuhammadFarhanBinAhmad
\par email: 2200544@sit.singaporetech.edu.sg
\date:		March 25, 2024
\brief		Sudoku solver
*/
/******************************************************************************/
#include "Sudoku.h"
Sudoku::Sudoku(int basesize, SymbolType stype, SUDOKU_CALLBACK callback)
    : stype_{stype}, callback_{callback}
{
  stats_.basesize = basesize;
  board_width = basesize * basesize;
  board_size = board_width * board_width;
}
Sudoku::~Sudoku()
{
  delete[] board_;
}

void Sudoku::SetupBoard(const char *values, size_t size)
{
  board_ = new char[size];

  // Set board values to be empty or filled with values;
  size_t i = 0;
  while (i < size)
  {
    if (values[i] == '.')
    {
      board_[i] = EMPTY_CHAR;
    }
    else
    {
      board_[i] = values[i];
    }
    i++;
  }
}
void Sudoku::Solve()
{
  // When you start the algorithm (the client calls Solve),
  // you will send MSG_STARTING.
  callback_(*this, board_, MSG_STARTING, stats_.moves,
            stats_.basesize, 0, stype_);

  int value = 0;

  if (place_value(value))
  {
    callback_(*this, board_, MSG_FINISHED_OK, stats_.moves, stats_.basesize, 0, stype_);
  }
  else
  {
    callback_(*this, board_, MSG_FINISHED_FAIL, stats_.moves, stats_.basesize, 0, stype_);
  }
}
bool Sudoku::place_value(int index)
{
  // return if index is at end of sudoku board
  if (index == board_size)
  {
    return true;
  }

  // if board position is filled with other values, move to next index
  if (board_[index] != EMPTY_CHAR)
  {
    return place_value(index + 1);
  }

  char value{};

  // set value type if its number or letter
  if (stype_ == SymbolType::SYM_NUMBER)
  {
    value = '1';
  }
  else
  {
    value = 'A';
  }

  for (int i = 0; i < board_width; i++)
  {
    // You will send MSG_ABORT_CHECK immediately before you place a value or
    // remove a value. If this call returns true, you will terminate
    // the search.
    if (callback_(*this, board_, MSG_ABORT_CHECK, stats_.moves, stats_.basesize, index, value))
    {
      return false;
    }

    // Place value onto board
    board_[index] = value;

    // Increment moves and place count
    stats_.moves++;
    stats_.placed++;

    // After you place a value on the board, you will send MSG_PLACING.
    callback_(*this, board_, MSG_PLACING, stats_.moves, stats_.basesize, index, value);

    // If if there is conflict
    if (!Conflict(index, value))
    {
      // Go to next index if there is no conflict
      if (place_value(index + 1))
      {
        return true;
      }
      // if fail to place value, need to increment backtrack count
      stats_.backtracks++;
    }

    // if conflict, remove value by setting board index back to empty
    // decrement number of place count
    board_[index] = EMPTY_CHAR;
    stats_.placed--;

    // After removing a value from the board, you will send MSG_REMOVING.
    callback_(*this, board_, MSG_REMOVING, stats_.moves, stats_.basesize, index, value);

    // increment to next number or letter
    value++;
  }

  return false;
}
bool Sudoku::Conflict(int index, char value)
{
  // get row as x-axis and column as y-axis
  int x = index % board_width;
  int y = index / board_width;

  int row_start = y * board_width;

  // Check row
  int rs = row_start;
  while (rs < row_start + board_width)
  {
    if (rs == index)
    {
      rs++;
      continue;
    }

    if (board_[rs] == value)
    {
      return true;
    }

    rs++;
  }

  // Check column
  int bw = 0;
  while (bw < board_width)
  {
    int curr_pos = bw * board_width + x;

    if (index == curr_pos)
    {
      bw++;
      continue;
    }

    if (board_[curr_pos] == value)
    {
      return true;
    }

    bw++;
  }

  // check box
  int startX = x - x % stats_.basesize;
  int startY = y - y % stats_.basesize;

  for (int i = 0; i < stats_.basesize; i++)
  {
    for (int j = 0; j < stats_.basesize; j++)
    {
      int curr_pos = ((startY + i) * board_width) + startX + j;

      if (index == curr_pos)
      {
        continue;
      }

      if (board_[curr_pos] == value)
      {
        return true;
      }
    }
  }

  return false;
}
const char *Sudoku::GetBoard() const
{
  return board_;
}
Sudoku::SudokuStats Sudoku::GetStats() const
{
  return stats_;
}
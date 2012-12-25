#include <cassert>
#include <iomanip>
#include "state.h"

State::State(Puzzle p) : puzzle(p), moves("") {
  space = 0;
  while ( p &0xf ) {
    space += 1;
    p >>= 4;
  }
}

bool State::audit() {
  // For testing
  // Should have one of each hex digit
  
  bool bits = auditBits(puzzle);
  if ( !bits ) 
    cout << "bitset" << endl;
  // Space marks position of space
  Puzzle mask = static_cast<Puzzle>(0xf) << (4*space);
  bool sp = (puzzle & mask) == 0;
  if ( !sp ) 
    cout << "space " << space << endl;
  // Bound is correct
  return (bits && sp);
}

State State::down() const {
  // Move the space down 1 position
  // Pre: space < 12

  assert(space < 12);
  State answer(*this);
  Puzzle mask = Puzzle(0xf) << (16 + 4*space);  // position of tile that moves
  Puzzle tile = puzzle & mask;
  answer.puzzle &= ~mask;                  // replace tile by space
  answer.puzzle |= ( tile >> 16 );         // replace space by tile
  /* Space moves down, so tile moves up.
     Therefore, newRow = oldRow - 1 ==> oldRow = newRow + 1
  */
  answer.moves.push_back('D');
  answer.space += 4;
  //if ( !answer.audit() )
  //   cout << *this << "\nDOWN\n" << answer << endl;
  return answer;
}

State State::up() const {
  // Move the space up 1 position
  // Pre: space > 3

  assert(space > 3);
  State answer(*this);
  Puzzle mask = Puzzle(0xf) << (4*space - 16);  // position of tile that moves
  Puzzle tile = puzzle & mask;
  answer.puzzle &= ~mask;                  // replace tile by space
  answer.puzzle |= ( tile << 16 );         // replace space by tile
  /* Space moves up, so tile moves down.
     Therefore, newRow = oldRow + 1 ==> oldRow = newRow - 1
  */
  answer.moves.push_back('U');
  answer.space -= 4;
 /* if ( !answer.audit() )
    cout << *this << "\nUP\n" << answer << endl;*/
  return answer;
}

State State::left() const {
  // Move the space left 1 position
  // Pre: space % 4 != 0

  assert(space %4 != 0 );
  State answer(*this);
  Puzzle mask = Puzzle(0xf) << (4*space - 4);  // position of tile that moves
  Puzzle tile = puzzle & mask;
  answer.puzzle &= ~mask;                        // replace tile by space
  answer.puzzle |= ( tile << 4 );                // replace space by tile
  /* Space moves left, so tile moves right.
     Therefore, newCol = oldCol + 1 ==> oldCol = newCol - 1
  */
  answer.moves.push_back('L');
  answer.space -= 1;
  //if ( !answer.audit() )
  //  cout << *this << "\nLEFT\n" << answer << endl;
  return answer;
}

State State::right() const {
  // Move the space right 1 position
  // Pre: space % 4 != 3

  assert (space %4 != 3);
  State answer(*this);
  Puzzle mask = Puzzle(0xf) << (4*space + 4);  // position of tile that moves
  Puzzle tile = puzzle & mask;
  answer.puzzle &= ~mask;                      // replace tile by space
  answer.puzzle |= ( tile >> 4 );              // replace space by tile
  /* Space moves right, so tile moves left.
     Therefore, newCol = oldCol - 1 ==> oldCol = newCol + 1
  */
  answer.moves.push_back('R');
  answer.space += 1;
 /* if ( !answer.audit() )
    cout << *this << "\nRIGHT\n" << answer << endl;*/
  return answer;
}

ostream& operator<<(ostream& out, const State& state) {
  Puzzle p = state.puzzle;
  for ( int r = 0; r < 4; ++r) {
    for (int c = 0; c < 4; ++c) {
      int tile = p & 0xf;
      p >>= 4;
      out << setw(2) << tile << " ";
    }
    out << '\n';
  }
  return out;
}


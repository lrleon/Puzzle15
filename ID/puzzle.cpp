#include <map>
#include <sstream>
#include "puzzle.h"

bool auditBits(Puzzle puzzle) {
  int bitset = 0;
  Puzzle p = puzzle;
  for ( int k = 0; k < 16; ++k ) {
    int shift = p & 0xf;
    bitset |= 1 << shift;
    p >>= 4;
  }
  return bitset == 0xffff;
}

bool isOdd(Puzzle p) {
  // Is p an odd permutation?

  map<int, int> perm;
  int total = 0;
 
  for ( int idx = 0; idx < 16; ++idx ) {
    perm[idx] = p & 0xf; ;
    p >>= 4;
  }
  while ( !perm.empty() ) {
    int key = perm.begin()->first;
    int length = 0;
    while ( perm.count(key) != 0 ) {
      length += 1;
      int value = perm[key];
      perm.erase(key);
      key = value;
    }
    total += length - 1;
  }
  return total % 2 == 1;
}

bool solvable(Puzzle puzzle) {
  bool odd = isOdd(puzzle);
  int idx;
  for ( idx = 0; idx < 16; ++idx ) {
    if ( (puzzle & 0xf) == 0 ) break;
    puzzle >>= 4;
  }
  int zero = idx % 2;
  return static_cast<int>(odd) == zero;       
}

Puzzle readPuzzle(istream& fin) {
  // Read one puzzle from fin.
  // Return 0 on EOF

  string line;
  int shiftAmt = 0;
  Puzzle puzzle = 0;
  getline(fin, line);
  if ( fin.eof() )
    return 0;
  istringstream stream(line);
  for ( int k = 0; k < 16; ++k ) {
    unsigned u;
    stream >> u;
    Puzzle temp(u);
    puzzle |= (temp << shiftAmt);
    shiftAmt += 4;
  }
  if ( !auditBits(puzzle) )
    throw line;
  return puzzle;
}
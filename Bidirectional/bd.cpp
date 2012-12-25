// 15puzzle.cpp
// Calculate minimum number of moves to solve 15-puzzle

// Each succeeding line is the initial configuration of the tiles,
// left to right, top to bottom, with the space indicated by 0.

// The goal state is
//     1   2   3
//  4  5   6   7
//  8  9  10  11
// 12 13  14  15 


// Use bidirectional search with iterative deepening, keeping track of the 
// nodes on the current search path.

// Input file:
// One puzzle per line.  The first 16 entries are the tiles, in order.
// There may be additional entries, giving expected results, but they are ignored.

// Output the sequence of moves to solve the puzzles, one per line.

#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <string>
#include <cassert>
#include <ctime>
#include "state.h"

using namespace std;

// Tiles represented as 4-bit ints.  Stored row-major in reverse order.
// This makes the methods up, down, left, right of the State class easier to write.
// The goal state is: 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 space

const unsigned INFINITY = 100000;
Puzzle State::goal = 0xfedcba9876543210;
set<Puzzle> dfsNodes;   // nodes on current DFS path

string solve(Puzzle puzzle);

int main(int argc, char *argv[]) {
  time_t start, stop;
  time(&start);
  string infile, outfile;
  cout << "Started at " << asctime(localtime(&start)) << endl;
  if ( argc == 3 ) {
    infile = argv[1];
    outfile = argv[2];
  }
  else {
    cout << "Enter input file name: ";
    cin >> infile;
    cout << "Enter output file name: ";
    cin >> outfile;
  }

  ifstream fin(infile);
  if (! fin) {
    cerr << "Could not open input file\n";
    exit(1);
  }
  ofstream fout(outfile);

  int num = 0;
  try {
    while ( !fin.eof() ) {
      Puzzle puzzle = readPuzzle(fin);
      num += 1;
      if ( !solvable(puzzle) )
        fout << "Impossible" << endl;
      else {
        string answer = solve(puzzle);
        cout << answer << endl;
        fout << answer << endl;
      }
      puzzle = readPuzzle(fin);
    }
  }
  catch ( string line) {
    cerr << "Invalid input: " << line << endl;
    fout.close();
    exit(1);
  }
  time(&stop);
  double elapsed = difftime(stop, start);
  unsigned hours = static_cast<unsigned> (elapsed / 3600);
  elapsed -= 3600*hours;
  unsigned minutes = static_cast<unsigned> (elapsed / 60);
  int seconds = static_cast<int> (elapsed - 60*minutes);
  cout << num << " puzzle ";
  cout << (num == 1) ? "\n" : "s\n";
  cout << "Ended at " << asctime(localtime(&stop)) << endl;
  cout << "Elapsed time " << hours << ":" << minutes << ":" << seconds  << endl;
  return 0;
}

Solution DLS(State node, unsigned depth) {
  // depth-limited search

  //cout << "DLS: minCost " << minCost << endl;

  if ( node.puzzle == node.goal )
    return Solution(node.moves);

  if ( depth == 0 )
    return("");

  if ( dfsNodes.count(node.puzzle) > 0 )
    return Solution("");
  else
    dfsNodes.insert(node.puzzle);

  if ( node.space < 12 ) {
    Solution soln = DLS(node.down(), depth-1);
    if ( soln != "" )
      return soln;
  }

  if ( node.space % 4 != 0 ) {
    Solution soln = DLS(node.left(), depth-1);
    if ( soln != "" ) 
      return soln;
  }

  if ( node.space  % 4 != 3 ) {
    Solution soln = DLS(node.right(), depth-1);
    if ( soln != "" ) 
      return soln;
  }

  if ( node.space > 3 ) {  
    Solution soln = DLS(node.up(), depth-1);
    if ( soln != "" ) 
      return soln;
  }

  dfsNodes.erase(node.puzzle);
  return Solution("");
}

string solve(Puzzle puzzle) {
  if ( puzzle == State::goal ) return "";   // no moves needed
  string answer;

  State node(puzzle);

  // We can tell from the structure of the puzzle whether an 
  // even or odd number of moves is required to solve it.

  unsigned depth = static_cast<int> (isOdd(puzzle));
  while (true) {
    assert(dfsNodes.empty());
    Solution answer = DLS(node, depth);
    if ( answer != "" )
      return answer; 
    depth += 2;
  }
  return "";   // should never get here
}


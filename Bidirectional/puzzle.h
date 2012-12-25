#pragma once;
#include <iostream>
#include <stdexcept>
using namespace std;

typedef unsigned long long Puzzle; 

bool auditBits(Puzzle puzzle);
bool isOdd(Puzzle perm);
bool solvable(Puzzle puzzle);
Puzzle readPuzzle(istream& fin);  // returns 0 on EOF; may throw invalid input

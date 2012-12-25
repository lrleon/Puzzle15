#pragma once
#include <iostream>
#include "puzzle.h"
using namespace std;

typedef string Solution;

struct State {
  static Puzzle goal;
  State() : moves(""), puzzle(goal), space(0) { }
  State(Puzzle p);
  State down() const;
  State left() const;
  State right() const;
  State up() const;
  bool audit();    // for debugging
  Puzzle puzzle;
  string moves;   // moves represented as D(own), L(eft), R(ight), U(p) 
  int space;
};

 ostream& operator<<(ostream& out, const State& state);

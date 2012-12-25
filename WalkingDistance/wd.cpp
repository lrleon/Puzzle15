/* This is an attempt to understand the walking distance heuristic from
   http://www.ic-net.or.jp/home/takaken/e/15pz/index.html. 
   where it is claimed that there are 24,964 cases.

   Now if the A's represent tiles whose goal is in row 1, the B's represent tiles
   with goal in row 2, and similarly for C's and D's, we have one symmetry:
   exchange the B's and C's and then exchange row 2 and row 3.  This program counts
   23,096 distinct configurations, modulo this symmetry, rather than 24,964.

   I haven't been able to reconcile this.  Of course, a program needn't use this symmery;
   it might be faster not to.
*/

#include <iostream>
#include <cassert>
using namespace std;

/* Place 4 A's, 4 B's, 4 C's and 4 D's.  Then since we must change 
   a D to a space, the permutation represents as many cases as there are rows
   with a D.  (It doesn't matter which D in a row we change to a space.)
*/
int main() {
  int count = 0;
  for ( int a1 = 0; a1 <= 4; ++ a1 )
  for ( int a2 = 0; a2 <= 4-a1; ++a2 )
  for ( int a3 = 0; a3 <= 4-a1-a2; ++a3 )
  for ( int b1 = 0; b1 <= 4-a1; ++b1 )
  for ( int b2 = 0; b2 <= min(4-a2, 4-b1); ++b2)
  for ( int b3 = 0; b3 <= min(4-a3, 4-b1-b2); ++b3)
  for ( int c1 = 0; c1 <= 4-a1-b1; c1++ )
  for ( int c2 = 0; c2 <= min(4-a2-b2, 4-c1); ++c2)
  for ( int c3 = 0; c3 <= min(4-a3-b3, 4-c1-c2); ++c3) {
    int d1 = 4 - a1 - b1 - c1;
    int d2 = 4 - a2 - b2 - c2;
    int d3 = 4 - a3 - b3 - c3;
    int a4 = 4 - a1 - a2 - a3;
    int b4 = 4 - b1 - b2 - b3;
    int c4 = 4 - c1 - c2 - c3;
    int d4 = 4 - d1 - d2 - d3;
    assert( a4 >= 0 && b4 >= 0 && c4 >= 0 && d4 >= 0);
    assert (d1 >= 0 && d2 >= 0 && d3 >= 0);
    if ( b1 < c1 || b1 == c1 && b4 < c4 ) continue; 
    if ( b1 == c1 && b4 == c4 ) {
      int m = min(min(b2, b3), min(c2, c3));
      if ( m != b2 && m != b3 ) continue;
    }
    int delta = (d1 > 0) + (d2 > 0) + (d3 > 0) + (d4 > 0);
    assert( 0 <= delta && delta <= 4);
    count += delta;
  }
  cout << count << " count" << endl;
  return 0;
}
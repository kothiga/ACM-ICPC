//
// Solution for ACM-ICPC 4422 - Combination Lock
//   (North America - Rocky Mountain Regional 2008)
//
//     Compile : g++11 -std=c++11 -o 4422 4422.cc -Wall
//  Written by : Austin Kothig
//    Semester : SPRING 2017
//     Problem : Given a lock, find the average number of ticks
//               required to open said lock from any starting position
//

#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;

double solve(int start, int n, int t1, int t2, int t3)
{
   // this can be done just once.
   double d = 3*n;

   // start -> t1 (CW)
   if(start != t1){d += (n + (start - t1)) % n;}

   // t1 -> t2 (CCW)
   d += ((n + (t2 - t1)) % n);

   // t2 -> t3 (CW)
   d += ((n + (t2 - t3)) % n);
   
   return d;
}

int main()
{
   // setup
   int n, t1, t2, t3;
   while(cin >> n >> t1 >> t2 >> t3)
   {
      // exit condition
      if (n == 0 && t1 == 0 && t2 == 0 && t3 == 0) break;

      // get the average
      double d = 0;
      for(int i = 0; i < n; i++)
	 d += solve(i, n, t1, t2, t3);
      d /= n;     

      // output
      cout << fixed << setprecision(3) << d << endl;
   }
}

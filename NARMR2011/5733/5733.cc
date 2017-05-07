//
// Solution for ACM-ICPC 5733 - Iterated Difference
//   (North America - Rocky Mountain Regional 2011)
//
//     Compile : g++11 -std=c++11 -o 5733 5733.cc -Wall
//  Written by : Austin Kothig
//    Semester : SPRING 2017
//     Problem : Find the number of times you are required
//               to iterate through to make an entire sequence
//               the same number.
//

#include <iostream>
#include <stdlib.h>

using namespace std;

const int MAX_N = 20;

bool check(int c, long long n[], int N)
{
   // if this counter
   // is larger than 1000
   // we are asked to exit   
   if(c > 1000)
      return false;

   // find out if this sequence
   // is all equivelent
   for(int i = 1; i < N; i++)
   {
      if(n[i] != n[i-1])
	 return true; // true means no
   }
   // sequence found
   return false;
}

int main()
{
   // setup
   int N;
   int CASE = 1;
   while(cin >> N && N != 0)
   {
      int c = -1;
      long long n[MAX_N];
      
      for(int i = 0; i < N; i++)
	 cin >> n[i];

      // loop until found or iterations = 1000
      while(check(c++, n, N))
      {
	 long long temp[MAX_N];
	 for(int i = 0; i < N; i++)
	    temp[i] = n[i];

	 // grab the abs of k - k+1
	 for(int i = 0; i < N; i++)
	    n[i] = abs( temp[i] - temp[(N+i+1)%N] ); 
      }

      // output
      cout << "Case " << CASE++ << ": ";
      if(c <= 1000)
	 cout << c << " iterations\n";
      else
	 cout << "not attained\n";
   }
}

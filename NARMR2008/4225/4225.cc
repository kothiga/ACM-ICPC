//
// Solution for ACM-ICPC 4225 - Prime Bases
//   (North America - Rocky Mountain Regional 2008)
//
//     Compile : g++11 -std=c++11 -o 4225 4225.cc -Wall
//  Written by : Austin Kothig
//    Semester : SPRING 2017
//     Problem : Given a number, deconstruct it
//               print out its mixed bases
//

#include <iostream>

using namespace std;

int main()
{
   unsigned int num;
   const int primeList[12] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37 };
   while(cin >> num && num)
   {
      // build our printing array
      int i;
      int out[12];
      cout << num << " = ";
      for(i = 0; num > 0; i++)
      {
	 // store the numbers to be
	 // multiplied by the primes
	 out[i] = num % primeList[i];

	 // this will cumulitively
	 // include all primes
	 num = num / primeList[i];
      }

      // output
      bool printCheck = false;
      for(int j = 0; j < i; j++)
      {
	 // make sure this index is non-zero
	 if(out[j])
	 {
	    // check if we have printed
	    // atleast one thing
	    if(printCheck){ cout << " + "; }

	    // print the number
	    cout << out[j];

	    // print all the primes that have divided it
	    for(int k = 0; k < j; k++)
	       cout << "*" << primeList[k];

	    // keep printing the ' + ' between
	    printCheck = true;
	 }
      }
      cout << endl;
   }
}

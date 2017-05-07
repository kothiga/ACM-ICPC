//
// Solution for ACM-ICPC 4192 - Close Enough Computations
//   (North America - Rocky Mountain Regional 2008)
//
//     Compile : g++11 -std=c++11 -o 4192 4192.cc -Wall
//  Written by : Austin Kothig
//    Semester : SPRING 2017
//     Problem : Find if the given calories are within
//               the range of if the fats, carbs, and
//               proteins were rounded up/down.
//

#include <iostream>

using namespace std;

const double UP = -0.5;
const double DW = 0.49999;

double rounder(double fats, double carbs, double prot, double r)
{
   // check to see if the
   // value is non-zero
   if(fats) fats += r;
   if(carbs) carbs += r;
   if(prot) prot += r;

   // calculate the calories
   return (fats)*9 + (carbs)*4 + (prot)*4;
}

int main()
{
   // setup
   double total, fat, carb, prot;
   
   while(cin >> total >> fat >> carb >> prot)
   {
      if(!total && !fat && !carb && !prot) break;

      // calculate the extremes had the
      // manufacturer rounded up or down 
      double RUp = rounder(fat, carb, prot, UP);
      double RDw = rounder(fat, carb, prot, DW);      

      // output
      if( RUp <= total && total <= RDw )
	 cout << "yes\n";
      else
	 cout << "no\n";
   }
}

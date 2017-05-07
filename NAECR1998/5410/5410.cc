//
// Solution for ACM-ICPC 5410 - Counterfeit Dollar
//   (North America - East Central NA Regionals 1998)
//
//     Compile : g++11 -std=c++11 -o 5410 5410.cc -Wall
//  Written by : Austin Kothig
//    Semester : SPRING 2017
//     Problem : Given a set of guesses,
//               find the counterfeit coin
//

#include <iostream>
#include <string>

using namespace std;

string guess[3][3];
const char letters[12]{ 'A','B','C','D','E','F',
      'G','H','I','J','K','L' };

bool check(char letter, string& weight)
{
   for(int i = 0; i < 3; i++)
   {
      // set these for simplicity
      string left = guess[i][0];
      string right = guess[i][1];
      string ans = guess[i][2];

      
      // if the scale is even, and
      // our coin is on either side
      // then the coin is real
      if(ans == "even")
      {
	 if( (left.find(letter) != string::npos) ||
	     (right.find(letter) != string::npos) )
	    return false;
      }

      
      // if the scale has been tipped
      // but our coin is not on either
      // side then it is real
      else
      {
	 if( (left.find(letter) == string::npos) &&
	     (right.find(letter) == string::npos) )
	    return false;
      }


      // if the coin is found on the
      // a side, that contradicts previous
      // statements return false
      if(ans == "up")
      {
	 if(left.find(letter) != string::npos)
	 {
	    if(weight == "light") return false;
	    else weight = "heavy";				     
	 }
	 
	 else if(right.find(letter) != string::npos)
	 {
	    if(weight == "heavy") return false;
	    else weight = "light";
	 }
      }
      
      if(ans == "down")
      {
	 if(left.find(letter) != string::npos)
	 {
	    if(weight == "heavy") return false;
	    else weight = "light";
	 }

	 if(right.find(letter) != string::npos)
	 {
	    if(weight == "light") return false;
	    else weight = "heavy";				     
	 }
      }  
   }

   // the coin has passed
   // all conditions and is
   // therefore found
   return true;
}



int main()
{
   // setup
   int DATASETS;
   cin >> DATASETS;
   while(DATASETS--)
   {
      for(int i = 0; i < 3; i++)
	 for(int j = 0; j < 3; j++)
	    cin >> guess[i][j];

      char letter;
      string weight;
      for(int i = 0; i < 12; i++)
      {
	 weight = "0";
	 letter = letters[i];
	 
	 // if a coin passes all test
	 // cases it is found, exit loop
	 if(check(letter, weight))
	    break;
      }

      // output
      cout << letter << " is the counterfeit coin and it is "
	   << weight << ".\n";
   }
}

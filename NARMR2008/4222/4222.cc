//
// Solution for ACM-ICPC 4222 - Dance
//   (North America - Rocky Mountain Regional 2008)
//
//     Compile : g++11 -std=c++11 -o 4222 4222.cc -Wall
//  Written by : Austin Kothig
//    Semester : SPRING 2017
//     Problem : Given a line that represents a dance routine,
//               mark it based on very specific rules.
//

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const int MAX = 1001;

bool rule1(string dance[], int n)
{
   // specail conditions of where a jiggle may occur 
   bool dip = true;
   for(int i = 0; i < n; i++)
      if(dance[i] == "dip")
      {
	 bool c1 = false, c2 = false;
	 //  i - a dip can appear 1 or 2
	 //      steps after a jiggle
	 if(i > 1)
	 { if(dance[i-1] == "jiggle" || dance[i-2] == "jiggle") c1 = true; }
	 
	 else if(i > 0)
	 { if(dance[i-1] == "jiggle") c1 = true; }	 

	 // ii - a dip appears before a twirl
	 if(i < n-2)
	 { if(dance[i+1] == "twirl") c2 = true; }
	 
	 if(!c1 && !c2)
	 {
	    dance[i] = "DIP";
	    dip = false;
	 }
      }

   return dip;
}


bool rule3(string dance[], int n)
{
   // if a dance contains a twirl,
   // it must have a hop
   bool hop = false, twirl = false;
   for(int i = 0; i < n; i++)
   {
      if(dance[i] == "twirl") twirl = true;
      if(dance[i] == "hop") hop = true;
   }

   // fancy bool return
   return !(twirl) || (twirl && hop);
}


bool rule5(string dance[], int n)
{
   // all dances must contain a dip
   bool dip = false;
   for(int i = 0; i < n; i++)
      if(dance[i] == "dip") dip = true;
   return dip;
}


int main()
{
   // setup
   string s;
   while (getline(cin, s))
   {
      bool rules[5]{false, false, false, false, false};
      string dance[MAX];
      istringstream ss(s);
      int n = -1;
      while(ss >> dance[++n]) {;}

      // (do rule 1 last)
      
      // rule 2
      if(n > 2)
      {
	 if(dance[n-3] == "clap" &&
	    dance[n-2] == "stomp" &&
	    dance[n-1] == "clap") rules[1] = true;
      }
	 
      // rule 3
      rules[2] = rule3(dance, n);
      
      // rule 4
      if(dance[0] != "jiggle") rules[3] = true;

      // rule 5
      rules[4] = rule5(dance, n);

      // rule 1
      rules[0] = rule1(dance, n);

      vector<int> wrong;      
      for(int i = 0; i < 5; i++)
	 if(!rules[i])
	    wrong.push_back(i);

      // output
      cout << "form ";
      if(wrong.size() == 0)
	 cout << "ok";

      else if(wrong.size() == 1)
	 cout << "error " << wrong[0]+1;
      
      else
      {
	 cout << "errors ";
	 if(wrong.size() == 2)
	    cout << wrong[0]+1 << " and "
		 << wrong[1]+1;

	 if(wrong.size() == 3)
	    cout << wrong[0]+1 << ", "
		 << wrong[1]+1 << " and " << wrong[2]+1;

	 if(wrong.size() == 4)
	    cout << wrong[0]+1 << ", "
		 << wrong[1]+1  << ", " << wrong[2]+1
		 << " and " << wrong[3]+1;

	 if(wrong.size() == 5)
	    cout << wrong[0]+1 << ", "
		 << wrong[1]+1  << ", " << wrong[2]+1
		 << ", " << wrong[3]+1 << " and " << wrong[4]+1;
      }

      cout << ":";
      for(int i = 0; i < n; i++)
	 cout << " " << dance[i];
      cout << endl;      
   }
}

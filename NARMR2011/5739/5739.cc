//
// Solution for ACM-ICPC 5739 - User Names
//   (North America - Rocky Mountain Regional 2011)
//
//     Compile : g++11 -std=c++11 -o 5739 5739.cc -Wall
//  Written by : Austin Kothig
//    Semester : SPRING 2017
//     Problem : Given a sequence of full names, generate
//               unique usernames for each name such that
//               its length does not go over some maximum
//

#include <iostream>
#include <sstream>
#include <string>
#include <set>

using namespace std;

int main()
{
   // setup
   int n, MAXLEN, CASE = 1;
   while(cin >> n >> MAXLEN && n && MAXLEN)
   {
      cout << "Case " << CASE++ << "\n";
      string s;
      cin.ignore();

      // set used to store unique usernames
      set<string> users;

      while(n--)
      {
	 getline(cin, s);
	 istringstream ss(s);
	 string first, last, username;

	 // store the first
	 ss >> first;

	 // only store the last name
	 // this will filter out middle names
	 while(ss >> last) {;}

	 // remove any non-alpha characters
	 // from a persons last name
	 for(string::iterator it = last.begin(); it != last.end(); it++)
	    if(!isalpha(last.at(it-last.begin())))
	    { last.erase(it); it--; }

	 // first val of a username
	 // is the first letter of
	 // of someones first name	 
	 username = tolower(first[0]);

	 // add as much last name as possible
	 // stop at maxlen or at entire lastname
	 for(int i = 0; i < MAXLEN-1 && (unsigned int) i < last.length(); i++)
	    username += tolower(last[i]);

	 // if this username already exists do work
	 if(users.find(username) != users.end())
	 {
	    int userid = 0;
	    while(true)
	    {
	       userid++;
	       string newuser = username, str = to_string(userid);
	       int len1 = newuser.length(); int len2 = str.length();

	       if(len1+len2 <= MAXLEN)
	       {
		  // add the numbers to the end
		  for(int i = 0; i < len2; i++)
		     newuser += str[i];
	       }

	       else
	       {
		  // resize the string
		  // and add the numbers
		  newuser.resize(MAXLEN);
		  for(int i = 0; i < len2; i++)
		     newuser[len1-len2+1+i] = str[i];
	       }

	       // exit if this is unique
	       if(users.find(newuser) == users.end())
		  { username = newuser; break; }
	    }
	 }
	 // insert and print
	 users.insert(username);
	 cout << username << endl;
      }
   }
}

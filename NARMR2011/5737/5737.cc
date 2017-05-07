//
// Solution for ACM-ICPC 5737 - Pills
//   (North America - Rocky Mountain Regional 2011)
//
//     Compile : g++11 -std=c++11 -o 5737 5737.cc -Wall
//  Written by : Austin Kothig
//    Semester : SPRING 2017
//     Problem : The question boils down to generating the
//               catalan numbers for some index. The reason
//               why this is a catalan number question, is
//               because catalan numbers are a way of counting
//               the number of different possible combinations
//               of a dynamically changing set, in which you
//               have at most 2 choices, or at least 1 choice
//

#include <iostream>

using namespace std;

//
// C(n+1) = (Summation for i 0->n) C(i) * C(n-i)
//  Base Case : C(0) = 1 && C(1) = 1
//
// The numbers the above function generates
/*
long long catalan[31] = {
   1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862, 16796,
   58786, 208012, 742900, 2674440, 9694845, 35357670,
   129644790, 477638700, 1767263190, 6564120420,
   24466267020, 91482563640, 343059613650, 1289904147324,
   4861946401452, 18367353072152, 69533550916004,
   263747951750360, 1002242216651368, 3814986502092304
};*/

long long catalan[31] = {1, 1};

long long catalanNum(int n)
{
   if(catalan[n] != 0) return catalan[n];
   long long cat = 0; 
   for(int i = 0; i < n; i++)
   { cat += (catalanNum(i) * catalanNum((n-1)-i)); }
   
   return catalan[n] = cat;
}

int main()
{
   int n;
   while(cin >> n && n != 0)
      cout << catalanNum(n) << "\n";
}

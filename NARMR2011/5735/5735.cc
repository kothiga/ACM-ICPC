//
// Solution for ACM-ICPC 5735 - Stock Prices
//   (North America - Rocky Mountain Regional 2011)
//
//     Compile : g++11 -std=c++11 -o 5735 5735.cc -Wall
//  Written by : Austin Kothig
//    Semester : SPRING 2017
//     Problem : Given the stock prices over n days, print
//               the k1 lowest stock prices, and the k2 highest
//               stock prices. Maintain lexicographical order
//

#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main()
{
   // setup
   int n, k1, k2, CASE = 1;
   while(cin >> n >> k1 >> k2 && n && k1 && k2)
   {
      cout << "Case " << CASE++ << "\n";
      int input;
      vector< pair<int, int> > v;
      for(int i = 1; i <= n; i++)
      {
	 cin >> input;
	 pair<int, int> a = make_pair(input, i);
	 v.push_back(a);
      }

      // sort the vector of pairs.
      // if first ties, use second
      // as a timestamp to maintain
      // appropriate order
      sort(v.begin(), v.end());

      // a - the k1 lowest vals
      // b - the k2 highest vals
      // only need to store the days
      vector<int> a, b;
      for(int i = 0; i < k1; i++)
	 a.push_back(v[i].second);
      
      for(int i = n-k2; i < n; i++)
	 b.push_back(v[i].second);

      // sort the days appropriately
      sort(a.begin(), a.end());
      sort(b.begin(), b.end(), greater<int>());

      // output
      unsigned int i;
      for(i = 0; i < a.size(); i++)
      { if(i) cout << " "; cout << a[i]; }
      cout << endl;
      
      for(i = 0; i < b.size(); i++)
      { if(i) cout << " "; cout << b[i]; }
      cout << endl;
   }
}

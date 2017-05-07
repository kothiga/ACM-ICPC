//
// Solution for ACM-ICPC 5736 - Contour Tracing
//   (North America - Rocky Mountain Regional 2011)
//
//     Compile : g++11 -std=c++11 -o 5736 5736.cc -Wall
//  Written by : Austin Kothig
//    Semester : SPRING 2017
//     Problem : Given an 'image', trace any contours, then
//               compile a list of the contours that have
//               more than 5 bits to them. Sort them and print.
//

#include <iostream>
#include <algorithm>
#include <utility>
#include <string.h>
#include <vector>

using namespace std;

const int MAX_RC = 200;
char bitM[MAX_RC][MAX_RC];
vector<int> objects;
//vector< pair<int, int> > objects;

//                  0   1   2   3   4   5   6   7
//                  W  NW   N  NE   E  SE   S  SW
const int derR[8]{  0, -1, -1, -1,  0,  1,  1,  1 };
const int derC[8]{ -1, -1,  0,  1,  1,  1,  0, -1 };


void trace(int x, int y)
{
   int d = 0;
   pair<int, int> b, b0, b1, c, c0, c1, prev, next, contour;

   // we start looking at a pixel
   contour = make_pair(0, 1);

   // store the position of the first spec
   // and the neighbor west of this position
   b0 = make_pair(x, y);
   c0 = make_pair(x+derR[d], y+derC[d]);

   // check the position below for a bit.
   // if it is found, mark it as seen and
   // incriment the bit counter. this is
   // done the way it is because of a specific
   // edge case, where the length of a contour is
   // 4, but still has 5 bits in it.
   if(bitM[b0.first+derR[6]][b0.second+derC[6]] == '1')
   {
      bitM[b0.first+derR[6]][b0.second+derC[6]] = '2';
      contour.second++;
   }

   // step 2
   for(int num = 0; num < 8; num++)
   {
      prev = c0;
      d = (d+1)%8;
      c0 = make_pair(b0.first+derR[d], b0.second+derC[d]);
	 
      if(bitM[c0.first][c0.second] == '1' || bitM[c0.first][c0.second] == '2')
      {
	 // if this has not been seen, 
	 if(bitM[c0.first][c0.second] == '1')
	 {
	    // increase bit count
	    contour.second++;
	 
	    // mark this as seen
	    bitM[c0.first][c0.second] = '2';
	 }
	 
	 b1 = c0;
	 c1 = prev;
	 d = (8+d-2)%8;
	 break;
      }
      
      // no contours around. leave.
      if(num == 7) return;
   }
      
   // step 3
   b = b1;
   c = c1;

   // append to the contour
   contour.first++;   

   // step 6
   bool breakBool = true;
   while(breakBool)
   {
      // step 4
      prev = c;
      for(int num = 0; num < 8; num++)
      {
	 next = make_pair(b.first+derR[d], b.second+derC[d]);

	 // exit condition of step 6
	 if(b == b0 && next == b1){breakBool = false; break;}
	 
	 // step 5
	 if(bitM[next.first][next.second] == '1' ||
	    bitM[next.first][next.second] == '2')
	 {
	    // increase length
	    contour.first++;

	    // if this bit has not been seen
	    // before, add it.
	    if(bitM[next.first][next.second] == '1')
	    {
	       contour.second++;

	       // mark this bit as seen
	       bitM[next.first][next.second] = '2';
	    }

	    b = next;
	    c = prev;
	    d = (8+d-2)%8;
	    break;
	 }
	    
	 prev = next;
	 d = (d+1)%8;	       
      }
   }

   // only store if the object
   // has more than 4 pixels
   if(contour.second > 4)
      objects.push_back(contour.first);
}


int main()
{
   // setup
   int R, C;
   int CASE = 1;
   while(cin >> R >> C && R != 0 && C != 0)
   {
      objects.clear();
      memset(bitM,'0', sizeof bitM);
      for(int i = 0; i < R; i++)
	 for(int j = 0; j < C; j++)
	 { cin >> bitM[i][j]; }
      
      // look for the start of a contour
      for(int i = 0; i < R; i++)
	 for(int j = 0; j < C; j++)
	 {
	    if(bitM[i][j] == '1')
	    {
	       // mark the position
	       // and trace around
	       bitM[i][j] = '2';
	       trace(i, j);
	    }
	    // increment colomn until looking at a '0'
	    if(bitM[i][j] == '2') { while(bitM[i][j] != '0') j++; }
	 }
   

      // output
      int total = 0;
      cout << "Case " << CASE++ << "\n";
      sort(objects.begin(), objects.end());
      for(unsigned int i = 0; i < objects.size(); i++)
      {
	 if(total) cout << " ";
	 cout << objects[i];
	 total++;
      }

      // this occurs if all of our
      // traced contours are too small
      // or there were no traces at all
      if(total == 0)
	 cout << "no objects found";
      
      cout << endl;
   }
}

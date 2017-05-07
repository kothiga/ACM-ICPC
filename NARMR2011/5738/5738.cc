//
// Solution for ACM-ICPC 5738 - Robot Navigation
//   (North America - Rocky Mountain Regional 2011)
//
//     Compile : g++11 -std=c++11 -o 5738 5738.cc -Wall
//  Written by : Austin Kothig
//    Semester : SPRING 2017
//     Problem : Given a map of an area, and the starting
//               position of a robot, find the number of
//               different shortest paths to get to the end
//

#include <iostream>
#include <string.h>
#include <queue>

using namespace std;

const int MAX_MN = 1005;
const int MAX_DIR = 4;
int M, N, m;

const char d[4]   { 'N', 'E', 'S', 'W'};
const int dirX[4] {  -1,   0,   1,  0 };
const int dirY[4] {   0,   1,   0, -1 };

char grid[MAX_MN][MAX_MN];
int going[MAX_MN][MAX_MN][MAX_DIR];
int came[MAX_MN][MAX_MN][MAX_DIR];

struct Node
{
   int x, y, dir;

   // first state constructor
   Node(int i, int j, int k)
   { x = i; y = j; dir = k; came[x][y][dir] = 1; going[x][y][dir] = 0;}

   // all future state constructor
   Node(int state, Node cur)
   {
      // set the things they share
      x = cur.x;
      y = cur.y;
      
      // do different things
      switch(state)
      {
	 // forward
	 case 0:
	    dir = cur.dir;
	    x += dirX[dir];
	    y += dirY[dir];  
	    break;
	    
	 // right
	 case 1:
	    dir = (cur.dir + 1) % MAX_DIR;
	    break;
	    
	 // left
	 case 2:
	    dir = (MAX_DIR + cur.dir - 1) % MAX_DIR;
	    break;
      }
   }

   bool check(Node next)
   {
      // if we have already been here before,
      // and we have taken a shorter path here
      // before, this is not a good move. Do not advance.
      if(going[next.x][next.y][next.dir] != -1 &&
	  going[next.x][next.y][next.dir] < going[x][y][dir] + 1)
	  return false;

      // if we have not been to this spot
      // we will push a new state to it
      bool unseen = (going[next.x][next.y][next.dir] == -1);

      // whether the next state has been seen before
      // or not, increase the distance needed to get
      // here. the number of paths for the next is
      // plus equals the previous from the same direction
      going[next.x][next.y][next.dir] = going[x][y][dir] + 1;
      came[next.x][next.y][next.dir] = (came[next.x][next.y][next.dir] +
					came[x][y][dir]) % m;

      return unseen;
   }
};


void setup()
{
   // init the global
   // tables
   memset(going, -1, sizeof going);
   memset(came, 0, sizeof came);

   // draw an out of
   // bounds box around
   // the input
   for(int i = 0; i <= M; i++)
      for(int j = 0; j <= N; j++)
	 if(i == 0 || j == 0 || i == M || j == N)
	    grid[i][j] = '*';
}

int main()
{
   // setup
   int CASE = 0;
   while(cin >> M >> N >> m)
   { if(m == 0) break;

      // move these one
      // off for normalizing
      M++; N++;

      for(int i = 1; i < M; i++)
	 for(int j = 1; j < N; j++)
	    cin >> grid[i][j];

      // init tables
      // and draw oob
      setup();
      
      int x1, y1, x2, y2, dir; char c;
      cin >> x1 >> y1 >> x2 >> y2 >> c;

      // normalize these
      x1++; y1++; x2++; y2++;
      
      // find pos in table
      for(int i = 0; i < MAX_DIR; i++)
	 if(d[i] == c)
	    dir = i;
      
      // bfs
      Node start(x1, y1, dir);
      queue<Node> q;
      q.push(start);

      while(!q.empty())
      {
	 // grab current
	 Node cur = q.front(); q.pop();

	 // leave after finding the first
	 // way to get to the end
	 if (cur.x == x2 && cur.y == y2) { break; }
		    
	 // make the next three states
	 Node forward(0, cur),
	        right(1, cur),
	         left(2, cur);

	 // if these are valid
	 // moves, add them to
	 // the bfs
	 if(cur.check(forward) && grid[forward.x][forward.y] != '*') q.push(forward);
	 if(cur.check(right)) q.push(right);
	 if(cur.check(left)) q.push(left);
      }

      // output
      int sum = 0;
      bool noAnswer = true;
      for(int i = 0; i < MAX_DIR; i++)
      {
	 if(going[x2][y2][i] != -1)
	 {
	    sum = (sum + came[x2][y2][i])%m;
	    noAnswer = false;
	 }
      }

      if(noAnswer) sum = -1;  
      cout << "Case " << ++CASE << ": " << m << " " << sum << "\n";
   }
}

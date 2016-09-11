
#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>  // for random seed
#include <vector>
#include <algorithm>

using namespace std;

char grid[15][15]; // the board to square up
int gridx[100];
int gridy[100];  // row, col coords for each tile on board

class Square
{
    public:
       int row; // 0..10
       int col;  // 0..10
       int cost; // equals tile count in v 0.1
};

bool square_lessthan(Square left, Square right)
       {
        return left.cost < right.cost;
        }

// blah bbbb bbbb bbbbb llll aasas hhhhh

Square all_squares[121]; // each 5x5 square

std::vector<Square> v_squares (all_squares, all_squares+121);

std::string letters  ("AAAAAAAAABBCCDDDDEEEEEEEEEEEEFFGGGHHIIIIIIIIIJKLLLLMMNNNNNNOOOOOOOO??PPQRRRRRRSSSSTTTTTTUUUUVVWWXYYZ");

int initGrid() {

   time_t seconds;
   time(&seconds);
   srand((unsigned int) seconds);


    for (int i=0; i<15; i++) {
        for (int j=0; j<15; j++) {
            grid[i][j] = '_';
    }}

    
  for (int i =0; i<100;i++) 
    {
        for (char g='.';g == '.';) 
        {
            int b = rand() % 15;
            int c = rand() % 15;
            if (grid[b][c] == '_')
            {
                g = letters[i];
                grid[b][c] = g;
               gridx[i]=b;
                gridy[i]=c;
             }
        }
    }

   return 0;
}

// version 0.1 movecost is number of moved tiles
// find set of four 5x5 blocks containing maximum number of tiles
int movecost(int a, int b, int u, int v) 
{
   if (a==u && b==v)
   {
      return 0;
   } else {
      //return 2 + max(abs(a-u), abs(b-v));
      return 1;
   }
}

int doCount() 
{
   int square_index = 0;
   for (int i=0; i<11; i++)
   {
      for (int j=0; j<11; j++)
      {
         int totalcost = 0;
         for (int k=0; k<5;k++)
         {
            for (int m=0; m<5; m++)
            {
                if (grid[i+k][j+m] !='_')
                {
                      totalcost ++; // todo: 5x speedup
                }
           }
        }
// make a square here
        Square* sq = all_squares + square_index++;

        sq->row = i;
       sq->col = j;
        sq->cost = totalcost;

// . . . . . . . . . . . . . . . m

   // cout <<  totalcost << ' ';
   }
  // cout << endl;
}
   return 0;
}

int doSort() {
    for (int count=0; count < 121; count++) {
      for (int p= 0; p< 120; p++) {
        Square squareone = all_squares[p+1];
        if (all_squares[p].cost < squareone.cost) {
           all_squares[p+1] = all_squares[p];
           all_squares[p] = squareone;
           //cout <<  squareone.cost << '!';
   }}}
}

int showGrid() {
    for (int i=0; i<15; i++)
    {
        for (int j= 0; j<15; j++)
        {
             cout << grid[i][ j ];
        }
        cout << endl;
    }
    return 0;
}

int showSorted() {

    for (int k=0; k<50; k++) {
        //Square sq = v_squares.component(k);
        Square sq = all_squares[k];
        cout << '(' <<  sq.row << ',' << sq.col << ','  << sq.cost  << ") ";
    }
   return 0;
}

bool overlap2(int p, int q) {
    return (abs(all_squares[p].row - all_squares[q].row)<5 && abs(all_squares[p].col - all_squares[q].col)<5);
}

bool overlap(int a, int b, int c, int d) {
    return overlap2(d,c) || overlap2(d,b) ||overlap2(d,a) ||overlap2(c,b) ||overlap2(c,a) ||overlap2(b,a) ;
}

int main(){

    cout<<("Squaring Tiles - 0.1 by Kevin Leeds\n");

    initGrid();  // randomize

   showGrid();

// plan
// v0.1 cost of squaring is number of tiles not in the four squares
// so maximize the tile count inside them
// i guess it can start with the four best and gradually relax and iterate exhaustively

    doCount();

   // std::sort (v_squares.begin(), v_squares.end(), square_lessthan);

   doSort();

 //  showSorted();

   // do complicated loop to search for best combination of four squares
    // simplified by the fact they don't interact to change each other's cost in v 0.1
    // tiles_limit is the max "cost" to consider (cost is perverse - todo: rename it)

 
    int a=0;
    int b=a+1;
    int c=b+1;
    int d=c+1;
    int tiles_restart=all_squares[a].cost +all_squares[b].cost + all_squares[c].cost + all_squares[d].cost;
     //cout << "hope for "+tiles_restart;

    // it starts out optimistic but it gets overlaps
    // it knows it can get tiles_restart but then they overlap
    // so it tries to find another combination without giving up its hope
    // if that doesn't work it relaxes its hope 

    while (overlap(a,b,c,d)) {
        // conditions are
        // 121>d>c>b>a
        // 
        // if tiles_inside unavoidably decreases to less than restart value, start back at 0,1,2,3
        int ta = all_squares[a].cost;
        int tb = ta + all_squares[b].cost;
        int tc = tb + all_squares[c].cost;

        // increase d if not exceed
        
        if (d<120 && tc+all_squares[d+1].cost>= tiles_restart) {
            d++;
            //cout << 'd';
         } else if (c < 119 && tb+all_squares[c+1].cost+all_squares[c+2].cost>= tiles_restart){
            c++;
            d= c+1; 
           // cout << 'c';
         } else if (b<118 && ta + all_squares[b+1].cost + all_squares[b+2].cost+all_squares[b+3].cost >= tiles_restart) {
            b++;
            c=b+1;
            d=c+1;
            //cout << 'b';
         } else if (a<117 && all_squares[a+1].cost+all_squares[a+2].cost+all_squares[a+3].cost+all_squares[a+4].cost >= tiles_restart ) {
            a++;
            b=a+1;
            c=b+1;
            d=c+1;
            //cout << 'a';
         } else {
            a=1;
            b=a+1;
            c=b+1;
            d=c+1;
            tiles_restart--;
            //cout << "Hoping for " << tiles_restart << "\n";
         }

       // cout << a << ' ' << b << ' ' << c << ' ' << d << '\n';

    }
    
   // cout << "Answer:\n";
 //  cout << "a,b,c,d=" << a << "," << b << "," << c << "," << d << "\n";
    cout << '(' << all_squares[a].row << ',' << all_squares[a].col << ") =" << all_squares[a].cost << " ";

Square* all_tiles = all_squares; // compensate for typo/goof

cout << '(' << all_tiles[b].row << ',' << all_tiles[b].col << ") =" << all_tiles[b].cost << " ";
cout << '(' << all_tiles[c].row << ',' << all_tiles[c].col << ") =" << all_tiles[d].cost << " ";
cout << '(' << all_tiles[d].row << ',' << all_tiles[d].col << ") =" << all_tiles[d].cost << " ";
    
cout << "total tiles to not move is " << all_tiles[a].cost + all_tiles[b].cost + all_tiles[c].cost + all_tiles[d].cost << ".\n";

    return 0;
}


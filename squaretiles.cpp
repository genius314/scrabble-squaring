/* version 0.2
   attempt to optimize version 0.1 just for fun of course.
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>  // for random seed
#include <vector>
#include <algorithm> // to sort using vector and algorithm got accomplished only partly

using namespace std;

char grid[15][15]; // the board to square up
size_t gridx[100];
size_t gridy[100];  // row, col coords for each tile on board

class Square
{
    // represents a 5x5 square, a sub-region of the 15x15 grid.
    public:
       size_t row; // 0..10
       size_t col;  // 0..10
       size_t tilecount;
       size_t cost;  // would be 25 - tilecount.
};

std::vector<Square> all_squares (121);  // each 5x5 square

std::string letters  ("AAAAAAAAABBCCDDDDEEEEEEEEEEEEFFGGGHHIIIIIIIIIJKLLLLMMNNNNNNOOOOOOOO??PPQRRRRRRSSSSTTTTTTUUUUVVWWXYYZ");

// Function to randomize the initial position
int initGrid() {

   time_t seconds;
   time(&seconds);
   srand((unsigned int) seconds);


    for (size_t i=0; i<15; i++) {
        for (size_t j=0; j<15; j++) {
            grid[i][j] = '_';
    }}

  for (size_t i =0; i<100;i++) 
    {
        for (char g='.';g == '.';) 
        {
            size_t b = rand() % 15;
            size_t c = rand() % 15;
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

// Function to inefficiently determine the cost, given it's the indicator cost function, of moving tiles into any given square
int doCount() 
{
    size_t square_index = 0;
    for (size_t i=0; i<11; i++)
    {
        for (size_t j=0; j<11; j++)
        {
           size_t tcount = 0;
           for (size_t k=0; k<5;k++)
           {
              for (size_t m=0; m<5; m++)
              {
                  if (grid[i+k][j+m] !='_')
                  {
                      tcount ++; // todo: 5x speedup
                  }
              }
           }

	// Set up the square in the vector of squares
           //all_squares[square_index];
           all_squares[square_index].row = i;
           all_squares[square_index].col = j;
           all_squares[square_index].tilecount = tcount;
           all_squares[square_index].cost = 25 - tcount;

           //cout <<  "Counted " << i << ',' << j << ' ' << tcount << "\n";

           square_index++;
       }
    }
    
    return 0;
}

// This uses bubble sort so the list of 5x5 squares is ordered from lowest cost to highest cost.
// todo: i think a better bubble sort might move the bubble more than 1 spot at a time.
int doBubbleSort() {
  for (size_t count=0; count < 121; count++) {
    for (size_t p= 0; p< 120; p++) {
      Square low_cost_square = all_squares[p+1];
      if (all_squares[p].cost < low_cost_square.cost) {
         all_squares[p+1] = all_squares[p];
         all_squares[p] = low_cost_square;
         //cout <<  squareone.cost << '!';
      }
    }
  }
}


bool square_compare(Square sq1, Square sq2) {
    return (sq1.cost < sq2.cost);
}


int doSort() {
   std::sort(all_squares.begin(), all_squares.end(), square_compare);
}


int showGrid() {
    for (size_t i=0; i<15; i++)
    {
        for (size_t j= 0; j<15; j++)
        {
             cout << grid[i][ j ];
        }
        cout << endl;
    }
    return 0;
}

int showSorted() {

    for (size_t k=0; k<121; k++) {
        Square sq = all_squares[k];
        cout << "square i,j,cost: (" <<  sq.row << ',' << sq.col << ','  << sq.cost  << ")" << endl;
    }
   return 0;
}

size_t absval(size_t a) {
	return (a >= 0 ? a : a);
}

// Does square p overlap square q? (referring to the global all_squares array)
bool overlap2(size_t p, size_t q) {
    return (absval(all_squares[p].row - all_squares[q].row)<5 && absval(all_squares[p].col - all_squares[q].col)<5);
}

// Do any of the four squares a, b, c, d overlap?  (Variables changed more often in the iteration are checked before others)
bool overlap(size_t a, size_t b, size_t c, size_t d) {
    return overlap2(d,c) || overlap2(d,b) ||overlap2(d,a) ||overlap2(c,b) ||overlap2(c,a) ||overlap2(b,a) ;
}

int doSolution() {


    size_t a=0;
    size_t b=a+1;
    size_t c=b+1;
    size_t d=c+1;   // start optimistically with the four best squares, but likely they will overlap 
    size_t tiles_restart = all_squares[a].cost +all_squares[b].cost + all_squares[c].cost + all_squares[d].cost;
     //cout << "hope for "+tiles_restart;

    // it starts out optimistic but it gets overlaps
    // it knows it can get tiles_restart but then they overlap
    // so it tries to find another combination without giving up its hope (or a target)
    // if that doesn't work it relaxes its hope 

    while (overlap(a,b,c,d)) {
        // conditions are
        // 121>d>c>b>a
        // 
        // if tiles_inside unavoidably decreases to less than restart value, start back at 0,1,2,3
        // note 'cost' is actually the tile count, not the cost of moving, so try to maximize it without overlapping here
        size_t ta = all_squares[a].cost;
        size_t tb = ta + all_squares[b].cost;
        size_t tc = tb + all_squares[c].cost;

        // increase d if not exceed
        // this is a 4-nested loop, for upper triangle, a<b<c<d, d ranges from c+1 to end of array, but 
        //   if we notice we are outside the target then iterate an earlier variable instead.  this is
        //   inefficient but it does work fast enough to enjoy the output
        
        if (d<120 && tc+all_squares[d+1].cost <= tiles_restart) {
            d++;
            cout << 'd';
         } else if (c < 119 && tb+all_squares[c+1].cost+all_squares[c+2].cost <= tiles_restart){
            c++;
            d= c+1; 
            cout << 'c';
         } else if (b<118 && ta + all_squares[b+1].cost + all_squares[b+2].cost+all_squares[b+3].cost <= tiles_restart) {
            b++;
            c=b+1;
            d=c+1;
            cout << 'b';
         } else if (a<117 && all_squares[a+1].cost+all_squares[a+2].cost+all_squares[a+3].cost+all_squares[a+4].cost <= tiles_restart ) {
            a++;
            b=a+1;
            c=b+1;
            d=c+1;
            cout << 'a';
         } else {
            a=1;
            b=a+1;
            c=b+1;
            d=c+1;
            tiles_restart++;
            cout << "\nHoping for " << tiles_restart << "\n";
         }

        //cout << a << ' ' << b << ' ' << c << ' ' << d << '\n';

    }
    
    cout << "\nAnswer:\n";
    //  cout << "a,b,c,d=" << a << "," << b << "," << c << "," << d << "\n";
    cout << '(' << all_squares[a].row << ',' << all_squares[a].col << ") =" << all_squares[a].cost << " ";

    cout << '(' << all_squares[b].row << ',' << all_squares[b].col << ") =" << all_squares[b].cost << " ";
    cout << '(' << all_squares[c].row << ',' << all_squares[c].col << ") =" << all_squares[d].cost << " ";
    cout << '(' << all_squares[d].row << ',' << all_squares[d].col << ") =" << all_squares[d].cost << " ";
    
    cout << "total tiles to move is " << all_squares[a].cost + all_squares[b].cost + all_squares[c].cost + all_squares[d].cost << ".\n";
}



int main(){

    cout<<("Squaring Tiles - 0.1 by Kevin Leeds\n"); // Egotizing

    initGrid();  // randomize

    showGrid();

// 
// v0.1 cost of squaring is number of tiles not in the four squares, so maximize the tile count inside them
// Work with a list all the possible 5x5 squares, sorted from lowest cost to highest
// Inspect all combinations of four of those.  Iterate to gradually increase the sum of the four costs ...
//    Don't look at higher cost solutions til various combinations have been inspected
//    That cutoff quantity is called "tiles_restart" in the program.
//    Then all that has to be done is locate a set that does not have overlaps - the first one encountered will be the best answer.

// If the cost function is more complicated then the search will not be so simple, 
//   because the location of each region will affect the cost amount of itself and the other ones too.

   doCount();

   //showSorted();

   //cout << " - - - - -- - - - -- \n";

   doSort();

   showSorted();

   // do complicated loop to search for best combination of four squares
    // simplified by the fact they don't interact to change each other's cost in v 0.1
    // tiles_limit is the max "cost" to consider (cost is perverse - todo: rename it)

    // todo: improve the iteration so it does not re-do all the work each time the target is relaxed
    // and also make it more readable I hope, maybe by abstracting the iterator or pre-computing somehow.
 
   doSolution();

    return 0;
}

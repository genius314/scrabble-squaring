
# scrabble-squaring
Solving an important problem for Scrabble players, to optimize re-checking that all 100 tiles are there

Given:

The input to the problem is a [0..14]x[0..14] array B with a standard set of English language Scrabble tiles S on it.

The standard set of Scrabble tiles is something like this
S = {t1 = A,A,AAAA,AAABBCCDDDDEEEEEEEEEEEEFFGGGHHIIIIIIIIIJKLLLLMMNNNNNNOOOOOOOOPPQRRRRRRSSSSTTTTTTUUVVWWXYY,Z,?, t100=?}

I = a one-to-one function with domain S and range B so now the 100 tiles are on the 15x15 grid.

There is a cost function C defined, to give the cost of moving a tile from one spot on the array to another.
C(B,B) => nonnegative real numbers
In the initial version this is simply the indicator function, 1 if the two spots are different or 0 otherwise.

Problem:
Find the set of four 5x5 square sub-arrays of B, (called Q1, Q2, Q3, Q4),
and a "movement" function J that moves each tile t from S(t) to J(s(t)),
such that 
1) Q1,Q2,Q3,Q4 don't overlap (have null intersection pairwise)
2) J moves the tiles so all of them end up in the squares, e.g. the union J(I(S)) is equal to the union of the Q sets
3) The total cost (sum the cost function applied to J movements over 100 tiles) is minimized


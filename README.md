
# word-game-squaring

An important problem for avid players of word games like Scrabble:

To optimize re-checking that all 100 tiles are there.

Here is the problem, in mathematical form (with not very good math notation)

1. Define E={1, 2, ... 15} and B = E×E will represent the board. (In the program this is 0..14 instead.)

2. Let S be a standard set of one hundred word game tiles represented by a sequence of characters:

> S = {s(1) = 'A', ... s(9) = 'A', s(10)='B', s(11)='B', .... s(98)='Z',S(99)='?',s(100)='?'}

for the tiles that are found in the word game's tile set ('?' denotes a blank tile).

3. Let I, the initial position, be a one-to-one function with domain S and range B so now the 100 tiles are located on the 15x15 grid.

4. There is a cost function C defined, to give the cost of moving a tile from one spot on the array to another.
C(B,B) => nonnegative real numbers

In the initial version of the program, C is simply the indicator function, where C(b1, b2) = 0 if b1=b2, or C(b1,b2) = 1 if b1≠b2.  In this simple case the code is written with this as the assumption so the function is not referenced.


Problem:  Move the 100 tiles into four squares that are 5x5 on the board.

Find a set of four 5×5 square sub-arrays of B, called Q1, Q2, Q3, Q4, with union Q,

and a one-to-one function J: I(S) ↦ B  to represent how the tiles are moved from the initial position I to the final position, with the following properties

1) Q1,Q2,Q3,Q4 don't overlap (have null intersection pairwise)

2) J(I(S)) = Q

3) The total cost (sum the cost function applied to J) is minimized, e.g. there doesn't exist any  one-to-one function J': I(s) -> Q satisfying condition 2 such that

> sum C( I(s), J'(I(s)) ) < sum C( I(s), J(I(s)) )



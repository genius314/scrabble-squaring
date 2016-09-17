
# word-game-squaring

An important problem for avid players of word games like Scrabble: To optimize re-checking that all 100 tiles are there.

There is a board with 15 by 15 points (squares, or places) for placing a tile, and a set of 100 distinct tiles that fit into the squares. Each tile has a letter on it or a blank, and initially assume each tile is placed on a square on the board. Then the problem is to find four nonoverlapping subsets of the board, each measuring 5 squares by 5, and manually transfer the tiles from square to square, so all tiles will be located within the 5 by 5 subsets. This must be done as economically as possible!

Mathematically,

1. Define E = {1, 2, ... 15} and B = E×E will represent the board. For example (3,12) is a square on the board different from (12,3).

2. Let S be a standard set of one hundred word game tiles represented by a sequence of characters for the tiles that are found in the word game's tile set ('?' denotes a blank tile)
> S = {s(1) = 'A', ... s(9) = 'A', s(10)='B', s(11)='B', .... s(98)='Z',S(99)='?',s(100)='?'}

3. Let I, the initial position, be a one-to-one function with domain S and range equal to a subset of B so now the 100 tiles are located on the 15x15 grid. 

4. There is a cost function C defined, to give the cost of moving a tile from one spot on the array to another.
C(B,B) => nonnegative real numbers

Then the goal is to find a function J and a region Q as described here:

1) The destinations: Four 5x5 square regions on the board, denoted Q1,Q2,Q3,Q4 with union Q, which don't overlap. ("Don't overlap" means they have null intersection pairwise.  If Qi, Qj are any two different regions selected from these four regions, then Qi intersect Qj is the null set.)

2) The movements: A function describing how tiles are moved from initial board locations to their destinations inside the four regions. This can be a function J, with domain and range being subsets of the board B, with domain equal to I(S) and range equal to Q.

3) Minimization: The total cost (sum the cost function applied to J) is minimized, e.g. there doesn't exist any better destination Q', or any better one-to-one function J': I(s) -> Q satisfying condition 2 that achieves a lower cost than J:

> sum C( I(s), J'(I(s)) ) <= sum C( I(s), J(I(s)) )  must be satisfied for any other J',Q' besides J,Q itself

Notes:

The problem may be extended to deal with tiles that are rotated or flipped upside down.

The cost function might have, for example, C((3,12), (12,3)) = 1 because these are two different spots on the board, and C((4,5), (4,5)) = 0 because the tile is not moved anywhere to get from the initial to the final location.  Or C((3,12), (12,3)) = the square root of (9 squared plus 9 squared) because that is the Euclidean distance between the locations on the board (but I think it is not very realistic).  

To estimate the time I think it would have the form C(s1, s2) = k1 + k2 d(s1, s2), where s1 and s2 are two different squares, k1 is a constant to represent the time spent to pick up a tile and put it down, k2 is the average speed of moving the tile manually, and d is a distance function that might consider some vertical movement when a tile is lifted and placed down.

In modeling the time of manual movement, I think it would be too complicated to include a factor like the visual complexity of the layout, or the interference of surrounding tiles when attempting to place a tile, etc.  although this could change if the stakes are very high - for example, it could be the World Championship of Programmatic Word Game Board Squaring, hypothetically.

(At this time I would like to mention that this feature would be extremely entertaining to include into Quackle.)

In the initial version of the program, C is simply the indicator function, where C(b1, b2) = 0 if b1=b2, or C(b1,b2) = 1 if b1≠b2.  In early versions of the .cpp program, the optimization code is written with this as the assumption so the function is not referenced.





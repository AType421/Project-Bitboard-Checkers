# Project-Bitboard-Checkers

## Author
Aaron Gamino

## Description 
A bitboard-based checkers game that demonstrates bit manipulation techniques

## Build Instructions

For the bit operations in phase 1
‘‘‘
bash
gcc -o convert phase1 phase1.c
./phase1
‘‘‘

For the checkers game
‘‘‘
bash
gcc -o convert checkers bitboard.c
./checkers
‘‘‘

## Game instructions
To move a checkers piece, type in the index of the piece you want to move and then type in the index of the destination you want to move that piece 

    +---------------------------------------------------+
 8  | 56 57 58 59 60 61 62 63 |
 7  | 48 49 50 51 52 53 54 55 |
 6  | 40 41 42 43 44 45 46 47 |
 5  | 32 33 34 35 36 37 38 39 |
 4  | 24 25 26 27 28 29 30 31 |
 3  | 16 17 18 19 20 21 22 23 |
 2  | 08 09 10 11 12 13 14 15 |
 1  | 00 01 02 03 04 05 06 07 |
    +---------------------------------------------------+
       a  b  c  d  e  f  g  h
^^This is a reference of what index the pieces will be

    +---------------------------------+
 8  | . b . b . b . b |
 7  | b . b . b . b . |
 6  | . b . b . b . b |
 5  | . . . . . . . . |
 4  | . . . . . . . . |
 3  | r . r . r . r . |
 2  | . r . r . r . r |
 1  | r . r . r . r . |
    +---------------------------------+
      a b c d e f g h

^^This is the actual board

For example to move the red piece at row 3 and col A to row 4 and col B you would type in
"16 25"

To capture a piece simply type the the source index of your piece and the destination index of what the piece would land if it captures a piece

to quit type q or Q


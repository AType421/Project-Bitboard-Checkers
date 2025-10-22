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

<img width="686" height="290" alt="image" src="https://github.com/user-attachments/assets/10a250c3-b6e1-484a-9df4-d4fc96ef5beb" />

^^This is a reference of what index the pieces will be

<img width="493" height="236" alt="image" src="https://github.com/user-attachments/assets/9aa6f8fa-3d2d-4388-9f80-4fcf918bcd8f" />


^^This is the actual board

For example to move the red piece at row 3 and col A to row 4 and col B you would type in
"16 25"

To capture a piece simply type the the source index of your piece and the destination index of what the piece would land if it captures a piece

to quit type q or Q


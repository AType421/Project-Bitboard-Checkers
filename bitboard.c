
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef uint64_t U64;

typedef struct {
    U64 red, red_k;
    U64 black, black_k;
    int turn; // 0 for red's turn and 1 for black's
} GameState;

static inline U64 SetBit64(U64 v, int pos)    { return v |  ((U64)1 << pos); }
static inline U64 ClearBit64(U64 v, int pos)  { return v & ~((U64)1 << pos); }
static inline int GetBit64(U64 v, int pos)    { return (v >> pos) & 1ULL; }
static inline int CountBits64(U64 v)          { int c=0; while(v){c+=v&1; v>>=1;} return c; }
static inline int in_bounds(int r,int f)      { return r>=0&&r<8&&f>=0&&f<8; }
static inline int rf_to_pos(int r,int f)      { return r*8+f; }

// Initalizes the board
void init_game(GameState* g){
    g->red = g->red_k = g->black = g->black_k = 0;
    g->turn = 0; // red starts
    for (int r=0;r<3;r++){
        for (int f=0;f<8;f++){
            if ((r+f)%2==1){
            g->black = SetBit64(g->black, (7-r)*8+f); 
            }
        }
    }
    for (int r=5;r<8;r++){
        for (int f=0;f<8;f++){
            if ((r+f)%2==1){
            g->red = SetBit64(g->red, (7-r)*8+f); 
            }
        }
    }
}

int is_occupied(const GameState*g, int p){
    return GetBit64(g->red,p)||GetBit64(g->black, p)
    ||GetBit64(g->red_k,p)||GetBit64(g->black_k,p);
}
int is_red_piece(const GameState*g,int p){
    return GetBit64(g->red,p)||GetBit64(g->red_k,p);
}
int is_black_piece(const GameState*g,int p){
    return GetBit64(g->black,p)||GetBit64(g->black_k,p);
}
int is_red_king(const GameState*g,int p){ return GetBit64(g->red_k,p); }
int is_black_king(const GameState*g,int p){ return GetBit64(g->black_k,p); }

void print_board(const GameState*g){
    printf("\n    +---------------------------------+\n");
    for (int r=7;r>=0;--r){
        printf(" %d  |", r+1);
        for(int f=0;f<8;++f){
            int sq=r*8+f;
            char c='.';
            if(GetBit64(g->red_k,sq))c='R';
            else if(GetBit64(g->red,sq))c='r';
            else if(GetBit64(g->black_k,sq))c='B';
            else if(GetBit64(g->black,sq))c='b';
            printf(" %c",c);
        }
        printf(" |\n");
    }
    printf("    +---------------------------------+\n");
    printf("      a b c d e f g h\n\n");
}

//Prints out a reference board to better visualize the square's indexes
void print_reference_board(void){
    printf("\n=== Bitboard Square Index Reference ===\n");
    printf("Each cell shows its square index (0-63):\n\n");

    printf("    +---------------------------------------------------+\n");
    for (int r = 7; r >= 0; --r) {
        printf(" %d  |", r + 1);
        for (int f = 0; f < 8; ++f) {
            int sq = r * 8 + f;
            printf(" %02d", sq);
        }
        printf(" |\n");
    }
    printf("    +---------------------------------------------------+\n");
    printf("       a  b  c  d  e  f  g  h\n");
    printf("\n========================================\n\n");
}

/* Game logic*/

//Checks to see if the pieces reach the end of the board
void apply_promotion(GameState*g){
    for(int pos=0; pos<64;++pos){
        int r=pos/8;
        if(r==7&&GetBit64(g->red,pos)){
            g->red=ClearBit64(g->red,pos);
            g->red_k=SetBit64(g->red_k,pos);
        }
        if(r==0&&GetBit64(g->black,pos)){
            g->black=ClearBit64(g->black,pos);
            g->black_k=SetBit64(g->black_k,pos);
        }
    }
}

int detect_winner(const GameState*g){
    int red=CountBits64(g->red)+CountBits64(g->red_k);
    int black=CountBits64(g->black)+CountBits64(g->black_k);
    if(!red) return 2; //Black wins 
    if(!black) return 1; //red wins 
    return 0;
}

//attempts to make the pieces move
int apply_move(GameState *g, int src, int dst) {
    if (!in_bounds(src/8, src%8) || !in_bounds(dst/8, dst%8)) return 0;
    if (!is_occupied(g, src) || is_occupied(g, dst)) return 0;

    int red_turn = (g->turn == 0);
    int is_red = is_red_piece(g, src);
    if (red_turn && !is_red) return 0;
    if (!red_turn && is_red) return 0;

    int sr = src / 8, sf = src % 8, dr = dst / 8, df = dst % 8;
    int drow = dr - sr, dcol = df - sf;
    int king = (is_red ? is_red_king(g, src) : is_black_king(g, src));

    // Simple move
    if (abs(drow) == 1 && abs(dcol) == 1) {
        if (!king) {
            if (is_red && drow < 0) return 0;
            if (!is_red && drow > 0) return 0;
        }

        if (is_red) {
            if (king) {
                g->red_k = ClearBit64(g->red_k, src);
                g->red_k = SetBit64(g->red_k, dst);   // set king dest
            } else {
                g->red = ClearBit64(g->red, src);
                g->red = SetBit64(g->red, dst);      
            }
        } else {
            if (king) {
                g->black_k = ClearBit64(g->black_k, src);
                g->black_k = SetBit64(g->black_k, dst); // set king dest
            } else {
                g->black = ClearBit64(g->black, src);
                g->black = SetBit64(g->black, dst);     
            }
        }
        return 1;
    }

    // Capture 
    if (abs(drow) == 2 && abs(dcol) == 2) {
        int mr = sr + drow / 2, mf = sf + dcol / 2, mid = rf_to_pos(mr, mf);
        if (!is_occupied(g, mid)) return 0;
        if (is_red_piece(g, mid) == is_red_piece(g, src)) return 0;

        if (is_red) {
            if (king) {
                g->red_k = ClearBit64(g->red_k, src);
                g->red_k = SetBit64(g->red_k, dst);   
            } else {
                g->red = ClearBit64(g->red, src);
                g->red = SetBit64(g->red, dst);       
            }
            // remove captured black piece
            if (is_black_king(g, mid)) g->black_k = ClearBit64(g->black_k, mid);
            else g->black = ClearBit64(g->black, mid);
        } else {
            if (king) {
                g->black_k = ClearBit64(g->black_k, src);
                g->black_k = SetBit64(g->black_k, dst); 
            } else {
                g->black = ClearBit64(g->black, src);
                g->black = SetBit64(g->black, dst);     
            }
            // remove captured red piece
            if (is_red_king(g, mid)) g->red_k = ClearBit64(g->red_k, mid);
            else g->red = ClearBit64(g->red, mid);
        }
        return 2;
    }

    return 0;
}


//Main game loop

int main(void){
    GameState g; init_game(&g);
    printf("Bitboard Checkers Game\n");
    while(1){
        print_reference_board();
        print_board(&g);

        int w=detect_winner(&g);
        if(w==1){printf("Red wins!\n");break;}
        if(w==2){printf("Black wins!\n");break;}

        printf("%s move (src dst): ",g.turn==0?"Red":"Black");

        char input[100];
        if (!fgets(input, sizeof(input), stdin)) {
            continue; // handle EOF or error
        }
        input[strcspn(input, "\n")] =0;

        if (strcmp(input, "q") == 0 || strcmp(input, "Q") == 0){
            break;
        }

        int s,d;
        if(sscanf(input, "%d %d",&s,&d)!=2){
            printf("Make sure to type (src dst) or q to quit.\n");
            continue;
        }
        
        if(apply_move(&g,s,d)){
            apply_promotion(&g);
            g.turn=1-g.turn;
        }else printf("Illegal move!\n");
    }
    return 0;
}




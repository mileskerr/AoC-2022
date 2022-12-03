#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


int points(char my_move, char opp_move) {
    char result = (my_move - opp_move + 3) % 3; //0 = tie, 1 = win, 2 = loss

    char points = my_move + 1; //rock = 1, paper = 2, scissors = 3
    switch ( result ) {
        case 0: 
            points += 3;
            break;
        case 1:
            points += 6;
            break;
    }

    return points;
}

int main() {

    FILE * fp = fopen("input", "r");
   
    int total = 0;
   
    char my_move;
    char opp_move;
    int line = 0;
    while (1) {
        opp_move = fgetc(fp)-65;
        if (feof(fp)) {break;}
        fgetc(fp);
        my_move = fgetc(fp)-88;
        fgetc(fp);
        
        total += points(my_move, opp_move);
    }

    fclose(fp);

    printf("%d\n",total);
}



#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


int points(char result, char opp_move) {

    char ofs;

    switch ( result ) {
        case 0: //loss
            ofs = 2;
            break;
        case 1: //tie
            ofs = 0;
            break;
        case 2: //win
            ofs = 1;
    }

    char my_move = ( opp_move + ofs ) % 3;

    char points = (my_move + 1) + (result * 3);

    return points;
}

int main() {

    FILE * fp = fopen("input", "r");
   
    int total = 0;
   
    char result;
    char opp_move;
    int line = 0;
    while (1) {
        opp_move = fgetc(fp)-65;
        if (feof(fp)) {break;}
        fgetc(fp);
        result = fgetc(fp)-88;
        fgetc(fp);
        
        total += points(result, opp_move);
    }

    fclose(fp);

    printf("%d\n",total);
}



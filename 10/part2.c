#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int readword(char * buf, FILE * fp) {
    char ch;
    do {
        ch = fgetc(fp);
        if (ch == EOF) return 0;
    } while (122 < ch || ch < 97);

    int i = 0;
    do {
        buf[i] = ch;
        ch = fgetc(fp);
        if (ch == EOF) return 0;
        i++;
    } while (96 < ch && ch < 123);
    
    buf[i] = 0;
}

int readint(FILE * fp) {
    char ch;
    do {
        ch = fgetc(fp);
    } while ((57 < ch || ch < 48) && ch != 45);

    char buf[10];
    int i = 0;
    do {
        buf[i] = ch;
        ch = fgetc(fp);
        i++;
    } while (47 < ch && ch < 58);
    
    buf[i] = 0;


    return atoi(buf);
}
    
int main() {
    FILE * fp = fopen("input","r");

    char buf[10];

    int cycle, addx, x, delay, sum;
    addx = cycle = delay = sum = 0;
    x = 1;

    while (1) {
        cycle++;
        if (delay) {
            delay--;
        } else {
            x += addx;
            addx = 0;
            if (!readword(buf, fp)) break;
            if (!strcmp(buf,"addx")) {
                delay = 1;
                addx = readint(fp);
                //printf("%d, ",addx);
            }
        }
        int pixelx = (cycle-1) % 40;
        if (pixelx >= x-1 && pixelx <= x+1) {
            printf("#");
        } else {
            printf(".");
        }
        if (pixelx == 39) printf("\n");
    }

}


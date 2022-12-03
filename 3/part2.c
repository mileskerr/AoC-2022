#include <stdio.h>
#include <stdlib.h>

int priority(char item) {
    if (96 < item && item < 123) { //lowercase
        return item - 96;
    }
    if (64 < item && item < 91) { //uppercase
        return item - 64 + 26;
    }
    return 0;
}


int main() {

    FILE * fp = fopen("input", "r");

    char ch;

    int line = 0;

    int total = 0;

    char items[3][60];

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 60; j++) {
            items[i][j] = 0;
        }
    }
    printf("hello\n");

    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\n') {
            if (line == 2) { //end of group
                line = 0; 
                for (int i = 0; i < 60; i++) {
                    if (items[0][i] && items[1][i] && items[2][i]) {
                        total += priority(i + 64);
                    }
                }
                for (int i = 0; i < 3; i++) { //clear items
                    for (int j = 0; j < 60; j++) {
                        items[i][j] = 0;
                    }
                }
            } else { line++; }
        } else {
            items[line][ch - 64] = 1;
        }
    }

    fclose(fp);

    printf("%d\n",total);

    return 0;
}

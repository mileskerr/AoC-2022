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

    char line[64];
    int col = 0;

    int total = 0;

    char first_comp_items[58];

    while ((ch = fgetc(fp)) != EOF) {
        if (ch != '\n') {
            line[col] = ch;
            col++;
        } else {
            for (int i = 0; i < 58; i ++) { //clear array
                first_comp_items[i] = 0;
            }
            for (int i = 0; i < ((col-1) / 2)+1; i++) {
                first_comp_items[line[i] - 65] = 1;
            }
            for (int i = ((col-1) / 2)+1; i < col; i++) {
                if (first_comp_items[line[i] - 65]) {
                    total += priority(line[i]);
                    break;
                }
            }
            col = 0;
        }
    }

    fclose(fp);

    printf("%d\n",total);

    return 0;
}

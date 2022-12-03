#include <stdio.h>
#include <stdlib.h>

int main() {

    char * filename = "input";
    FILE * fp = fopen(filename, "r");

    if (fp == NULL) {
        fprintf( stderr, "failed to read file\n" );
        return 1;
    }
  
    char str_val[10];
    int i = 0, total = 0, largest = 0;

    char ch;
    while ((ch = fgetc(fp)) != EOF) {
        if (ch != '\n') {
            str_val[i] = ch;
            i++;
        } else {
            if (i) {
                //first newline
                str_val[i] = '\0';
                i = 0;
                total += atoi(str_val);
            } else {
                //second newline
                if ( total > largest ) { largest = total; }
                i = total = 0;
            }
        }
    }

    fclose(fp);

    printf("%d\n",largest);

    return 0;
}

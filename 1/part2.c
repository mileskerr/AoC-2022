#include <stdio.h>
#include <stdlib.h>

const int LEN = 3;


int main() {

    char * filename = "input";
    FILE * fp = fopen(filename, "r");

    if (fp == NULL) {
        fprintf( stderr, "failed to read file\n" );
        return 1;
    }
  
    char str_val[10];
    int i = 0, total = 0;
    int largest[LEN];
    for (int i = 0; i < LEN; i++) { largest[i] = 0; }

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
                for (int i = 0; i < LEN; i++) {
                    if ( total > largest[i] ) { 
                        for (int j = LEN-1; j > i; j--) { //shift rest of ranking down
                            largest[j] = largest[j - 1];
                        }
                        largest[i] = total;
                        break;
                    }
                }

                i = total = 0;
            }
        }
    }

    fclose(fp);

    int result = 0;
    for (int i = 0; i < LEN; i++) {
        printf("%d ",largest[i]);
        result += largest[i];
    }

    printf("%d\n",result);

    return 0;
}

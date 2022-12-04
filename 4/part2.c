#include <stdio.h>
#include <stdlib.h>


int is_overlapping( int bounds[4] ) {
    return !((bounds[1] < bounds[2]) || bounds[0] > bounds[3]);
}

int main() {

    FILE * fp = fopen("input", "r");

    char ch;

    int bounds[4];
    
    char buf[3];

    int buf_ind = 0;
    int bound_ind = 0;

    int count = 0;

    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\n') {

            bounds[bound_ind] = atoi(buf);
            buf_ind = bound_ind = 0;
            for (int i = 0; i < 3; i++) { buf[i] = '\0'; }

            //printf("%d-%d,%d-%d -- %d\n", bounds[0], bounds[1], bounds[2], bounds[3], is_containing(bounds));
            count += is_overlapping(bounds);

        } if (ch == ',' || ch == '-') {

            bounds[bound_ind] = atoi(buf);
            buf_ind = 0;
            for (int i = 0; i < 3; i++) { buf[i] = '\0'; }

            bound_ind++;
        } else {
            buf[buf_ind] = ch;
            buf_ind++;
        }
    }

    fclose(fp);

    printf("%d\n",count);
    //printf("%d\n",is_containing( (int []) {2, 4, 1, 5} ));
    //printf("%d\n",is_containing( (int []) {1, 6, 2, 3} ));

    return 0;
}

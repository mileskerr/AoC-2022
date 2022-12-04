#include <stdio.h>
#include <stdlib.h>


int is_containing( int bounds[4] ) {
    return ( (bounds[0] <= bounds[2]) && (bounds[1] >= bounds[3]) ) || ( (bounds[2] <= bounds[0]) && (bounds[3] >= bounds[1]) );
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
            count += is_containing(bounds);

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

    return 0;
}

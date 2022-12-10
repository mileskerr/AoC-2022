#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} v2;

v2 v2new(int x,int y) {
    v2 new;
    new.x = x;
    new.y = y;
    return new;
}
v2 v2add(v2 a, v2 b) {
    v2 res;
    res.x = a.x + b.x;
    res.y = a.y + b.y;
    return res;
}
v2 v2sub(v2 a, v2 b) {
    v2 res;
    res.x = b.x - a.x;
    res.y = b.y - a.y;
    return res;
}
v2 v2mul(v2 a, int b) {
    v2 res;
    res.x = a.x * b;
    res.y = a.y * b;
    return res;
}
int v2eq(v2 a, v2 b) {
    return (a.x == b.x && a.y == b.y);
}

int readword(char * buf, FILE * fp) {
    char ch;
    do {
        ch = fgetc(fp);
        if (ch == EOF) return 0;
    } while (ch == '\n' || ch == ' ' || ch == '\t');

    int i = 0;
    do {
        buf[i] = ch;
        ch = fgetc(fp);
        if (ch == EOF) return 0;
        i++;
    } while (!(ch == '\n' || ch == ' ' || ch == '\t'));
    
    buf[i] = 0;
}
    

int main() {
    FILE * fp = fopen("input","r");

    char buf[4];

    v2 visited[20000];
    int vi = 0;

    v2 head = v2new(0,0);
    v2 tail = v2new(0,0);

    while (1) {
        if (!readword(buf,fp)) break;
        v2 dir = v2new(0,0);

        switch (buf[0]) {
            case 'U':
                dir = v2new(0,1);
                break;
            case 'D':
                dir = v2new(0,-1);
                break;
            case 'L':
                dir = v2new(-1,0);
                break;
            case 'R':
                dir = v2new(1,0);
                break;
        }
        
        if (!readword(buf,fp)) break;
        int dist = atoi(buf);

        for (int i = 0; i<dist; i++) {
            head = v2add(head,dir);
            v2 diff = v2sub(tail,head);
            if (diff.x > 1 || diff.x < -1) {
                tail = v2add(tail,v2new(diff.x / 2, diff.y));
            }
            if (diff.y > 1 || diff.y < -1) {
                tail = v2add(tail,v2new(diff.x, diff.y / 2));
            }
            
            //check visited location
            printf("x: %d y: %d -- x: %d y: %d\n", head.x, head.y, tail.x, tail.y);
            for (int i = 0; i < vi; i++) {
                if (v2eq(visited[i], tail)) {
                    goto repeat;
                }
            }
            visited[vi].x = tail.x;
            visited[vi].y = tail.y;
            vi++;
            printf("%d\n",vi);
repeat:
        }

    }




}



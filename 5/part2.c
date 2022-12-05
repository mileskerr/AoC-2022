#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char item;
    struct Node * next;
};

typedef struct {
    struct Node * head;
}List;

void push(List * list, char item) {
    struct Node * head = list->head;
    list->head = malloc(sizeof(struct Node));
    list->head->item = item;
    list->head->next = head;
}
char pop(List * list) {
    char item = list->head->item;
    struct Node * next = list->head->next;
    free(list->head);
    list->head = next;
    return item;
}
List list_init() {
    List new;
    new.head = NULL;
    return new;
}
void list_print(List * list) {
    struct Node * node = list->head;
    while ( node != NULL ) {
        printf("%c ",node->item);
        node = node->next;
    }
    printf("\n");
}

int main() {
    char * start[] = {
        "BSVZGPW",
        "JVBCZF",
        "VLMHNZDC",
        "LDMZPFJB",
        "VFCGJBQH",
        "GFQTSLB",
        "LGCZV",
        "NLG",
        "JFHC"
    };
    List stacks[9];
    for (int i = 0; i < 9; i++) {
        stacks[i] = list_init();
        int j = 0;
        while ( start[i][j] != '\0' ) {
            push(&stacks[i], start[i][j]);
            j++;
        }
    }

    int args[3];

    char ch;
    char buf[3];

    int buf_ind = 0;
    int arg_ind = 0;

    FILE * fp = fopen("input", "r");
    while ((ch = fgetc(fp)) != EOF) {
        if (ch > 47 && ch < 58) {
            buf[buf_ind] = ch;
            buf_ind++;
        } else if (buf_ind) {
            buf_ind = 0;
            args[arg_ind] = atoi(buf);
            arg_ind++;
            memset(buf, 0, 3 * sizeof(char));
            if (ch == '\n') {
                arg_ind = 0;
                
                List tmp = list_init();
                for (int i = 0; i < args[0]; i++) {
                    push(&tmp, pop(&stacks[args[1]-1]));
                }
                for (int i = 0; i < args[0]; i++) {
                    push(&stacks[args[2]-1],pop(&tmp));
                }
            }
        }
    }
    for (int i = 0; i < 9; i++) {
        printf("%c", pop(&stacks[i]));
    }
    printf("\n");
    fclose(fp);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum parse_state{command,arg,fs,dirname,filename};

struct ListNode {
    int item;
    struct ListNode * next;
};

struct List {
    struct ListNode * head;
};

typedef struct List List;

void push(struct List * list, int item) {
    struct ListNode * head = list->head;
    list->head = malloc(sizeof(struct ListNode));
    list->head->item = item;
    list->head->next = head;
}
int pop(struct List * list) {
    int item = list->head->item;
    struct ListNode * next = list->head->next;
    free(list->head);
    list->head = next;
}
struct List list_init() {
    struct List new;
    new.head = NULL;
    return new;
}

void list_print(struct List * list) {
    struct ListNode * node = list->head;
    while ( node != NULL ) {
        printf("%d ",node->item);
        node = node->next;
    }
    printf("\n");
}

struct Dir {
    char name[32];
    struct Dir * up;
    struct Dir * subdirs[16];
    int subdirs_len;
    int size;
};

typedef struct Dir Dir;

int main() {
    
    FILE * fp = fopen("input","r");

    Dir root;
    root.up = NULL;
    Dir * current_dir;

    enum parse_state state = command;

    char ch = fgetc(fp);

    List sizes = list_init();

    while (1) {
        char wordbuf[32];
        char wi = 0;
        if (ch == ' ' || ch == '\n') ch = fgetc(fp);
        while (ch != ' ' && ch != '\n') {
            if (ch == EOF) {
                int smallest = 0x7FFFFFFF;
                int space_available = 70000000 - root.size;
                int space_needed = 30000000 - space_available;
                struct ListNode * node = sizes.head;
                while ( node != NULL ) {
                    if (node->item > space_needed && node->item < smallest) {
                        smallest=node->item;
                    }
                    node = node->next;
                }
                printf("%d\n",smallest);
                return 0;
            }
            wordbuf[wi] = ch;
            wi++;
            ch = fgetc(fp);
        }
        wordbuf[wi] = '\0';

        //printf(wordbuf);
        //printf(" %d\n", state);
        switch (state) {
            case command :
                if (!strcmp(wordbuf, "cd")) {
                    state = arg;
                } else if (!strcmp(wordbuf, "ls")) {
                    state = fs;
                } else {
                    state = command;
                }
                break;
            case arg :
                if (!strcmp(wordbuf, "/")) {
                    current_dir = &root;
                } else if (!strcmp(wordbuf, "..")) {
                    int tmp_size = current_dir->size;
                    current_dir = current_dir->up;
                    current_dir->size += tmp_size;
                    push(&sizes,tmp_size);
                } else {
                    for (int i = 0; i<current_dir->subdirs_len; i++) {
                        if (!strcmp(wordbuf, current_dir->subdirs[i]->name)) {
                            current_dir = current_dir->subdirs[i];
                            break;
                        }
                    }
                }
                state = command;
                break;
            case fs :
                if (!strcmp(wordbuf, "dir")) {
                    state = dirname;
                } else if (!strcmp(wordbuf, "$")) {
                    state = command;
                } else {
                    current_dir->size += atoi(wordbuf);
                    state = filename;
                }
                break;
            case dirname :
                Dir * new = malloc(sizeof(Dir));
                strcpy(new->name, wordbuf);
                new->up = current_dir;
                new->subdirs_len = 0;
                current_dir->subdirs[current_dir->subdirs_len] = new;
                current_dir->subdirs_len ++;
                state = fs;
                break;
            case filename :
                state = fs;
                break;

        }
    }
}

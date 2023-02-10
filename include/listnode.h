#ifndef LISTNODE_H
#define LISTNODE_H

typedef struct s_listnode{
    char* fname;
    struct s_listnode* next;
}listnode;

listnode* add_last(listnode* fl, char* name);

#endif
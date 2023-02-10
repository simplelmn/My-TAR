#include <stdlib.h>
#include "../include/listnode.h"

listnode* add_last(listnode* fl, char* name){
    listnode* temp = (listnode*)malloc(sizeof(listnode));
    temp->fname = name;
    temp->next = NULL;
    if(fl == NULL){
        fl = temp;
    }
    else{
        listnode* node = fl;
        while(node->next != NULL){
            node = node->next;
        }
        node->next = temp;
    }
    return fl;
}
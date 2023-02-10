#include <unistd.h>
#include <stdlib.h>
char* my_strcat(char* str1 ,  char* str2){
    int i = 0;
    while(str1[i])i++;
    int j = i;
    i=0;
    while(str2[i]){
        str1[j++] = str2[i++];
    }
    return str1;
}

int prints(char* str){
    int i = 0; 
    while(str[i]){
        write(1, &str[i++], 1);
    }
    write(1, "\n", 1);
    return i;
}

void fill_string(char* str, char* str1){
    for(int i  = 0; str1[i] != '\0'; i++){
        str[i] = str1[i];
    }
}

char* my_strcpy(char* str1, char* str2){
    if(str1 == NULL){
        return NULL;
    }
    char *p = str1;
    while(*str2 != '\0'){
        *str1 = *str2;
        str1++;
        str2++;
    }

    *str1 = '\0';
    return p;
}
char* fill_string_zero(char *str){
    int i = 0;
    while(str[i] != '\0'){
        str[i] = 0;
    }
    return str;
}

int my_strcmp(char* p1 , char* p2){
    for(int i = 0; p1[i] || p2[i]; i++){
        if(p1[i] != p2[i]){
            return p2[i] - p1[1];
        }
        if(!p1[i]) return 0;
        if(!p2[i]) return -1;
    }

    return 0;
}
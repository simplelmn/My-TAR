#include <stdlib.h>

char* octalnumber(int size){
   char* string = malloc(sizeof(char)* 12); 
    *string = '\0';
    int i = 0;
    while(size){
        string--;
        *string = size % 8  + '0';
        size /= 8;
        i++;
    }
    i = 6 - i;
    while(i >=0 ){
        string--;
        *string = '0';
        i--;
    }
    return  string;
}

char* int_to_char(int size){
    char* string = malloc(sizeof(char)* 11); 
    *string = '\0';
    int i = 0;
    while(size){
        string--;
        *string = size % 8  + '0';
        size /= 8;
        i++;
    }
    i = 10 - i;
    while(i >=0 ){
        string--;
        *string = '0';
        i--;
    }
    return  string;
}

int my_pow(int base, int degree){
    int res = 1;
    for(int i = 0; i < degree; i++){
        res *= base;
    }

    return res;
}

int decimal_num(char* octal){
    int i = 0;
    int res = 0; 
    while(octal[i]){
        res = res * 10 + octal[i] - '0';
        i++;
    }

    int degree = 0, decimal = 0, r;

    
    while(res > 0){
        r = res % 10;
        res /= 10;
        decimal = decimal + r * my_pow(8, degree);
        ++degree;
    }

    return decimal;
}
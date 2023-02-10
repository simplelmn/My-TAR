#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "../include/my_string.h"
#include "../include/converting.h"
#include "../include/listnode.h"
#include "../include/converting.h"
#include "../include/tar.h"

extern box* fill_zero(box* m_box){
    fill_string_zero(m_box->name);
    fill_string_zero(m_box->mode);
    fill_string_zero(m_box->uid);
    fill_string_zero(m_box->gid);
    fill_string_zero(m_box->size);
    fill_string_zero(m_box->mtime);
    fill_string_zero(m_box->chksum);
    fill_string_zero(&m_box->typeflag);
    fill_string_zero(m_box->linkname);
    fill_string_zero(m_box->magic);
    fill_string_zero(m_box->version);
    fill_string_zero(m_box->uname);
    fill_string_zero(m_box->gname);
    fill_string_zero(m_box->devmajor);
    fill_string_zero(m_box->devminor);
    fill_string_zero(m_box->prefix);
    return m_box;
}

extern char* cheksum_(char* cheksum_count){
    int i = 0 ;
    int count = 0 ; 
    while(cheksum_count[i]){
        count += (int)cheksum_count[i++];
    }
    count += 256;
    my_strcpy(cheksum_count , octalnumber(count));
    return cheksum_count;
}

extern box* fill_tar(listnode* fl){
    char* cheksum_count = malloc(512);
    struct stat filestat;
    char* temp = malloc(11);
    stat(fl->fname, &filestat);
    box* temp_box = (box*)malloc(sizeof(box));

    fill_string(temp_box->name, fl->fname);
    my_strcat(cheksum_count, temp_box->name);

    my_strcpy(temp,octalnumber(filestat.st_mode));
    fill_string(temp_box->mode, temp);
    my_strcat(cheksum_count, temp_box->mode);


    my_strcpy(temp , octalnumber(filestat.st_uid));
    fill_string(temp_box->uid, temp);
    my_strcat(cheksum_count, temp_box->uid);

    my_strcpy(temp , octalnumber(filestat.st_gid));
    fill_string(temp_box->gid, temp);
    my_strcat(cheksum_count, temp_box->gid);

    my_strcpy(temp , int_to_char(filestat.st_size));
    fill_string(temp_box->size, temp);
    my_strcat(cheksum_count, temp_box->size);

    my_strcpy(temp, octalnumber(filestat.st_mtime));
    fill_string(temp_box->mtime, temp);
    my_strcat(cheksum_count, temp_box->mtime);

    fill_string(&temp_box->typeflag, "0");
    my_strcat(cheksum_count, &temp_box->typeflag);

    fill_string(temp_box->magic, "ustar  ");
    my_strcat(cheksum_count, temp_box->magic);

    fill_string(temp_box->uname, "docode");
    my_strcat(cheksum_count, temp_box->uname);

    fill_string(temp_box->gname, "docode");
    my_strcat(cheksum_count, temp_box->gname);

    cheksum_count = cheksum_(cheksum_count);
    fill_string(temp_box->chksum, cheksum_count);
    return temp_box;
}

extern void adding_files(char* tar_name, listnode* fl, char flag){
    struct stat filestat;
    int check = 0;
    if(open(fl->fname, O_RDONLY) < 0) {
        fprintf(stderr, "my_tar: %s: Cannot stat: No such file or directory\n", fl->fname); 
        return;
    }
    stat(fl->fname, &filestat);
    if(flag == 'u'){
        box chek_box;
        int test = open(tar_name, O_RDONLY);
        while(read(test, &chek_box, 512) > 0){
            if(my_strcmp(chek_box.magic, "ustar  ")== 0 && my_strcmp(chek_box.name, fl->fname) == 0 && my_strcmp(chek_box.mtime, octalnumber(filestat.st_mtime)) == 0){
                check = 1;
            }
        }
        close(test);
        if (check) {
            return;
        }
    }
    int size = 512;
    int i = 1 , fd;
    stat(fl->fname, &filestat);
    int tempsize = filestat.st_size;
    while (tempsize > 512) {
        tempsize -= 512;
        i++;
    }
    size *= i;
    char* content = (char*)malloc(sizeof(char) * size);
    fill_string_zero(content);
    fd=open(fl->fname, O_RDONLY);
    read(fd, content, filestat.st_size);
    close(fd);

    box* m_box = (box*)malloc(sizeof(box));
    fill_zero(m_box);
    m_box = fill_tar(fl);
    fd = open(tar_name, O_WRONLY | O_APPEND);
    write(fd, m_box, 512);
    write(fd, content, size);
    close(fd);
    fl = fl->next;
}

extern void append_by_time(char* tar_name, listnode* fl){
    while (fl) {
        adding_files(tar_name, fl, 'u');
        fl = fl->next;
    }
}

extern void create_file(char* tar_name){
    struct stat filestat;
    int fd = open(tar_name, O_RDONLY);
    box chek_box;
    while(read(fd, &chek_box, 512) > 0){
        if(my_strcmp(chek_box.magic, "ustar  ")== 0){
            creat(chek_box.name, decimal_num(chek_box.mode));
            stat(chek_box.name, &filestat);
            
            int fd2 = open(chek_box.name, O_WRONLY | O_APPEND);
            int f_size = decimal_num(chek_box.size);
            int test = f_size, j = 1;
            while (test > 512) {
                test = test - 512;
                j++;
            } 

            int temp = f_size;           
            while(temp > 0){
                char c;
                read(fd, &c, 1);
                write(fd2, &c, 1);
                temp--;
            }

            close(fd2);

            j *= 512;
            j = j - f_size;
            lseek(fd, j, SEEK_CUR);
            
            filestat.st_mtime = decimal_num(chek_box.mtime);
        }
    }
    close(fd);
}

extern void append(char* tar_name, listnode* fl){
    while (fl) {
        adding_files(tar_name, fl, 'r');
        fl = fl->next;
    }
}

extern void show_name(char* tar_name){
    int fd = open(tar_name, O_RDONLY);
    box chek_box;
    while(read(fd, &chek_box, 512) > 0){
        if(my_strcmp(chek_box.magic, "ustar  ")== 0){
            prints(chek_box.name);
        }
    }
    close(fd);
}

extern void create_tar(char* tar_name, listnode* fl){
    int test = 0 ;
    if((test = open(tar_name, O_RDONLY))){
        unlink(tar_name);
        close(test);
    }
    creat(tar_name, 000644);
    while (fl) {
        adding_files(tar_name, fl, 'c');
        fl = fl->next;
    }
    
}

extern void redirect(char* tar_name, listnode* fl, char flag){
    if(flag == 'c'){
        create_tar(tar_name, fl);
    }
    else if (flag == 't') {
        show_name(tar_name);
    }else if(flag == 'x'){
        create_file(tar_name);
    }
    else if(flag == 'r'){
        append(tar_name, fl);
    }
    else if(flag == 'u'){
        append_by_time(tar_name, fl);
    }
}

extern int my_tar(int ac, char** av){
    listnode* fl = (listnode*)malloc(sizeof(listnode));
    fl = NULL;
    char* tar_name = (char*)malloc(sizeof(char)*50);
    char flag;
    int fl_size = 0;
    for(int i = 1 ; i < ac; i++){
        if(my_strcmp(av[1], "-cf") == 0 ){
            flag = 'c';
        }
        else if(my_strcmp(av[i], "-tf")==0){
            flag = 't';
        }
        else if(my_strcmp(av[i], "-xf")==0){
            flag = 'x';
        }
        else if (my_strcmp(av[i], "-rf")==0) {
            flag = 'r';
        }
         else if (my_strcmp(av[i], "-uf")==0) {
            flag = 'u';
        }
        if(i > 2){
            fl = add_last(fl, av[i]);
            fl_size++;
        }
    }
    tar_name = av[2];
    redirect(tar_name, fl, flag);
    return 0;
}
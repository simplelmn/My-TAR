#include "../include/listnode.h"
#ifndef TAR_H
#define TAR_H

typedef struct posix_header
{
    char name[100];               /*   0 */
    char mode[8];                 /* 100 */
    char uid[8];                  /* 108 */
    char gid[8];                  /* 116 */
    char size[12];                /* 124 */
    char mtime[12];               /* 136 */
    char chksum[8];               /* 148 */
    char typeflag;                /* 156 */
    char linkname[100];           /* 157 */
    char magic[6];                /* 257 */
    char version[2];              /* 263 */
    char uname[32];               /* 265 */
    char gname[32];               /* 297 */
    char devmajor[8];             /* 329 */
    char devminor[8];             /* 337 */
    char prefix[155];             /* 345 */
    char add[12];                 /* 500 */
} box;

box* fill_zero(box* m_box);
char* cheksum_(char* cheksum_count);
box* fill_tar(listnode* fl);
void adding_files(char* tar_name, listnode* fl, char flag);
void append_by_time(char* tar_name, listnode* fl);
void create_file(char* tar_name);
void append(char* tar_name, listnode* fl);
void show_name(char* tar_name);
void create_tar(char* tar_name, listnode* fl);
void redirect(char* tar_name, listnode* fl, char flag);
int my_tar(int ac, char** av);

#endif
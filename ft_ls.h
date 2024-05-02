#define _GNU_SOURCE
#include <sys/types.h>
#include <errno.h>
#include <dirent.h>
#include <stdio.h>
#include <stddef.h>
#include "libft/libft.h"
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <sys/sysmacros.h>

typedef struct s_HasFlag
{
    int R;
    int l;
    int a;
    int t;
    int r;
    int u;
    int others;
}t_HasFlag;

typedef struct s_filename
{
    char *filename;
    int type;   
    struct stat sta;
    char *link;
    struct s_filename *next;
    int needplus;
} t_filename;

typedef struct s_max
{
    int max_len_size;
    int max_len_link;
    int max_name;
    int max_group;
    int max_major;
    int hasplus;
    int hascmod;
} t_max;


void    parsing(char **av, t_HasFlag *HasFlag);
void    sort(t_filename *list, t_HasFlag *hasflag);
void    freelist(t_filename *list);
void    print_right(t_filename *file, t_max *max, int *flagc, char*dirname);
void    print_time(t_filename *file);
void    print_link(t_filename *file);
void    print_size(t_filename *file, int max);
void    print_total(t_filename *file, t_HasFlag *hasflag);
void    print_name_group(t_filename *file, t_max *max);
void    print_major(t_filename *file, int max);

// UTILS

int     get_len_nbr(long int nbr);
int     get_max_len_size(t_filename *list, t_HasFlag *hasflag);
int     get_max_len_nlink(t_filename *list, t_HasFlag *hasflag);
void    init_max(t_filename *list, t_max *max, t_HasFlag *hasflag, char *dirname);

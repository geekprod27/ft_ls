#include "../ft_ls.h"

void print_total(t_filename *file, t_HasFlag *hasflag)
{
    int block = 0;
    while (file)
    {
        if(file->filename[0] != '.' || hasflag->a)
            block += file->sta.st_blocks;
        file = file->next;
    }
    ft_putstr_fd("total ", 1);
    ft_putnbr_fd(block/2, 1);
    ft_putchar_fd('\n', 1);
}

void print_name_group(t_filename *file, t_max *max)
{
    struct passwd *infouser = getpwuid(file->sta.st_uid);
    ft_putstr_fd(infouser->pw_name, 1);
    ft_putchar_fd(' ', 1);
    int len = ft_strlen(infouser->pw_name);
    while(len < max->max_name)
    {
        ft_putchar_fd(' ', 1);
        len++;
    }


    struct group *grou = getgrgid(file->sta.st_gid);
    ft_putstr_fd(grou->gr_name, 1);
    ft_putchar_fd(' ', 1);
    len = ft_strlen(grou->gr_name);
    while(len < max->max_group)
    {
        ft_putchar_fd(' ', 1);
        len++;
    }
}

void print_link(t_filename *file)
{
    if(file->link != NULL)
    {
        ft_putstr_fd(" -> ", 1);
        ft_putstr_fd(file->link, 1);
    }
}

void test(int test, unsigned int st_mode, char c)
{
    if(test & st_mode)
        ft_putchar_fd(c, 1);
    else
        ft_putchar_fd('-', 1);
}

void testplus(int test,int testplus, unsigned int st_mode, char c)
{
    if(test & st_mode && testplus & st_mode)
        ft_putchar_fd(c, 1);
    else if (!(test & st_mode) && testplus & st_mode)
        ft_putchar_fd(c-32, 1);
    else if (test & st_mode && !(testplus & st_mode))
        ft_putchar_fd('x', 1);
    else
        ft_putchar_fd('-', 1);
}

void print_time(t_filename *file)
{
    char *modif_time = ctime(&file->sta.st_mtim.tv_sec);
    int len = ft_strlen(modif_time);
    time_t actual_time = time(NULL);
    if (actual_time - file->sta.st_mtim.tv_sec < 2629800 * 6)
    {
        modif_time[len - 9] = '\0';
        ft_putstr_fd(modif_time+4, 1);
    }
    else
    {
        modif_time[len - 14] = ' ';
        modif_time[len - 13] = modif_time[len - 5];
        modif_time[len - 12] = modif_time[len - 4];
        modif_time[len - 11] = modif_time[len - 3];
        modif_time[len - 10] = modif_time[len - 2];
        modif_time[len - 9] = '\0';
        ft_putstr_fd(modif_time+4, 1);
    }
}

void print_right(t_filename *file, t_max *max, int *flagc, char*dirname)
{

    if (S_ISDIR(file->sta.st_mode))
        ft_putchar_fd('d', 1);
    else if (S_ISLNK(file->sta.st_mode))
        ft_putchar_fd('l', 1);
    else if(S_ISSOCK(file->sta.st_mode))
        ft_putchar_fd('s', 1);
    else if (S_ISFIFO(file->sta.st_mode))
        ft_putchar_fd('p', 1);
    else if (S_ISCHR(file->sta.st_mode))
    {
        *flagc = 1;
        ft_putchar_fd('c', 1);
    }
    else if (S_ISBLK(file->sta.st_mode))
        ft_putchar_fd('b', 1);
    else
        ft_putchar_fd('-', 1);
    test(S_IRUSR, file->sta.st_mode, 'r');
    test(S_IWUSR, file->sta.st_mode, 'w');
    testplus(S_IXUSR, S_ISGID, file->sta.st_mode, 's');
    test(S_IRGRP, file->sta.st_mode, 'r');
    test(S_IWGRP, file->sta.st_mode, 'w');
    testplus(S_IXGRP, S_ISGID, file->sta.st_mode, 's'); // -> si S_ISGID -> 's'
    test(S_IROTH, file->sta.st_mode, 'r');
    test(S_IWOTH, file->sta.st_mode, 'w');
    testplus(S_IXOTH, S_ISVTX, file->sta.st_mode, 't'); // -> si S_ISVTX -> 't' si pas les 2 maj
    if(file->needplus)
        ft_putchar_fd('+', 1);
    else if (max->hasplus)
        ft_putchar_fd(' ', 1);
    ft_putchar_fd(' ', 1);
    int len = get_len_nbr(file->sta.st_nlink);
    while(len < max->max_len_link)
    {
        ft_putchar_fd(' ', 1);
        len++;
    }
    ft_putnbr_fd(file->sta.st_nlink, 1);
    ft_putchar_fd(' ', 1);
    (void) dirname;
}

void print_major(t_filename *file, int max)
{
    int len;
    if(S_ISCHR(file->sta.st_mode) || S_ISBLK(file->sta.st_mode))
        len =  get_len_nbr(major(file->sta.st_rdev));
    else
        len = 0;
    while(len < max)
    {
        ft_putchar_fd(' ', 1);
        len++;
    }
    if(S_ISCHR(file->sta.st_mode) || S_ISBLK(file->sta.st_mode))
    {
        ft_putnbr_fd(major(file->sta.st_rdev), 1);
        ft_putchar_fd(',', 1);
    }
    ft_putchar_fd(' ', 1);
}

void print_size(t_filename *file, int max)
{
    int len;
    if(S_ISCHR(file->sta.st_mode) || S_ISBLK(file->sta.st_mode))
        len =  get_len_nbr(minor(file->sta.st_rdev)) +1;
    else
        len = get_len_nbr(file->sta.st_size);
    while(len < max)
    {
        ft_putchar_fd(' ', 1);
        len++;
    }
    if(S_ISCHR(file->sta.st_mode) || S_ISBLK(file->sta.st_mode))
        ft_putnbr_fd(minor(file->sta.st_rdev), 1);
    else
        ft_putnbr_fd(file->sta.st_size, 1);
    ft_putchar_fd(' ', 1);
}
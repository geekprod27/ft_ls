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
    int len = 0;
    char *toprint = ft_calloc(max->max_name + max->max_group + 10, sizeof(char));
    if (!toprint)
    {
        perror("ft_calloc");
        return ;
    }
    while(infouser->pw_name[len])
    {
        toprint[len] = infouser->pw_name[len];
        len++;
    }
    toprint[len] = ' ';
    len++;
    while(len < max->max_name)
    {
        toprint[len] = ' ';
        len++;
    }
    int savelen = len;
    struct group *grou = getgrgid(file->sta.st_gid);
    if (!grou)
    {
        len = get_len_nbr(file->sta.st_gid);
        while(len < max->max_group)
        {
            toprint[savelen] = ' ';
            savelen++;
            len++;
        }
        ft_putstr_fd(toprint, 1);
        free(toprint);
        ft_putnbr_fd(file->sta.st_gid, 1);
        ft_putchar_fd(' ', 1);
    }
    else
    {
        int igr = 0;
        while(grou->gr_name[igr])
        {
            toprint[savelen] = grou->gr_name[igr];
            igr++;
            savelen++;
        }
        toprint[savelen] = ' ';
        savelen++;
        len = ft_strlen(grou->gr_name);
        while(len < max->max_group)
        {
            toprint[savelen] = ' ';
            savelen++;
            len++;
        }
        toprint[savelen] = 0;
        ft_putstr_fd(toprint, 1);
        free(toprint);
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

char test(int test, unsigned int st_mode, char c)
{
    if(test & st_mode)
        return (c);
    else
        return('-');
}

char testplus(int test,int testplus, unsigned int st_mode, char c)
{
    if(test & st_mode && testplus & st_mode)
        return(c);
    else if (!(test & st_mode) && testplus & st_mode)
        return(c-32);
    else if (test & st_mode && !(testplus & st_mode))
        return('x');
    else
        return('-');
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
    char *toprint = ft_calloc(40, sizeof(char));
    if (S_ISDIR(file->sta.st_mode))
        toprint[0] = 'd';
    else if (S_ISLNK(file->sta.st_mode))
        toprint[0] = 'l';
    else if(S_ISSOCK(file->sta.st_mode))
        toprint[0] = 's';
    else if (S_ISFIFO(file->sta.st_mode))
        toprint[0] = 'p';
    else if (S_ISCHR(file->sta.st_mode))
    {
        *flagc = 1;
        toprint[0] = 'c';
    }
    else if (S_ISBLK(file->sta.st_mode))
        toprint[0] = 'b';
    else
        toprint[0] = '-';
    toprint[1] = test(S_IRUSR, file->sta.st_mode, 'r');
    toprint[2] = test(S_IWUSR, file->sta.st_mode, 'w');
    toprint[3] = testplus(S_IXUSR, S_ISGID, file->sta.st_mode, 's');
    toprint[4] = test(S_IRGRP, file->sta.st_mode, 'r');
    toprint[5] = test(S_IWGRP, file->sta.st_mode, 'w');
    toprint[6] = testplus(S_IXGRP, S_ISGID, file->sta.st_mode, 's');
    toprint[7] = test(S_IROTH, file->sta.st_mode, 'r');
    toprint[8] = test(S_IWOTH, file->sta.st_mode, 'w');
    toprint[9] = testplus(S_IXOTH, S_ISVTX, file->sta.st_mode, 't');
    int i = 10;
    if(file->needplus)
    {
        toprint[i] = '+';
        i++;
    }
    else if (max->hasplus)
    {
        toprint[i] =' ';
        i++;
    }
    toprint[i] =' ';
    i++;
    int len = get_len_nbr(file->sta.st_nlink);
    while(len < max->max_len_link)
    {
        toprint[i] =' ';
        i++;
        len++;
    }
    ft_putstr_fd(toprint, 1);
    free(toprint);
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

void	ft_putofft_fd(off_t nb, int fd)
{
	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		nb = -nb;
	}
	if (nb > 9)
	{
		ft_putofft_fd(nb / 10, fd);
		ft_putchar_fd(nb % 10 + 48, fd);
	}
	else
		ft_putchar_fd(nb + 48, fd);
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
    {
        ft_putofft_fd(file->sta.st_size, 1);
    }
    ft_putchar_fd(' ', 1);
}
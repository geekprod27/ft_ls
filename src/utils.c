#include "../ft_ls.h"
#include <attr/xattr.h>

int get_len_nbr(long int nbr)
{
    int i = 1;
    while(nbr >= 10)
    {
        nbr = nbr / 10;
        i++;
    }
    return (i);
}

// int get_max_len_size(t_filename *list, t_HasFlag *hasflag)
// {
//     int max = 0;
//     int tmp;
//     while (list)
//     {
//         if(list->filename[0] != '.' || hasflag->a)
//         {
//             tmp = get_len_nbr(list->sta.st_size);
//             if (tmp > max)
//                 max = tmp;
//         }
//         list = list->next;
//     }
//     return max;
// }

// int get_max_len_nlink(t_filename *list, t_HasFlag *hasflag)
// {
//     int max = 0;
//     int tmp;
//     while (list)
//     {
//         if(list->filename[0] != '.' || hasflag->a)
//         {
//             tmp = get_len_nbr(list->sta.st_nlink);
//             if (tmp > max)
//                 max = tmp;
//         }
//         list = list->next;
//     }
//     return max;
// }

// int get_max_len_name(t_filename *list, t_HasFlag *hasflag)
// {
//     int max = 0;
//     int tmp;
//     while (list)
//     {
//         if(list->filename[0] != '.' || hasflag->a)
//         {
//             struct passwd *infouser = getpwuid(list->sta.st_uid);
//             tmp = ft_strlen(infouser->pw_name);
//             if (tmp > max)
//                 max = tmp;
//         }
//         list = list->next;
//     }
//     return max;
// }

// int get_max_len_group(t_filename *list, t_HasFlag *hasflag)
// {
//     int max = 0;
//     int tmp;
//     while (list)
//     {
//         if(list->filename[0] != '.' || hasflag->a)
//         {
//             struct group *grou = getgrgid(list->sta.st_gid);
//             tmp = ft_strlen(grou->gr_name);
//             if (tmp > max)
//                 max = tmp;
//         }
//         list = list->next;
//     }
//     return max;
// }

void init_max(t_filename *list, t_max *max, t_HasFlag *hasflag, char *dirname)
{
    struct group *grou;
    struct passwd *infouser;
    int tmp;
    max->max_group = 0;
    max->max_len_link = 0;
    max->max_len_size = 0;
    max->max_name = 0;
    max->max_major = 0;
    max->hasplus = 0;
    max->hascmod = 0;
    while (list)
    {
        if(list->filename[0] != '.' || hasflag->a)
        {
            tmp = get_len_nbr(list->sta.st_nlink);
            if (tmp > max->max_len_link)
                max->max_len_link = tmp;
            grou = getgrgid(list->sta.st_gid);
            tmp = ft_strlen(grou->gr_name);
            if (tmp > max->max_group)
                max->max_group = tmp;
            infouser = getpwuid(list->sta.st_uid);
            tmp = ft_strlen(infouser->pw_name);
            if (tmp > max->max_name)
                max->max_name = tmp;
            if (!S_ISCHR(list->sta.st_mode) && !S_ISBLK(list->sta.st_mode))
            {
                tmp = get_len_nbr(list->sta.st_size);
                if (tmp > max->max_len_size)
                    max->max_len_size = tmp;
            }
            else
            {
                max->hascmod = 1;
                tmp = get_len_nbr(minor(list->sta.st_rdev))+1;
                if (tmp > max->max_len_size)
                    max->max_len_size = tmp;
                tmp = get_len_nbr(major(list->sta.st_rdev));
                if (tmp > max->max_major)
                    max->max_major = tmp;
            }
            if(dirname)
            {
                char *tmpstr = ft_strjoin(dirname, list->filename);
                if(listxattr(tmpstr, NULL, 0) > 0 && S_ISCHR(list->sta.st_mode))
                {
                    list->needplus = 1;
                    max->hasplus = 1;
                }
                free(tmpstr);
            }
            else if(listxattr(list->filename, NULL, 0) > 0 && S_ISCHR(list->sta.st_mode))
            {
                list->needplus = 1;
                max->hasplus = 1;
            }
        }
        list = list->next;
    }
}
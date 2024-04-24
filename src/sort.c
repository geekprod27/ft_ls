#include "../ft_ls.h"

long long cmptimespec(struct timespec *time1, struct timespec *time2)
{
    if (time1->tv_nsec == time2->tv_nsec && time1->tv_sec == time2->tv_sec)
        return (0);
    if (time1->tv_sec == time2->tv_sec)
        return (time1->tv_nsec - time2->tv_nsec);
    return (time1->tv_sec - time2->tv_sec);
}

int cmpname(char *str1, char *str2)
{
    int i = 0;
    int j = 0;

    while(str1[i] && str2[j])
    {
        if(ft_tolower(str1[i]) != ft_tolower(str2[j]))
            return (ft_tolower(str1[i]) - ft_tolower(str2[j]));
        j++;
        i++;
    }
    return (ft_tolower(str1[i]) - ft_tolower(str2[j]));
}

void    sort(t_filename *list, t_HasFlag *hasflag)
{
    t_filename *start = list;
    char *tmp;
    struct stat aa;

    while (start)
    {
        list = start->next;
        while(list)
        {
            if (hasflag->t)
            {
                if (cmptimespec(&start->sta.st_mtim, &list->sta.st_mtim) == 0)
                {
                    if ((ft_strncmp(start->filename, list->filename, 255) > 0 && !hasflag->r) || (ft_strncmp(start->filename, list->filename, 255) < 0 && hasflag->r))
                    {
                        aa = start->sta;
                        tmp = start->filename;
                        start->filename = list->filename;
                        start->sta = list->sta;
                        list->sta = aa;
                        list->filename = tmp;
                    }
                }
                else if ((cmptimespec(&start->sta.st_mtim, &list->sta.st_mtim) < 0 && !hasflag->r) || (cmptimespec(&start->sta.st_mtim, &list->sta.st_mtim) > 0 && hasflag->r))
                {
                    aa = start->sta;
                    tmp = start->filename;
                    start->filename = list->filename;
                    start->sta = list->sta;
                    list->sta = aa;
                    list->filename = tmp;
                }
            }
            else if ((ft_strncmp(start->filename, list->filename, 255) > 0 && !hasflag->r) || (ft_strncmp(start->filename, list->filename, 255) < 0 && hasflag->r))
            {
                aa = start->sta;
                tmp = start->filename;
                start->filename = list->filename;
                start->sta = list->sta;
                list->sta = aa;
                list->filename = tmp;
            }
            list = list->next;
        }
        start = start->next;
    }
}
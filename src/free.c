#include "../ft_ls.h"

void freelist(t_filename *list)
{
    t_filename *tmp;

    while(list)
    {
        tmp = list;
        free(tmp->filename);
        list = list->next;
        free(tmp);
    }
}
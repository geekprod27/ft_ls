#include "../ft_ls.h"


void printfilename(t_filename *file, int i, t_HasFlag *HasFlag, t_max *max, char *dirname)
{
    if(!HasFlag->l)
    {
        if (i != 0)
            ft_putstr_fd("  ", 1);
        ft_putstr_fd(file->filename, 1);
    }
    else
    {
        int flagc = 0;
        print_right(file, max, &flagc, dirname);
        print_name_group(file, max);
        if(max->hascmod)
            print_major(file, max->max_major);
        print_size(file, max->max_len_size);
        print_time(file);
        ft_putchar_fd(' ', 1);
        ft_putstr_fd(file->filename, 1);
        if(S_ISLNK(file->sta.st_mode))
            print_link(file);
        ft_putchar_fd('\n', 1);
    }
}

void ls_dir(char *name, t_HasFlag *hasflag, int isfirst)
{
    int flagfree = 0;
    if(name[ft_strlen(name)-1] != '/')
    {
        name = ft_strjoin(name, "/");
        flagfree = 1;
    }
    DIR *dir = opendir(name);
    if(!dir)
    {
        char *tmp = ft_strjoin("ft_ls: cannot open directory \'", name);
        tmp[ft_strlen(tmp)-1] = 0;
        char *tmp2 = ft_strjoin(tmp, "\'");
        perror(tmp2);
        free(tmp);
        free(tmp2);
        if(flagfree)
            free(name);
        return ;
    }
    if(isfirst == 0)
        ft_putchar_fd('\n', 1);
    struct dirent *d;
    while(1)
    {
        errno = 0;
        d = readdir(dir);
        if(d == NULL && errno == 0)
            return ;
        if(d != NULL && errno == 0)
            break ;
        if(d == NULL && errno != 0)
        {
            char *tmp = ft_strjoin("ft_ls: reading directory \'", name);
            tmp[ft_strlen(tmp)-1] = 0;
            char *tmp2 = ft_strjoin(tmp, "\'");
            perror(tmp2);
            free(tmp);
            free(tmp2);
            break ;
        }
    }
    t_filename *list;
    t_filename *savestart;
    if(d != NULL)
    {
        list = malloc(sizeof(t_filename));
        if (!list)
        {
            perror("malloc list");
            return ;
        }
        savestart = list;
        char *temp;
        list->filename = ft_strdup(d->d_name);
        list->needplus = 0;
        list->type = d->d_type;
        temp = ft_strjoin(name, d->d_name);
        if(lstat(temp, &list->sta) == -1)
            perror("stat1");
        if(S_ISLNK(list->sta.st_mode))
        {
            char *buf = ft_calloc(256, sizeof(char));
            if(!buf)
            {
                perror("calloc");
                return ;
            }
            if(readlink(temp, buf, 255) == -1)
            {
                char *tmp = ft_strjoin("ft_ls: cannot read symbolic link \'", temp);
                char *tmp2 = ft_strjoin(tmp, "\'");
                perror(tmp2);
                free(tmp);
                free(tmp2);
                free(buf);
            }
            list->link = buf;
        }
        else
            list->link = NULL;
        free(temp);
        list->next =NULL;
        if (hasflag->R)
        {

            int antiwarn = write(1, name, ft_strlen(name)-1);
            antiwarn++;
            ft_putchar_fd(':', 1);
        }
        while(1)
        {
            errno = 0;
            d = readdir(dir);
            if(d == NULL && errno == 0)
                break ;
            else if(d != NULL)
            {
                list->next =malloc(sizeof(t_filename));
                if(!list->next)
                {
                    perror("malloc list->next");
                    return ;
                }
                list = list->next;
                list->filename = ft_strdup(d->d_name);
                list->needplus = 0;
                temp = ft_strjoin(name, d->d_name);
                if (!temp)
                {
                    perror("strjoin2");
                    return ;
                }
                if(lstat(temp, &list->sta) == -1)
                    perror("stat2");
                
                if(S_ISLNK(list->sta.st_mode))
                {
                    char *buf = ft_calloc(256, sizeof(char));
                    if(!buf)
                    {
                        perror("calloc");
                        return ;
                    }
                    if(readlink(temp, buf, 255) == -1)
                    {
                        char *tmp = ft_strjoin("ft_ls: cannot read symbolic link \'", temp);
                        char *tmp2 = ft_strjoin(tmp, "\'");
                        perror(tmp2);
                        free(tmp);
                        free(tmp2);
                        free(buf);
                    }
                    list->link = buf;
                }
                else
                    list->link = NULL;
                free(temp);
                list->type = d->d_type;
                list->next =NULL;
            }
            else
            {
                char *tmp = ft_strjoin("ft_ls: cannot open directory \'", name);
                tmp[ft_strlen(tmp)-1] = 0;
                char *tmp2 = ft_strjoin(tmp, "\'");
                perror(tmp2);
                free(tmp);
                free(tmp2);
            }
        }
        if (hasflag->l)
        {
            if (hasflag->R)
            {
                ft_putchar_fd('\n', 1);
            }
            print_total(savestart, hasflag);
        }
        if (!hasflag->u)
            sort(savestart, hasflag);
        list = savestart;
        int i = 0;
        t_max max;
        init_max(savestart, &max, hasflag, name);
        while(list)
        {
            if(list->filename[0] != '.' || hasflag->a)
            {
                if(i == 0 && hasflag->R && !hasflag->l)
                {
                    ft_putchar_fd('\n', 1);
                }
                printfilename(list, i, hasflag, &max, name);
                i++;
            }
            list = list->next;
        }
        if (hasflag->R)
        {
            if (!hasflag->l)
                ft_putchar_fd('\n', 1);
            list = savestart;
            while (list)
            {
                if(S_ISDIR(list->sta.st_mode) && ft_strncmp(list->filename,  ".", 2) && ft_strncmp(list->filename,  "..", 3)
                && (list->filename[0] != '.' || hasflag->a))
                {
                    char *tt = ft_strjoin(name, list->filename);
                    if(!tt)
                    {
                        perror("strjoin");
                        return ;
                    }
                    ls_dir(tt, hasflag, 0);
                    free(tt);
                }
                list = list->next;
            }
        }
        else if (!hasflag->l && i) {
            ft_putchar_fd('\n', 1);
        }
        if(flagfree)
            free(name);
        closedir(dir);
        freelist(savestart);
    }
}

t_filename *add_back(t_filename *file, char*name)
{
    t_filename*savestart = file;
    if(!file)
    {
        file = malloc(sizeof(t_filename));
        if(!file)
        {
            perror("addback");
            return (NULL);
        }
        file->filename = ft_strdup(name);
        if(lstat(name, &file->sta) == -1)
            perror("addbackstat");
        if(S_ISLNK(file->sta.st_mode))
        {
            char *buf = ft_calloc(256, sizeof(char));
            if(!buf)
            {
                perror("calloc");
                return (NULL);
            }
            if(readlink(name, buf, 255) == -1)
            {
                char *tmp = ft_strjoin("ft_ls: cannot read symbolic link \'", name);
                char *tmp2 = ft_strjoin(tmp, "\'");
                perror(tmp2);
                free(tmp);
                free(tmp2);
                free(buf);
            }
            file->link = buf;
        }
        else
            file->link = NULL;
        file->next = NULL;
        return (file);
    }
    while(file->next)
        file = file->next;
    file->next =malloc(sizeof(t_filename));
    if(!file->next)
    {
        perror("mallocaddback");
        return (NULL);
    }
    file = file->next;
    file->filename = ft_strdup(name);
    file->next = NULL;
    return(savestart);
}

int main(int argc, char**argv)
{
    (void) argc;
    t_HasFlag hasflag;
    hasflag.a = 0;
    hasflag.l = 0;
    hasflag.R = 0;
    hasflag.r = 0;
    hasflag.t = 0;
    hasflag.u = 0;
    hasflag.others = 0;
    t_filename *rep = NULL;
    t_filename *fichier = NULL;

    parsing(argv, &hasflag);
    
    if(hasflag.others)
    {
        int i = 1;
        int nbfile = 0;
        while(argv[i])
        {
            if (argv[i][0] != '-')
            {
                struct stat sta;
                if(stat(argv[i], &sta) == -1)
                {
                    ft_putstr_fd("ft_ls: cannot access '", 2);
                    ft_putstr_fd(argv[i], 2);
                    perror("'");
                }
                else
                {
                    nbfile++;
                    if (S_ISDIR(sta.st_mode) || S_ISLNK(sta.st_mode))
                    {
                        rep = add_back(rep, argv[i]);
                        if (!rep)
                            return (1);
                    }
                    else
                    {
                        fichier = add_back(fichier, argv[i]);
                        if (!fichier)
                            return (1);
                    }
                }
            }
            i++;
        }
        t_filename *save;
        t_max max;
        init_max(fichier, &max, &hasflag, NULL);
        if(fichier)
        {
            save = fichier;
            if (!hasflag.u)
                sort(fichier, &hasflag);
            int i = 0;
            while (fichier)
            {
                printfilename(fichier, i, &hasflag, &max, NULL);
                fichier = fichier->next;
                i++;
            }
            if (!hasflag.l && i)
                ft_putchar_fd('\n', 1);
            freelist(save);
        }
        if(rep)
        {
            save = rep;
            if (!hasflag.u)
                sort(rep, &hasflag);
            while(rep)
            {
                if(nbfile > 1 && !hasflag.R)
                {
                    ft_putstr_fd(rep->filename, 1);
                    ft_putstr_fd(":\n", 1);
                }
                ls_dir(rep->filename, &hasflag, 1);
                if(nbfile > 1 && rep->next)
                    ft_putchar_fd('\n', 1);
                rep = rep->next;
            }
            freelist(save);
        }
    }
    else
        ls_dir(".", &hasflag, 1);
}
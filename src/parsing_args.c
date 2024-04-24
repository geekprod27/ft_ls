#include "../ft_ls.h"

void parsing(char **av, t_HasFlag *HasFlag)
{
    int i = 1;
    int k;

    while (av[i])
    {
        if (av[i][0] == '-')
        {
            k = 1;
            while (av[i][k])
            {
                switch (av[i][k])
                {
                case 'a':
                    HasFlag->a = 1;
                    break;
                case 'R':
                    HasFlag->R = 1;
                    break;
                case 'r':
                    HasFlag->r = 1;
                    break;
                case 't':
                    HasFlag->t = 1;
                    break;
                case 'l':
                    HasFlag->l = 1;
                    break;
                default:
                    ft_putstr_fd("invalid flag\n", 2);
                    exit(2);
                    break;
                }
                k++;
            }
        }
        else
        {
            HasFlag->others = 1;
        }
        i++;
    }
}
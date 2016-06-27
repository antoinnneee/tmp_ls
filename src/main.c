
#include "../includes/ft_ls.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>



static t_larg	*creat_elem(char *str)
{
    t_larg	*tmp;

    tmp = (t_larg*) ft_memalloc(sizeof(t_larg));
    tmp->name = ft_strdup(str);
    tmp->len = ft_strlen(str);
    tmp->dir = opendir(str);
    tmp->state = 1;
    if (tmp->dir == NULL)
    {
	if (errno == ENOTDIR)
	{		
	    tmp->state = 2;
	}
	else
	{
	    perror("error ");
	    tmp->state = 0;
	}
    }
    tmp->next = NULL;
    return (tmp);
}

t_larg	*filename_parser(char *str, t_ls *ls_param)
{
    t_larg	*tmp;
    t_larg	*index;

    index = ls_param->l_arg;
    tmp = creat_elem(str);
    if (tmp->state)
    {
	if (!index)
	    return (tmp);
	while (index->next != NULL)
	{
	    index = index->next;
	}
	index->next = tmp;
    }
    else
		free(tmp);
    return(ls_param->l_arg);	
}

static void explore(void	*list)
{
    t_larg *tmp = (t_larg*)list;

    while(tmp != NULL)
    {
	ft_putendl(tmp->name);
	tmp = tmp->next;
    }
}

void	option_parser(char *str, t_ls *option)
{

    while (*++str != 0 )
    {
	if (*str == 'l')
	    option->option = option->option | (1U << 0);
	else if (*str == 'r')
	    option->option = option->option | (1U << 1);
	else if (*str == 'R')
	    option->option = option->option | (1U << 2);
	else if (*str == 'a')
	    option->option = option->option | (1U << 3);
	else if (*str == 't')
	    option->option = option->option | (1U << 4);
	else
	{
	    ft_putendl("invalid option Phoque !");
	    free(option);
	    exit(-42);
	}
    }

}

void 	arg_parser(int nbarg, char **str)
{
    int	arg;
    t_ls	*ls_param;

    ls_param = (t_ls*)ft_memalloc(sizeof(t_ls));
    arg = 1;
    ls_param->option = 0;
    ls_param->l_arg = NULL;
    ft_putstrnb("number of arg : ", nbarg);
    while (nbarg > arg)
    {
	if (str[arg][0] == '-')
	    option_parser(str[arg], ls_param);
	else
	    ls_param->l_arg = filename_parser(str[arg], ls_param);
	arg++;
    }
 //   explore(ls_param->l_arg);
	process_reading(ls_param);
 
   //		ft_putendl(ls_param->l_arg->name);
    //		ft_putendl(ls_param->l_arg->next->name);
//    ft_putstrnb("option value : ", ls_param->option);
	ft_putchar('\n');
}

void	process_reading(t_ls *ls_param)
{
	DIR				*local;
	struct dirent*	ptrfile;
	t_larg			*tmp;

	tmp = ls_param->l_arg;
	while (tmp != NULL)
	{
		local = opendir(tmp->name);
		if (local)
		{
		while ((ptrfile = readdir(local)))
		{
			if (!(ls_param->option & (1U << 3)))
			{
				if (ptrfile->d_name[0] != '.')
				{			
					ft_putendl(ptrfile->d_name);
				}

			}
			else
			{
				ft_putendl(ptrfile->d_name);
			}
		}
		}
		closedir(local);
		tmp = tmp->next;
	}
}

int	main(int a, char **b)
{
    arg_parser(a, b);
    return 0;
}













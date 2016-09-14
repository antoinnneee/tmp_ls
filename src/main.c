
#include "../includes/ft_ls.h"
#include "../includes/read.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <sys/stat.h>

static t_larg	*creat_elem(char *str)
{
	t_larg	*tmp;

	tmp = (t_larg*) ft_memalloc(sizeof(t_larg));
	tmp->name = ft_strdup(str);
	tmp->len = ft_strlen(str);
	tmp->dir = opendir(str);
	stat(tmp->name, &tmp->f_stat);
	tmp->state = 1;
	if (tmp->dir == NULL)
	{
		if (errno == ENOTDIR)
			tmp->state = 2;
		else
			tmp->state = 0;
	}
	tmp->next = NULL;
	return (tmp);
}

void	push_file_in_list(t_larg *begin, char *str)
{
	t_larg	*tmp;
	t_larg	*index;

	index = begin;
	tmp = creat_elem(str);
	if (tmp->state)
	{
		if (!index)
			return ;
		while (index->next != NULL)
		{
			index = index->next;
		}
		index->next = tmp;
	}
	else
	{
		ft_putstr("ls: ");
		ft_putstr(tmp->name);
		ft_putendl(": No Such file or directory");
		free(tmp);
	}

	return ;
}

static int	get_option(int nbarg, char **str, t_ls *ls_param)
{
	int	arg;
	arg = 1;

	while ((arg < nbarg) && (str[arg][0] == '-'))
	{
		ft_putstr("arg : str ::");
		ft_putstrnb(str[arg], arg);
		option_parser(str[arg], ls_param);
		arg++;
	}
	return (arg);

}

void 	arg_parser(int nbarg, char **str)
{
    int	arg;
    t_ls	*ls_param;

    ls_param = (t_ls*)ft_memalloc(sizeof(t_ls));
    ls_param->option = 0;
    ls_param->l_arg = NULL;
    arg = get_option(nbarg, str, ls_param);
    if (nbarg == arg)
	{
	if (!ls_param->l_arg)
	    ls_param->l_arg = (t_larg*)ft_memalloc(sizeof(t_larg));
    push_file_in_list(ls_param->l_arg, "./");
	}
    while (arg < nbarg)
    {
	if (!ls_param->l_arg)
	    ls_param->l_arg = (t_larg*)ft_memalloc(sizeof(t_larg));
	push_file_in_list(ls_param->l_arg, str[arg]);
	arg++;
    }
    ft_putstrnb("option value : ", ls_param->option);
	l_mod(ls_param->l_arg, &p_elem);
}

int	main(int a, char **b)
{
	if (is_sort(b[1], b[2]))
		ft_putendl("str correctly sort");
	else
		ft_putendl("str is not sort");
//    arg_parser(a, b);
    return 0;
}




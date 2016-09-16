
#include "../includes/ft_ls.h"
#include "../includes/read.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <sys/stat.h>

t_content	*creat_content(struct dirent *ent)
{
	t_content	*content;

	content = (t_content*) ft_memalloc(sizeof(t_content));
	content->name = ft_strdup(ent->d_name);
	content->next = NULL;
	return (content);
}

static t_content	*push_content(t_content *begin, struct dirent *str)
{
	t_content	*tmp;
	t_content	*index;

	index = begin;
	tmp = creat_content(str);
	if (tmp)
	{
		if (!index)
		{
			return (tmp);
		}
		while (index->next != NULL)
		{
			index = index->next;
		}
		index->next = tmp;
	}
	return (begin);
}

static t_larg	*creat_elem(char *str)
{
	t_larg	*tmp;
	struct dirent *ent;
	t_content *cnt;

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
		closedir(tmp->dir);
	}
	else
		while ((ent = readdir(tmp->dir)))
			push_content(tmp->content, ent);
	while (tmp->state == 1 && (ent = readdir(tmp->dir)))
	{
		if (cnt != NULL)
		{
			while (cnt)
				cnt = cnt->next;
		}
			cnt = creat_content(ent);
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

static void	read_content(t_larg *tmp)
{
	while (tmp->content)
	{
		ft_putendl(tmp->content->name);
		tmp->content = tmp->content->next;
	}
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
		ls_param->l_arg = creat_elem(str[arg]);
	else
		push_file_in_list(ls_param->l_arg, str[arg]);
	arg++;
    }
    ft_putstrnb("option value : ", ls_param->option);
	ls_param->l_arg = l_mod2(ls_param->l_arg, &l_sort_alpha);
	l_mod(ls_param->l_arg, &p_elem);
	l_mod(ls_param->l_arg, &read_content);
}

int	main(int a, char **b)
{
	arg_parser(a, b);
    return 0;
}




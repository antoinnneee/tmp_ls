
#include "../includes/ft_ls.h"
#include "../includes/read.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <sys/stat.h>

t_larg	*creat_content(struct dirent *ent)
{
	t_larg	*content;

	content = (t_larg*) ft_memalloc(sizeof(t_larg));
	content->name = ft_strdup(ent->d_name);
	content->next = NULL;
	return (content);
}

static t_larg	*push_content(t_larg *begin, struct dirent *str)
{
	t_larg	*tmp;
	t_larg	*index;

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

static void	standardize(char *str)
{
	unsigned int	i;

	i = ft_strlen(str);
	while(i > ft_strlen(str)-2)
	{
		if (str[i] == '/' && i > 0)
			str[i] = '\0';
		i--;
	}
}

static t_larg	*creat_elem(char *str)
{
	t_larg	*tmp;
	DIR	*dir;
	struct dirent *ent;
	t_larg *cnt;

	tmp = (t_larg*) ft_memalloc(sizeof(t_larg));
	tmp->name = ft_strdup(str);
	dir = opendir(str);
	tmp->state = 1;
	if (dir == NULL)
	{
		if (errno == ENOTDIR)
			tmp->state = 2;
		else
			tmp->state = 0;
			tmp->state = 3;
	}
	else
	{
		standardize(tmp->name);
		while ((ent = readdir(dir)))
			if (ft_strcmp(ent->d_name, "..") && ft_strcmp(ent->d_name, "."))
			{
				ft_putendl(ent->d_name);
				push_file_in_list(&tmp->content, secure_cat(secure_cat(tmp->name, "/"), ent->d_name));
				tmp->content = l_mod2(tmp->content, &l_sort_alpha);
			}
		//push_file_in_list(tmp->content, secure_cat(tmp->name, ent->d_name));
	}
	closedir(dir);
	return (tmp);
}

void	push_file_in_list(t_larg **begin, char *str)
{
	t_larg	*tmp;
	t_larg	*index;

	index = *begin;
	tmp = creat_elem(str);
	if (tmp->state)
	{
		if (!index)
		{
			*begin = tmp;
			return ;
		}
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
		if (tmp)
		{
				if (tmp->state == 1)
					read_content(tmp->content);
			ft_putstr("\nFOLDER :: ");
			ft_putendl(tmp->name);
			while (tmp->content)
			{
				ft_putendl(tmp->content->name);
				tmp->content = tmp->content->next;
			}
			ft_putstr("END OF FOLDER\n\n");
		}
}

static void	print_folder(t_larg *tmp)
{
	if (tmp->state == 1)
		ft_putendl(tmp->name);	
}

static void	print_file(t_larg *tmp)
{
	if (tmp->state == 2)
		ft_putendl(tmp->name);	
}

void 	arg_parser(int nbarg, char **str)
{
	int		arg;
	t_ls	*ls_param;

	ls_param = (t_ls*)ft_memalloc(sizeof(t_ls));
	ls_param->option = 0;
	ls_param->l_arg = NULL;
	arg = get_option(nbarg, str, ls_param);
	if (nbarg == arg)
	{
		push_file_in_list(&ls_param->l_arg, "./");
	}
    while (arg < nbarg)
    {
		push_file_in_list(&ls_param->l_arg, str[arg]);
	arg++;
    }
	ft_putstrnb("option value : ", ls_param->option);
	ls_param->l_arg = l_mod2(ls_param->l_arg, &l_sort_alpha);
	l_mod(ls_param->l_arg, &p_elem);
	ft_putendl("====== Print Folder ======");
	l_mod(ls_param->l_arg, &print_folder);	
	ft_putendl("====== Print File ======");
	l_mod(ls_param->l_arg, &print_file);	
	ft_putendl("====== Print Content ======");
	l_mod(ls_param->l_arg, &read_content);
}

int	main(int a, char **b)
{
	arg_parser(a, b);
    return 0;
}




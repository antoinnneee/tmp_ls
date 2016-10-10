
#include "../includes/ft_ls.h"
#include "../includes/read.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <sys/stat.h>

static t_larg	*alpha_sort(t_larg **begin);

unsigned int	set_option(unsigned int option, int state)
{
	static unsigned int opt = 0;
	static unsigned int arg = 0;

	if (state == 1)
		opt = option;
	else if (state == 2 && option != 0)
	{
			arg = option;
	}
	else if (state == 2)
			return (arg);
	return (opt);	
}

static char	*standardize(char *str)
{
	int	i;
	int	j;
	char 		*dest;
	

	i = ft_strlen(str);
	j = ft_strlen(str);
	while(i > 0)
	{
		if (str[i] == '/')
		{
			j = i;
			i = 0;
		}
		else if (ft_isprint(str[i]) && str[i] != ' ')
			i = 0;
		i--;
	}
	dest = (char*)ft_memalloc(sizeof(char) + j + 1);
	ft_strncpy(dest, str, j);
	dest[j] = '\0';
	free(str);
	return (dest);

}

static t_larg	*creat_elem(char **str, int state)
{
	t_larg	*tmp;
	DIR	*dir;
	struct dirent *ent;

	tmp = (t_larg*) ft_memalloc(sizeof(t_larg));
	if (!tmp)
		ft_putendl("ERROR!!!!");
	ft_bzero(&ent, sizeof(ent));
	tmp->name = ft_strdup(str);
	tmp->content = NULL;
	tmp->next = NULL;
	dir = opendir(str);
	lstat(str, &tmp->st);
	tmp->state = 1;
	tmp->name = standardize(tmp->name);
	if (dir == NULL)
	{
		tmp->state = 0;
		if (errno == ENOTDIR)
			tmp->state = 2;
		if (errno == ENOMEM)
		{
			ft_putendl("No more MEMORY");
			exit(0);
		}
		if (errno == EMFILE)
		{
			ft_putendl("Too many file descriptors");
			exit(0);
		}
		if (errno == ENFILE)
		{
			ft_putendl("Too many file open");
			exit(0);
		}
		if (errno == EBADF)
		{
			ft_putendl("Not valid fd");
			exit(0);
		}
		if (errno == EACCES)
		{
			ft_putendl("Permission denied");
			exit(0);
		}
		if (errno == ENOENT)
		{
			tmp->state = 2;
		}
	}
	else
	{
			if (state)
			{
				if (!(set_option(0,0) & (1U << 2)))
					state = 0;
				while ((ent = readdir(dir)))
				{
					if (!(ft_strcmp(ent->d_name, "..") && ft_strcmp(ent->d_name, ".")) || ent->d_name[0] == '.')
					{
						if (ft_strcmp(ent->d_name, "..") && ft_strcmp(ent->d_name, ".") && set_option(0, 0) & (1U << 3))
							push_file_in_list(&tmp->content, secure_cat(secure_cat(tmp->name, "/"), ent->d_name), state);	
						else if (set_option(0, 0) & (1U << 3))
							push_file_in_list(&tmp->content, secure_cat(secure_cat(tmp->name, "/"), ent->d_name), 0);
					}	
					else if (ft_strcmp(ent->d_name, "..") && ft_strcmp(ent->d_name, "."))
						push_file_in_list(&tmp->content, secure_cat(secure_cat(tmp->name, "/"), ent->d_name), state);
					else if ((set_option(0,0) & (1U << 3)))
						push_file_in_list(&tmp->content, secure_cat(secure_cat(tmp->name, "/"), ent->d_name), 0);
					tmp->content = alpha_sort(&tmp->content);
				}
			}
			else
				tmp->state = 2;
	}
	closedir(dir);
	return (tmp);
}

void	push_file_in_list(t_larg **begin, char *str, int state)
{
	t_larg	*tmp;
	t_larg	*index;

	index = *begin;
			//				add condition ici pour ajouter les "./.." a la liste
	
	tmp = creat_elem(str, state);
	if (tmp && tmp->state)
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
		//ft_putendl(index->name);
		index->next = tmp;
	}
	else
	{
		if (tmp)
		{
			if (state)
			{
				ft_putstr("ls: ");
				ft_putstr(tmp->name);
				ft_putendl(": No Such file or directory");
		}
		free(tmp->name);
		free(tmp);
		}
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
		ft_putstr(str[arg]);
		option_parser(str[arg], ls_param);
		arg++;
	}
	return (arg);
}

static void	free_content(t_larg *elem)
{
	t_larg *tmp;
	t_larg *tmp2;
	tmp = elem->content;
		if (tmp)
		{
			if (tmp->state != 2)
				free_content(tmp);
			while (tmp)
			{
				tmp2 = tmp;
				tmp = tmp->next;
				free(tmp2->name);
				free(tmp2);
			}
		}
}

static void	print_folder(t_larg *tmp)
{
	if (tmp->state == 1)
	{
		ft_putstr(tmp->name);	
		ft_putstr("/:\n");
	}
}

static void	print_file(t_larg *tmp)
{
	if (tmp->state == 2)
		ft_putendl(tmp->name);	
}

static void	print_content(t_larg **data)
{
	t_larg	*tmp;

	tmp = *data;
	while (tmp)
	{
		if (tmp != *data)
			ft_putstr("\n\n");
		if (set_option(0, 0) & (1U << 2))
			read_content(&tmp);
		else
			non_recursiv_read(&tmp);
			tmp = tmp->next;
	}
		ft_putchar('\n');
}

static int	is_list_sort(t_larg **begin)
{
	t_larg *elem;

	elem = (*begin);
	while(elem)
	{
		if (elem->next && elem->next->name)
			if (!is_sort(elem->name, elem->next->name))
				return (0);
		elem = elem->next;
	}
	return(1);
}

static void	ft_swap(t_larg **begin)
{
	t_larg	*first;
	t_larg	*last;
	t_larg	*tmp;

	first = *begin;
	last = first->next;
	tmp = last->next;
	last->next = first;
	first->next = tmp;
	*begin = last;
}

static t_larg	*alpha_sort(t_larg **data)
{
	t_larg	*tmp;

	tmp = *data;
		if (tmp != *data)
			ft_putstr("\n\n");
	while (!is_list_sort(&tmp))
	{
		if (!is_sort(tmp->name, tmp->next->name))
			ft_swap(data);
		else
			tmp = l_mod2(tmp, &l_sort_alpha);
	tmp = *data;
	}
		return (tmp);
}


void 	arg_parser(int nbarg, char **str)
{
	int		arg;
	t_ls	*ls_param;

	ls_param = (t_ls*) ft_memalloc(sizeof(t_ls));
	ls_param->option = 0;
	ls_param->l_arg = NULL;
	arg = get_option(nbarg, str, ls_param);
	set_option(ls_param->option, 1);
	set_option(nbarg - arg, 2);
	if (nbarg == arg)
	{
		push_file_in_list(&ls_param->l_arg, ".", 1);
	}
    while (arg < nbarg)
    {
		push_file_in_list(&ls_param->l_arg, str[arg], 1);
		arg++;
    }
	t_larg	*argument;
	ft_putstrnb(" --> option value : ", ls_param->option);
	argument = ls_param->l_arg;
	argument = alpha_sort(&argument);
//	ft_putendl("====== Print FOLDER ======");
//	l_mod(&argument, &print_folder);
//	ft_putendl("====== Print Content ======");
	print_content(&argument);
	l_mod(&argument, &free_content);
	free(ls_param);
}

int	main(int a, char **b)
{
	arg_parser(a, b);
    return 0;
}




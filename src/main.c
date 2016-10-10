/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abureau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 12:57:02 by abureau           #+#    #+#             */
/*   Updated: 2016/10/10 16:29:50 by abureau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/ft_ls.h"
#include "../includes/read.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <sys/stat.h>

static t_larg	*alpha_sort(t_larg **begin);
static t_larg	*time_sort(t_larg **begin);
static t_larg	*revalpha_sort(t_larg **data);

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

static t_larg	*sort(t_larg **data,int state)
{
	if (state)
	{
		return (time_sort(data));
	}
	else
		if (set_option(0, 0) & (1U << 4))
		return(revalpha_sort(data));
		else
		return(alpha_sort(data));
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

static t_larg	*creat_elem(char *str, int state)
{
	t_larg	*tmp;
	DIR	*dir;
	struct dirent *ent;
	int size;

	tmp = (t_larg*) ft_memalloc(sizeof(t_larg));
	if (!tmp)
		ft_putendl("ERROR!!!!");
	ft_bzero(&ent, sizeof(ent));
	tmp->name = ft_strdup(str);
	tmp->size = 0;
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
							size = (push_file_in_list(&tmp->content, secure_cat(secure_cat(tmp->name, "/"), ent->d_name), state));
						else if (set_option(0, 0) & (1U << 3))
							size = push_file_in_list(&tmp->content, secure_cat(secure_cat(tmp->name, "/"), ent->d_name), 0);
					}	
					else if (ft_strcmp(ent->d_name, "..") && ft_strcmp(ent->d_name, "."))
						size = push_file_in_list(&tmp->content, secure_cat(secure_cat(tmp->name, "/"), ent->d_name), state);
					else if ((set_option(0,0) & (1U << 3)))
						size = push_file_in_list(&tmp->content, secure_cat(secure_cat(tmp->name, "/"), ent->d_name), 0);
					tmp->content = sort(&tmp->content, 0);
					if ((set_option(0, 0) & (1U << 4)))
						tmp->content = sort(&tmp->content, 1);
					tmp->size += (size % 512) ? size / 512 + 1  : size / 512 ;
				}
			}
			else
				tmp->state = 2;
	closedir(dir);
	}
	return (tmp);
}

long long push_file_in_list(t_larg **begin, char *str, int state)
{
	t_larg	*tmp;
	t_larg	*index;

	index = *begin;
	tmp = creat_elem(str, state);
	if (tmp && tmp->state)
	{
		if (!index)
		{
			*begin = tmp;
			return (tmp->st.st_size);
		}
		while (index->next != NULL)
		{
			index = index->next;
		}
		//ft_putendl(index->name);
		index->next = tmp;
	return (tmp->st.st_size);
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
	return (0);
	}
}

static int	get_option(int nbarg, char **str, t_ls *ls_param)
{
	int	arg;
	arg = 1;

	while ((arg < nbarg) && (str[arg][0] == '-'))
	{
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


static int	is_list_sort_t(t_larg **begin)
{
	t_larg *elem;

	elem = (*begin);
	while(elem)
	{
		if (elem->next)
		{
			if (!is_sort_t(elem->st, elem->next->st))
			{
				return (0);
			}
		}
		elem = elem->next;
	}
	return(1);
}

static int	is_list_sort_ra(t_larg **begin)
{
	t_larg *elem;

	elem = (*begin);
	while(elem)
	{
		if (elem->next && elem->next->name)
			if (is_sort(elem->name, elem->next->name))
				return (0);
		elem = elem->next;
	}
	return(1);
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

static t_larg	*time_sort(t_larg **data)
{
	t_larg	*tmp;

	tmp = *data;
	while (!is_list_sort_t(&tmp))
	{
		if (!is_sort_t(tmp->st, tmp->next->st))
		{
					ft_swap(data);
		}
		else
		{
			tmp = l_mod2(tmp, &l_sort_time, 1);
		}
			tmp = *data;
	}
	return (tmp);
}

static t_larg	*revalpha_sort(t_larg **data)
{
	t_larg	*tmp;

	tmp = *data;
	while (!is_list_sort_ra(&tmp))
	{
		if (is_sort(tmp->name, tmp->next->name))
			ft_swap(data);
		else
			tmp = l_mod2(tmp, &l_sort_revalpha, 2);
		tmp = *data;
	}
	return (tmp);
}

static t_larg	*alpha_sort(t_larg **data)
{
	t_larg	*tmp;

	tmp = *data;
	while (!is_list_sort(&tmp))
	{
		if (!is_sort(tmp->name, tmp->next->name))
			ft_swap(data);
		else
			tmp = l_mod2(tmp, &l_sort_alpha, 0);
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




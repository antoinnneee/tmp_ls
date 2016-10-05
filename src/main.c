
#include "../includes/ft_ls.h"
#include "../includes/read.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <sys/stat.h>

unsigned int	set_option(unsigned int option, int state)
{
	static unsigned int opt = 0;
	if (state)
		opt = option;
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

static t_larg	*creat_elem(char *str)
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
			ft_putendl(str);
			ft_putendl("DIR NOT EXIST");
			exit(0);
		}
	}
	else
	{
		while ((ent = readdir(dir)))
		{
			if (ft_strcmp(ent->d_name, "..") && ft_strcmp(ent->d_name, "."))
			{
				push_file_in_list(&tmp->content, secure_cat(secure_cat(tmp->name, "/"), ent->d_name));
			}
				tmp->content = l_mod2(tmp->content, &l_sort_alpha);
		}
	}
	closedir(dir);
	return (tmp);
}

void	push_file_in_list(t_larg **begin, char *str)
{
	t_larg	*tmp;
	t_larg	*index;

	index = *begin;
			//				add condition ici pour ajouter les "./.." a la liste
	
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
		//ft_putendl(index->name);
		index->next = tmp;
	}
	else
	{
		ft_putstr("ls: ");
		ft_putstr(tmp->name);
		ft_putendl(": No Such file or directory");
		free(tmp->name);
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

static void	old_read_content(t_larg *elem)
{
	t_larg *tmp;
	tmp = elem->content;
	if (tmp)
	{
		if (tmp->state == 2)
		{
			ft_putstr("FOLDER : ");
			ft_putendl(elem->name);
		}
		while (tmp)
		{
			if (tmp != elem->content)
			ft_putendl(tmp->name);
			if (tmp->state != 2)
				read_content(tmp);
			tmp = tmp->next;
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

void 	arg_parser(int nbarg, char **str)
{
	int		arg;
	t_ls	*ls_param;

	ls_param = (t_ls*) ft_memalloc(sizeof(t_ls));
	ls_param->option = 0;
	ls_param->l_arg = NULL;
	arg = get_option(nbarg, str, ls_param);
	set_option(ls_param->option, 1);
	if (nbarg == arg)
	{
		push_file_in_list(&ls_param->l_arg, ".");
	}
    while (arg < nbarg)
    {
		push_file_in_list(&ls_param->l_arg, str[arg]);
		arg++;
    }
	t_larg	*argument;
	argument = ls_param->l_arg;
	ft_putstrnb("option value : ", ls_param->option);
	ls_param->l_arg = l_mod2(ls_param->l_arg, &l_sort_alpha);
	ft_putendl("====== Print FOLDER ======");
	l_mod(&argument, &print_folder);
//	ft_putendl("====== Print Content ======");
	read_content(&argument);
	l_mod(&argument, &free_content);
	free(ls_param);
}

int	main(int a, char **b)
{
	arg_parser(a, b);
    return 0;
}




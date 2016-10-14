#include "../includes/ft_ls.h"

static void			recur_statement(int *state, t_larg **tmp, DIR **dir)
{
	int	size;
	struct dirent *ent;

	size = 0;
	if (!(set_option(0,0) & (1U << 2)))
		*state = 0;
	while ((ent = readdir(*dir)))
	{
		if (!(ft_strcmp(ent->d_name, "..") && ft_strcmp(ent->d_name, ".")) || ent->d_name[0] == '.')
		{
			if (ft_strcmp(ent->d_name, "..") && ft_strcmp(ent->d_name, ".") && set_option(0, 0) & (1U << 3))
				size = (push_file(&(*tmp)->content, secure_cat(secure_cat((*tmp)->name, "/"), ent->d_name), *state));
			else if (set_option(0, 0) & (1U << 3))
				size = push_file(&(*tmp)->content, secure_cat(secure_cat((*tmp)->name, "/"), ent->d_name), 0);
		}	
		else if (ft_strcmp(ent->d_name, "..") && ft_strcmp(ent->d_name, "."))
			size = push_file(&(*tmp)->content, secure_cat(secure_cat((*tmp)->name, "/"), ent->d_name), *state);
		else if ((set_option(0,0) & (1U << 3)))
			size = push_file(&(*tmp)->content, secure_cat(secure_cat((*tmp)->name, "/"), ent->d_name), 0);
		(*tmp)->content = sort(&(*tmp)->content, 0);
		if ((set_option(0, 0) & (1U << 4)))
			(*tmp)->content = sort(&(*tmp)->content, 1);
		(*tmp)->size += (size % 512) ? size / 512 + 1  : size / 512 ;
	}
}

static t_larg		*creat_elem(char *str, int state)
{
	t_larg	*tmp;
	DIR	*dir;

	tmp = init_elem(str, &dir);
	if (dir == NULL)
		init_p_error(&tmp);
	else
	{
		if (state)
			recur_statement(&state, &tmp, &dir);
		else
			tmp->state = 2;
		closedir(dir);
	}
	return (tmp);
}

static void			f_p_err(t_larg **tmp, int state)
{
	if (state)
	{
		ft_putstr("ls: ");
		ft_putstr((*tmp)->name);
		ft_putendl(": No Such file or directory");
	}
	free((*tmp)->name);
	free((*tmp));
}

unsigned long long	push_file(t_larg **begin, char *str, int state)
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
			index = index->next;
		index->next = tmp;
		return (tmp->st.st_size);
	}
	else
	{
		if (tmp)
			f_p_err(&tmp, state);
		return (0);
	}
}



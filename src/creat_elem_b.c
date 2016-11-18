/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_elem_b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abureau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 12:26:27 by abureau           #+#    #+#             */
/*   Updated: 2016/11/18 19:16:58 by abureau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

char	*standardize(char *str)
{
	int		i;
	int		j;
	char	*dest;

	i = ft_strlen(str);
	j = ft_strlen(str);
	while (i > 0)
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

void	init_p_error(t_larg **tmp)
{
	(*tmp)->state = 0;
	if (errno == ENOTDIR)
		(*tmp)->state = 2;
	if (errno == ENOENT)
	{
		(*tmp)->state = 0;
		ft_putstr("ls: cannot acces ");
		if (!ft_strncmp((*tmp)->name, "//", 2))
			ft_putstr(&(*tmp)->name[1]);
		else
			ft_putstr((*tmp)->name);
		ft_putstr(": No such file or directory\n");
	}
	if (errno == EACCES)
	{
		(*tmp)->state = 3;
	}
	p_error();
}

void	p_error(void)
{
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
}

t_larg	*init_elem(char *str, DIR **dir)
{
	t_larg	*tmp;

	tmp = (t_larg*)ft_memalloc(sizeof(t_larg));
	if (!tmp)
		ft_putendl("ERROR!!!!");
	tmp->name = ft_strdup(str);
	tmp->size = 0;
	tmp->content = NULL;
	tmp->next = NULL;
	lstat(str, &tmp->st);
	tmp->state = 1;
	tmp->name = standardize(tmp->name);
	if ((tmp->st.st_mode & S_IFMT) == S_IFLNK)
	{
		tmp->state = 2;
	}
	*dir = opendir(str);
	tmp->dir = *dir;
	return (tmp);
}

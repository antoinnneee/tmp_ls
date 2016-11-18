/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abureau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 15:22:26 by abureau           #+#    #+#             */
/*   Updated: 2016/11/14 16:15:24 by abureau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void		color_set(t_larg *file)
{
	if ((file->st.st_mode & S_IFMT) == S_IFCHR)
		ft_putstr("\x1B[33m");
	else if ((file->st.st_mode & S_IFMT) == S_IFDIR)
		ft_putstr("\x1B[32m");
	else if ((file->st.st_mode & S_IFMT) == S_IFLNK)
		ft_putstr("\x1B[36m");
}

static void		read_e(t_larg *fold, t_larg *file)
{
	if (set_option(0, 0) & (1U << 1))
	{
		if (file->next)
			read_e(fold, file->next);
		color_set(file);
		print_elem(fold, file);
		ft_putstr("\x1B[0m");
		if (set_option(0, 0) & (1U << 0))
			ft_putchar('\n');
		else if (file->next)
			ft_putchar('\t');
	}
	else
	{
		color_set(file);
		print_elem(fold, file);
		ft_putstr("\x1B[0m");
		if (set_option(0, 0) & (1U << 0))
			ft_putchar('\n');
		else if (file->next)
			ft_putchar('\t');
		else
			ft_putchar('\n');
		if (file->next)
			read_e(fold, file->next);
	}
}

void			recur(t_larg **tmp)
{
	t_larg	*file;

	file = *tmp;
	if (set_option(0, 0) & (1U << 1))
	{
		if (file->next)
			recur(&file->next);
		if (file->state == 1)
		{
			ft_putchar('\n');
			read_content(&file);
		}
	}
	else
	{
		if (file->state == 1)
		{
			ft_putchar('\n');
			read_content(&file);
		}
		if (file->next)
			recur(&file->next);
	}
}

void			read_content(t_larg **begin)
{
	t_larg	*file;
	t_larg	*fold;
	t_larg	*tmp;

	fold = (*begin);
	tmp = NULL;
	if (*begin)
	{
		file = (*begin)->content;
		if (file)
			tmp = file;
		if (fold->state == 1)
		{
			ft_putstr("\x1B[31m");
			print_elem(fold, fold);
			ft_putstr("\x1B[0m");
		}
		non_recursiv_read(&fold);
		if (tmp)
			recur(&tmp);
	}
}

void			non_recursiv_read(t_larg **begin)
{
	t_larg	*file;
	t_larg	*fold;

	fold = (*begin);
	if (*begin)
	{
		if (fold->state == 1)
		{
			if (set_option(0, 2) > 1 || set_option(0, 0) & (1U << 2))
				print_fold(fold->name);
			if (set_option(0, 0) & (1U << 0))
				print_size(fold->size);
		}
		else if (fold->state == 3)
		{
			ft_putstr("ls : cannot open directory ");
			if (!ft_strncmp((fold)->name, "//", 2))
				ft_putstr(&(fold)->name[1]);
			else
				ft_putstr((fold)->name);
			ft_putstr(": permission denied\n");
		
		}
		file = (*begin)->content;
		if (file)
			read_e(fold, file);
	}
}

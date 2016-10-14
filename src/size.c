/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abureau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 14:41:20 by abureau           #+#    #+#             */
/*   Updated: 2016/10/14 14:49:57 by abureau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void			non_recursiv_size(t_larg **begin);
static void			size_content(t_larg **begin);

static void		read_e(t_larg **fold, t_larg **file, long long *size)
{
	if (*fold)
	{
		if (file)
		{
			*size += ((*file)->st.st_size % 512) ? (*file)->st.st_size / 512 + 1 : (*file)->st.st_size / 512;
			(*fold)->size = *size;
		}
		if ((*file)->next)
		{
			read_e(fold, &(*file)->next, size);
		}
	}
		//metre ici le clacul de la size//
}

static void			recur(t_larg **tmp)
{
	t_larg	*file;

	file = *tmp;
	if (set_option(0, 0) & (1U << 1))
	{
		if (file->next)
			recur(&file->next);
		if (file->state == 1)
		{
			read_content(&file);
		}
	}
	else
	{
		if (file->state == 1)
		{
			size_content(&file);
		}
		if (file->next)
			recur(&file->next);
	}
}

static void			size_content(t_larg **begin)
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
		non_recursiv_size(&fold);
		if (tmp)
			recur(&tmp);
	}
}

static void			non_recursiv_size(t_larg **begin)
{
	t_larg	*file;
	t_larg	*fold;
	long long		size;

	size = 0;
	fold = (*begin);
	if (*begin)
	{
		file = (*begin)->content;
		if (file)
			read_e(&fold, &file, &size);
	}
}

static void		size_cho(t_larg	**tmp)
{
	if (set_option(0, 0) & (1U << 2))
		size_content(tmp);
	else
		non_recursiv_size(tmp);
}

void			size_setter(t_larg **data)
{
	t_larg	*tmp;

	tmp = *data;
	if (tmp)
	{
			size_cho(&tmp);
			size_setter(&tmp->next);
	}
}

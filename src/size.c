/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abureau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 14:41:20 by abureau           #+#    #+#             */
/*   Updated: 2016/10/17 15:56:03 by abureau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void			read_e(t_larg **fold, t_larg **file, long long *size, int add)
{
	int	tmp;

	tmp = 0;
	if (*fold)
	{
		if (!(((*file)->st.st_mode & S_IFMT) == S_IFLNK))
		{
				
			tmp = (*file)->st.st_size % 1024;
			if (tmp == 0)
			{
					tmp = (*file)->st.st_size / 1024;
					if (tmp % 4 == 0)
						*size += (*file)->st.st_size / 1024 ;
					else
						*size += (*file)->st.st_size / 1024 + (4 - (tmp % 4));
			}
			else if ((((*file)->st.st_mode & S_IFMT) == S_IFDIR))
				;
			else
			{
				if ((*file)->st.st_size < 4096)
				*size +=  4;
				else
				{
					tmp = (*file)->st.st_size / 1024;
					if (tmp % 4 == 0)
						*size += (*file)->st.st_size / 1024 + 4;
					else
						*size += (*file)->st.st_size / 1024 + (4 - (tmp % 4));
				}
			}
			(*fold)->size = *size;
		}
		if ((*file)->next)
			read_e(fold, &(*file)->next, size, add + tmp);
	}
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

void				size_content(t_larg **begin)
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

void				non_recursiv_size(t_larg **begin)
{
	t_larg		*file;
	t_larg		*fold;
	long long	size;

	size = 0;
	fold = (*begin);
	if (*begin)
	{
		file = (*begin)->content;
		if (file)
			read_e(&fold, &file, &size, 0);
	}
}

void				size_setter(t_larg **data)
{
	t_larg	*tmp;

	tmp = *data;
	if (tmp)
	{
		size_cho(&tmp);
		size_setter(&tmp->next);
	}
}

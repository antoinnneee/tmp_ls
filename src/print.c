/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abureau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 13:29:21 by abureau           #+#    #+#             */
/*   Updated: 2016/11/18 20:58:21 by abureau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"
#include "../libft/includes/libft.h"
#include <pwd.h>
#include <sys/types.h>
#include <time.h>
#include <grp.h>

void			p_date(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(str);
	while (str[i] != ' ')
		i++;
	while (str[j] != ':')
		j--;
	while (i < j)
	{
		ft_putchar(str[i]);
		i++;
	}
}

static void		print_typerm(t_larg *file)
{
	print_type(file);
	print_perm(file);
}

void			print_elem(t_larg *fold, t_larg *file)
{
	char	*str;

	str = (char*)ft_memalloc(sizeof(char) + 256);
	if (file)
	{
		if (set_option(0, 0) & (1U << 0) && (file != fold))
		{
			print_typerm(file);
		}
		if (file == fold)
			fold_a(file);
		else
		{
			ft_putstr(&file->name[ft_strlen(fold->name) + 1]);
			if ((file->st.st_mode & S_IFMT) == S_IFLNK &&
					set_option(0, 0) & 1U << 0)
			{
				readlink(file->name, str, 256);
				ft_putstr(" -> ");
				ft_putstr(str);
			}
		}
	}
	free(str);
}

static void		print_cho(t_larg **tmp)
{
	if (set_option(0, 0) & (1U << 2))
		non_recursiv_read(tmp);
	else
		non_recursiv_read(tmp);
}

void			print_content(t_larg **data, t_larg **prev)
{
	t_larg	*tmp;

	tmp = *data;
	if (tmp)
	{
		print_cho(&tmp);
		if (tmp != *prev && !(set_option(0, 0) & (1U << 2)))
			ft_putstr("\n\n");
	}
}

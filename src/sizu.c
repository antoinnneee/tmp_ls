/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sizu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abureau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 15:30:03 by abureau           #+#    #+#             */
/*   Updated: 2016/11/18 19:57:37 by abureau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void				size_cho(t_larg **tmp)
{
	non_recursiv_size(tmp);
}

static void			some_test(int *state, t_larg **tmp, t_dir *ent)
{
	if (ft_strcmp(ent->d_name, "..") &&
			ft_strcmp(ent->d_name, ".") && set_option(0, 0) & (1U << 3))
	{
		push_file(&(*tmp)->content,
				secure_cat(secure_cat((*tmp)->name, "/"), ent->d_name), *state);
	}
	else if (set_option(0, 0) & (1U << 3))
	{
		push_file(&(*tmp)->content,
				secure_cat(secure_cat((*tmp)->name, "/"), ent->d_name), 1);
	}
}

void				recur_statement(int *state, t_larg **tmp, DIR **dir)
{
	struct dirent	*ent;

	*state = 0;
	while ((ent = readdir(*dir)))
	{
		if (!(ft_strcmp(ent->d_name, "..") &&
					ft_strcmp(ent->d_name, ".")) || ent->d_name[0] == '.')
			some_test(state, tmp, ent);
		else if (ft_strcmp(ent->d_name, "..") && ft_strcmp(ent->d_name, "."))
			push_file(&(*tmp)->content, secure_cat(
						secure_cat((*tmp)->name, "/"), ent->d_name), *state);
		else if ((set_option(0, 0) & (1U << 3)))
			push_file(&(*tmp)->content,
					secure_cat(secure_cat((*tmp)->name, "/"), ent->d_name), 0);
	}
}

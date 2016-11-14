/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_mod.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abureau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 12:51:11 by abureau           #+#    #+#             */
/*   Updated: 2016/10/17 12:52:32 by abureau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static int		chose_sort(t_larg *file1, t_larg *file2, int state)
{
	if (state == 1)
		return (is_sort_t(file1->st, file2->st));
	else if (state == 2)
		return (!is_sort(file1->name, file2->name));
	else
		return (is_sort(file1->name, file2->name));
}

t_larg			*sort_first(t_larg *begin)
{
	t_larg	*tmp;

	tmp = begin;
	while (!is_sort(tmp->name, tmp->next->name))
		tmp = swap_e(tmp, &tmp);
	begin = tmp;
	return (begin);
}

void			l_mod(t_larg **begin, void (*func)(t_larg*))
{
	t_larg	*tmp;

	tmp = *begin;
	if (begin)
	{
		while (tmp)
		{
			func(tmp);
			tmp = tmp->next;
		}
	}
}

static t_larg	*exec_func(t_larg *begin, void (*func)(t_larg*),
		t_larg *tmp, int state)
{
	while (tmp)
	{
		if (!tmp->next || !tmp->next->next)
			return (begin);
		if (!chose_sort(tmp->next, tmp->next->next, state))
		{
			func(tmp);
			tmp = tmp->next;
			tmp = begin;
			if (!chose_sort(tmp, tmp->next, state))
			{
				begin = tmp->next;
				tmp = begin;
			}
		}
		else
			tmp = tmp->next;
	}
	return (begin);
}

t_larg			*l_mod2(t_larg *begin, void (*func)(t_larg*), int state)
{
	t_larg	*tmp;

	tmp = begin;
	if (tmp)
	{
		if (tmp->next)
		{
			return (exec_func(begin, func, tmp, state));
		}
	}
	return (begin);
}

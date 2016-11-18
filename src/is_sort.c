/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abureau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 12:47:50 by abureau           #+#    #+#             */
/*   Updated: 2016/11/18 19:08:41 by abureau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		is_list_sort_t(t_larg **begin)
{
	t_larg	*elem;

	elem = (*begin);
	while (elem)
	{
		if (elem->next)
		{
			if (!t_s(elem, elem->next))
			{
				return (0);
			}
		}
		elem = elem->next;
	}
	return (1);
}

int		is_list_sort_ra(t_larg **begin)
{
	t_larg *elem;

	elem = (*begin);
	while (elem)
	{
		if (elem->next && elem->next->name)
			if (is_sort(elem->name, elem->next->name))
				return (0);
		elem = elem->next;
	}
	return (1);
}

int		is_list_sort(t_larg **begin)
{
	t_larg	*elem;

	elem = (*begin);
	while (elem)
	{
		if (elem->next && elem->next->name)
			if (!is_sort(elem->name, elem->next->name))
				return (0);
		elem = elem->next;
	}
	return (1);
}

t_larg	*sort(t_larg **data, int state)
{
	if (state)
	{
		return (time_sort(data));
	}
	else
	{
		return (alpha_sort(data));
	}
}

void	ft_swap(t_larg **begin)
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

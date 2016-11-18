/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abureau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 12:58:27 by abureau           #+#    #+#             */
/*   Updated: 2016/10/17 12:59:14 by abureau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int	t_s(t_larg *tmp, t_larg *tnext)
{
	if (tmp->st.st_mtime < tnext->st.st_mtime)
		return (0);
	else if (tmp->st.st_mtime == tnext->st.st_mtime)
	{
		if (is_sort(tmp->name, tnext->name))
			return (1);
		else
			return (0);
	}
	else
		return (1);
}
t_larg	*swap_elem(t_larg *begin, t_larg *prev)
{
	t_larg	*elemf;
	t_larg	*eleml;
	t_larg	*tmp;

	elemf = begin;
	eleml = elemf->next;
	tmp = eleml->next;
	eleml->next = elemf;
	elemf->next = tmp;
	begin = eleml;
	prev->next = begin;
	return (begin);
}

t_larg	*revalpha_sort(t_larg **data)
{
	t_larg	*tmp;

	tmp = *data;
	while (!is_list_sort_ra(&tmp))
	{
		if (is_sort(tmp->name, tmp->next->name))
			ft_swap(data);
		else
			tmp = l_mod2(tmp, &l_sort_revalpha, 2);
		tmp = *data;
	}
	return (tmp);
}

t_larg	*alpha_sort(t_larg **data)
{
	t_larg	*tmp;

	tmp = *data;
	while (!is_list_sort(&tmp))
	{
		if (!is_sort(tmp->name, tmp->next->name))
			ft_swap(data);
		else
			tmp = l_mod2(tmp, &l_sort_alpha, 0);
		tmp = *data;
	}
	return (tmp);
}

t_larg	*time_sort(t_larg **data)
{
	t_larg	*tmp;

	tmp = *data;
	while (!is_list_sort_t(&tmp))
	{
		//if (!is_sort_t(tmp->st, tmp->next->st))
		if (!t_s(tmp, tmp->next))
		{
			ft_swap(data);
		}
		else
		{
			tmp = l_mod2(tmp, &l_sort_time, 1);
		}
		tmp = *data;
	}
	return (tmp);
}

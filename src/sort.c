/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abureau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 12:56:07 by abureau           #+#    #+#             */
/*   Updated: 2016/10/17 15:36:18 by abureau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"
#include "../libft/includes/libft.h"

int		is_sort(char *s1, char *s2)
{
	while (*s1 == *s2 && *s1 && *s2)
		ft_inctwovar((int *)&s1, (int*)&s2);
	if (*s1 == *s2 && !*s1)
		return (1);
	else if (!*s2)
		return (0);
	else if (!*s1)
		return (1);
	if (*s1 < *s2)
		return (1);
	else
		return (0);
}

int		is_sort_t(struct stat st1, struct stat st2)
{
	if (st1.st_mtime < st2.st_mtime)
		return (0);
	else
		return (1);
}

void	l_sort_time(t_larg *elem)
{
	t_larg	*prev;

	prev = elem;
	if (elem->next)
		if (elem->next->next)
			if (!is_sort_t(elem->next->st, elem->next->next->st))
				elem->next = (swap_elem(elem->next, prev));
}

void	l_sort_revalpha(t_larg *elem)
{
	t_larg	*prev;

	prev = elem;
	if (elem->next)
		if (elem->next->next)
			if (is_sort(elem->next->name, elem->next->next->name))
				elem->next = (swap_elem(elem->next, prev));
}

void	l_sort_alpha(t_larg *elem)
{
	t_larg	*prev;

	prev = elem;
	if (elem->next)
		if (elem->next->next)
			if (!is_sort(elem->next->name, elem->next->next->name))
				elem->next = (swap_elem(elem->next, prev));
}

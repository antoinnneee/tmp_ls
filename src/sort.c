/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abureau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 12:56:07 by abureau           #+#    #+#             */
/*   Updated: 2016/09/16 15:16:59 by abureau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"
#include "../libft/includes/libft.h"

static int	ft_issymbol(char s1)
{
	if (ft_isprint(s1) && !ft_isalnum(s1))
		return (1);
	else
		return (0);
}

static int	comp_alpha(char s1, char s2)
{
		if (s1 >= 'a')
		{
			if (s2 >= 'a')
				return ((s1 < s2) ? 1 : 0);
			if (s2 < 'a')
				return (0);
		}
		else
		{
			if (s2 >= 'a')
				return (1);
			if (s2 < 'a')
				return ((s1 < s2) ? 1 : 0);
		}
	return (0);
}

int			is_sort(char *s1, char *s2)
{
	while (*s1 == *s2 && *s1 && *s2)
		ft_inctwovar((int *)&s1, (int*)&s2);
	if (*s1 == *s2 && !*s1)
		return (1);
	else if (!*s2)
		return (0);
	else if (!*s1)
		return (1);
	if (*s1 < 0)
	{
		if (*s2 < 0)
		{
			return ((*s1 <= *s2) ? 1 : 0);
		}
		else
			return (0);
	}
	if (*s2 < 0)
	{
		if (*s1 < 0)
		{
			return ((*s1 <= *s2) ? 1 : 0);
		}
		else 
			return (1);
	}
	if (*s1 < *s2)
		return (1);
	if (*s1 < *s2)
		return (1);
	else
		return (0);
	return (0);
}

t_larg	*swap_elem(t_larg *begin, t_larg *prev)
{
	t_larg	*elemF;
	t_larg	*elemL;
	t_larg	*tmp;

	elemF = begin;
	elemL = elemF->next;
	tmp = elemL->next;
	elemL->next = elemF;
	elemF->next = tmp;
	begin = elemL;
	prev->next = begin;
	return (begin);
}

void	l_sort_alpha(t_larg *elem)
{
	t_larg *prev;
	prev = elem;
	if (elem->next)
		if (elem->next->next)
			if (!is_sort(elem->next->name, elem->next->next->name))
				elem->next = (swap_elem(elem->next, prev));
}

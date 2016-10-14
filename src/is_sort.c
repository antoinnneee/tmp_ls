#include "../includes/ft_ls.h"

int		is_list_sort_t(t_larg **begin)
{
	t_larg *elem;

	elem = (*begin);
	while(elem)
	{
		if (elem->next)
		{
			if (!is_sort_t(elem->st, elem->next->st))
			{
				return (0);
			}
		}
		elem = elem->next;
	}
	return(1);
}

int		is_list_sort_ra(t_larg **begin)
{
	t_larg *elem;

	elem = (*begin);
	while(elem)
	{
		if (elem->next && elem->next->name)
			if (is_sort(elem->name, elem->next->name))
				return (0);
		elem = elem->next;
	}
	return(1);
}

int		is_list_sort(t_larg **begin)
{
	t_larg *elem;

	elem = (*begin);
	while(elem)
	{
		if (elem->next && elem->next->name)
			if (!is_sort(elem->name, elem->next->name))
				return (0);
		elem = elem->next;
	}
	return(1);
}

t_larg	*sort(t_larg **data,int state)
{
	if (state)
	{
		return (time_sort(data));
	}
	else
		if (set_option(0, 0) & (1U << 4))
			return(revalpha_sort(data));
		else
			return(alpha_sort(data));
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

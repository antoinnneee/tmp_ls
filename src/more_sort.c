#include "../includes/ft_ls.h"

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
		if (!is_sort_t(tmp->st, tmp->next->st))
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

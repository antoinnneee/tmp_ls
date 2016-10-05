
#include "../libft/includes/libft.h"
#include "../includes/ft_ls.h"

void	l_f_mod(t_larg **begin)
{
	t_larg	*tmp;
	t_larg	*fold;
	int	i;

	fold = (*begin);
	i = 0;
	if (*begin)
	{
	tmp = (*begin)->content;
		while (tmp)
		{
				ft_putendl(tmp->name);
			tmp = tmp->next;
			if (tmp && (set_option(0, 0) & (1U << 2)))
			{
				if (tmp->state != 2)
					l_f_mod(&tmp);
			}
		}
	}
}

void	read_content(t_larg **begin)
{
	t_larg	*tmp;
	t_larg	*fold;

	fold = (*begin);
	if (*begin)
	{
		tmp = (*begin)->content;
		while (tmp)
		{
			if (!(set_option(0, 0) & (1U << 2)))
					ft_putstr(&tmp->name[ft_strlen(fold->name) + 1]);
			if (tmp && (set_option(0, 0) & (1U << 2)))
			{
				ft_putstr("/:\n");
				if (tmp->state != 2)
					l_f_mod(&tmp);
			}
			ft_putchar('\t');
			tmp = tmp->next;
		}
			ft_putchar('\n');
	}
}

void	option_parser(char *str, t_ls *option)
{

	while (*str != 0 )
	{
		ft_putchar(*str);
		ft_putendl("=================");
		if (*str != 0)
		{
			if (*str == 'l')
				option->option = option->option | (1U << 0);
			else if (*str == 'r')
				option->option = option->option | (1U << 1);
			else if (*str == 'R')
				option->option = option->option | (1U << 2);
			else if (*str == 'a')
				option->option = option->option | (1U << 3);
			else if (*str == 't')
				option->option = option->option | (1U << 4);
			else if (*str == '-')
				;
			else
			{
			ft_putendl("invalid option Phoque !");
			free(option);
			exit(-42);
		}
	}
	    str++;
	}
}

void	p_elem(t_larg *elem)
{
	if (elem)
		ft_putendl(elem->name);
}

void	l_mod(t_larg	**begin, void (*func)(t_larg*))
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


static t_larg	*swap_e(t_larg *begin, t_larg **prev)
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
	(*prev) = begin;
	return (begin);
}

static t_larg	*sort_first(t_larg *begin, t_larg **adr)
{
	t_larg	*tmp;

	tmp = begin;
	while(!is_sort(tmp->name, tmp->next->name))
		tmp = swap_e(tmp, &tmp);
	begin = tmp;
	return(begin);
}

t_larg	*l_mod2(t_larg	*begin, void (*func)(t_larg*))
{
	t_larg	*tmp;
	t_larg	**t2;
	tmp = begin;
	if (tmp)
	{
		if (tmp->next)
		{
		while (tmp)
		{
			if (!tmp->next)
				return (begin);
			if (!tmp->next->next)
				return (begin) ;
				if (!is_sort(tmp->next->name, tmp->next->next->name))
				{
					func(tmp);
					tmp = tmp->next;
					tmp = begin;
					if (!is_sort(tmp->name, tmp->next->name))
					{
							begin = tmp->next;
							tmp = begin;
					}
				}
				else
					tmp = tmp->next;
		}
		}
	}
	return (begin);
}







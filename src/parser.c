
#include "../libft/includes/libft.h"
#include "../includes/ft_ls.h"
#include <stdio.h>
#include <pwd.h>
#include <sys/types.h>
#include <time.h>
#include <grp.h>

void			l_f_mod(t_larg **begin)
{
	t_larg	*tmp;

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

static void		err_option(t_ls *option)
{
	ft_putendl("invalid option Phoque !");
	free(option);
	exit(-42);
}

void			option_parser(char *str, t_ls *option)
{

	while (*str != 0 )
	{
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
				err_option(option);
		}
		str++;
	}
}

t_larg			*swap_e(t_larg *begin, t_larg **prev)
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



#include "../libft/includes/libft.h"
#include "../includes/ft_ls.h"
#include <stdio.h>
#include <pwd.h>
#include <sys/types.h>
#include <time.h>
#include <grp.h>


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
	t_larg	*file;
	t_larg	*fold;
	t_larg	*tmp;

	fold = (*begin);
	tmp = NULL;
	if (*begin)
	{
		file = (*begin)->content;
		if (file)
			tmp = file;
		print_elem(fold, fold);
		while (tmp)
		{
			while (file)
			{
				if (set_option(0, 0) & (1U << 0))
					ft_putstr("\n");
				print_elem(fold, file);
				file = file->next;
			}
			if (tmp->state == 1)
			{
			ft_putstr("\n");
			ft_putstr("\n");
				read_content(&tmp);
//				ft_putstr("total : ");
//				ft_putnbr(file->size);
			}
			tmp = tmp->next;
		}
	}
}

void	non_recursiv_read(t_larg **begin)
{
	t_larg	*file;
	t_larg	*fold;
	t_larg	*tmp;

	fold = (*begin);
	tmp = NULL;
	if (*begin)
	{
		if (fold->state == 1)
		{
			if (set_option(0, 2) > 1)
			{
				ft_putstr(fold->name);
				ft_putstr(":\n");
			}
		if (set_option(0, 0) & (1U << 0))
		{
			ft_putstr("total : ");
				ft_putnbr(fold->size);
			ft_putendl("");
		}
		}
		else
			print_elem(fold, fold);
		file = (*begin)->content;	
//		if (set_option(0, 0) & (1 << 3))
//			ft_putstr(".\t..\t");
		while (file)
		{
			if (fold->content != file && set_option(0, 0) & (1U << 0))
				ft_putstr("\n");
			print_elem(fold, file);
			file = file->next;
		}
	}
}

void	option_parser(char *str, t_ls *option)
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
			{
			ft_putendl("invalid option Phoque !");
			free(option);
			exit(-42);
		}
	}
	    str++;
	}
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

t_larg	*sort_first(t_larg *begin)
{
	t_larg	*tmp;

	tmp = begin;
	while(!is_sort(tmp->name, tmp->next->name))
		tmp = swap_e(tmp, &tmp);
	begin = tmp;
	return(begin);
}

static	int	chose_sort(t_larg *file1, t_larg	*file2,int state)
{
	if (state == 1)
		return (is_sort_t(file1->st, file2->st));
	else if (state == 2)
		return (!is_sort(file1->name, file2->name));
	else
		return (is_sort(file1->name, file2->name));
}

t_larg	*l_mod2(t_larg	*begin, void (*func)(t_larg*), int state)
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
		}
	}
	return (begin);
}

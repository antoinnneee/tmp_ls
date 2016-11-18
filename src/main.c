/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abureau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 12:57:02 by abureau           #+#    #+#             */
/*   Updated: 2016/11/14 16:18:54 by abureau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <sys/stat.h>

unsigned int	set_option(unsigned int option, int state)
{
	static unsigned int	opt = 0;
	static unsigned int	arg = 0;

	if (state == 1)
		opt = option;
	else if (state == 2 && option != 0)
	{
		arg = option;
	}
	else if (state == 2)
		return (arg);
	return (opt);
}

static int		get_option(int nbarg, char **str, t_ls *ls_param)
{
	int	arg;

	arg = 1;
	while ((arg < nbarg) && (str[arg][0] == '-'))
	{
		option_parser(str[arg], ls_param);
		arg++;
	}
	return (arg);
}

static void		free_content(t_larg *elem)
{
	t_larg	*tmp;
	t_larg	*tmp2;

	tmp = elem->content;
	if (tmp)
	{
		while (tmp)
		{
			tmp2 = tmp;
			tmp = tmp->next;
			free(tmp2->name);
			free(tmp2);
		}
	}
}

static void		init_p(int nbarg, char **str, t_ls **ls_param, int arg)
{

	if (nbarg == arg)
		init_file(&(*ls_param)->l_arg, ".", 1);
	while (arg < nbarg)
	{
		init_file(&(*ls_param)->l_arg, str[arg], 1);
		arg++;
	}

}

static t_larg	*reverse(t_larg *liste)
{
    t_larg	*nouvelle_liste = 0;
    t_larg	*suivant = 0;

    while (liste) {
	suivant = liste->next;
	liste->next = nouvelle_liste;
	nouvelle_liste = liste;
	liste = suivant;
    }
    return (nouvelle_liste);
}

static void		process(t_larg	**fold, int state)
{
	int test;
	t_larg	*argument;
	t_larg	*art;

	argument = *fold;
	while (argument)
	{
		test = 0;
		if (argument->state == 2 && state == 1)
		{
			print_elem(argument, argument);	
		}
		else if (argument->state == 1)
		{
			if ((set_option(0, 0) & (1U << 2)) || state)
				recur_statement( &test, &argument ,&argument->dir);
			if ((set_option(0, 0) & (1U << 4)))
				argument->content = sort(&argument->content, 1);
			else
				argument->content = sort(&argument->content, 0);
			if ((set_option(0, 0) & (1U << 1)))
				argument->content = reverse(argument->content);
			size_setter(&argument);
			print_content(&argument, &argument);
		}
		else if (argument->state == 3)
		{
			print_content(&argument, &argument);
		}
		closedir(argument->dir);
		if (argument->content && set_option(0, 0) & (1U << 2))
			process(&argument->content, 0);
		art = argument;
		argument = argument->next;
		l_mod(&art, &free_content);
	}
}


void			arg_parser(int nbarg, char **str)
{
	int		arg;
	t_ls	*ls_param;
	t_larg	*argument;
	t_larg	*content;

	ls_param = (t_ls*)ft_memalloc(sizeof(t_ls));
	ls_param->option = 0;
	ls_param->l_arg = NULL;
	arg = get_option(nbarg, str, ls_param);
	set_option(ls_param->option, 1);
	set_option(nbarg - arg, 2);
	init_p(nbarg, str, &ls_param, arg);	
	argument = ls_param->l_arg;
	if ((set_option(0, 0) & (1U << 4)))
		argument = sort(&argument, 1);
    else
		argument = sort(&argument, 0);
    if ((set_option(0, 0) & (1U << 1)))
		argument = reverse(argument);
    process(&argument, 1);
    argument = ls_param->l_arg;
    free(ls_param);
}

int				main(int a, char **b)
{
    arg_parser(a, b);
    return (0);
}

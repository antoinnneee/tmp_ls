/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abureau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 19:25:00 by abureau           #+#    #+#             */
/*   Updated: 2016/11/18 21:52:05 by abureau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void			init_p(int nbarg, char **str, t_ls **ls_param, int arg)
{
	if (nbarg == arg)
		init_file(&(*ls_param)->l_arg, ".", 1);
	while (arg < nbarg)
	{
		init_file(&(*ls_param)->l_arg, str[arg], 1);
		arg++;
	}
}

t_larg			*reverse(t_larg *liste)
{
	t_larg	*nouvelle_liste;
	t_larg	*suivant;

	nouvelle_liste = NULL;
	suivant = NULL;
	while (liste)
	{
		suivant = liste->next;
		liste->next = nouvelle_liste;
		nouvelle_liste = liste;
		liste = suivant;
	}
	return (nouvelle_liste);
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

static void		p_as(int state, int test, t_larg **argument)
{
	if ((set_option(0, 0) & (1U << 2)) || state)
		recur_statement(&test, argument, &(*argument)->dir);
	if ((set_option(0, 0) & (1U << 4)))
		(*argument)->content = sort(&(*argument)->content, 1);
	else
		(*argument)->content = sort(&(*argument)->content, 0);
	if ((set_option(0, 0) & (1U << 1)))
		(*argument)->content = reverse((*argument)->content);
	size_setter(argument);
	print_content(argument, argument);
}

void			process(t_larg **fold, int state)
{
	int		test;
	t_larg	*argument;
	t_larg	*art;

	argument = *fold;
	test = 1;
	while (argument)
	{
		test = 0;
		if (argument->state == 2 && state == 1)
			print_elem(argument, argument);
		else if (argument->state == 1)
			p_as(state, test, &argument);
		else if (argument->state == 3)
			print_content(&argument, &argument);
		if (argument->dir)
			closedir(argument->dir);
		if (argument->content && set_option(0, 0) & (1U << 2))
		{
			process(&argument->content, 0);
		}
		art = argument;
		argument = argument->next;
		l_mod(&art, &free_content);
	}
}

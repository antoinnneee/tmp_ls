/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abureau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 12:57:02 by abureau           #+#    #+#             */
/*   Updated: 2016/10/10 16:29:50 by abureau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/ft_ls.h"
#include "../includes/read.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <sys/stat.h>

unsigned int	set_option(unsigned int option, int state)
{
	static unsigned int opt = 0;
	static unsigned int arg = 0;

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

static int	get_option(int nbarg, char **str, t_ls *ls_param)
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

static void	free_content(t_larg *elem)
{
	t_larg *tmp;
	t_larg *tmp2;
	tmp = elem->content;
	if (tmp)
	{
		if (tmp->state != 2)
			free_content(tmp);
		while (tmp)
		{
			tmp2 = tmp;
			tmp = tmp->next;
			free(tmp2->name);
			free(tmp2);
		}
	}
}

void 	arg_parser(int nbarg, char **str)
{
	int		arg;
	t_ls	*ls_param;

	ls_param = (t_ls*) ft_memalloc(sizeof(t_ls));
	ls_param->option = 0;
	ls_param->l_arg = NULL;
	arg = get_option(nbarg, str, ls_param);
	set_option(ls_param->option, 1);
	set_option(nbarg - arg, 2);
	if (nbarg == arg)
	{
		push_file(&ls_param->l_arg, ".", 1);
	}
	while (arg < nbarg)
	{
		push_file(&ls_param->l_arg, str[arg], 1);
		arg++;
	}
	t_larg	*argument;
	argument = ls_param->l_arg;
	argument = alpha_sort(&argument);
	print_content(&argument, &argument);
	l_mod(&argument, &free_content);
	free(ls_param);
}

int	main(int a, char **b)
{
	arg_parser(a, b);
	return 0;
}

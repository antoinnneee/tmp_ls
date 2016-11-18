/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abureau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 12:57:02 by abureau           #+#    #+#             */
/*   Updated: 2016/11/18 19:32:32 by abureau          ###   ########.fr       */
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

void			arg_parser(int nbarg, char **str)
{
	int		arg;
	t_ls	*ls_param;
	t_larg	*argument;

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

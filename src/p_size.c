/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_size.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abureau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 19:52:22 by abureau           #+#    #+#             */
/*   Updated: 2016/11/18 22:06:33 by abureau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "../includes/ft_ls.h"

void	p_denied(t_larg *fold)
{
	print_fold(fold->name);
	ft_putstr("ls : cannot open directory ");
	ft_putstr((ft_strncmp((fold)->name, "//", 2)) ? (fold)->name
			: &(fold)->name[1]);
	ft_putstr(": permission denied\n");
}

void	print_type(t_larg *file)
{
	if ((file->st.st_mode & S_IFMT) == S_IFREG)
		ft_putchar('-');
	else if ((file->st.st_mode & S_IFMT) == S_IFDIR)
	{
		ft_putchar('d');
	}
	else if ((file->st.st_mode & S_IFMT) == S_IFCHR)
		ft_putchar('c');
	else if ((file->st.st_mode & S_IFMT) == S_IFLNK)
		ft_putchar('l');
	else if ((file->st.st_mode & S_IFMT) == S_IFBLK)
		ft_putchar('b');
	else if ((file->st.st_mode & S_IFMT) == S_IFIFO)
		ft_putchar('p');
	else if ((file->st.st_mode & S_IFMT) == S_IFSOCK)
		ft_putchar('s');
	else
		ft_putchar('-');
}

void	print_fold(char *str)
{
	static int	first = 1;

	if (first)
	{
		ft_putstr("\x1B[31m");
		first = 0;
	}
	else
	{
		ft_putstr("\n\x1B[31m");
	}
	if (!ft_strncmp(str, "//", 2))
		ft_putstr(&str[1]);
	else
		ft_putstr(str);
	ft_putstr(":\n");
	ft_putstr("\x1B[0m");
}

void	print_size(unsigned long long size)
{
	char	*strsize;

	ft_putstr("total : ");
	strsize = ft_lltoa_base((t_64)size, 10, 0);
	ft_putendl(strsize);
	free(strsize);
}

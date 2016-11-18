/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_addon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abureau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 15:20:36 by abureau           #+#    #+#             */
/*   Updated: 2016/11/18 20:57:23 by abureau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"
#include "../libft/includes/libft.h"
#include <pwd.h>
#include <sys/types.h>
#include <time.h>
#include <grp.h>
#include <stdio.h>

static void	p_s(int value, int max)
{
	int	len;
	int	space;

	len = intlen(value);
	space = max - len;
	while (space)
	{
		space--;
		ft_putchar(' ');
	}
	ft_putnbr(value);
}

static void	pr_size(t_larg *filestat)
{
	if ((filestat->st.st_mode & S_IFMT) == S_IFCHR)
	{
		p_s((filestat->st.st_rdev >> 24), 5);
		ft_putstr(",");
		p_s(filestat->st.st_rdev & 0xFF, 5);
	}
	else
		p_s(filestat->st.st_size, 9);
}

void		print_perm(t_larg *filestat)
{
	ft_putchar((filestat->st.st_mode & S_IRUSR) ? 'r' : '-');
	ft_putchar((filestat->st.st_mode & S_IWUSR) ? 'w' : '-');
	ft_putchar((filestat->st.st_mode & S_IXUSR) ? 'x' : '-');
	ft_putchar((filestat->st.st_mode & S_IRGRP) ? 'r' : '-');
	ft_putchar((filestat->st.st_mode & S_IWGRP) ? 'w' : '-');
	ft_putchar((filestat->st.st_mode & S_IXGRP) ? 'x' : '-');
	ft_putchar((filestat->st.st_mode & S_IROTH) ? 'r' : '-');
	ft_putchar((filestat->st.st_mode & S_IWOTH) ? 'w' : '-');
	ft_putchar((filestat->st.st_mode & S_IXOTH) ? 'x' : '-');
	ft_putchar(' ');
	ft_putnbr(filestat->st.st_nlink);
	ft_putchar(' ');
	ft_putstr(getpwuid(filestat->st.st_uid)->pw_name);
	ft_putchar('\t');
	ft_putstr(getgrgid(filestat->st.st_gid)->gr_name);
	ft_putchar('\t');
	pr_size(filestat);
	ft_putchar('\t');
	p_date(ctime(&filestat->st.st_mtime));
	ft_putchar(' ');
}

void		fold_a(t_larg *file)
{
	if ((file->st.st_mode & S_IFMT) == S_IFDIR)
	{
		ft_putstr(file->name);
		ft_putstr(":\n");
	}
	else if (set_option(0, 0) & (1U << 0))
	{
		print_type(file);
		print_perm(file);
		ft_putendl(file->name);
		ft_putstr("\x1B[0m");
	}
	else
	{
		ft_putendl(file->name);
	}
}

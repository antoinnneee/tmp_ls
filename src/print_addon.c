/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_addon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abureau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 15:20:36 by abureau           #+#    #+#             */
/*   Updated: 2016/11/14 15:45:05 by abureau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"
#include "../libft/includes/libft.h"
#include <pwd.h>
#include <sys/types.h>
#include <time.h>
#include <grp.h>
#include <stdio.h>

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

void	print_perm(t_larg *filestat)
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
	ft_putnbr(filestat->st.st_size);
	ft_putchar('\t');
	p_date(ctime(&filestat->st.st_mtime));
	ft_putchar(' ');
}

void	print_fold(char *str)
{
		ft_putstr("\x1B[31m");
	ft_putchar('\n');
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

void	fold_a(t_larg *file)
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

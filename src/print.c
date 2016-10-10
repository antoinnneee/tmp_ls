/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abureau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 13:29:21 by abureau           #+#    #+#             */
/*   Updated: 2016/10/10 16:44:12 by abureau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"
#include "../libft/includes/libft.h"
#include <pwd.h>
#include <sys/types.h>
#include <time.h>
#include <grp.h>

static void	print_type(t_larg *file)
{
	if ((file->st.st_mode & S_IFMT) == S_IFREG)
		ft_putchar('-');
	else if ((file->st.st_mode & S_IFMT) == S_IFDIR)
		ft_putchar('d');
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

static void	p_date(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(str);
	while (str[i] != ' ')
		i++;	
	while (str[j] != ':')
		j--;
	while(i < j)
	{
		ft_putchar(str[i]);
		i++;
	}
}

static void	print_perm(t_larg *fileStat)
{
    ft_putchar( (fileStat->st.st_mode & S_IRUSR) ? 'r' : '-');
    ft_putchar( (fileStat->st.st_mode & S_IWUSR) ? 'w' : '-');
    ft_putchar( (fileStat->st.st_mode & S_IXUSR) ? 'x' : '-');
    ft_putchar( (fileStat->st.st_mode & S_IRGRP) ? 'r' : '-');
    ft_putchar( (fileStat->st.st_mode & S_IWGRP) ? 'w' : '-');
    ft_putchar( (fileStat->st.st_mode & S_IXGRP) ? 'x' : '-');
    ft_putchar( (fileStat->st.st_mode & S_IROTH) ? 'r' : '-');
    ft_putchar( (fileStat->st.st_mode & S_IWOTH) ? 'w' : '-');
    ft_putchar( (fileStat->st.st_mode & S_IXOTH) ? 'x' : '-');
	ft_putchar(' ');
	ft_putnbr(fileStat->st.st_nlink);
	ft_putchar(' ');
	ft_putstr(getpwuid(fileStat->st.st_uid)->pw_name);
	ft_putchar('\t');
	ft_putstr(getgrgid(fileStat->st.st_gid)->gr_name);
	ft_putchar('\t');
    	ft_putnbr(fileStat->st.st_size);
	ft_putchar('\t');
 	p_date(ctime(&fileStat->st.st_mtime));
	ft_putchar(' ');
}

void	print_elem(t_larg *fold, t_larg *file)
{
	char	*str;

	str = (char*) ft_memalloc(sizeof(char) + 256);
	if (file)
	{
		if (set_option(0, 0) & (1U << 0) && (file != fold))
		{
			print_type(file);
			print_perm(file);
		}
		if (file == fold)
		{
			ft_putstr(file->name);
			ft_putstr(":\n");
			if (set_option(0, 0) & 1U << 0)
			{
			ft_putstr("total : ");
			ft_putnbr(file->size);
			}
		}
		else
		{
			ft_putstr(&file->name[ft_strlen(fold->name) + 1]);
			if ((file->st.st_mode & S_IFMT) == S_IFLNK && set_option(0, 0) & 1U << 0)
			{
				readlink(file->name, str, 256);
				ft_putstr(" -> ");
				ft_putstr(str);
			}
		}
		if (set_option(0, 0) & (1U << 0))
			;
		else
			ft_putstr("\t");
	}
}

void	print_content(t_larg **data)
{
	t_larg	*tmp;

	tmp = *data;
	while (tmp)
	{
		if (tmp != *data && !(set_option(0, 0) & (1U << 2)))
			ft_putstr("\n\n");
		if (set_option(0, 0) & (1U << 2))
			read_content(&tmp);
		else
			non_recursiv_read(&tmp);
			tmp = tmp->next;
	}
		ft_putchar('\n');
}

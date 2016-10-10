
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

static void	print_type(t_larg *file)
{
// S_IFDIR
/*
           switch (file->st.st_mode & S_IFMT) {
           case S_IFBLK:  printf("block device\n");            break;
           case S_IFCHR:  printf("character device\n");        break;
           case S_IFDIR:  printf("directory\n");               break;
           case S_IFIFO:  printf("FIFO/pipe\n");               break;
           case S_IFLNK:  printf("symlink\n");                 break;
           case S_IFREG:  printf("regular file\n");            break;
           case S_IFSOCK: printf("socket\n");                  break;
           default:       printf("unknown?\n");                break;
           }
*/
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
    	ft_putnbr(gmtime(&fileStat->st.st_mtime)->tm_year + 1900);
	ft_putchar(' ');
}

static void	print_elem(t_larg *fold, t_larg *file)
{
	if (file)
	{
		if (set_option(0, 0) & (1U << 0))
		{
			print_type(file);
			print_perm(file);
		}
		if (file == fold)
			ft_putstr(file->name);
		else
			ft_putstr(&file->name[ft_strlen(fold->name) + 1]);
		if (set_option(0, 0) & (1U << 0))
			ft_putstr("\n");
		else
			ft_putstr("\t");
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
		print_elem(fold, fold);
		if (fold->state == 1)
			ft_putstr("/:\n");
		if (file)
			tmp = file;
		while (tmp)
		{
			while (file)
			{
				print_elem(fold, file);
				file = file->next;
			}
			if (tmp->state == 1)
			{
				ft_putstr("\n\n");
				read_content(&tmp);
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
				ft_putstr("/:\n");
			}
		}
		else
			print_elem(fold, fold);
		file = (*begin)->content;	
//		if (set_option(0, 0) & (1 << 3))
//			ft_putstr(".\t..\t");
		while (file)
		{
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

void	p_elem(t_larg *elem)
{
	if (elem)
		ft_putendl(elem->name);
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

t_larg	*l_mod2(t_larg	*begin, void (*func)(t_larg*))
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
				if (!is_sort(tmp->next->name, tmp->next->next->name))
				{
					func(tmp);
					tmp = tmp->next;
					tmp = begin;
					if (!is_sort(tmp->name, tmp->next->name))
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







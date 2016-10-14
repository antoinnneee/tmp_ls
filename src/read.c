#include "../includes/ft_ls.h"

static void		read_e(t_larg *fold, t_larg *file)
{
	if (set_option(0, 0) & (1U << 1))
	{
		if (file->next)
			read_e(fold, file->next);
		print_elem(fold, file);
		if (set_option(0, 0) & (1U << 0))
			ft_putchar('\n');
		else if (file->next)
			ft_putchar('\t');
	}
	else
	{
		print_elem(fold, file);
		if (set_option(0, 0) & (1U << 0))
			ft_putchar('\n');
		else if (file->next)
			ft_putchar('\t');
		else
			ft_putchar('\n');
		if (file->next)
			read_e(fold, file->next);
	}
}

void			recur(t_larg **tmp)
{
	t_larg	*file;

	file = *tmp;
	if (set_option(0, 0) & (1U << 1))
	{
		if (file->next)
			recur(&file->next);
		if (file->state == 1)
		{
			ft_putchar('\n');
			read_content(&file);
		}
	}
	else
	{
		if (file->state == 1)
		{
			ft_putchar('\n');
			read_content(&file);
		}
		if (file->next)
			recur(&file->next);
	}
}

void			read_content(t_larg **begin)
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
		if (fold->state == 1)
			print_elem(fold, fold);
		non_recursiv_read(&fold);
		if (tmp)
			recur(&tmp);
	}
}

void			non_recursiv_read(t_larg **begin)
{
	t_larg	*file;
	t_larg	*fold;

	fold = (*begin);
	if (*begin)
	{
		if (fold->state == 1)
		{
			if (set_option(0, 2) > 1)
				print_fold(fold->name);
			if (set_option(0, 0) & (1U << 0))
				print_size(fold->size);
		}
		else
			print_elem(fold, fold);
		file = (*begin)->content;	
		if (file)
			read_e(fold, file);
	}
}


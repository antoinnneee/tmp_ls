
#include "../libft/includes/libft.h"
#include "../includes/ft_ls.h"

void	option_parser(char *str, t_ls *option)
{

	while (*++str != 0 )
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
		else
		{
			ft_putendl("invalid option Phoque !");
			free(option);
			exit(-42);
		}
	}
}

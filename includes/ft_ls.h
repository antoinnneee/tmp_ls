
#ifndef _FT_LS_H
# define _FT_LS_H
# include <unistd.h>
# include "../libft/includes/libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>

/*
 *	struct : state : 1 = folder, 2 = files, 0 = doesn't exist
 */

typedef struct	s_arglist{
	unsigned int		state : 2;
	char				*name;
	int					len;
	DIR					*dir;
	struct stat			f_stat;
	struct s_content	*content;
	struct s_arglist	*next;
} t_larg;

typedef struct	s_content{
	char*				name;
	struct s_content	*next;
}				t_content;

typedef	struct	s_lsparam{
	unsigned int	option : 5 ;
	t_larg			*l_arg;
} t_ls;

t_larg	*swap_elem(t_larg *begin, t_larg *prev);
void	l_sort_alpha(t_larg *elem);
t_larg*	l_mod2(t_larg *begin, void (*func)(t_larg*));
int		is_sort(char *s1, char *s2);
void	p_elem(t_larg *elem);
void	l_mod(t_larg *begin, void (*func)(t_larg*));
void	option_parser(char *str, t_ls *option);
void	arg_parser(int nbarg, char **str);
void	push_file_in_list(t_larg *l_arg, char *str);
#endif

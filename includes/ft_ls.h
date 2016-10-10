
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
	long long		size;
	struct stat		st;
	struct s_arglist	*content;
	struct s_arglist	*next;
} t_larg;

typedef	struct	s_lsparam{
	unsigned int	option : 5 ;
	t_larg			*l_arg;
} t_ls;


void	print_content(t_larg	**data);
void	print_elem(t_larg *fold, t_larg *file);
t_larg	*swap_elem(t_larg *begin, t_larg *prev);
void	l_sort_revalpha(t_larg *elem);
void	l_sort_alpha(t_larg *elem);
void	l_sort_time(t_larg *elem);
//void	l_content_sort(t_content *elem);
t_larg*	l_mod2(t_larg *begin, void (*func)(t_larg*), int state);
int		is_sort(char *s1, char *s2);
int		is_sort_t(struct stat st1, struct stat st2);
void	l_mod(t_larg **begin, void (*func)(t_larg*));
void	option_parser(char *str, t_ls *option);
void	arg_parser(int nbarg, char **str);
long long	push_file_in_list(t_larg **l_arg, char *str, int state);
char	*secure_cat(char* dest, char *str);
t_larg	*sort_first(t_larg *begin);
unsigned int	set_option(unsigned int option, int state);
void	l_f_mod(t_larg **begin);
void	read_content(t_larg **begin);
void	non_recursiv_read(t_larg **begin);

#endif

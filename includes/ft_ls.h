
#ifndef _FT_LS_H
# define _FT_LS_H
# include <unistd.h>
# include "../libft/includes/libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <dirent.h>
typedef struct	s_arglist{
	int	state : 2;
	char	*name;
	int	len;
	DIR	*dir;
	struct s_arglist	*next;	
} t_larg;

typedef	struct	s_lsparam{
	unsigned int	option : 5 ;
	t_larg		*l_arg;
	
} t_ls;


void	option_parser(char *str, t_ls *option);
void	arg_parser(int nbarg, char **str);
t_larg	*filename_parser(char *str, t_ls *ls_param);
#endif

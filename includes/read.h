
#ifndef _READ_H
# define _READ_H
# include <unistd.h>
# include "../libft/includes/libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <dirent.h>

typedef struct	s_container{
	char		*path;
	char		*name;
	struct dirent	*infofile;
	struct	stat	*fistat;
	l_container	*next;

} l_container;

typedef	struct	s_node{
	DIR	*local;
	char	*name;
	int	len;
	l_container	*contain;
	l_node		*next;
} l_node;

l_node	*creat_list(t_ls *ls_param);
void	process_reading(t_ls *ls_param);

#endif

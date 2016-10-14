#include "../includes/ft_ls.h"

char	*standardize(char *str)
{
	int	i;
	int	j;
	char 		*dest;


	i = ft_strlen(str);
	j = ft_strlen(str);
	while(i > 0)
	{
		if (str[i] == '/')
		{
			j = i;
			i = 0;
		}
		else if (ft_isprint(str[i]) && str[i] != ' ')
			i = 0;
		i--;
	}
	dest = (char*)ft_memalloc(sizeof(char) + j + 1);
	ft_strncpy(dest, str, j);
	dest[j] = '\0';
	free(str);
	return (dest);

}

void	init_p_error(t_larg **tmp)
{
	(*tmp)->state = 0;
	if (errno == ENOTDIR)
		(*tmp)->state = 2;
	if (errno == ENOENT)
		(*tmp)->state = 0;
	p_error();
}


void	p_error()
{
	if (errno == ENOMEM)
	{
		ft_putendl("No more MEMORY");
		exit(0);
	}
	if (errno == EMFILE)
	{
		ft_putendl("Too many file descriptors");
		exit(0);
	}
	if (errno == ENFILE)
	{
		ft_putendl("Too many file open");
		exit(0);
	}
	if (errno == EBADF)
	{
		ft_putendl("Not valid fd");
		exit(0);
	}
	if (errno == EACCES)
	{
		ft_putendl("Permission denied");
		exit(0);
	}
}

t_larg	*init_elem(char *str, DIR **dir)
{
	t_larg	*tmp;

	tmp = (t_larg*) ft_memalloc(sizeof(t_larg));
	if (!tmp)
		ft_putendl("ERROR!!!!");
	tmp->name = ft_strdup(str);
	tmp->size = 0;
	tmp->content = NULL;
	tmp->next = NULL;
	lstat(str, &tmp->st);
	tmp->state = 1;
	tmp->name = standardize(tmp->name);
	if ((tmp->st.st_mode & S_IFMT) == S_IFLNK)
		tmp->state = 2;
	*dir = opendir(str);
	return (tmp);
}

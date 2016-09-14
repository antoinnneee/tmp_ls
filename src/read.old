
void	process_reading(t_ls *ls_param)
{
	t_larg			*tmp;
	l_node			*begin;

	tmp = ls_param->l_arg;
	begin = NULL;
	begin = creat_node(tmp);
	while (tmp != NULL)
	{
		tmp = tmp->next;
	}
}

static l_container	*creat_file(char *name, struct stat	*fstat)
{
	l_container	*tmp;
	tmp = (l_container*) ft_memalloc(sizeof(l_container));

}


static l_container	*get_file(l_node *mynode)
{
	l_container		*begin;
	l_container		*tmp;
	struct	stat	*fs;
	struct dirent*	ptrfile;

	begin = NULL;
		while ((ptrfile = readdir(mynode->local)))
		{
			if (begin == NULL)
			{	
				begin = creat_file(ptrfile, mynode->path);
				tmp = begin;
			}
			else
			{
				
			}


		}

	return (begin);		
}

static l_node	*new_node(t_ls *lsp)
{
	l_node	*mynode;

	mynode = NULL;
	mynode = (l_node*) ft_memalloc(sizeof(l_node));
	mynode->local = lsp->l_arg->dir;
		
	mynode->path = 		
	mynode->name = lsp->l_arg->name;
	mynode->len = lsp->l_arg->len;
	mynode->next = NULL;
	if (my_node->local == NULL)
		mynode->contain = get_file(mynode);
}

l_node *creat_node(t_ls *ls_param)
{
	struct dirent*	ptrfile;

	if (local)
	{
		while ((ptrfile = readdir(local)))
		{

		}
	}
}


/*
			if (!(ls_param->option & (1U << 3)))
			{
				if (ptrfile->d_name[0] != '.')
				{			
					ls_param->
				}
			}
			else
			{
				ft_putendl(ptrfile->d_name);
			}
*/



#include "../includes/ft_ls.h"
#include "../libft/includes/libft.h"

static int ft_issymbol(char s1)
{
	if (ft_isprint(s1) && !ft_isalnum(s1))
	{
		return (1);	
	}
	else
		return (0);

}

int is_sort(char *s1, char *s2)
{
    int i;

    i = 0;
    while (s1[i] && s2[i])
    {
	while (s1[i] == s2[i] && s1[i] && s2[i])
	    i++;
	if(s1[i] == s2[i] && !s1[i])
	    return(1);
	else if (!s2[i])
	    return(0);
	else if (!s1[i])
	    return(1);
	if (ft_issymbol(s1[i]) && ft_issymbol(s2[i]))
	{
	    if (s1[i] > s2[i])
		return(0);
	    else
		return (1);
	}
	if (ft_isdigit(s1[i]) && ft_isdigit(s2[i]))
	{
	    if (s1[i] < s2[i])
		return (1);
	    else
		return(0);
	}
	if (ft_issymbol(s1[i]) && !ft_issymbol(s2[i]))
	    return (1);
	if (ft_issymbol(s2[i]) && !ft_issymbol(s1[i]))
	    return (0);
	if (ft_isdigit(s1[i]) && ft_isalpha(s2[i]))
	    return (1);
	if (ft_isdigit(s2[i]) && ft_isalpha(s1[i]))
	    return (0);
	if (ft_isalpha(s1[i]) && ft_isalpha(s2[i]))
	{
	    if (s1[i] == (s2[i] + 32))
		return (1);
	    else if (s1[i] == (s2[i] - 32))
		return (0);
	    else
	    {
		if (s1[i] >= 'a')
		{
		    if (s2[i] >= 'a')
		    {
			if (s1[i] < s2[i])
			    return (1);
			else
			    return (0);
		    }
		    if (s2[i] < 'a')
		    {
			if (s1[i] - 32 < s2[i])
			    return (1);
			else
			    return (0);
		    }
		}
		else
		{
		    if (s2[i] >= 'a')
		    {
			if (s1[i] + 32 < s2[i])
			    return (1);
			else
			    return (0);
		    }
		    if (s2[i] < 'a')
		    {
			if (s1[i] < s2[i])
			    return (1);
			else
			    return (0);
		    }
		}
	    }
	}
    }
    return (0);
}

static void swap_elem(t_larg **elem)
{
	t_larg	*tmp;
	t_larg	*sec;
	
	sec = *(elem)->next;
	tmp = *(elem);
	elem->next = sec->next;
	sec->next = *(elem)->next;
	*elem = tmp;
}

void	l_sort_alpha(t_larg *elem)
{
	if (elem)
		if (elem->next)
			if (!is_sort(elem->name, elem->next->name))
				swap_elem(&elem);
}



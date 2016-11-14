/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abureau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 12:30:24 by abureau           #+#    #+#             */
/*   Updated: 2016/10/17 15:46:13 by abureau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "../includes/ft_ls.h"

static int	length(t_64 value, unsigned int base)
{
	int	i;

	i = 0;
	if (value == 0)
		i++;
	while (value)
	{
		value /= base;
		i++;
	}
	return (i);
}

char		*ft_lltoa_base(t_64 value, unsigned int base, int signe)
{
	int		len;
	char	*str;

	len = (signe) ? length(value, base) + 1 : length(value, base);
	str = ft_strnew(len);
	if (!str)
		return (NULL);
	(signe) ? str[0] = '-' : '+';
	while ((signe) ? len > 1 : len > 0)
	{
		len--;
		str[len] = (value % base) > 9 ? (value % base) - 10 + 'a'
			: (value % base) + '0';
		value = value / base;
	}
	return (str);
}

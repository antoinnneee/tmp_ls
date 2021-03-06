/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secure_cat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abureau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 15:23:05 by abureau           #+#    #+#             */
/*   Updated: 2016/11/18 19:48:17 by abureau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"

char	*secure_cat(char *dest, char *str)
{
	char	*mstr;
	int		llen;

	llen = ft_strlen(str) + ft_strlen(dest);
	mstr = (char*)ft_memalloc(sizeof(char) * llen + 1);
	ft_strcpy(mstr, dest);
	ft_strcpy(&mstr[ft_strlen(mstr)], str);
	mstr[llen] = '\0';
	return (mstr);
}

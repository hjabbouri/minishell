/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjabbour <hjabbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 13:10:37 by stamim            #+#    #+#             */
/*   Updated: 2022/10/17 13:12:57 by hjabbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

char	*ft_strdup(const char *const src)
{
	char	*res;
	size_t	len;

	if (!src)
		return (NULL);
	len = 0;
	while (src && src[len])
		len += 1;
	res = (char *)ft_malloc(len + 1);
	if (res)
	{
		res[len] = '\0';
		while (len--)
			res[len] = src[len];
	}
	return (res);
}

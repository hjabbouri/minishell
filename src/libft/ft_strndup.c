/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjabbour <hjabbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 11:54:56 by stamim            #+#    #+#             */
/*   Updated: 2022/10/23 16:37:10 by hjabbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

char	*ft_strndup(const char *const src, size_t size)
{
	char	*res;

	res = (char *)ft_malloc(size + 1);
	if (res)
	{
		res[size] = '\0';
		while (size--)
			res[size] = src[size];
	}
	return (res);
}

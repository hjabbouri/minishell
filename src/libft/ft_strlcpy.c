/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjabbour <hjabbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 16:35:54 by hjabbour          #+#    #+#             */
/*   Updated: 2022/10/16 11:09:18 by hjabbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"

size_t	ft_strlcpy(char *restrict const dst, const char *restrict const src,
	const size_t dstsize)
{
	size_t	idx;

	idx = 0;
	if (dstsize > 0)
	{
		while (idx < dstsize - 1 && src[idx])
		{
			dst[idx] = src[idx];
			idx++;
		}
		dst[idx] = 0;
	}
	idx = 0;
	while (src[idx])
		idx++;
	return (idx);
}

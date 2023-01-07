/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjabbour <hjabbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 09:36:42 by hjabbour          #+#    #+#             */
/*   Updated: 2022/10/21 11:39:33 by hjabbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"

void	ft_strcpy(size_t start, char *dest, char const *src)
{
	int	idx;

	idx = 0;
	while (src[idx])
		dest[start++] = src[idx++];
}

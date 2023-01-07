/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjabbour <hjabbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 11:29:44 by hjabbour          #+#    #+#             */
/*   Updated: 2022/10/22 08:11:03 by hjabbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	idx;

	idx = 0;
	if (!str1 || !str2)
		return (0);
	while ((str1[idx] != '\0' || str2[idx] != '\0') && idx < n)
	{
		if (str1[idx] != str2[idx])
			return ((unsigned char)str1[idx] - (unsigned char)str2[idx]);
		idx++;
	}
	return (0);
}

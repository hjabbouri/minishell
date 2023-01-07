/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjabbour <hjabbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 14:44:36 by hjabbour          #+#    #+#             */
/*   Updated: 2022/10/20 10:36:27 by hjabbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"

int	ft_chr(const char *str, const char chr, int ret)
{
	int	idx;

	idx = 0;
	if (!str)
		return (ret);
	while (str[idx])
	{
		if (str[idx] == chr)
			return (idx);
		idx++;
	}
	return (ret);
}

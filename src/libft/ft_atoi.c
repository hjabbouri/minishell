/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjabbour <hjabbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:41:05 by hjabbour          #+#    #+#             */
/*   Updated: 2022/10/20 10:39:25 by hjabbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"

int	ft_atoi(const char *str)
{
	int	signe;
	int	nbr;
	int	idx;

	idx = 0;
	nbr = 0;
	signe = 1;
	while ((str[idx] >= '\t' && str[idx] <= '\r') || str[idx] == ' ')
		idx++;
	if (str[idx] == '-')
	{
		signe *= (-1);
		idx++;
	}
	else if (str[idx] == '+')
		idx++;
	while (str[idx] >= '0' && str[idx] <= '9')
			nbr = (nbr * BASE) + (str[idx++] - '0');
	return (nbr * signe);
}

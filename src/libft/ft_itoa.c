/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stamim <stamim@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 12:37:43 by hjabbour          #+#    #+#             */
/*   Updated: 2022/10/21 18:26:56 by stamim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"

static	void	print_nb(char *str, long num, int len)
{
	if (num < 0)
	{
		str[0] = '-';
		num = num * (-1);
	}
	str[len--] = '\0';
	if (num == 0)
		str[0] = '0';
	while (num != 0)
	{
		str[len--] = (num % BASE) + '0';
		num /= BASE;
	}
}

char	*ft_itoa(char *buf, int n)
{
	int		len;
	long	num;

	len = 0;
	num = n;
	while (n != 0)
	{
		n /= BASE;
		len++;
	}
	if (num == 0)
		len = 1;
	else if (num < 0)
		len++;
	print_nb(buf, num, len);
	return (buf);
}

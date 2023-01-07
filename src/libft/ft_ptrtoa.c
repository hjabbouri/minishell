/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptrtoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjabbour <hjabbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 12:37:43 by hjabbour          #+#    #+#             */
/*   Updated: 2022/10/21 09:30:24 by hjabbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"

static char	*fill_str(unsigned long pnbr, size_t len)
{
	char			*str;
	const char		*tab = "0123456789abcdef";

	str = malloc((len + 2 + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	len += 2;
	str[len--] = '\0';
	str[0] = '0';
	str[1] = 'x';
	while (pnbr)
	{
		str[len--] = tab[pnbr % 16];
		pnbr /= 16;
	}
	return (str);
}

char	*ft_ptrtoa(void *nbr)
{
	size_t			len;
	unsigned long	pnbr;

	pnbr = (unsigned long)nbr;
	len = 0;
	while (pnbr)
	{
		pnbr /= 16;
		len++;
	}
	return (fill_str((unsigned long)nbr, len));
}

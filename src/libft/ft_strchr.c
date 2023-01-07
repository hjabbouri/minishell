/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stamim <stamim@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:52:40 by stamim            #+#    #+#             */
/*   Updated: 2022/10/18 14:25:45 by stamim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strchr(const char *str, int chr)
{
	int	idx;

	if (!str)
		return (NULL);
	idx = 0;
	chr = (unsigned char )chr;
	if (chr == '\0')
	{
		while (str[idx])
			idx++;
		return ((char *) str + idx);
	}
	while (str[idx])
	{
		if (str[idx] == chr)
			return ((char *) str + idx);
		idx++;
	}
	return (NULL);
}

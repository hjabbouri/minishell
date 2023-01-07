/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjabbour <hjabbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:52:06 by stamim            #+#    #+#             */
/*   Updated: 2022/10/19 09:37:45 by hjabbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"

char	*ft_strjoin(char const *str1, char const *str2)
{
	size_t	len;
	char	*str;

	str = NULL;
	if (str1 && str2)
	{
		len = ft_strlen(str1) + ft_strlen(str2);
		str = (char *)ft_malloc(len + 1);
		if (str)
		{
			str[len] = 0;
			ft_strcpy(0, str, str1);
			ft_strcpy(ft_strlen(str1), str, str2);
		}
	}
	return (str);
}

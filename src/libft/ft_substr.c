/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjabbour <hjabbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 14:56:03 by hjabbour          #+#    #+#             */
/*   Updated: 2022/10/16 11:14:01 by hjabbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	if (!s)
		return (NULL);
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	str = ft_malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	else
	{
		while (i < len && start <= ft_strlen(s))
			str[i++] = s[start++];
		str[i] = '\0';
	}
	return (str);
}

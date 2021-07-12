/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iariss <iariss@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 11:07:32 by iariss            #+#    #+#             */
/*   Updated: 2021/07/12 11:08:11 by iariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"

void	print_three(char *s1, char *s2, char *s3)
{
	print_error(s1);
	print_error(s2);
	print_error(s3);
}

char	*join_free(char *s1, char *s2, int index)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	j = 0;
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i++] = s2[j];
		j++;
	}
	str[i] = '\0';
	if (index == 0)
		free(s1);
	else if (index == 1)
		free(s2);
	return (str);
}

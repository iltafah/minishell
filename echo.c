/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iariss <iariss@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 10:45:42 by iariss            #+#    #+#             */
/*   Updated: 2021/06/30 10:46:43 by iariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"
#include "minishell.h"

void	echo(char **v, t_varso *vars)
{

	int i;
	int j;
	int k;
	int num_args;
	
	i = 0;
	j = 1;
	k = 2;
	num_args = check_echo(v);
	if (!num_args)
		return ;
	while (j < num_args && !ft_strncmp(v[j], "-n", 2))
	{
		k = 2;
		while (v[j][k])
		{
			if(v[j][k] != 'n')
			{
				k = 0;
				break ;
			}
			k++;
		}
		if (!k)
			break ;
		j++;
		i = 1;
	}
	while (v[j])
	{
		ft_printf_string(v[j]);
		j++;
		if (v[j])
			write(1, " ", 1);
	}
	if (!i)
		write(1, "\n", 1);
}

int check_echo(char **v)
{
	int i;

	i = 0;
	while (v[i])
	{
		i++;
	}
	if (i == 1)
	{
		printf("\n");
		return (0);
	}
	return(i);
}

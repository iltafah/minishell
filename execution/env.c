/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iariss <iariss@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 10:54:37 by iariss            #+#    #+#             */
/*   Updated: 2021/07/05 15:32:58 by iariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"
#include "../minishell.h"

void	enviro(void)
{
	int		i;

	i = 0;
	while (i <= g_vars.env_table.name.last_index)
	{
		if (g_vars.env_table.value.elements[i] != NULL)
		{
			printf("%s=%s\n", g_vars.env_table.name.elements[i],
				g_vars.env_table.value.elements[i]);
		}
		i++;
	}
}

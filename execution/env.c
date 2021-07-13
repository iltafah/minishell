/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iariss <iariss@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 10:54:37 by iariss            #+#    #+#             */
/*   Updated: 2021/07/13 11:13:00 by iariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"
#include "../minishell.h"

void	enviro(void)
{
	int		i;

	i = 0;
	while (i < g_vars.env_table.name.used_size)
	{
		if (g_vars.env_table.value.elements[i] != NULL)
		{
			printf("%s=%s\n", g_vars.env_table.name.elements[i],
				g_vars.env_table.value.elements[i]);
		}
		i++;
	}
}

void	merge_env(t_varso *vars)
{
	int		i;
	char	*hello;

	i = 0;
	vars->export.env = (char **)malloc(sizeof(char *)
			* g_vars.env_table.name.used_size + 1);
	while (i < g_vars.env_table.name.used_size)
	{
		vars->export.env[i] = ft_strjoin(g_vars.env_table.name.elements[i],
				"=");
		hello = g_vars.env_table.value.elements[i];
		if (!g_vars.env_table.value.elements[i])
			hello = "";
		vars->export.env[i] = join_free(vars->export.env[i],
				hello, 0);
		i++;
	}
	vars->export.env[i] = NULL;
}

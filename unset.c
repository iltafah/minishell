/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iariss <iariss@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 10:52:18 by iariss            #+#    #+#             */
/*   Updated: 2021/06/30 10:52:47 by iariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "file.h"

void	unset(t_ast *scn, t_varso *vars)
{
	int x;
	int	i;
	int	j;
	char **args;

	j = 0;
	i = 1;
	args = scn->node.data.args_vec.elements;
	while (i <= scn->node.data.args_vec.last_index)
	{
		x = 0;
		while (args[i][x] && args[i][x] != '=')
			x++;
		if ((x == 1 && args[i][0] && args[i][0] == '='))
		{
			printf("minishell: unset: `=': not a valid identifier\n");
			g_vars.last_err_num = 1;
		}
		if (!ft_isalpha(args[i][0]) || (!ft_isalpha(args[i][ft_strlen(args[i]) - 1]) && !ft_isdigit(args[i][ft_strlen(args[i]) - 1])))
		{
			printf("minishell: unset: '%s': not a valid identifier\n", args[i]);
			g_vars.last_err_num = 1;
		}
		else
		{
			j = 0;
			while (j <= g_vars.env_table.name.last_index)
			{
				if(!(ft_strncmp(args[i], g_vars.env_table.name.elements[j], x)))
				{
					printf("%s | %d\n", args[i], x);
					g_vars.env_table.name.delete_element_at_index(&g_vars.env_table.name, j);
					g_vars.env_table.value.delete_element_at_index(&g_vars.env_table.value, j);
				}
				j++;
			}
		}
		i++;
	}
}
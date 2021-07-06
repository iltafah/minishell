/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iariss <iariss@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 10:52:18 by iariss            #+#    #+#             */
/*   Updated: 2021/07/06 10:47:37 by iariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "file.h"

void	remove_variable(char **a, int i, int x)
{
	int	j;

	j = 0;
	while (j <= g_vars.env_table.name.last_index)
	{
		if (!(ft_strcmp(a[i], g_vars.env_table.name.elements[j])))
		{
			g_vars.env_table.name.delete_element_at_index(
				&g_vars.env_table.name, j);
			// printf("in\n");
			g_vars.env_table.value.delete_element_at_index(
				&g_vars.env_table.value, j);
			// printf("out\n");
			return ;
		}
		j++;
	}
}

void	unset(t_ast *scn, t_varso *vars)
{
	t_unset_vars	u;

	u.i = 1;
	u.a = scn->node.data.args_vec.elements;
	while (u.i <= scn->node.data.args_vec.last_index)
	{
		u.x = 0;
		while (u.a[u.i][u.x] && u.a[u.i][u.x] != '=')
			u.x++;
		if ((u.x == 1 && u.a[u.i][0] && u.a[u.i][0] == '='))
		{
			printf("minishell: unset: `=': not a valid identifier\n");
			g_vars.last_err_num = 1;
		}
		if (!ft_isalpha(u.a[u.i][0])
		|| (!ft_isalpha(u.a[u.i][ft_strlen(u.a[u.i]) - 1])
		&& !ft_isdigit(u.a[u.i][ft_strlen(u.a[u.i]) - 1])))
		{
			printf("minishell: unset: '%s': not a valid identifier\n", u.a[u.i]);
			g_vars.last_err_num = 1;
		}
		else
			remove_variable(u.a, u.i, u.x);
		u.i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iariss <iariss@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 10:55:47 by iariss            #+#    #+#             */
/*   Updated: 2021/06/30 10:56:36 by iariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "file.h"

void	check_exit(t_ast *scn)
{
	int i;
	int j;
	char *nb;
	int	ex_num;

	j = 0;
	i = 1;
	while (i <= scn->node.data.args_vec.last_index)
	{
		if (scn->node.data.args_vec.last_index == 1)
		{
			j = 0;
			while (scn->node.data.args_vec.elements[i][j])
			{
				if(!ft_isdigit(scn->node.data.args_vec.elements[i][j]) && scn->node.data.args_vec.elements[i][0] != '-')
					break ;
				j++;
			}
			check_exit_num(scn->node.data.args_vec.elements[i], j, scn);
		}
		else if (scn->node.data.args_vec.last_index > 1)
		{
			j = 1;
			while (scn->node.data.args_vec.elements[i][j])
			{
				if(!ft_isdigit(scn->node.data.args_vec.elements[i][j]))
					break ;
				j++;
			}
			if (ft_strlen(scn->node.data.args_vec.elements[i]) != j)
			{
				printf("exit\nminishell: exit: %s: numeric argument required\n", scn->node.data.args_vec.elements[i]);
				exit(ft_atoi(scn->node.data.args_vec.elements[i]));
			}
			printf("exit\nminishell: exit: too many arguments\n");
			g_vars.last_err_num = 1;
			break ;
		}
		i++;
	}
	if (scn->node.data.args_vec.last_index == 0)
	{
		// g_vars.last_err_num = 0;
		exit(g_vars.last_err_num);
	}
}

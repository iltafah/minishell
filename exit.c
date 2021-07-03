/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iariss <iariss@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 10:55:47 by iariss            #+#    #+#             */
/*   Updated: 2021/07/01 14:03:47 by iariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "file.h"

int	check_exit_num(char *num, int j, t_ast *scn)
{
	char	*max_long;

	max_long = "9223372036854775807";
	if (num[0] != '-' && (ft_strlen(num) != j || (ft_strlen(num) > 19
				&& num[0] != '0') || (ft_strlen(num) == 19
				&& ft_strncmp(max_long, num, ft_strlen(num)) < 0)))
	{
		printf("exit\nminishell: exit: %s: numeric argument required\n", num);
		exit(255);
	}
	else if (num[0] == '-' && (ft_strlen(num) != j || (ft_strlen(num) > 20
				&& num[0] != '0') || (ft_strlen(num) == 20
				&& ft_strncmp(max_long, num, ft_strlen(num)) < 0)))
	{
		printf("exit\nminishell: exit: %s: numeric argument required\n", num);
		exit(255);
	}
	else
	{
		printf("exit\n");
		exit(ft_atoi(num));
	}
}

void	one_exit_arg(t_ast *scn, int i)
{
	int	j;

	j = 0;
	while (scn->node.data.args_vec.elements[i][j])
	{
		if (!ft_isdigit(scn->node.data.args_vec.elements[i][j])
			&& scn->node.data.args_vec.elements[i][0] != '-')
			break ;
		j++;
	}
	check_exit_num(scn->node.data.args_vec.elements[i], j, scn);
}

void	multi_exit_arg(t_ast *scn, int i)
{
	int	j;

	j = 1;
	while (scn->node.data.args_vec.elements[i][j])
	{
		if (!ft_isdigit(scn->node.data.args_vec.elements[i][j]))
			break ;
		j++;
	}
	if (ft_strlen(scn->node.data.args_vec.elements[i]) != j)
	{
		printf("exit\nminishell: exit: %s: numeric argument required\n",
			scn->node.data.args_vec.elements[i]);
		exit(ft_atoi(scn->node.data.args_vec.elements[i]));
	}
	printf("exit\nminishell: exit: too many arguments\n");
	g_vars.last_err_num = 1;
}

void	check_exit(t_ast *scn)
{
	int		i;
	int		j;
	char	*nb;
	int		ex_num;

	j = 0;
	i = 1;
	while (i <= scn->node.data.args_vec.last_index)
	{
		if (scn->node.data.args_vec.last_index == 1)
			one_exit_arg(scn, i);
		else if (scn->node.data.args_vec.last_index > 1)
		{
			multi_exit_arg(scn, i);
			break ;
		}
		i++;
	}
	if (scn->node.data.args_vec.last_index == 0)
		exit(g_vars.last_err_num);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iariss <iariss@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 16:47:17 by iariss            #+#    #+#             */
/*   Updated: 2021/07/07 12:55:45 by iariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"
#include "../minishell.h"

void	merge_env(t_varso *vars)
{
	int		i;
	char	*hello;

	i = 0;
	vars->export.env = (char **)malloc(sizeof(char *)
			* g_vars.env_table.name.used_size + 1);
	while (i <= g_vars.env_table.name.last_index)
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

void	add_one(t_varso *vars)
{
	int	i;

	i = 0;
	while (vars->export.env[i])
	{
		if (!(ft_strncmp(vars->export.env[i], "SHLVL", 5)))
		{
			vars->export.env[i][6] = vars->export.env[i][6] + 1;
		}
		i++;
	}
}

void	check_command2(char *sticker, t_varso *vars, t_rand *num, t_ast *scn)
{
	char	*tmp;
	char	cwd[PATH_MAX];

	getcwd(cwd, sizeof(cwd));
	if (scn->node.data.args_vec.elements[0][0] != '/'
		&& ft_strncmp(scn->node.data.args_vec.elements[0], "./", 2))
	{
		tmp = num->tab[num->i];
		num->tab[num->i] = ft_strjoin(num->tab[num->i], sticker);
		free(tmp);
	}
	else if (!ft_strncmp(scn->node.data.args_vec.elements[0], "./", 2))
	{
		num->tab[num->i] = ft_strjoin(cwd, sticker + 2);
		if (!ft_strcmp(scn->node.data.args_vec.elements[0], "./minishell"))
			add_one(vars);
	}
	else
		num->tab[num->i] = ft_strdup(scn->node.data.args_vec.elements[0]);
}

int	check_command(t_ast *scn, char *sticker, t_varso *vars, t_rand *num)
{
	if (!ft_strcmp(scn->node.data.args_vec.elements[0], "./"))
	{
		print_error("minishell: ./: is a directory\n");
		g_vars.last_err_num = 126;
		return (0);
	}
	else if (!ft_strcmp(scn->node.data.args_vec.elements[0], "."))
	{
		g_vars.last_err_num = 2;
		print_error("minishell: .: filename argument required\n");
		print_error(".: usage: . filename [arguments]\n");
		return (0);
	}
	else
	{
		check_command2(sticker, vars, num, scn);
	}
	return (1);
}

void	execv_errors(t_rand *num, t_ast *scn, struct stat buff)
{
	if (stat(num->tab[num->i], &buff) && scn->node.data.args_vec.elements[0][0]
	!= '/' && ft_strncmp(scn->node.data.args_vec.elements[0], "./", 2))
	{
		print_three("minishell: ", scn->node.data.args_vec.elements[0],
			(": command not found\n"));
		g_vars.last_err_num = 127;
	}
	else if ((scn->node.data.args_vec.elements[0][0] == '/'
		|| (!ft_strncmp(scn->node.data.args_vec.elements[0], "./", 2)))
		&& num->y)
	{
		if (!stat(num->tab[num->i], &buff))
		{
			g_vars.last_err_num = 126;
			print_three("minishell: ", scn->node.data.args_vec.elements[0],
				(": is a directory\n"));
		}
		else
		{
			g_vars.last_err_num = 127;
			print_three("minishell: ", scn->node.data.args_vec.elements[0],
				": No such file or directory\n");
		}
	}
}

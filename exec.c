/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iariss <iariss@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 12:56:09 by iariss            #+#    #+#             */
/*   Updated: 2021/07/03 19:47:50 by iariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"
#include "minishell.h"
#include <string.h>

void	builtins(t_ast *scn, t_varso *vars)
{
	char	*first_arg;

	first_arg = scn->node.data.args_vec.elements[0];
	if (!ft_strcmp(first_arg, "echo"))
		echo(scn->node.data.args_vec.elements, vars);
	else if (!ft_strcmp(first_arg, "cd"))
		cd(scn->node.data.args_vec.elements, vars);
	else if (!ft_strcmp(first_arg, "pwd"))
		pwd();
	else if (!ft_strcmp(first_arg, "export"))
		export(scn->node.data.args_vec.elements, vars, scn);
	else if (!ft_strcmp(first_arg, "unset"))
		unset(scn, vars);
	else if (!ft_strcmp(first_arg, "env"))
		enviro();
	else if (!ft_strcmp(first_arg, "exit"))
		check_exit(scn);
	else
	{
		exv(scn, vars);
	}
}

void	execution(t_ast *scn, int num_pipes)
{
	char	*first_arg;
	char	cwd[PATH_MAX];
	t_varso	vars;

	getcwd(cwd, sizeof(cwd));
	vars.prev_path = cwd;
	signal(SIGQUIT, handle_quit);
	signal(SIGINT, handle_c);
	if (scn->node.data.redirections)
	{
		if (!check_redis(scn))
		{
			g_vars.last_err_num = 1;
			return ;
		}
	}
	if (scn->node.data.args_vec.used_size)
		builtins(scn, &vars);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_start.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 12:56:09 by iariss            #+#    #+#             */
/*   Updated: 2021/07/12 12:45:24 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "file.h"
#include "../minishell.h"
#include <string.h>

void	builtins(t_ast *scn, t_varso *vars)
{
	char		*first_arg;
	static int	prev_error;
	int			go;

	first_arg = scn->node.data.args_vec.elements[0];
	if (!ft_strcmp(first_arg, "echo"))
		echo(scn->node.data.args_vec.elements);
	else if (!ft_strcmp(first_arg, "cd"))
		cd(scn->node.data.args_vec.elements, vars);
	else if (!ft_strcmp(first_arg, "pwd"))
		pwd();
	else if (!ft_strcmp(first_arg, "export"))
		export(scn->node.data.args_vec.elements, vars, scn);
	else if (!ft_strcmp(first_arg, "unset"))
		unset(scn);
	else if (!ft_strcmp(first_arg, "env"))
		enviro();
	else if (!ft_strcmp(first_arg, "exit"))
	{
		go = prev_error;
		check_exit(scn, go);
	}
	else
		exv(scn, vars);
	prev_error = g_vars.last_err_num;
}

void	execution(t_ast *scn)
{
	int		last_i;
	char	cwd[PATH_MAX];
	t_varso	vars;

	last_i = scn->node.data.args_vec.last_index;
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

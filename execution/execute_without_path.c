/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_without_path.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iariss <iariss@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 11:18:30 by iariss            #+#    #+#             */
/*   Updated: 2021/07/13 11:46:05 by iariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"



void	execute_path(int *y, t_ast *scn, t_varso *vars)
{
	pid_t	pid;
	int		status;

	if (!ft_strcmp(scn->node.data.args_vec.elements[0], "./minishell")
		|| !ft_strcmp(scn->node.data.args_vec.elements[0], "./MINISHELL"))
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
		add_one(vars);
	}
	pid = fork();
	if (pid == 0)
	{
		if (execve(scn->node.data.args_vec.elements[0],
				scn->node.data.args_vec.elements, vars->export.env) == -1)
			exit(1);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_vars.last_err_num = WEXITSTATUS(status);
	if (WEXITSTATUS(status))
		*y = 1;
}

void	without_path_slash(t_varso *vars, t_ast *scn)
{
	int			y;
	struct stat	buff;
	int			i;

	y = 0;
	i = 0;
	merge_env(vars);
	if (!stat(scn->node.data.args_vec.elements[0], &buff))
		execute_path(&y, scn, vars);
	if (!stat(scn->node.data.args_vec.elements[0], &buff) && y && buff.st_mode & S_IFDIR)
	{	
		g_vars.last_err_num = 126;
		print_three("minishell: ", scn->node.data.args_vec.elements[0],
			": is a directory\n");
	}
	else if (stat(scn->node.data.args_vec.elements[0], &buff))
	{
		g_vars.last_err_num = 127;
		print_error("minishell: ");
		print_error(scn->node.data.args_vec.elements[0]);
		print_error(": No such file or directory\n");
	}
	while (vars->export.env[i])
		free(vars->export.env[i++]);
	free(vars->export.env);
}

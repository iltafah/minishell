/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iariss <iariss@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 10:57:19 by iariss            #+#    #+#             */
/*   Updated: 2021/07/09 11:30:10 by iariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "file.h"

void	free_vars(t_rand num, t_varso *vars)
{
	num.i = 0;
	while (num.tab[num.i])
		free(num.tab[num.i++]);
	free(num.tab);
	num.i = 0;
	while (vars->export.env[num.i])
		free(vars->export.env[num.i++]);
	free(vars->export.env);
}

void	with_path(char *path, t_varso *vars, t_ast *scn)
{
	char	cwd[PATH_MAX];
	t_rand	num;
	int		k;

	k = 0;
	num.tab = ft_split(path, ':');
	getcwd(cwd, sizeof(cwd));
	num.sticker = scn->node.data.args_vec.elements[0];
	if (scn->node.data.args_vec.elements[0][0] != '/')
	{
		num.sticker = ft_strjoin("/", scn->node.data.args_vec.elements[0]);
		k = 1;
	}
	merge_env(vars);
	num.i = 0;
	execv_main_loop(&num, scn, vars);
	if (stat(num.tab[num.i], &num.buff))
		num.y = 1;
	execv_errors(&num, scn, num.buff);
	if (k)
		free(num.sticker);
	free_vars(num, vars);
}

void	execute_path(int *y, t_ast *scn, t_varso *vars)
{
	pid_t	pid;
	int		status;

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

	y = 0;
	merge_env(vars);
	if (!stat(scn->node.data.args_vec.elements[0], &buff))
		execute_path(&y, scn, vars);
	if (!stat(scn->node.data.args_vec.elements[0], &buff) && y)
	{	
		g_vars.last_err_num = 126;
		print_error("minishell: ");
		print_error(scn->node.data.args_vec.elements[0]);
		print_error(": is a directory\n");
	}
	else if (stat(scn->node.data.args_vec.elements[0], &buff))
	{
		g_vars.last_err_num = 127;
		print_error("minishell: ");
		print_error(scn->node.data.args_vec.elements[0]);
		print_error(": No such file or directory\n");
	}
}

void	exv(t_ast *scn, t_varso *vars)
{
	t_exv_vars	exv;

	getcwd(exv.cwd, sizeof(exv.cwd));
	exv.path = find_env("PATH");
	if (exv.path && scn->node.data.args_vec.elements[0][0])
		with_path(exv.path, vars, scn);
	else if (!exv.path && scn->node.data.args_vec.elements[0][0] == '/')
		without_path_slash(vars, scn);
	else
	{
		print_error("minishell: ");
		print_error(scn->node.data.args_vec.elements[0]);
		print_error(": command not found\n");
	}
	return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iariss <iariss@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 10:57:19 by iariss            #+#    #+#             */
/*   Updated: 2021/06/30 11:20:14 by iariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "file.h"

void	 exv(t_ast *scn, t_varso *vars)
{
	char	*path;
	char	cwd[PATH_MAX];
	char	**tab;
	char	*sticker;
	char	*tmp1;
	char	*tmp2;
	int x;
	int		i;
	pid_t		pid;
	int status;
	struct stat buff;

	x = 0;
	getcwd(cwd, sizeof(cwd));
	path = find_env("PATH");
	if (path && scn->node.data.args_vec.elements[0][0])
	{
		tab = ft_split(path, ':');
		sticker = scn->node.data.args_vec.elements[0];
		if (scn->node.data.args_vec.elements[0][0] != '/')
		{
			sticker = ft_strjoin("/", scn->node.data.args_vec.elements[0]);
		}
		merge_env(scn, vars);
		i = 0;
		while(tab[i])
		{
			x = 0;
			if (scn->node.data.args_vec.elements[0][0] != '/' && ft_strncmp(scn->node.data.args_vec.elements[0], "./", 2))
			{
				tab[i] = ft_strjoin(tab[i], sticker);
				tmp1 = tab[i];
			}
			else if (!ft_strncmp(scn->node.data.args_vec.elements[0], "./", 2))
			{
				tab[i] = ft_strjoin(cwd, sticker + 2);
				tmp1 = tab[i];
				if(!ft_strcmp(scn->node.data.args_vec.elements[0], "./minishell"))
				{
					add_one(vars);
				}
				free(tmp1);
			}
			else
			{
				tab[i] = ft_strdup(scn->node.data.args_vec.elements[0]);
				x = 1;
			}
			if (!stat(tab[i], &buff))
			{
				pid = fork();
				if (pid == 0)
				{
					execve(tab[i], scn->node.data.args_vec.elements, vars->export.env);
				}
				waitpid(pid, &status, 0);
				if (WIFEXITED(status))
				{
					g_vars.last_err_num = WEXITSTATUS(status);
				}
				kill(pid, SIGKILL);
				break ;
			}
			if (!x)
				free(tab[i]);
			i++;
		}
		if (stat(tab[i], &buff))
		{
			printf("minishell : %s: command not found\n", scn->node.data.args_vec.elements[0]);
			g_vars.last_err_num = 127;
		}
		free(tab);
		free(vars->export.env);
	}
	else if (!path && scn->node.data.args_vec.elements[0][0])
	{
		if (!stat(scn->node.data.args_vec.elements[0], &buff))
		{
			merge_env(scn, vars);
			pid = fork();
			if (pid == 0)
			{
				execve(scn->node.data.args_vec.elements[0], scn->node.data.args_vec.elements, vars->export.env);
				exit(0);
			}
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
			{
				g_vars.last_err_num = WEXITSTATUS(status);
			}
			kill(pid, SIGKILL);
		}
		else
		{
			printf("minishell : %s: command not found\n", scn->node.data.args_vec.elements[0]);
			g_vars.last_err_num = 127;
		}
	}
	else
		printf("minishell : %s: command not found\n", scn->node.data.args_vec.elements[0]);
	return ;
}
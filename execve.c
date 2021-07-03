/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iariss <iariss@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 10:57:19 by iariss            #+#    #+#             */
/*   Updated: 2021/07/03 12:00:02 by iariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "file.h"

char	*join_free(char *s1, char *s2, int index)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	j = 0;
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i++] = s2[j];
		j++;
	}
	str[i] = '\0';
	if (index == 0)
		free(s1);
	else if (index == 1)
		free(s2);
	return (str);
}

void	merge_env(t_ast *scn, t_varso *vars)
{
	int		i;
	char	*tmp;

	i = 0;
	vars->export.env = (char **)malloc(sizeof(char *)
			* g_vars.env_table.name.used_size);
	while (i <= g_vars.env_table.name.last_index)
	{
		vars->export.env[i] = ft_strjoin(g_vars.env_table.name.elements[i],
				"=");
		if (!g_vars.env_table.value.elements[i])
			g_vars.env_table.value.elements[i] = "";
		vars->export.env[i] = join_free(vars->export.env[i],
				g_vars.env_table.value.elements[i], 0);
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

int	check_command(t_ast *scn, char *sticker, t_varso *vars, t_rand *num)
{
	char	cwd[PATH_MAX];
	int		x;
	char	*tmp;

	getcwd(cwd, sizeof(cwd));
	if (!ft_strcmp(scn->node.data.args_vec.elements[0], "./"))
	{
		printf("minishell: ./: is a directory\n");
		g_vars.last_err_num = 126;
		return (0);
	}
	else if (!ft_strcmp(scn->node.data.args_vec.elements[0], "."))
	{
		g_vars.last_err_num = 2;
		printf("minishell: .: filename argument required\n");
		printf(".: usage: . filename [arguments]\n");
		return (0);
	}
	else if (scn->node.data.args_vec.elements[0][0] != '/'
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
	return (1);
}

void	execv_errors(t_rand *num, t_ast *scn, struct stat buff)
{
	if (stat(num->tab[num->i], &buff) && scn->node.data.args_vec.elements[0][0]
	!= '/' && ft_strncmp(scn->node.data.args_vec.elements[0], "./", 2))
	{
		printf("minishell : %s: command not found\n",
			scn->node.data.args_vec.elements[0]);
		g_vars.last_err_num = 127;
	}
	else if ((scn->node.data.args_vec.elements[0][0] == '/'
		|| (!ft_strncmp(scn->node.data.args_vec.elements[0], "./", 2)))
		&& num->y)
	{
		if (!stat(num->tab[num->i], &buff))
		{
			g_vars.last_err_num = 126;
			printf("minishell: %s: is a directory\n",
				scn->node.data.args_vec.elements[0]);
		}
		else
		{
			g_vars.last_err_num = 127;
			printf("minishell: %s: No such file or directory\n",
				scn->node.data.args_vec.elements[0]);
		}
	}
}

void	execv_main_loop(t_rand *num, t_ast *scn, t_varso *vars)
{
	while (num->tab[num->i])
	{
		num->y = 0;
		num->x = 0;
		if (!check_command(scn, num->sticker, vars, num))
			return ;
		if (!stat(num->tab[num->i], &num->buff))
		{
			num->pid = fork();
			if (num->pid == 0)
			{
				if (execve(num->tab[num->i], scn->node.data.args_vec.elements,
						vars->export.env) == -1)
					exit(1);
			}
			waitpid(num->pid, &num->status, 0);
			if (WIFEXITED(num->status))
				g_vars.last_err_num = WEXITSTATUS(num->status);
			if (WEXITSTATUS(num->status))
				num->y = 1;
			else if (!WEXITSTATUS(num->status))
				change_value("_", num->tab[num->i]);
			break ;
		}
		num->i++;
	}
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
	merge_env(scn, vars);
	num.i = 0;
	execv_main_loop(&num, scn, vars);
	if (stat(num.tab[num.i], &num.buff))
		num.y = 1;
	execv_errors(&num, scn, num.buff);
	num.i = 0;
	while (vars->export.env[num.i])
		free(vars->export.env[num.i++]);
	free(vars->export.env);
	if (k)
		free(num.sticker);
	num.i = 0;
	while (num.tab[num.i])
		free(num.tab[num.i++]);
	free(num.tab);
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
	else if (!WEXITSTATUS(status))
	{
		change_value("_", scn->node.data.args_vec.elements[0]);
	}
}

void	without_path_slash(t_varso *vars, t_ast *scn)
{
	int			y;
	pid_t		pid;
	struct stat	buff;
	int			status;

	y = 0;
	merge_env(scn, vars);
	if (!stat(scn->node.data.args_vec.elements[0], &buff))
		execute_path(&y, scn, vars);
	if (!stat(scn->node.data.args_vec.elements[0], &buff) && y)
	{	
		g_vars.last_err_num = 126;
		printf("minishell: %s: is a directory\n",
			scn->node.data.args_vec.elements[0]);
	}
	else if (stat(scn->node.data.args_vec.elements[0], &buff))
	{
		g_vars.last_err_num = 127;
		printf("minishell: %s: No such file or directory\n",
			scn->node.data.args_vec.elements[0]);
	}
}

void	exv(t_ast *scn, t_varso *vars)
{
	t_exv_vars	exv;

	getcwd(exv.cwd, sizeof(exv.cwd));
	exv.path = find_env("PATH");
	if (exv.path && scn->node.data.args_vec.elements[0][0])
	{
		with_path(exv.path, vars, scn);
	}
	else if (!exv.path && scn->node.data.args_vec.elements[0][0] == '/')
		without_path_slash(vars, scn);
	else
		printf("minishell : %s: command not found\n",
			scn->node.data.args_vec.elements[0]);
	return ;
}

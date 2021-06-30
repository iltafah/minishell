/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iariss <iariss@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 10:42:54 by iariss            #+#    #+#             */
/*   Updated: 2021/06/30 10:43:56 by iariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"
#include "minishell.h"

void	cd(char **args, t_varso *vars)
{
	struct stat buffer;
	char *path;
	char *home;
	char cwd[PATH_MAX];
	int		f;

	f = 0;
	home = find_env("HOME");
	if (!args[1])
	{
		if (home)
			path = home;
		else
		{
			printf("minishell: cd: HOME not set\n");
			g_vars.last_err_num = 1;
			return ;
		}
	}
	else
	{
		path = args[1];
	}
	check_path(&path, vars, &f);
	getcwd(cwd, sizeof(cwd));
	vars->prev_path = cwd;
	change_value("OLDPWD", vars->prev_path);
	if (stat(path, &buffer) == -1)
	{
		error_msg("minishell: cd:No such file or directory\n");
		g_vars.last_err_num = 1;
	}
	else if (chdir(path) != 0 && getcwd(cwd, sizeof(cwd)))
	{
		error_msg("chdir failed\n");
		g_vars.last_err_num = 1;
	}
	else if (!getcwd(cwd, sizeof(cwd)))
	{
		printf("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
		g_vars.last_err_num = 1;
	}
	getcwd(cwd, sizeof(cwd));
	if (f)
		free(path);
	path = ft_strdup(cwd);
	change_value("PWD", path);
	free(path);
}

void	check_path(char **path, t_varso *vars, int *f)
{
	char *new;

	new = find_home();
	if (*path[0] == '~' || !(ft_strcmp(*path, "~/")))
	{
		if ((ft_strlen(*path) == 1 && *path[0] == '~') || ft_strlen(*path) == 2)
		{
			*path = ft_strdup(new);
			*f = 1;
		}
		else
		{
			*path = ft_strjoin(new, *path + 1);
			*f = 1;
		}
		return ;
	}
	return ;
}

void	change_value(char *name, char *new_value)
{
	int i;
	i = 0;
	
	while (i <= g_vars.env_table.name.last_index)
	{
		if (!(ft_strncmp(g_vars.env_table.name.elements[i], name, ft_strlen(name))))
		{
			g_vars.env_table.value.replace_element_at_index( &g_vars.env_table.value, ft_strdup(new_value), i);
			return ;
		}
		i++;
	}
}

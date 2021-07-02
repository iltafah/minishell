/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iariss <iariss@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 12:56:09 by iariss            #+#    #+#             */
/*   Updated: 2021/07/02 15:08:14 by iariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"
#include "minishell.h"
#include <string.h>

void	ft_printf_string(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
}

void	error_msg(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(2, &s[i], 1);
		i++;
	}
}

char	*find_var(char *s)
{
	int	i;

	i = 0;
	while (i <= g_vars.env_table.name.last_index)
	{
		if (!ft_strncmp(g_vars.env_table.name.elements[i],
				s + 1, ft_strlen(s) - 1))
		{
			return (g_vars.env_table.value.elements[i]);
		}
		i++;
	}
	return (NULL);
}

char	*find_env(char *targ)
{
	int	i;

	i = 0;
	while (i <= g_vars.env_table.name.last_index)
	{
		if (!(ft_strncmp(g_vars.env_table.name.elements[i],
					targ, ft_strlen(targ))))
		{
			return (g_vars.env_table.value.elements[i]);
		}
		i++;
	}
	return (NULL);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*a1;
	unsigned char	*a2;

	a1 = (unsigned char *)s1;
	a2 = (unsigned char *)s2;
	while (*a1 && *a2)
	{
		if (*a1 != *a2)
			return (*a1 - *a2);
		a1++;
		a2++;
	}
	return (*a1 - *a2);
}

void	handle_quit(int sig_num)
{
	if (sig_num == SIGQUIT)
	{
		write(2, "^\\Quit: 3\n", 10);
	}
}

void	handle_c(int sig_num)
{
	if (sig_num == SIGINT)
	{
		write(2, "^C\n", 3);
	}
}

void	pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	else if (find_env("PWD"))
		printf("%s\n", find_env("PWD"));
	else
	{
		g_vars.last_err_num = 1;
		printf("error retrieving current directory: getcwd: cannot ");
		printf("access parent directories: No such file or directory\n");
	}
}

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
		check_redis(scn);
	if (scn->node.data.args_vec.used_size)
		builtins(scn, &vars);
}

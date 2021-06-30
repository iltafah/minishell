/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iariss <iariss@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 12:56:09 by iariss            #+#    #+#             */
/*   Updated: 2021/06/30 11:10:58 by iariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"
#include "minishell.h"
#include <string.h>

void	ft_printf_string(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
}

void	error_msg(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		write(2, &s[i], 1);
		i++;
	}
}

char	*find_var(char *s)
{
	int i;

	i = 0;
	while (i <= g_vars.env_table.name.last_index)
	{
		if (!ft_strncmp(g_vars.env_table.name.elements[i], s + 1, ft_strlen(s) - 1))
		{
			return (g_vars.env_table.value.elements[i]);
		}
		i++;
	}
	return (NULL);
}

int check_echo(char **v)
{
	int i;

	i = 0;
	while (v[i])
	{
		i++;
	}
	if (i == 1)
	{
		printf("\n");
		return (0);
	}
	return(i);
}

void	echo(char **v, t_varso *vars)
{

	int i;
	int j;
	int k;
	int num_args;
	
	i = 0;
	j = 1;
	k = 2;
	num_args = check_echo(v);
	if (!num_args)
		return ;
	while (j < num_args && !ft_strncmp(v[j], "-n", 2))
	{
		k = 2;
		while (v[j][k])
		{
			if(v[j][k] != 'n')
			{
				k = 0;
				break ;
			}
			k++;
		}
		if (!k)
			break ;
		j++;
		i = 1;
	}
	while (v[j])
	{
		ft_printf_string(v[j]);
		j++;
		if (v[j])
			write(1, " ", 1);
	}
	if (!i)
		write(1, "\n", 1);
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

char	*find_env(char *targ)
{
	int i;

	i = 0;
	while (i <= g_vars.env_table.name.last_index)
	{
		if (!(ft_strncmp(g_vars.env_table.name.elements[i], targ, ft_strlen(targ))))
		{
			return (g_vars.env_table.value.elements[i]);
		}
		i++;
	}
	return (NULL);
}

void	old_export(char **env, char *path)
{
	int i;
	int x;

	x = 0;
	i = 0;
	while (path[x] && path[x] != '=')
	{
		x++;	
	}
	while (env[i])
	{
		if (!ft_strncmp(env[i], path, x))
		{
			env[i] = path;
			return ;
		}
		i++;
	}
	env[i] = path;
	env[i + 1] = NULL;
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

char	*find_home()
{
	char	*home;
	char	cwd[PATH_MAX];
	int		i;
	int		slash;

	i = 0;
	slash = 2;
	getcwd(cwd, sizeof(cwd));
	while (cwd[i] && slash)
	{
		i++;
		if (cwd[i] == '/')
			slash--;
	}
	home = ft_substr(cwd, 0, i);
	return (home);
}

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
	else if (chdir(path) != 0 && getcwd(cwd, sizeof(cwd))
	{
		error_msg("chdir failed\n");
		g_vars.last_err_num = 1;
	}
	else if (!getcwd(cwd, sizeof(cwd)))
	{
		printf("")
	}
	getcwd(cwd, sizeof(cwd));
	if (f)
		free(path);
	path = ft_strdup(cwd);
	change_value("PWD", path);
	free(path);
}


void	next(char **env, int index)
{
	int i;

	i = index;
	while (env[i])
	{
		env[i] = env[i + 1];
		i++;
	}
}

void	unset(t_ast *scn, t_varso *vars)
{
	int x;
	int	i;
	int	j;
	char **args;

	j = 0;
	i = 1;
	args = scn->node.data.args_vec.elements;
	while (i <= scn->node.data.args_vec.last_index)
	{
		x = 0;
		while (args[i][x] && args[i][x] != '=')
			x++;
		if ((x == 1 && args[i][0] && args[i][0] == '='))
		{
			printf("minishell: unset: `=': not a valid identifier\n");
			g_vars.last_err_num = 1;
		}
		if (!ft_isalpha(args[i][0]) || (!ft_isalpha(args[i][ft_strlen(args[i]) - 1]) && !ft_isdigit(args[i][ft_strlen(args[i]) - 1])))
		{
			printf("minishell: unset: '%s': not a valid identifier\n", args[i]);
			g_vars.last_err_num = 1;
		}
		else
		{
			j = 0;
			while (j <= g_vars.env_table.name.last_index)
			{
				if(!(ft_strncmp(args[i], g_vars.env_table.name.elements[j], x)))
				{
					printf("%s | %d\n", args[i], x);
					g_vars.env_table.name.delete_element_at_index(&g_vars.env_table.name, j);
					g_vars.env_table.value.delete_element_at_index(&g_vars.env_table.value, j);
				}
				j++;
			}
		}
		i++;
	}
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


void	swap_values(char **s1, char **s2)
{
	char *tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

void	sort_expo(t_varso *vars)
{
	int i;
	int j;
	int x;
	char *smallest;
	int k;

	i = 0;
	smallest = g_vars.env_table.name.elements[0];
	while (i <= g_vars.env_table.name.last_index)
	{
		j = i;
		smallest = vars->export.names[i];
		k = i;
		while (j <= g_vars.env_table.name.last_index)
		{
			if (ft_strcmp(vars->export.names[j], smallest) < 0)
			{
				smallest = vars->export.names[j];
				k = j;
			}
			j++;
		}
		swap_values(&vars->export.names[i], &vars->export.names[k]);
		swap_values(&vars->export.values[i], &vars->export.values[k]);
		i++;
	}
	i = 0;
	while (i <= g_vars.env_table.name.last_index)
	{
		j = 0;
		while(vars->export.names[i][j] && vars->export.names[i][j] != '=')
			j++;
		if (!vars->export.values[i])
			printf("declare -x %s\n", vars->export.names[i]);
		else	
			printf("declare -x %s=\"%s\"\n", vars->export.names[i], vars->export.values[i]);
		i++;
	}
}

void	empty_expo(t_varso *vars)
{
	int i;
	int j;
	char *tmp;
	char lost;

	i = 0;
	j = 0;
	while (i <= g_vars.env_table.name.last_index)
	{
		vars->export.names[i] = g_vars.env_table.name.elements[i];	
		vars->export.values[i] = g_vars.env_table.value.elements[i];
		i++;
	}
	vars->export.names[i] = NULL;
	vars->export.values[i] = NULL;
	sort_expo(vars);
}

int	check_args(char **args, t_ast *all, int x, int lp)
{
	int i;
	char	*new_value;
	char	*new_name;
	char	*subbed;

	i = 0;
	if (args[lp][0] == '-')
	{
		subbed = ft_substr(args[lp], 0, 2);
		printf("minishell: export: %s: invalid option\nexport: usage: export [-nf] [name[=value] ...] or export -p\n", subbed);
		g_vars.last_err_num = 2;
	}
	else if (ft_isdigit(args[lp][0]))
	{
		printf("minishell: export: `%s': not a valid identifier\n", args[lp]);
		g_vars.last_err_num = 1;
		return (0);
	}
	else if ((x == 1 && args[lp][0] && args[lp][0] == '='))
	{
		printf("minishell: export: `=': not a valid identifier\n");
		g_vars.last_err_num = 1;
		return (0);
	}
	else if (((!ft_isalpha(args[lp][0]) || (!ft_isalnum(args[lp][ft_strlen(args[lp]) - 1])
	&& args[lp][ft_strlen(args[lp]) - 1] != '='))) && args[lp][0] != '_' && args[lp][ft_strlen(args[lp]) - 1] != '_')
	{
		printf("minishell: export: '%s': not a valid identifier\n", args[lp]);
		g_vars.last_err_num = 1;
		return (0);
	}
	return (1);
}

void	add_to_vars(char *add, int x)
{
	int i;

	i = 0;
	while(i <= g_vars.env_table.name.last_index)
	{
		if (!(ft_strcmp(g_vars.env_table.name.elements[i], ft_substr(add, 0, x))))
		{
			if (!g_vars.env_table.value.elements[i])
				g_vars.env_table.value.elements[i] = ft_strdup("");
			g_vars.env_table.value.replace_element_at_index(&g_vars.env_table.value, ft_strjoin(g_vars.env_table.value.elements[i], add + x + 2), i);
			return ;
		}
		i++;
	}
	g_vars.env_table.name.add_new_element(&g_vars.env_table.name, ft_substr(add, 0, x));
	g_vars.env_table.value.add_new_element(&g_vars.env_table.value, ft_strdup(add + x + 2));
}

void	export(char **args, t_varso *vars, t_ast *sim_cmd_nd)
{
	int i;
	int x;
	int	lp;

	x = 0;
	i = 0;
	lp = 1;
	vars->export.names = malloc(sizeof(char *) * g_vars.env_table.name.used_size);
	vars->export.values = malloc(sizeof(char *) * g_vars.env_table.value.used_size);
	if (!args[1])
	{
		empty_expo(vars);
		return ;
	}
	else
	{
		while(lp <= sim_cmd_nd->node.data.args_vec.last_index)
		{
			x = 0;
			while (args[lp][x] && args[lp][x] != '=' && ft_strncmp(args[lp] + x , "+=", 2))
			{
				x++;	
			}
			if (check_args(args, sim_cmd_nd, x, lp))
			{	
				if (!ft_strncmp(args[lp] + x, "+=", 2))
				{
					add_to_vars(args[lp], x);
				}
				else
				{	
					i = 0;
					while (i <= g_vars.env_table.name.last_index)
					{
						if(!ft_strcmp(g_vars.env_table.name.elements[i], ft_substr(args[lp], 0, x)) && args[lp][x])
						{
							g_vars.env_table.value.replace_element_at_index( &g_vars.env_table.value, ft_strdup(args[lp] + x + 1), i);
							return ;
						}
						if (!args[lp][x])
							return ;
						i++;
					}
					g_vars.env_table.name.add_new_element(&g_vars.env_table.name, ft_substr(args[lp], 0, x));
					if (ft_strlen(args[lp]) == x && !args[lp][x])
						g_vars.env_table.value.add_new_element(&g_vars.env_table.value, NULL);
					else
						g_vars.env_table.value.add_new_element(&g_vars.env_table.value, ft_substr(args[lp], x + 1, ft_strlen(args[lp]) - x));
				}
			}
			lp++;
		}
	}
	free(vars->export.names);
	free(vars->export.values);
}

void	enviro()
{
	int i;

	i = 0;
	while (i <= g_vars.env_table.name.last_index)
	{
		if (g_vars.env_table.value.elements[i] != NULL)
			printf("%s=%s\n", g_vars.env_table.name.elements[i], g_vars.env_table.value.elements[i]);
		i++;
	}
}

void	merge_env(t_ast *scn, t_varso *vars)
{
	int i;
	char *tmp;
	
	i = 0;
	vars->export.env = (char **)malloc(sizeof(char *) * g_vars.env_table.name.used_size);
	while (i <= g_vars.env_table.name.last_index)
	{
		vars->export.env[i] = ft_strjoin(g_vars.env_table.name.elements[i], "=");
		if (!g_vars.env_table.value.elements[i])
			g_vars.env_table.value.elements[i] = "";
		// tmp = vars->export.env[i];
		vars->export.env[i] = ft_strjoin(vars->export.env[i], g_vars.env_table.value.elements[i]);
		// free(tmp);
		i++;	
	}
	vars->export.env[i] = NULL;
}

void	check_redis(t_ast *scn)
{
	int fd;
	int dep;
	t_data_content head;
	char	*input;
	char	*all;
	int		x;
	int dupp;
	int out;
	int		*p;

	head = scn->node.data;
	x = 1;
	while (head.redirections)
	{
		if(!(ft_strcmp(head.redirections->type, ">")))
		{
			fd = open(head.redirections->file, O_CREAT | O_RDWR | O_TRUNC, 0644);
			if(head.args_vec.used_size)
				dup2(fd, 1);
			close(fd);
		}
		else if(!(ft_strcmp(head.redirections->type, "<")))
		{
			fd = open(head.redirections->file, O_RDONLY);
			if(fd == -1)
			{
				printf("minishell: %s: No such file or directory\n", head.redirections->file);
				g_vars.last_err_num = 1;
			}
			else
			{
				dup2(fd, 0);
				close(fd);
			}
		}
		else if(!(ft_strcmp(head.redirections->type, ">>")))
		{
			fd = open(head.redirections->file, O_RDWR | O_APPEND | O_CREAT, 0644);
			dup2(fd, 1);
			close(fd);
		}
		else if(!(ft_strcmp(head.redirections->type, "<<")))
		{
			p = malloc(sizeof(int) * 2);
			// dupp = dup(0);
			pipe(p);
			write(p[1], head.redirections->file, ft_strlen(head.redirections->file));
			dup2(p[0], 0);
			close (p[1]);
			close (p[0]);
			free(p);
		}
		head.redirections = head.redirections->next;
	}
}

void	add_one(t_varso *vars)
{
	int i;

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

int	check_exit_num(char *num, int j, t_ast *scn)
{
	char	*max_long;

	max_long = "9223372036854775807";
	// printf("%d\n", j);
	if (num[0] != '-' && (ft_strlen(num) != j || (ft_strlen(num) > 19 && num[0] != '0') ||
	(ft_strlen(num) == 19 && ft_strncmp(max_long, num, ft_strlen(num)) < 0)))
	{
		printf("exit\nminishell: exit: %s: numeric argument required\n", num);
		exit(255);
	}
	else if (num[0] == '-' && (ft_strlen(num) != j || (ft_strlen(num) > 20 && num[0] != '0') ||
	(ft_strlen(num) == 20 && ft_strncmp(max_long, num, ft_strlen(num)) < 0)))
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

void	check_exit(t_ast *scn)
{
	int i;
	int j;
	char *nb;
	int	ex_num;

	j = 0;
	i = 1;
	while (i <= scn->node.data.args_vec.last_index)
	{
		if (scn->node.data.args_vec.last_index == 1)
		{
			j = 0;
			while (scn->node.data.args_vec.elements[i][j])
			{
				if(!ft_isdigit(scn->node.data.args_vec.elements[i][j]) && scn->node.data.args_vec.elements[i][0] != '-')
					break ;
				j++;
			}
			check_exit_num(scn->node.data.args_vec.elements[i], j, scn);
		}
		else if (scn->node.data.args_vec.last_index > 1)
		{
			j = 1;
			while (scn->node.data.args_vec.elements[i][j])
			{
				if(!ft_isdigit(scn->node.data.args_vec.elements[i][j]))
					break ;
				j++;
			}
			if (ft_strlen(scn->node.data.args_vec.elements[i]) != j)
			{
				printf("exit\nminishell: exit: %s: numeric argument required\n", scn->node.data.args_vec.elements[i]);
				exit(ft_atoi(scn->node.data.args_vec.elements[i]));
			}
			printf("exit\nminishell: exit: too many arguments\n");
			g_vars.last_err_num = 1;
			break ;
		}
		i++;
	}
	if (scn->node.data.args_vec.last_index == 0)
	{
		// g_vars.last_err_num = 0;
		exit(g_vars.last_err_num);
	}
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

void	execution(t_ast *scn, int num_pipes)
{
	char *first_arg;
	char	cwd[255];
	t_varso	vars;

	getcwd(cwd, sizeof(cwd));
	vars.prev_path = cwd;
	// vars.pwd = cwd;
	first_arg = scn->node.data.args_vec.elements[0];
	signal(SIGQUIT, handle_quit);
	signal(SIGINT, handle_c);
	if (scn->node.data.redirections)
	{
		check_redis(scn);
	}
	if (scn->node.data.args_vec.used_size)
	{
		if (!ft_strcmp(first_arg, "echo"))
		{
			echo(scn->node.data.args_vec.elements, &vars);
		}
		else if (!ft_strcmp(first_arg, "cd"))
		{
			cd(scn->node.data.args_vec.elements, &vars);
		}
		else if (!ft_strcmp(first_arg, "pwd"))
		{
			if (getcwd(cwd, sizeof(cwd))) 
				printf("%s\n", cwd);
			// else if (find_env("PWD"))
			// 	printf("%s\n", find_env("PWD"));
			else
				printf("error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
		}
		else if (!ft_strcmp(first_arg, "export"))
		{
			export(scn->node.data.args_vec.elements, &vars, scn);
		}
		else if (!ft_strcmp(first_arg, "unset"))
		{
			unset(scn, &vars);
		}
		else if (!ft_strcmp(first_arg, "env"))
		{
			enviro();
		}
		else if (!ft_strcmp(first_arg, "exit"))
		{
			check_exit(scn);
		}
		else
		{
			exv(scn, &vars);
		}
	}
}

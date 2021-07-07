/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iariss <iariss@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 16:47:17 by iariss            #+#    #+#             */
/*   Updated: 2021/07/03 20:15:47 by iariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"
#include "minishell.h"

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
	// i = 0;
	// while (vars->export.env[i])
	// 	printf("%s\n", vars->export.env[i++]);
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

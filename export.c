/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iariss <iariss@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 10:48:41 by iariss            #+#    #+#             */
/*   Updated: 2021/07/02 09:34:01 by iariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"
#include "minishell.h"

void	export_add(char **args, int lp, int x)
{
	int	i;
	int	in;

	i = 0;
	in = 0;
	while (i <= g_vars.env_table.name.last_index)
	{
		if (!ft_strcmp(g_vars.env_table.name.elements[i],
				ft_substr(args[lp], 0, x)) && args[lp][x])
		{
			g_vars.env_table.value.replace_element_at_index(
			&g_vars.env_table.value, ft_strdup(args[lp] + x + 1), i);
			in = 1;
		}
		else if (!ft_strcmp(g_vars.env_table.name.elements[i],
				ft_substr(args[lp], 0, x)) && !args[lp][x])
			in = 1;
		i++;
	}
	if (!in)
	{
		g_vars.env_table.name.add_new_element(&g_vars.env_table.name,
		ft_substr(args[lp], 0, x));
		if (ft_strlen(args[lp]) == x && !args[lp][x])
			g_vars.env_table.value.add_new_element(
				&g_vars.env_table.value, NULL);
		else
			g_vars.env_table.value.add_new_element(&g_vars.env_table.value,
			ft_substr(args[lp], x + 1, ft_strlen(args[lp]) - x));
	}
}

void	export_add_vars(t_ast *scn, char **args)
{
	int	lp;
	int	x;

	lp = 1;
	while (lp <= scn->node.data.args_vec.last_index)
	{
		x = 0;
		while (args[lp][x] && args[lp][x] != '=' &&
		ft_strncmp(args[lp] + x, "+=", 2))
			x++;
		if (check_args(args, scn, x, lp))
		{	
			if (!ft_strncmp(args[lp] + x, "+=", 2))
				add_to_vars(args[lp], x);
			else
				export_add(args, lp, x);
		}
		lp++;
	}
}

void	export(char **args, t_varso *vars, t_ast *sim_cmd_nd)
{
	int	i;
	int	x;
	int	lp;
	int	in;

	x = 0;
	i = 0;
	lp = 1;
	vars->export.names = malloc(sizeof(char *)
			* g_vars.env_table.name.used_size);
	vars->export.values = malloc(sizeof(char *)
			* g_vars.env_table.value.used_size);
	if (!args[1])
	{
		empty_expo(vars);
		return ;
	}
	else
		export_add_vars(sim_cmd_nd, args);
	free(vars->export.names);
	free(vars->export.values);
}

void	add_to_vars(char *add, int x)
{
	int	i;

	i = 0;
	while (i <= g_vars.env_table.name.last_index)
	{
		if (!(ft_strcmp(g_vars.env_table.name.elements[i],
					ft_substr(add, 0, x))))
		{
			if (!g_vars.env_table.value.elements[i])
				g_vars.env_table.value.elements[i] = ft_strdup("");
			g_vars.env_table.value.replace_element_at_index(
				&g_vars.env_table.value,
			ft_strjoin(g_vars.env_table.value.elements[i], add + x + 2), i);
			return ;
		}
		i++;
	}
	g_vars.env_table.name.add_new_element(&g_vars.env_table.name,
	ft_substr(add, 0, x));
	g_vars.env_table.value.add_new_element(&g_vars.env_table.value,
	ft_strdup(add + x + 2));
}

int	check_args(char **a, t_ast *all, int x, int lp)
{
	t_expo_vars	cv;

	cv.i = 0;
	if (a[lp][0] == '-')
	{
		cv.subbed = ft_substr(a[lp], 0, 2);
		printf("minishell: export: %s: invalid option\n", cv.subbed);
		printf("export: usage: export [-nf] [name[=value] ...] or export -p\n");
		g_vars.last_err_num = 2;
	}
	else if (ft_isdigit(a[lp][0]))
	{
		printf("minishell: export: `%s': not a valid identifier\n", a[lp]);
		g_vars.last_err_num = 1;
		return (0);
	}
	else if (((!ft_isalpha(a[lp][0])
			|| (!ft_isalnum(a[lp][ft_strlen(a[lp]) - 1])
			&& a[lp][ft_strlen(a[lp]) - 1] != '=')))
			&& a[lp][0] != '_' && a[lp][ft_strlen(a[lp]) - 1] != '_')
	{
		printf("minishell: export: '%s': not a valid identifier\n", a[lp]);
		g_vars.last_err_num = 1;
		return (0);
	}
	return (1);
}

void	empty_expo(t_varso *vars)
{
	int		i;
	int		j;
	char	*tmp;
	char	lost;

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

void	sort_loop(t_expo_vars *exp, t_varso *vars)
{
	exp->j = exp->i;
	exp->smallest = vars->export.names[exp->i];
	exp->k = exp->i;
	while (exp->j <= g_vars.env_table.name.last_index)
	{
		if (ft_strcmp(vars->export.names[exp->j], exp->smallest) < 0)
		{
			exp->smallest = vars->export.names[exp->j];
			exp->k = exp->j;
		}
		exp->j++;
	}
	swap_values(&vars->export.names[exp->i], &vars->export.names[exp->k]);
	swap_values(&vars->export.values[exp->i], &vars->export.values[exp->k]);
	exp->i++;
}

void	sort_expo(t_varso *vars)
{
	t_expo_vars	exp;

	exp.i = 0;
	exp.smallest = g_vars.env_table.name.elements[0];
	while (exp.i <= g_vars.env_table.name.last_index)
		sort_loop(&exp, vars);
	exp.i = 0;
	while (exp.i <= g_vars.env_table.name.last_index)
	{
		exp.j = 0;
		while (vars->export.names[exp.i][exp.j] &&
				vars->export.names[exp.i][exp.j] != '=')
			exp.j++;
		if (!vars->export.values[exp.i])
		{
			printf("declare -x %s\n", vars->export.names[exp.i]);
		}
		else
		{
			printf("declare -x %s=\"%s\"\n", vars->export.names[exp.i],
				vars->export.values[exp.i]);
		}
		exp.i++;
	}
}

void	swap_values(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

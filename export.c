/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iariss <iariss@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 10:48:41 by iariss            #+#    #+#             */
/*   Updated: 2021/06/30 10:50:26 by iariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"
#include "minishell.h"

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

void	swap_values(char **s1, char **s2)
{
	char *tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}
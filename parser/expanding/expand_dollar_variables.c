/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_variables.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 19:32:55 by iltafah           #+#    #+#             */
/*   Updated: 2021/06/19 11:23:29 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"

int	expand_quoted_var(char *str, int *i, t_char_vec *vec)
{
	char		*name;
	char		*value;
	int			is_expanded;

	is_expanded = false;
	name = get_dollar_name(str, i);
	if (name != NULL)
	{
		value = get_dollar_value(name);
		vec->add_set_of_elements_at_index(vec, value, vec->used_size);
		is_expanded = true;
		free(name);
	}
	return (is_expanded);
}

int	expand_unquoted_var(char *str, int *i, t_char_vec *vec)
{
	char		*name;
	char		*value;
	int			is_expanded;

	is_expanded = false;
	if (str[*i + 1] == SP_DOUBLE_QUOTES || str[*i + 1] == SP_SINGLE_QUOTES)
	{
		*i += 1;
		is_expanded = true;
	}
	else
	{
		name = get_dollar_name(str, i);
		if (name != NULL)
		{
			value = get_dollar_value(name);
			vec->add_set_of_elements_at_index(vec, value, vec->used_size);
			is_expanded = true;
			free(name);
		}
	}
	return (is_expanded);
}

void	initialize_expanding_vars(t_expnd_vars *vars)
{
	initialize_vec_of_char(&vars->arg_vec);
	initialize_quotes_vars(&vars->quotes);
}

void	expand_dollar_vars(char **arg)
{
	t_expnd_vars	vars;
	int				i;
	int				is_expanded;

	i = 0;
	initialize_expanding_vars(&vars);
	while ((*arg)[i] != '\0')
	{
		if ((*arg)[i] == SP_SINGLE_QUOTES || (*arg)[i] == SP_DOUBLE_QUOTES)
			open_and_close_quotes((*arg)[i], &vars.quotes);
		else if ((*arg)[i] == DOLLAR && vars.quotes.backslash == NONE
			&& vars.quotes.single_quotes == CLOSED)
		{
			if (vars.quotes.double_quotes == OPEND)
				is_expanded = expand_quoted_var(*arg, &i, &vars.arg_vec);
			else
				is_expanded = expand_unquoted_var(*arg, &i, &vars.arg_vec);
			if (is_expanded == true)
				continue ;
		}
		does_backslash_exist((*arg)[i], &vars.quotes);
		vars.arg_vec.add_new_element(&vars.arg_vec, (*arg)[i++]);
	}
	free(*arg);
	*arg = vars.arg_vec.elements;
}

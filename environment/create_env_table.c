/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env_table.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 19:46:06 by iltafah           #+#    #+#             */
/*   Updated: 2021/06/25 09:48:18 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./environment.h"

void	extract_env_data(t_str_vec *name_vec, t_str_vec *value_vec, char *env)
{
	int		len;
	char	*name;
	char	*value;

	len = 0;
	while (env[len] != '=')
		len++;
	name = ft_substr(env, 0, len);
	value = ft_strdup(env + len + 1);
	if (strcmp(name, "OLDPWD") != 0)
	{
		name_vec->add_new_element(name_vec, name);
		value_vec->add_new_element(value_vec, value);
	}
	else
	{
		free(name);
		free(value);
	}
}


#include <stdio.h>

void	create_env_table(t_env_table *env_table, char **env)
{
	int		i;

	i = -1;
	initialize_vec_content(&env_table->name);
	initialize_vec_content(&env_table->value);
	while (env[++i])
		extract_env_data(&env_table->name, &env_table->value, env[i]);
}

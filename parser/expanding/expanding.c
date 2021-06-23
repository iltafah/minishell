/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 19:35:38 by iltafah           #+#    #+#             */
/*   Updated: 2021/06/23 20:01:57 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./expanding.h"

void	expand_args_vec(t_str_vec *args_vec)
{
	int			i;

	i = 0;
	while (args_vec->elements[i])
	{
		give_quotes_special_meaning(args_vec->elements[i]);
		expand_dollar_vars(&args_vec->elements[i]);
		split_element_to_args(args_vec, &i);
	}
}

void	expand_redirection_list(t_redirection *rdir_list)
{
	t_redirection	*curr_redir_node;

	curr_redir_node = rdir_list;
	while (curr_redir_node != NULL)
	{
		if (strcmp(curr_redir_node->type, "<<") != 0)
		{
			give_quotes_special_meaning(curr_redir_node->file);
			expand_dollar_vars(&curr_redir_node->file);
			remove_special_quotes(&curr_redir_node->file);
		}
		curr_redir_node = curr_redir_node->next;
	}
}

void	expand_curr_cmd(t_ast *curr_simple_cmd)
{
	t_ast	*data;

	data = curr_simple_cmd->node.dir.bottom;
	expand_args_vec(&data->node.data.args_vec);
	expand_redirection_list(data->node.data.redirections);
	g_vars.last_err_num = 0;
}

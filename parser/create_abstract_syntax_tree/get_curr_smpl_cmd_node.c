/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_curr_smpl_cmd_node.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 21:51:16 by iltafah           #+#    #+#             */
/*   Updated: 2021/07/14 21:51:29 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./create_abstract_syntax_tree.h"

t_ast *get_curr_smpl_cmd_node(t_ast *pipeline_seq)
{
	static t_ast	*curr_smpl_cmd = NULL;
	static int		first = 1;

	if (pipeline_seq)
	{
		if (first == 1)
			curr_smpl_cmd = pipeline_seq->node.pipe.dir.bottom;
		else if (curr_smpl_cmd != NULL)
			curr_smpl_cmd = curr_smpl_cmd->node.dir.next;
		first++;
	}
	if (curr_smpl_cmd == NULL)
		first = 1;
	return (curr_smpl_cmd);
}

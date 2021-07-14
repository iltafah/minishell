/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_curr_pipeline_seq_node.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 21:50:48 by iltafah           #+#    #+#             */
/*   Updated: 2021/07/14 21:51:08 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./create_abstract_syntax_tree.h"

t_ast *get_curr_pipeline_seq_node(t_ast *ast)
{
	static t_ast	*curr_pipeline_seq = NULL;
	static int		first = 1;

	if (ast)
	{
		if (first == 1)
			curr_pipeline_seq = ast->node.dir.bottom;
		else if (curr_pipeline_seq != NULL)
			curr_pipeline_seq = curr_pipeline_seq->node.pipe.dir.next;
		first++;
	}
	if (curr_pipeline_seq == NULL)
		first = 1;	
	return (curr_pipeline_seq);
}

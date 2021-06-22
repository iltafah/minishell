/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_herdocs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 17:55:27 by iltafah           #+#    #+#             */
/*   Updated: 2021/06/22 17:55:52 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char	*treat_herdocs(char *delimiter)
{
	char		*herdoc_line;
	t_char_vec	buffer_vec;

	initialize_vec_of_char(&buffer_vec);
	while (true)
	{
		herdoc_line = readline(">> ");
		if (strcmp(herdoc_line, delimiter) == 0)
			break ;
		buffer_vec.add_set_of_elements(&buffer_vec, herdoc_line);
		buffer_vec.add_new_element(&buffer_vec, '\n');
		free(herdoc_line);
	}
	free(herdoc_line);
	return (buffer_vec.elements);
}

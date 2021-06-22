/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_after_cursor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 19:49:29 by iltafah           #+#    #+#             */
/*   Updated: 2021/06/13 19:49:31 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../readline.h"

void	print_after_cursor(t_rdline *rdl_vars, char *str, int option)
{
	int		i;

	i = 0;
	if (option == restore)
		save_curr_cursor_pos(rdl_vars);
	clear_curr_line_after_cursor(rdl_vars);
	while (str[i])
	{
		rdl_print_char(rdl_vars, str[i], WHT);
		i++;
	}
	if (option == restore)
		restore_cursor_pos(rdl_vars);
}

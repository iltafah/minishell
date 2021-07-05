/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_curr_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 19:49:26 by iltafah           #+#    #+#             */
/*   Updated: 2021/07/04 20:57:49 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../readline.h"

void	print_curr_char(t_rdline *rdl_vars, char c)
{
	t_char_vec		*history_line;
	t_vchar_vec		*history_vec;
	int				*l_i;
	int				*c_i;

	c_i = &rdl_vars->c_i;
	l_i = &rdl_vars->l_i;
	history_vec = &rdl_vars->history_vec;
	history_line = history_vec->elements;
	history_line[*l_i].add_new_element_at_index(&history_line[*l_i], c, *c_i);
	print_line_with_chosen_method(rdl_vars, history_line[*l_i].elements + *c_i,
		restore);
	if (rdl_vars->auto_suggestions == on)
		print_suggestions(rdl_vars);
	
	move_cursor_right(rdl_vars);
	if (rdl_vars->curs_colm_pos == rdl_vars->width_of_screen)
	{
		// sleep(2);
		// fprintf(fd1, "print ? and make curs colm 0\n");
		// fflush(fd1);
		// put_char('?');
		move_cursor_start_of_next_line(rdl_vars);
		rdl_vars->curs_row_pos++;
		rdl_vars->curs_colm_pos = 0;
		// clear_curr_line_after_cursor(rdl_vars);
	}
	// else
	// {
	// 	fprintf(fd1, "don't move me right onichan\n");
	// 	fflush(fd1);
	// }
	// if (rdl_vars->curs_colm_pos == rdl_vars->width_of_screen - 1)
	// 	move_cursor_start_of_next_line(rdl_vars);
	// else
	// 	move_cursor_right(rdl_vars);
	(*c_i)++;
	update_cursor_data(rdl_vars);
}

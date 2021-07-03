/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_enter_action.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 19:51:14 by iltafah           #+#    #+#             */
/*   Updated: 2021/07/02 12:59:04 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../readline.h"

void	start_enter_action(t_rdline *rdl_vars)
{
	t_char_vec		*hstry_line;

	if (rdl_vars->tab_mode == on)
	{
		hstry_line = &rdl_vars->history_vec.elements[rdl_vars->l_i];
		clear_curr_line_after_and_below_cursor(rdl_vars);
		if (hstry_line->elements[rdl_vars->c_i - 1] == '/')
			print_line_with_chosen_method(rdl_vars, hstry_line->elements + rdl_vars->c_i, restore);
		else
			print_curr_char(rdl_vars, ' ');
		rdl_vars->tab_vars.matched_files.free(&rdl_vars->tab_vars.matched_files);
		if (rdl_vars->tab_vars.dir_to_search != NULL)
			free(rdl_vars->tab_vars.dir_to_search);
		if (rdl_vars->tab_vars.file_to_match != NULL)
			free(rdl_vars->tab_vars.file_to_match);
		rdl_vars->previous_key = disable_enter;
		rdl_vars->tab_mode = off;
	}
	else
	{
		rdl_vars->previous_key = enter;
		quit_highlighting_mode(rdl_vars, enter);
		insert_curr_line_to_history(rdl_vars);
		move_cursor_to_end_of_printed_line(rdl_vars);
		if (rdl_vars->auto_suggestions == on)
			erase_suggestions(rdl_vars);
		put_char('\n');
	}
}

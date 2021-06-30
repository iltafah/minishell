/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_enter_action.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 19:51:14 by iltafah           #+#    #+#             */
/*   Updated: 2021/06/30 20:02:18 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../readline.h"

void	start_enter_action(t_rdline *rdl_vars)
{
	if (rdl_vars->previous_key == tab)
	{
		rdl_vars->previous_key = disable_enter;
		clear_curr_line_after_and_below_cursor(rdl_vars);
		return ;
	}
	rdl_vars->previous_key = enter;
	quit_highlighting_mode(rdl_vars, enter);
	insert_curr_line_to_history(rdl_vars);
	move_cursor_to_end_of_printed_line(rdl_vars);
	if (rdl_vars->auto_suggestions == on)
		erase_suggestions(rdl_vars);
	put_char('\n');
}

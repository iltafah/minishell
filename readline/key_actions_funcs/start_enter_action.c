/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_enter_action.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 19:51:14 by iltafah           #+#    #+#             */
/*   Updated: 2021/06/20 16:33:30 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../readline.h"

void	start_enter_action(t_rdline *rdl_vars)
{
	quit_highlighting_mode(rdl_vars, enter);
	insert_curr_line_to_history(rdl_vars);
	move_cursor_to_end_of_printed_line(rdl_vars);
	if (rdl_vars->auto_suggestions == on)
		erase_suggestions(rdl_vars);
	put_char('\n');
}

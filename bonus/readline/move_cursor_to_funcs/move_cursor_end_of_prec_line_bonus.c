/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor_end_of_prec_line_bonus.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 19:50:40 by iltafah           #+#    #+#             */
/*   Updated: 2021/07/17 12:13:53 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../readline_bonus.h"

void	move_cursor_end_of_prec_line(t_rdline *rdl_vars)
{
	move_cursor_up_vertically(rdl_vars);
	move_cursor_to_colum(rdl_vars, rdl_vars->width_of_screen - 1);
}

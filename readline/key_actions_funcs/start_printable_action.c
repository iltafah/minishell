/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_printable_action.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 19:51:02 by iltafah           #+#    #+#             */
/*   Updated: 2021/06/30 17:48:22 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../readline.h"

void	start_printable_action(t_rdline *rdl_vars, char c)
{
	quit_highlighting_mode(rdl_vars, printable);
	print_curr_char(rdl_vars, c);
	rdl_vars->previous_key = printable;
}

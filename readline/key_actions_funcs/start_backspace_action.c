/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_backspace_action.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 19:51:52 by iltafah           #+#    #+#             */
/*   Updated: 2021/06/30 17:48:38 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../readline.h"

void	start_backspace_action(t_rdline *rdl_vars)
{
	quit_highlighting_mode(rdl_vars, backspace);
	erase_and_remove_curr_char(rdl_vars);
	rdl_vars->previous_key = backspace;
}

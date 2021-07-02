/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_backspace_action.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 19:51:52 by iltafah           #+#    #+#             */
/*   Updated: 2021/07/02 13:08:58 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../readline.h"

void	start_backspace_action(t_rdline *rdl_vars)
{
	if (rdl_vars->tab_mode == on)
	{
		clear_curr_line_after_and_below_cursor(rdl_vars);
		rdl_vars->tab_vars.matched_files.free(&rdl_vars->tab_vars.matched_files);
		if (rdl_vars->tab_vars.dir_to_search != NULL)
			free(rdl_vars->tab_vars.dir_to_search);
		if (rdl_vars->tab_vars.file_to_match != NULL)
			free(rdl_vars->tab_vars.file_to_match);
		rdl_vars->tab_mode = off;
	}
	quit_highlighting_mode(rdl_vars, backspace);
	erase_and_remove_curr_char(rdl_vars);
	rdl_vars->previous_key = backspace;
}

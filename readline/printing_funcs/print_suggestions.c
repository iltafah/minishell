/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_suggestions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 19:49:14 by iltafah           #+#    #+#             */
/*   Updated: 2021/06/19 15:12:16 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../readline.h"

void	erase_suggestions(t_rdline *rdl_vars)
{
	move_cursor_to_end_of_printed_line(rdl_vars);
	clear_curr_line_after_and_below_cursor(rdl_vars);
}

void	search_for_matched_history(t_rdline *rdl_vars)
{
	t_vchar_vec		*hstry_vec;
	t_char_vec		*hstry_line;
	int				curr_line_index;
	int				l_i;

	rdl_vars->is_matched_history = false;
	hstry_vec = &rdl_vars->history_vec;
	hstry_line = hstry_vec->elements;
	l_i = rdl_vars->l_i;
	if (l_i > 0 && hstry_line[l_i].used_size > 0)
	{
		curr_line_index = l_i - 1;
		while (curr_line_index >= 0)
		{
			if (ft_strncmp(hstry_line[l_i].elements,
					hstry_line[curr_line_index].elements,
					hstry_line[l_i].used_size) == 0)
			{
				rdl_vars->is_matched_history = true;
				rdl_vars->matched_history_index = curr_line_index;
				break ;
			}
			curr_line_index--;
		}
	}
}

void	print_suggestions(t_rdline *rdl_vars)
{
	t_vchar_vec		*hstry_vec;
	t_char_vec		*hstry_line;
	int				l_i;
	int				i;

	hstry_vec = &rdl_vars->history_vec;
	hstry_line = hstry_vec->elements;
	l_i = rdl_vars->l_i;
	i = hstry_line[l_i].last_index + 1;
	save_curr_cursor_pos(rdl_vars);
	erase_suggestions(rdl_vars);
	search_for_matched_history(rdl_vars);
	if (rdl_vars->is_matched_history == true)
	{
		while (i < hstry_line[rdl_vars->matched_history_index].used_size)
		{
			rdl_print_char(rdl_vars,
				hstry_line[rdl_vars->matched_history_index].elements[i],
				GRY);
			i++;
		}
	}
	restore_cursor_pos(rdl_vars);
}

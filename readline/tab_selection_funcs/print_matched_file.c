/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_matched_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 13:50:21 by iltafah           #+#    #+#             */
/*   Updated: 2021/07/05 13:50:43 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../readline.h"

void	print_matched_file(t_rdline *rdl_vars, t_str_vec files, int curr_index)
{
	int				i;
	t_char_vec		*hstry_line;

	hstry_line = &rdl_vars->history_vec.elements[rdl_vars->l_i];
	hstry_line->add_set_of_elements_at_index(hstry_line, files.elements[curr_index], rdl_vars->c_i);
	print_after_cursor(rdl_vars, files.elements[curr_index], dont_restore);
	rdl_vars->c_i += ft_strlen(files.elements[curr_index]);
	print_after_cursor(rdl_vars, hstry_line->elements + rdl_vars->c_i, restore);
	update_cursor_data(rdl_vars);
}

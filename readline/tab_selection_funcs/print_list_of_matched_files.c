/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list_of_matched_files.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 13:51:03 by iltafah           #+#    #+#             */
/*   Updated: 2021/07/07 16:46:09 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../readline.h"


void	print_curr_file_with_colors(t_rdline *rdl_vars, t_tab_vars *tab_vars, int i, int len,
	int *spaces)
{
	char			*file_full_path;
	struct stat		file_stat;
	
	file_full_path = ft_strjoin(tab_vars->dir_to_search,
		tab_vars->matched_files.elements[i]);
	stat(file_full_path, &file_stat);
	if (S_ISDIR(file_stat.st_mode))
		write(1, PRP, ft_strlen(PRP));
	else if (file_stat.st_mode & S_IXUSR)
		write(1, GRN, ft_strlen(GRN));
	write(1, tab_vars->matched_files.elements[i], len);
	rdl_vars->curs_colm_pos += len;
	if (S_ISDIR(file_stat.st_mode))
	{
		write(1, "/", 1);
		*spaces -= 1;
	}
	write(1, WHT, ft_strlen(WHT));
	free(file_full_path);
}


void	print_file_without_highlighting(t_rdline *rdl_vars, t_tab_vars *tab_vars,
	int max_len, int i)
{
	int				len;
	int				spaces;

	len = ft_strlen(tab_vars->matched_files.elements[i]);
	spaces = max_len - len - 2;
	print_curr_file_with_colors(rdl_vars, tab_vars, i, len, &spaces);
	while (spaces > 0)
	{
		write(1, " ", 1);
		rdl_vars->curs_colm_pos++;
		spaces--;
	}
}


void	print_file_with_highlighting(t_rdline *rdl_vars, t_tab_vars *tab_vars,
	int max_len, int i)
{
	int				len;
	int				hilited_spaces;
	char			*file_full_path;
	struct stat		file_stat;

	len = ft_strlen(tab_vars->matched_files.elements[i]);
	hilited_spaces = max_len - len - 2;
	file_full_path = ft_strjoin(tab_vars->dir_to_search,
		tab_vars->matched_files.elements[i]);
	stat(file_full_path, &file_stat);
	tputs(rdl_vars->capability.enter_standout_mode, 1, put_char);
	write(1, tab_vars->matched_files.elements[i], len);
	if (S_ISDIR(file_stat.st_mode))
	{
		write(1, "/", 1);
		hilited_spaces -= 1;
	}
	write(1, WHT, ft_strlen(WHT));
	rdl_vars->curs_colm_pos += len;
	while (hilited_spaces > 0)
	{
		write(1, " ", 1);
		rdl_vars->curs_colm_pos++;
		hilited_spaces--;
	}
	tputs(rdl_vars->capability.leave_standout_mode, 1, put_char);
}

void	print_list_of_matched_files(t_rdline *rdl_vars, t_tab_vars *tab_vars)
{
	int		i;
	int		len;
	int		hilited_spaces;
	int		max_len;

	i = 0;
	max_len = get_max_len(tab_vars->matched_files) + 2 + 1;

	save_curr_cursor_pos(rdl_vars);
	move_cursor_to_end_of_printed_line(rdl_vars);
	move_cursor_start_of_next_line(rdl_vars);
	while (i < tab_vars->matched_files.used_size)
	{
		if (rdl_vars->curs_colm_pos + max_len > rdl_vars->width_of_screen)
			move_cursor_start_of_next_line(rdl_vars);
		
		if (i == tab_vars->curr_index && rdl_vars->tab_mode == on)
			print_file_with_highlighting(rdl_vars, tab_vars, max_len, i);
		else
			print_file_without_highlighting(rdl_vars, tab_vars, max_len, i);

		// len = ft_strlen(tab_vars->matched_files.elements[i]);
		// hilited_spaces = max_len - len - 2;




		// rdl_vars->curs_colm_pos += len;
		// while (hilited_spaces > 0)
		// {
		// 	write(1, " ", 1);
		// 	rdl_vars->curs_colm_pos++;
		// 	hilited_spaces--;
		// }
		// if (i == tab_vars->curr_index && rdl_vars->tab_mode == on)
		// 	tputs(rdl_vars->capability.leave_standout_mode, 1, put_char);
		write(1, "  ", 2);
		rdl_vars->curs_colm_pos += 2;
		i++;
	}
	if (rdl_vars->curs_colm_pos + max_len > rdl_vars->width_of_screen)
		move_cursor_start_of_next_line(rdl_vars);
	clear_curr_line_after_and_below_cursor(rdl_vars);
	restore_cursor_pos(rdl_vars);
}

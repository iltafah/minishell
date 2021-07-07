/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 16:40:58 by iltafah           #+#    #+#             */
/*   Updated: 2021/07/07 14:15:12 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./readline.h"

void	set_rdl_vars(t_rdline *rdl_vars, char *prompt)
{
	t_vchar_vec		*history_vec;

	history_vec = &rdl_vars->history_vec;
	rdl_vars->old_history = convert_history_vec_to_array(history_vec);
	add_empty_char_vec_to_history_vec(history_vec);
	rdl_vars->prompt = prompt;
	if (prompt == NULL)
		rdl_vars->prompt_len = 0;
	else
		rdl_vars->prompt_len = ft_strlen_utf8(rdl_vars->prompt);
	rdl_vars->width_of_screen = get_screen_width();
	rdl_vars->c_i = 0;
	rdl_vars->l_i = history_vec->last_index;
	rdl_vars->curs_row_pos = 0;
	rdl_vars->curs_colm_pos = rdl_vars->prompt_len;
}

int	which_prototype(int key)
{
	if (key >= up_arrow && key <= tab)
		return (first);
	else if (key == printable)
		return (second);
	return (none);
}

void	call_suitable_func(t_func_ptr *func, t_rdline *rdl_v, int key, char c)
{
	int	proto_type;

	proto_type = which_prototype(key);
	if (proto_type == first)
		func[key].first(rdl_v);
	else if (proto_type == second)
		func[key].second(rdl_v, c);
}

// void	get_matched_files(t_tab_vars *vars)
// {
// 	DIR				*curr_directory;
// 	struct dirent	*entry;
// 	struct stat		file_stat;
// 	char			*file_with_path;

// 	curr_directory = opendir(vars->dir_to_search);
// 	// initialize_vec_content(&files);
// 	if (curr_directory == NULL)
// 		return ;
// 	while (true)
// 	{
// 		entry = readdir(curr_directory);
// 		if (entry == NULL)
// 			break ;
// 		if (vars->file_to_match != NULL)
// 		{
// 			if (entry->d_name[0] != '.'
// 				&& ft_strncmp(vars->file_to_match, entry->d_name, ft_strlen(vars->file_to_match)) == 0)
// 			{
// 				file_with_path = ft_strjoin(vars->dir_to_search, entry->d_name);
// 				stat(file_with_path, &file_stat);
// 				if (S_ISDIR(file_stat.st_mode))
// 				{
// 					vars->matched_files.add_new_element(&vars->matched_files, ft_strjoin(entry->d_name, "/"));
// 					vars->files_colors.add_new_element(&vars->files_colors, red);
// 				}
// 				else
// 				{
// 					vars->matched_files.add_new_element(&vars->matched_files, ft_strdup(entry->d_name));
// 					vars->files_colors.add_new_element(&vars->files_colors, white);
// 				}
// 				free(file_with_path);
// 			}
// 		}
// 		else if (entry->d_name[0] != '.')
// 		{
// 			file_with_path = ft_strjoin(vars->dir_to_search, entry->d_name);
// 			stat(file_with_path, &file_stat);
// 			if (S_ISDIR(file_stat.st_mode))
// 			{
// 				vars->matched_files.add_new_element(&vars->matched_files, ft_strjoin(entry->d_name, "/"));
// 				vars->files_colors.add_new_element(&vars->files_colors, red);
// 			}
// 			else
// 			{
// 				vars->matched_files.add_new_element(&vars->matched_files, ft_strdup(entry->d_name));
// 				vars->files_colors.add_new_element(&vars->files_colors, white);
// 			}
// 			free(file_with_path);
// 		}
// 	}
// 	closedir(curr_directory);
// 	return ;
// }

// int		get_max_len(t_str_vec files)
// {
// 	int		i;
// 	int		len;
// 	int		curr_len;

// 	i = 0;
// 	len = 0;
// 	curr_len = 0;
// 	while (i < files.used_size)
// 	{
// 		curr_len = ft_strlen(files.elements[i]);
// 		if (curr_len > len)
// 			len = curr_len;
// 		i++;
// 	}
// 	return (len);
// }

// char	*get_dir_to_search(t_rdline *rdl_vars)
// {
// 	int				i;
// 	int				start;
// 	int				end;
// 	char			*dir_to_search;
// 	t_char_vec		*hstry_line;

// 	i = rdl_vars->c_i;
// 	dir_to_search = NULL;	
// 	hstry_line = &rdl_vars->history_vec.elements[rdl_vars->l_i];
// 	while (i != 0 && hstry_line->elements[i - 1] != ' ')
// 		i--;
// 	start = i;
// 	end = start;
// 	while (hstry_line->elements[i] != ' ' && hstry_line->elements[i] != '\0')
// 	{
// 		if (hstry_line->elements[i] == '/')
// 			end = i;
// 		i++;
// 	}
// 	if (end - start > 0)
// 		dir_to_search = ft_substr(hstry_line->elements, start, end - start + 1);
// 	return (dir_to_search);
// }

// char	*get_file_to_match(t_rdline *rdl_vars)
// {
// 	int				i;
// 	char			*file_to_match;
// 	t_char_vec		*hstry_line;

// 	i = rdl_vars->c_i;
// 	file_to_match = NULL;	
// 	hstry_line = &rdl_vars->history_vec.elements[rdl_vars->l_i];
// 	while (i != 0 && hstry_line->elements[i - 1] != ' ' && hstry_line->elements[i - 1] != '/')
// 		i--;
// 	if (rdl_vars->c_i - i > 0)
// 		file_to_match = ft_substr(hstry_line->elements, i, rdl_vars->c_i - i);
// 	return (file_to_match);	
// }

// void	print_list_of_matched_files(t_rdline *rdl_vars, t_tab_vars *tab_vars)
// {
// 	int		i;
// 	int		len;
// 	int		hilited_spaces;
// 	int		max_len;

// 	i = 0;
// 	max_len = get_max_len(tab_vars->matched_files) + 2;
// 	save_curr_cursor_pos(rdl_vars);
// 	move_cursor_to_end_of_printed_line(rdl_vars);
// 	move_cursor_start_of_next_line(rdl_vars);
// 	while (i < tab_vars->matched_files.used_size)
// 	{
// 		if (rdl_vars->curs_colm_pos + max_len > rdl_vars->width_of_screen)
// 			move_cursor_start_of_next_line(rdl_vars);
// 		if (i == tab_vars->curr_index && rdl_vars->tab_mode == on)
// 			tputs(rdl_vars->capability.enter_standout_mode, 1, put_char);
// 		len = ft_strlen(tab_vars->matched_files.elements[i]);
// 		hilited_spaces = max_len - len - 2;
		
// 		if (i != tab_vars->curr_index && tab_vars->files_colors.elements[i] == red)
// 			write(1, RED, ft_strlen(RED));
// 		write(1, tab_vars->matched_files.elements[i], len);
// 		if (i != tab_vars->curr_index && tab_vars->files_colors.elements[i] == red)
// 			write(1, WHT, ft_strlen(WHT));
// 		rdl_vars->curs_colm_pos += len;
// 		while (hilited_spaces > 0)
// 		{
// 			write(1, " ", 1);
// 			rdl_vars->curs_colm_pos++;
// 			hilited_spaces--;
// 		}
// 		if (i == tab_vars->curr_index && rdl_vars->tab_mode == on)
// 			tputs(rdl_vars->capability.leave_standout_mode, 1, put_char);
// 		write(1, "  ", 2);
// 		rdl_vars->curs_colm_pos += 2;
// 		i++;
// 	}
// 	if (rdl_vars->curs_colm_pos + max_len > rdl_vars->width_of_screen)
// 		move_cursor_start_of_next_line(rdl_vars);
// 	clear_curr_line_after_and_below_cursor(rdl_vars);
// 	restore_cursor_pos(rdl_vars);
// }

/////////////
// void	print_matched_file(t_rdline *rdl_vars, t_str_vec files, int curr_index)
// {
// 	int				i;
// 	t_char_vec		*hstry_line;

// 	// && hstry_line->elements[rdl_vars->c_i - 1] != '/')
// 	hstry_line = &rdl_vars->history_vec.elements[rdl_vars->l_i];
// 	// if (first_tab == true)
// 		// while (rdl_vars->c_i != 0 && hstry_line->elements[rdl_vars->c_i - 1] != ' ')
// 		// {
// 		// 	rdl_vars->c_i--;
// 		// 	hstry_line->delete_element_at_index(hstry_line, rdl_vars->c_i);
// 		// 	if (rdl_vars->curs_colm_pos == 0)
// 		// 		move_cursor_end_of_prec_line(rdl_vars);
// 		// 	else
// 		// 		move_cursor_left(rdl_vars);
// 		// 	if (hstry_line->elements[rdl_vars->c_i - 1] == '/')
// 		// 		break ;
// 		// }
// 	hstry_line->add_set_of_elements_at_index(hstry_line, files.elements[curr_index], rdl_vars->c_i);
// 	print_after_cursor(rdl_vars, files.elements[curr_index], dont_restore);
// 	rdl_vars->c_i += ft_strlen(files.elements[curr_index]);
// 	print_after_cursor(rdl_vars, hstry_line->elements + rdl_vars->c_i, restore);
// 	update_cursor_data(rdl_vars);
// }
/////////////

// void	select_matched_file(t_rdline *rdl_vars, int curr_index, t_str_vec matched_files)
// {
// 	t_char_vec			*hstry_line;

// 	hstry_line = &rdl_vars->history_vec.elements[rdl_vars->l_i];
// 	if (hstry_line->elements[rdl_vars->c_i] != ' ' && hstry_line->elements[rdl_vars->c_i] != '\0')
// 		return ;

// 	if (matched_files.used_size > 0)
// 	{
// 		tputs(rdl_vars->capability.make_cursor_invisible, 1, put_char);
// 		print_matched_file(rdl_vars, matched_files, curr_index);
// 		if (matched_files.used_size > 1)
// 			print_list_of_matched_files(rdl_vars, matched_files, curr_index);
// 		tputs(rdl_vars->capability.return_cursor_to_normal, 1, put_char);
// 	}
// 	curr_index++;
// }



// void	erase_prec_file(t_rdline *rdl_vars, t_tab_vars *tab_vars)
// {
// 	t_char_vec		*hstry_line;

// 	hstry_line = &rdl_vars->history_vec.elements[rdl_vars->l_i];
// 	while (tab_vars->printd_matched_file_len > 0)
// 	{
// 		rdl_vars->c_i--;
// 		hstry_line->delete_element_at_index(hstry_line, rdl_vars->c_i);
// 		if (rdl_vars->curs_colm_pos == 0)
// 			move_cursor_end_of_prec_line(rdl_vars);
// 		else
// 			move_cursor_left(rdl_vars);
// 		tab_vars->printd_matched_file_len--;
// 	}
// }

// void	modify_on_matched_files(t_tab_vars *tab_vars)
// {
// 	int				i;
// 	char			*tmp;
// 	char			*file_full_path;
// 	struct stat		file_stat;

// 	i = 0;
// 	while (i < tab_vars->matched_files.used_size)
// 	{
// 		// len = ft_strlen(tab_vars->matched_files.elements[i]);
// 		// hilited_spaces = max_len - len - 2;
// 		file_full_path = ft_strjoin(tab_vars->dir_to_search, tab_vars->matched_files.elements[i]);
// 		stat(file_full_path, &file_stat);
// 		if (i != tab_vars->curr_index)
// 		{
// 			if (S_ISDIR(file_stat.st_mode))
// 			{	
// 				tmp = ft_strjoin(PRP, tab_vars->matched_files.elements[i]);// 	write(1, PRP, ft_strlen(PRP));
// 				tab_vars->modified_matched_files.add_new_element(&tab_vars->modified_matched_files, ft_strjoin(tmp, WHT));
// 				free(tmp);
// 			}
// 			else
// 				tab_vars->modified_matched_files.add_new_element(&tab_vars->modified_matched_files, ft_strdup(tab_vars->matched_files.elements[i]));

// 			// else if (file_stat.st_mode & S_IXUSR)
// 			// 	write(1, GRN, ft_strlen(GRN));
// 		}
// 		else
// 			tab_vars->modified_matched_files.add_new_element(&tab_vars->modified_matched_files, ft_strdup(tab_vars->matched_files.elements[i]));
// 		// write(1, tab_vars->matched_files.elements[i], len);
// 		// if (i != tab_vars->curr_index)
// 		// {
// 		// 	if (S_ISDIR(file_stat.st_mode))
// 		// 	{
// 		// 		write(1, "/", 1);
// 		// 	// 	write(1, WHT, ft_strlen(WHT));
// 		// 	}
// 		// 	else if (file_stat.st_mode & S_IXUSR)
// 		// 	;// 	write(1, WHT, ft_strlen(WHT));
// 		// }
// 		free(file_full_path);

// 		// rdl_vars->curs_colm_pos += len;
// 		// while (hilited_spaces > 0)
// 		// {
// 		// 	write(1, " ", 1);
// 		// 	rdl_vars->curs_colm_pos++;
// 		// 	hilited_spaces--;
// 		// }
// 		// write(1, "  ", 2);
// 		i++;
// 	}
// }

// void	select_wanted_file(t_rdline *rdl_vars, t_tab_vars *tab_vars)
// {

// 	fprintf(fd1, "saved_curs_pos : (%d, %d)\n", rdl_vars->curs_colm_pos, rdl_vars->curs_row_pos);
// 	fflush(fd1);
// 	save_curr_cursor_pos(rdl_vars);
// 	// move_cursor_to_end_of_printed_line(rdl_vars);
// 	sleep(1);
// 	move_cursor_start_of_next_line(rdl_vars);
// 	sleep(1);
				
// 	int		col_to_move;
// 	int		row_to_move;

// 	int		col_to_move_prec;
// 	int		row_to_move_prec;

// 	col_to_move = tab_vars->curr_index % tab_vars->colm;
// 	row_to_move = tab_vars->curr_index / tab_vars->colm;

// 	col_to_move_prec = tab_vars->prec_index % tab_vars->colm;
// 	row_to_move_prec = tab_vars->prec_index / tab_vars->colm;
// 	// fprintf(fd1, "to move (%d, %d)\n", col_to_move, row_to_move);
// 	fprintf(fd1, "to move (%d, %d) width = %d\n", col_to_move * (get_max_len(tab_vars->matched_files) + 2 + 1), row_to_move, rdl_vars->width_of_screen);
// 	fflush(fd1);
// 	// move_cursor_to_colum_and_row(rdl_vars, col_to_move, row_to_move);
// 	while (row_to_move > 0)
// 	{
// 	sleep(1);
// 		move_cursor_down_vertically(rdl_vars);
// 		row_to_move--;
// 	}
// 	sleep(1);
// 	move_cursor_to_colum(rdl_vars, col_to_move * (get_max_len(tab_vars->matched_files) + 2 + 1));
// 	sleep(1);
// 				tputs(rdl_vars->capability.enter_standout_mode, 1, put_char);
// 				write(1, tab_vars->matched_files.elements[tab_vars->curr_index], ft_strlen(tab_vars->matched_files.elements[tab_vars->curr_index]));
// 				tputs(rdl_vars->capability.leave_standout_mode, 1, put_char);
// sleep(1);
// 	restore_cursor_pos(rdl_vars);
// 	fprintf(fd1, "restored_curs_pos : (%d, %d)\n", rdl_vars->curs_colm_pos, rdl_vars->curs_row_pos);
// 	fflush(fd1);

// // sleep(2);
// // save_curr_cursor_pos(rdl_vars);
// // 	move_cursor_to_colum(rdl_vars, col_to_move_prec * (get_max_len(tab_vars->matched_files) + 2 + 1));
// // 	while (row_to_move_prec > 0)
// // 	{
// // 		move_cursor_down_vertically(rdl_vars);
// // 		row_to_move_prec--;
// // 	}
// // 	// sleep(2);
// // 				write(1, tab_vars->matched_files.elements[tab_vars->prec_index], ft_strlen(tab_vars->matched_files.elements[tab_vars->prec_index]));
// // restore_cursor_pos(rdl_vars);
// }


void	free_tab_vars(t_tab_vars *tab_vars)
{
	if (tab_vars->dir_to_search != NULL)
		free(tab_vars->dir_to_search);
	if (tab_vars->file_to_match != NULL)
		free(tab_vars->file_to_match);
	tab_vars->matched_files.free(&tab_vars->matched_files);
}

void	enter_tab_mode(t_rdline *rdl_vars, t_tab_vars *tab_vars)
{
	initialize_tab_vars(tab_vars);
	tab_vars->dir_to_search = get_dir_to_search(rdl_vars);
	tab_vars->file_to_match = get_file_to_match(rdl_vars);		
	initialize_vec_content(&tab_vars->matched_files);
	get_matched_files(tab_vars);
	if (tab_vars->matched_files.used_size == 0)
	{
		free_tab_vars(tab_vars);
		return ;
	}
	if (tab_vars->file_to_match != NULL)
		tab_vars->printd_matched_file_len = ft_strlen(tab_vars->file_to_match);
	if (tab_vars->matched_files.used_size == 1)
	{
		erase_prec_file(rdl_vars, tab_vars);
		print_matched_file(rdl_vars, tab_vars);
		free_tab_vars(tab_vars);
		return ;
	}
	print_list_of_matched_files(rdl_vars, tab_vars);
	rdl_vars->tab_mode = on;
}

void	select_next_file(t_rdline *rdl_vars, t_tab_vars *tab_vars)
{
	erase_prec_file(rdl_vars, tab_vars);
	print_matched_file(rdl_vars, tab_vars);
	tputs(rdl_vars->capability.make_cursor_invisible, 1, put_char);
	print_list_of_matched_files(rdl_vars, tab_vars);
	tab_vars->prec_index = tab_vars->curr_index;
	tab_vars->curr_index += 1;
	if (tab_vars->curr_index > tab_vars->matched_files.last_index)
		tab_vars->curr_index = 0;
	tputs(rdl_vars->capability.return_cursor_to_normal, 1, put_char);
}


void	start_tab_action(t_rdline *rdl_vars)
{
	t_char_vec		*hstry_line;

	hstry_line = &rdl_vars->history_vec.elements[rdl_vars->l_i];
	if (rdl_vars->tab_mode == off)
	{
		if (hstry_line->elements[rdl_vars->c_i] != ' '
			&& hstry_line->elements[rdl_vars->c_i] != '\0')
			return ;
		enter_tab_mode(rdl_vars, &rdl_vars->tab_vars);
	}
	else
		select_next_file(rdl_vars, &rdl_vars->tab_vars);
	rdl_vars->previous_key = tab;
}

void	start_key_action(t_rdline *rdl_vars, int key, char c)
{
	static t_func_ptr	func_ptrs[22] = {
		{NULL}, {NULL},
		{.first = start_up_arrow_action},
		{.first = start_down_arrow_action},
		{.first = start_left_arrow_action},
		{.first = start_right_arrow_action},
		{.first = start_enter_action},
		{.first = start_backspace_action},
		{.first = start_home_action},
		{.first = start_end_action},
		{.first = start_shift_right_arrow_action},
		{.first = start_shift_left_arrow_action},
		{.first = start_ctl_up_arrow_action},
		{.first = start_ctl_down_arrow_action},
		{.first = start_ctl_right_arrow_action},
		{.first = start_ctl_left_arrow_action},
		{.first = start_ctl_s_action},
		{.first = start_ctl_v_action},
		{.first = start_ctl_x_action},
		{.first = exit_program},
		{.first = start_tab_action},
		{.second = start_printable_action}
	};

	call_suitable_func(func_ptrs, rdl_vars, key, c);
}

void	process_input(t_rdline *rdl_vars, char *prompt)
{
	int		key;
	char	c;
	//////////////////////
	

	fd1 = fopen("debug1", "w");
	fclose(fd1);
	fd1 = fopen("debug2", "w");
	fclose(fd2);
	//////////////////////
	key = none;
	set_rdl_vars(rdl_vars, prompt);
	print_prompt(rdl_vars);
	while (read(STDIN_FILENO, &c, 1))
	{
		fd1 = fopen("debug1", "a");
		fd2 = fopen("debug2", "a");
		key = get_key(rdl_vars->key_seq_trie, c);
		if (key == none || key == waiting)
			SKIP ;
		start_key_action(rdl_vars, key, c);
		if (key == enter && rdl_vars->previous_key != disable_enter)
			break ;

		fprintf(fd1, "curs pos (%d, %d)\n", rdl_vars->curs_colm_pos, rdl_vars->curs_row_pos);
		fflush(fd1);
		// fprintf(fd2, "width of screen : %d\n", rdl_vars->width_of_screen);
		// fflush(fd2);
		fclose(fd1);
		fclose(fd2);
	}
	free_array(&rdl_vars->old_history);
	///////////////////////
	///////////////////////
}

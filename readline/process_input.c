/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 16:40:58 by iltafah           #+#    #+#             */
/*   Updated: 2021/06/30 21:39:08 by iltafah          ###   ########.fr       */
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
	if (key >= up_arrow && key <= ctl_x)
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

t_str_vec	get_matched_files(char *dir, char *file)
{
	DIR				*curr_directory;
	struct dirent	*entry;
	t_str_vec		files;

	curr_directory = opendir(dir);
	initialize_vec_content(&files);
	while (true)
	{
		entry = readdir(curr_directory);
		if (entry == NULL)
			break ;
		if (file != NULL)
		{
			if (ft_strncmp(file, entry->d_name, ft_strlen(file)) == 0)
				files.add_new_element(&files, entry->d_name);
		}
		else
			files.add_new_element(&files, entry->d_name);
	}
	return (files);
}

int		get_max_len(t_str_vec files)
{
	int		i;
	int		len;
	int		curr_len;

	i = 0;
	len = 0;
	curr_len = 0;
	while (i < files.used_size)
	{
		curr_len = ft_strlen(files.elements[i]);
		if (curr_len > len)
			len = curr_len;
		i++;
	}
	return (len);
}

char	*get_dir_to_search(t_rdline *rdl_vars)
{
	int				i;
	int				start;
	int				end;
	char			*dir_to_search;
	t_char_vec		*hstry_line;

	i = rdl_vars->c_i;
	dir_to_search = NULL;	
	hstry_line = &rdl_vars->history_vec.elements[rdl_vars->l_i];
	while (i != 0 && hstry_line->elements[i - 1] != ' ')
		i--;
	start = i;
	while (hstry_line->elements[i] != ' ' && hstry_line->elements[i] != '\0')
	{
		if (hstry_line->elements[i] == '/')
			end = i;
		i++;
	}
	if (end - start > 0)
		dir_to_search = ft_substr(hstry_line->elements, start, end - start);
	return (dir_to_search);
}

char	*get_file_to_match(t_rdline *rdl_vars)
{
	int				i;
	char			*file_to_match;
	t_char_vec		*hstry_line;

	i = rdl_vars->c_i;
	file_to_match = NULL;	
	hstry_line = &rdl_vars->history_vec.elements[rdl_vars->l_i];
	while (i != 0 && hstry_line->elements[i - 1] != ' ' && hstry_line->elements[i - 1] != '/')
		i--;
	if (rdl_vars->c_i - i > 0)
		file_to_match = ft_substr(hstry_line->elements, i, rdl_vars->c_i - i);
	return (file_to_match);	
}

void	print_list_of_matched_files(t_rdline *rdl_vars, t_str_vec files, int index)
{
	int		i;
	int		len;
	int		spaces;
	int		max_len;

	i = 0;
	max_len = get_max_len(files) + 2;
	save_curr_cursor_pos(rdl_vars);
	move_cursor_start_of_next_line(rdl_vars);
	while (i < files.used_size)
	{
		if (rdl_vars->curs_colm_pos + max_len > rdl_vars->width_of_screen)
			move_cursor_start_of_next_line(rdl_vars);
		len = ft_strlen(files.elements[i]);
		spaces = max_len - len;
		
		if (i == index)
			tputs(rdl_vars->capability.enter_standout_mode, 1, put_char);
		int	j = 0;
		// while (j < len)
		// {
		// 	rdl_print_char(rdl_vars, files.elements[i][j], WHT);
		// 	j++;
		// }
		// if (rdl_vars->curs_colm_pos + max_len > rdl_vars->width_of_screen)
		// {
		// 	move_cursor_start_of_next_line(rdl_vars);
		// 	rdl_vars->curs_colm_pos = 0;
		// 	rdl_vars->curs_row_pos++;
		// }
		write(1, files.elements[i], len);
		rdl_vars->curs_colm_pos += len;
		while (spaces > 0)
		{
			// rdl_print_char(rdl_vars, ' ', WHT);
			write(1, " ", 1);
			rdl_vars->curs_colm_pos++;
			spaces--;
		}
		if (i == index)
			tputs(rdl_vars->capability.leave_standout_mode, 1, put_char);
		i++;
	}
	// printf("\n");
	// rdl_vars->curs_row_pos++;
	restore_cursor_pos(rdl_vars);
}

/////////////
void	print_matched_file(t_rdline *rdl_vars, t_str_vec files, int curr_index)
{
	int				i;
	t_char_vec		*hstry_line;

	hstry_line = &rdl_vars->history_vec.elements[rdl_vars->l_i];
	while (hstry_line->elements[rdl_vars->c_i - 1] != ' ' && hstry_line->elements[rdl_vars->c_i - 1] != '/')
	{
		rdl_vars->c_i--;
		hstry_line->delete_element_at_index(hstry_line, rdl_vars->c_i);
		if (rdl_vars->curs_colm_pos == 0)
			move_cursor_end_of_prec_line(rdl_vars);
		else
			move_cursor_left(rdl_vars);
	}
	hstry_line->add_set_of_elements_at_index(hstry_line, files.elements[curr_index], rdl_vars->c_i);
	print_after_cursor(rdl_vars, files.elements[curr_index], dont_restore);
	rdl_vars->c_i += ft_strlen(files.elements[curr_index]);
	print_after_cursor(rdl_vars, hstry_line->elements + rdl_vars->c_i, restore);
	update_cursor_data(rdl_vars);
}
/////////////

void	select_matched_file(t_rdline *rdl_vars)
{
	static int		curr_index = 0;
	static char		*dir_to_search = NULL;
	static char		*file_to_match = NULL;
	t_str_vec		matched_files;

	if (rdl_vars->previous_key != tab)
	{
		curr_index = 0;
		dir_to_search = get_dir_to_search(rdl_vars);
		file_to_match = get_file_to_match(rdl_vars);
		if (dir_to_search == NULL)
			dir_to_search = ft_strdup(".");
		matched_files = get_matched_files(dir_to_search, file_to_match);
		clear_curr_line_after_and_below_cursor(rdl_vars);
	}
	if (curr_index > matched_files.last_index)
		curr_index = 0;
	print_matched_file(rdl_vars, matched_files, curr_index);
	print_list_of_matched_files(rdl_vars, matched_files, curr_index);
	curr_index++;
}

void	start_tab_action(t_rdline *rdl_vars)
{
	select_matched_file(rdl_vars);
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

	key = none;
	set_rdl_vars(rdl_vars, prompt);
	print_prompt(rdl_vars);
	while (read(STDIN_FILENO, &c, 1))
	{
		key = get_key(rdl_vars->key_seq_trie, c);
		if (key == none || key == waiting)
			SKIP ;
		start_key_action(rdl_vars, key, c);
		if (key == enter && rdl_vars->previous_key != disable_enter)
			break ;
	}
	free_array(&rdl_vars->old_history);
}

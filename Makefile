NAME = minishell

LIBFT = ./libft/libft.a

CC := gcc

CFLAGS := #-Wall -Wextra -Werror

SRC := environment/convert_env_table_to_array.c \
environment/create_env_table.c \
environment/get_value_of_env_name.c \
freeing_time/free_abstract_syntax_tree.c \
freeing_time/free_array_of_pointers.c \
freeing_time/free_tokens_list.c \
get_curr_dir_name.c \
get_next_line/get_next_line.c \
get_next_line/get_next_line_utils.c \
get_prompt_name.c \
minishell.c \
treat_herdocs.c \
parser/check_tokens_syntax/check_simple_word_syntax.c \
parser/check_tokens_syntax/check_tokens_order.c \
parser/check_tokens_syntax/check_tokens_syntax.c \
parser/create_abstract_syntax_tree/create_abstract_syntax_tree.c \
parser/create_abstract_syntax_tree/create_ast_nodes.c \
parser/create_abstract_syntax_tree/get_suitable_nodes.c \
parser/create_abstract_syntax_tree/initialize_ast_vars.c \
parser/create_abstract_syntax_tree/store_redirection_in_suitable_node.c \
parser/create_abstract_syntax_tree/store_word_in_suitable_node.c \
parser/expanding/expand_dollar_variables.c \
parser/expanding/expanding.c \
parser/expanding/get_dollar_name.c \
parser/expanding/get_dollar_value.c \
parser/expanding/give_quotes_special_meaning.c \
parser/expanding/remove_special_quotes.c \
parser/expanding/split_element_to_args.c \
parser/expanding/expand_quoted_var.c \
parser/expanding/expand_unquoted_var.c \
parser/tokenization/cases_treating.c \
parser/tokenization/tokenization.c \
parser/usefull_functions/does_backslash_exist.c \
parser/usefull_functions/does_pipe_exist.c \
parser/usefull_functions/does_semicolon_exist.c \
parser/usefull_functions/open_and_close_quotes.c \
vectors/vector_of_char_vectors/add_new_char_vec.c \
vectors/vector_of_char_vectors/add_new_char_vec_at_index.c \
vectors/vector_of_char_vectors/delete_char_vec_at_index.c \
vectors/vector_of_char_vectors/delete_last_char_vec.c \
vectors/vector_of_char_vectors/initialize_vec_of_char_vec.c \
vectors/vector_of_char_vectors/realloc_and_free_vec.c \
vectors/vector_of_chars/add_new_char.c \
vectors/vector_of_chars/add_new_char_at_index.c \
vectors/vector_of_chars/add_set_of_chars.c \
vectors/vector_of_chars/add_set_of_chars_at_index.c \
vectors/vector_of_chars/delete_char_at_index.c \
vectors/vector_of_chars/initialize_vec_of_char.c \
vectors/vector_of_chars/realloc_and_free_vec.c \
vectors/vector_of_chars/replace_char_at_index.c \
vectors/vector_of_int/add_new_int.c \
vectors/vector_of_int/add_new_int_at_index.c \
vectors/vector_of_int/delete_int_at_index.c \
vectors/vector_of_int/initialize_vec_of_int.c \
vectors/vector_of_int/pop_int.c \
vectors/vector_of_int/push_int.c \
vectors/vector_of_int/realloc_int_vector.c \
vectors/vector_of_int/replace_int_at_index.c \
vectors/vector_of_string/add_new_element.c \
vectors/vector_of_string/add_new_element_at_index.c \
vectors/vector_of_string/delete_element_at_index.c \
vectors/vector_of_string/initialize_vec_content.c \
vectors/vector_of_string/realloc_and_free_vec.c \
vectors/vector_of_string/replace_element_at_index.c \
./readline/clear_lines.c \
./readline/create_key_seq_trie.c \
./readline/detect_screen_resizing.c \
./readline/erase_and_remove_char.c \
./readline/exit_program.c \
./readline/get_screen_width.c \
./readline/initializing.c \
./readline/insert_curr_line_to_history.c \
./readline/key_actions_funcs/start_backspace_action.c \
./readline/key_actions_funcs/start_ctl_down_arrow_action.c \
./readline/key_actions_funcs/start_ctl_left_arrow_action.c \
./readline/key_actions_funcs/start_ctl_right_arrow_action.c \
./readline/key_actions_funcs/start_ctl_s_action.c \
./readline/key_actions_funcs/start_ctl_up_arrow_action.c \
./readline/key_actions_funcs/start_ctl_v_action.c \
./readline/key_actions_funcs/start_ctl_x_action.c \
./readline/key_actions_funcs/start_down_arrow_action.c \
./readline/key_actions_funcs/start_end_action.c \
./readline/key_actions_funcs/start_enter_action.c \
./readline/key_actions_funcs/start_home_action.c \
./readline/key_actions_funcs/start_left_arrow_action.c \
./readline/key_actions_funcs/start_printable_action.c \
./readline/key_actions_funcs/start_right_arrow_action.c \
./readline/key_actions_funcs/start_shift_left_arrow_action.c \
./readline/key_actions_funcs/start_shift_right_arrow_action.c \
./readline/key_actions_funcs/start_tab_action.c \
./readline/key_actions_funcs/start_up_arrow_action.c \
./readline/load_history_file_to_vec.c \
./readline/move_cursor_to_funcs/move_cursor_end_of_prec_line.c \
./readline/move_cursor_to_funcs/move_cursor_left_or_up.c \
./readline/move_cursor_to_funcs/move_cursor_left_right.c \
./readline/move_cursor_to_funcs/move_cursor_right_or_down.c \
./readline/move_cursor_to_funcs/move_cursor_start_of_next_line.c \
./readline/move_cursor_to_funcs/move_cursor_to_colum.c \
./readline/move_cursor_to_funcs/move_cursor_to_colum_and_row.c \
./readline/move_cursor_to_funcs/move_cursor_to_end_of_printed_line.c \
./readline/move_cursor_to_funcs/move_cursor_to_row.c \
./readline/move_cursor_to_funcs/move_cursor_up_down_vertically.c \
./readline/move_cursor_to_funcs/move_left.c \
./readline/move_cursor_to_funcs/move_right.c \
./readline/move_cursor_to_funcs/move_to_beginning_of_line.c \
./readline/move_cursor_to_funcs/move_to_end_of_line.c \
./readline/move_cursor_to_funcs/move_to_next_word.c \
./readline/move_cursor_to_funcs/move_to_prec_word.c \
./readline/move_cursor_to_funcs/move_up_down_vertically.c \
./readline/open_history_file.c \
./readline/overwrite_history_file.c \
./readline/printing_funcs/print_after_cursor.c \
./readline/printing_funcs/print_curr_char.c \
./readline/printing_funcs/print_line_with_chosen_method.c \
./readline/printing_funcs/print_prompt.c \
./readline/printing_funcs/print_suggestions.c \
./readline/printing_funcs/put_char.c \
./readline/printing_funcs/put_colorful_char.c \
./readline/printing_funcs/rdl_print_char.c \
./readline/process_input.c \
./readline/readline.c \
./readline/restore_cursor_position.c \
./readline/show_history.c \
./readline/signals_handler.c \
./readline/syntax_highlighting_funcs/check_if_cmd_exist.c \
./readline/syntax_highlighting_funcs/check_if_file_exist.c \
./readline/syntax_highlighting_funcs/print_with_syntax_highlighting.c \
./readline/syntax_highlighting_funcs/select_printing_method.c \
./readline/tab_selection_funcs/enter_tab_mode.c \
./readline/tab_selection_funcs/erase_prec_file.c \
./readline/tab_selection_funcs/free_tab_vars.c \
./readline/tab_selection_funcs/get_dir_to_search.c \
./readline/tab_selection_funcs/get_file_to_match.c \
./readline/tab_selection_funcs/get_matched_files.c \
./readline/tab_selection_funcs/get_max_len.c \
./readline/tab_selection_funcs/initialize_tab_vars.c \
./readline/tab_selection_funcs/print_list_of_matched_files.c \
./readline/tab_selection_funcs/print_matched_file.c \
./readline/tab_selection_funcs/select_next_file.c \
./readline/text_highlighting_funcs/copy_highlighted_text.c \
./readline/text_highlighting_funcs/cut_highlighted_text.c \
./readline/text_highlighting_funcs/determine_beg_last_highlighted_text_index.c \
./readline/text_highlighting_funcs/left_highlight.c \
./readline/text_highlighting_funcs/past_highlighted_text.c \
./readline/text_highlighting_funcs/quit_highlighting_mode.c \
./readline/text_highlighting_funcs/right_highlight.c \
./readline/text_highlighting_funcs/start_highlighting_mode.c \
./readline/update_cursor_data.c \
./readline/usefull_history_vec_func.c \
./execution/execution_start.c \
./execution/execve.c \
./execution/execve2.c \
./execution/exit.c \
./execution/export.c \
./execution/echo.c \
./execution/env.c \
./execution/unset.c \
./execution/redirections.c \
./execution/small.c \
./execution/cd.c \
./execution/export2.c \
./execution/export3.c \
./execution/file_status_check.c \
./execution/tools.c \
./execution/execute_w_path.c \
./execution/execute_without_path.c \
./execution_loop.c

OBJ_DIR = objs

OBJ := $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(OBJ) $(LIBFT) -o $(NAME) -ltermcap -lreadline

$(LIBFT): force
	make -C ./libft

$(OBJ): $(OBJ_DIR)/%.o : %.c
	mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $< -o $@

clean :
	rm -f $(OBJ)
	rm -rf $(OBJ_DIR)
	make clean -C ./libft

fclean : clean
	rm -f $(NAME)
	make fclean -C ./libft

re : fclean all

.PHONY : all clean fclean re force

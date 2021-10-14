NAME = minishell

LIBFT = ./srcs/libft/libft.a

CC := gcc

CFLAGS := -Wall -Wextra -Werror

HDRS := srcs/environment/environment.h \
srcs/execution/file.h \
srcs/freeing_time/freeing_time.h \
srcs/get_next_line/get_next_line.h \
srcs/minishell.h \
srcs/minishell_typedefs.h \
srcs/parser/check_tokens_syntax/check_tokens_syntax.h \
srcs/parser/create_abstract_syntax_tree/create_abstract_syntax_tree.h \
srcs/parser/expanding/expanding.h \
srcs/parser/parser.h \
srcs/parser/parser_typedefs.h \
srcs/parser/tokenization/tokenization.h \
srcs/parser/usefull_functions/usefull_functions.h \
srcs/parser/usefull_functions/usefull_functions_typedefs.h \
srcs/readline/readline.h \
srcs/readline/readline_typedefs.h \
srcs/vectors/vectors.h

B_HDRS := bonus/environment/environment_bonus.h \
bonus/execution/file_bonus.h \
bonus/freeing_time/freeing_time_bonus.h \
bonus/get_next_line/get_next_line_bonus.h \
bonus/minishell_bonus.h \
bonus/minishell_typedefs_bonus.h \
bonus/parser/check_tokens_syntax/check_tokens_syntax_bonus.h \
bonus/parser/create_abstract_syntax_tree/create_abstract_syntax_tree_bonus.h \
bonus/parser/expanding/expanding_bonus.h \
bonus/parser/parser_bonus.h \
bonus/parser/parser_typedefs_bonus.h \
bonus/parser/tokenization/tokenization_bonus.h \
bonus/parser/usefull_functions/usefull_functions_bonus.h \
bonus/parser/usefull_functions/usefull_functions_typedefs_bonus.h \
bonus/readline/readline_bonus.h \
bonus/readline/readline_typedefs_bonus.h \
bonus/vectors/vectors_bonus.h

SRC := srcs/minishell.c \
srcs/environment/convert_env_table_to_array.c \
srcs/environment/create_env_table.c \
srcs/environment/get_value_of_env_name.c \
srcs/execution/cd.c \
srcs/execution/echo.c \
srcs/execution/env.c \
srcs/execution/execute_w_path.c \
srcs/execution/execute_without_path.c \
srcs/execution/execution_start.c \
srcs/execution/execve.c \
srcs/execution/execve2.c \
srcs/execution/exit.c \
srcs/execution/export.c \
srcs/execution/export2.c \
srcs/execution/export3.c \
srcs/execution/file_status_check.c \
srcs/execution/redirections.c \
srcs/execution/small.c \
srcs/execution/tools.c \
srcs/execution/unset.c \
srcs/execution_loop.c \
srcs/freeing_time/free_abstract_syntax_tree.c \
srcs/freeing_time/free_array_of_pointers.c \
srcs/freeing_time/free_main_allocated_memory.c \
srcs/freeing_time/free_tokens_list.c \
srcs/get_next_line/get_next_line.c \
srcs/get_next_line/get_next_line_utils.c \
srcs/parser/check_tokens_syntax/check_simple_word_syntax.c \
srcs/parser/check_tokens_syntax/check_tokens_order.c \
srcs/parser/check_tokens_syntax/check_tokens_syntax.c \
srcs/parser/create_abstract_syntax_tree/create_abstract_syntax_tree.c \
srcs/parser/create_abstract_syntax_tree/create_ast_nodes.c \
srcs/parser/create_abstract_syntax_tree/get_curr_pipeline_seq_node.c \
srcs/parser/create_abstract_syntax_tree/get_curr_smpl_cmd_node.c \
srcs/parser/create_abstract_syntax_tree/get_suitable_nodes.c \
srcs/parser/create_abstract_syntax_tree/initialize_ast_vars.c \
srcs/parser/create_abstract_syntax_tree/store_redirection_in_suitable_node.c \
srcs/parser/create_abstract_syntax_tree/store_word_in_suitable_node.c \
srcs/parser/create_abstract_syntax_tree/treat_herdocs.c \
srcs/parser/expanding/expand_dollar_variables.c \
srcs/parser/expanding/expand_quoted_var.c \
srcs/parser/expanding/expand_unquoted_var.c \
srcs/parser/expanding/expanding.c \
srcs/parser/expanding/get_dollar_name.c \
srcs/parser/expanding/get_dollar_value.c \
srcs/parser/expanding/give_quotes_special_meaning.c \
srcs/parser/expanding/remove_special_quotes.c \
srcs/parser/expanding/split_element_to_args.c \
srcs/parser/tokenization/cases_treating.c \
srcs/parser/tokenization/tokenization.c \
srcs/parser/usefull_functions/does_backslash_exist.c \
srcs/parser/usefull_functions/does_pipe_exist.c \
srcs/parser/usefull_functions/does_semicolon_exist.c \
srcs/parser/usefull_functions/open_and_close_quotes.c \
srcs/prompt/get_curr_dir_name.c \
srcs/prompt/get_prompt_name.c \
srcs/readline/clear_lines.c \
srcs/readline/create_key_seq_trie.c \
srcs/readline/detect_screen_resizing.c \
srcs/readline/erase_and_remove_char.c \
srcs/readline/exit_program.c \
srcs/readline/get_screen_width.c \
srcs/readline/initializing.c \
srcs/readline/insert_curr_line_to_history.c \
srcs/readline/key_actions_funcs/start_backspace_action.c \
srcs/readline/key_actions_funcs/start_ctl_down_arrow_action.c \
srcs/readline/key_actions_funcs/start_ctl_left_arrow_action.c \
srcs/readline/key_actions_funcs/start_ctl_right_arrow_action.c \
srcs/readline/key_actions_funcs/start_ctl_s_action.c \
srcs/readline/key_actions_funcs/start_ctl_up_arrow_action.c \
srcs/readline/key_actions_funcs/start_ctl_v_action.c \
srcs/readline/key_actions_funcs/start_ctl_x_action.c \
srcs/readline/key_actions_funcs/start_down_arrow_action.c \
srcs/readline/key_actions_funcs/start_end_action.c \
srcs/readline/key_actions_funcs/start_enter_action.c \
srcs/readline/key_actions_funcs/start_home_action.c \
srcs/readline/key_actions_funcs/start_left_arrow_action.c \
srcs/readline/key_actions_funcs/start_printable_action.c \
srcs/readline/key_actions_funcs/start_right_arrow_action.c \
srcs/readline/key_actions_funcs/start_shift_left_arrow_action.c \
srcs/readline/key_actions_funcs/start_shift_right_arrow_action.c \
srcs/readline/key_actions_funcs/start_tab_action.c \
srcs/readline/key_actions_funcs/start_up_arrow_action.c \
srcs/readline/load_history_file_to_vec.c \
srcs/readline/move_cursor_to_funcs/move_cursor_end_of_prec_line.c \
srcs/readline/move_cursor_to_funcs/move_cursor_left_or_up.c \
srcs/readline/move_cursor_to_funcs/move_cursor_left_right.c \
srcs/readline/move_cursor_to_funcs/move_cursor_right_or_down.c \
srcs/readline/move_cursor_to_funcs/move_cursor_start_of_next_line.c \
srcs/readline/move_cursor_to_funcs/move_cursor_to_colum.c \
srcs/readline/move_cursor_to_funcs/move_cursor_to_colum_and_row.c \
srcs/readline/move_cursor_to_funcs/move_cursor_to_end_of_printed_line.c \
srcs/readline/move_cursor_to_funcs/move_cursor_to_row.c \
srcs/readline/move_cursor_to_funcs/move_cursor_up_down_vertically.c \
srcs/readline/move_cursor_to_funcs/move_left.c \
srcs/readline/move_cursor_to_funcs/move_right.c \
srcs/readline/move_cursor_to_funcs/move_to_beginning_of_line.c \
srcs/readline/move_cursor_to_funcs/move_to_end_of_line.c \
srcs/readline/move_cursor_to_funcs/move_to_next_word.c \
srcs/readline/move_cursor_to_funcs/move_to_prec_word.c \
srcs/readline/move_cursor_to_funcs/move_up_down_vertically.c \
srcs/readline/open_history_file.c \
srcs/readline/overwrite_history_file.c \
srcs/readline/printing_funcs/print_after_cursor.c \
srcs/readline/printing_funcs/print_curr_char.c \
srcs/readline/printing_funcs/print_line_with_chosen_method.c \
srcs/readline/printing_funcs/print_prompt.c \
srcs/readline/printing_funcs/print_suggestions.c \
srcs/readline/printing_funcs/put_char.c \
srcs/readline/printing_funcs/put_colorful_char.c \
srcs/readline/printing_funcs/rdl_print_char.c \
srcs/readline/process_input.c \
srcs/readline/readline.c \
srcs/readline/restore_cursor_position.c \
srcs/readline/show_history.c \
srcs/readline/signals_handler.c \
srcs/readline/syntax_highlighting_funcs/check_if_cmd_exist.c \
srcs/readline/syntax_highlighting_funcs/check_if_file_exist.c \
srcs/readline/syntax_highlighting_funcs/print_with_syntax_highlighting.c \
srcs/readline/syntax_highlighting_funcs/select_printing_method.c \
srcs/readline/tab_selection_funcs/enter_tab_mode.c \
srcs/readline/tab_selection_funcs/erase_prec_file.c \
srcs/readline/tab_selection_funcs/free_tab_vars.c \
srcs/readline/tab_selection_funcs/get_dir_to_search.c \
srcs/readline/tab_selection_funcs/get_file_to_match.c \
srcs/readline/tab_selection_funcs/get_matched_files.c \
srcs/readline/tab_selection_funcs/get_max_len.c \
srcs/readline/tab_selection_funcs/initialize_tab_vars.c \
srcs/readline/tab_selection_funcs/print_list_of_matched_files.c \
srcs/readline/tab_selection_funcs/print_matched_file.c \
srcs/readline/tab_selection_funcs/select_next_file.c \
srcs/readline/text_highlighting_funcs/copy_highlighted_text.c \
srcs/readline/text_highlighting_funcs/cut_highlighted_text.c \
srcs/readline/text_highlighting_funcs/determine_beg_last_highlighted_text_index.c \
srcs/readline/text_highlighting_funcs/left_highlight.c \
srcs/readline/text_highlighting_funcs/past_highlighted_text.c \
srcs/readline/text_highlighting_funcs/quit_highlighting_mode.c \
srcs/readline/text_highlighting_funcs/right_highlight.c \
srcs/readline/text_highlighting_funcs/start_highlighting_mode.c \
srcs/readline/update_cursor_data.c \
srcs/readline/usefull_history_vec_func.c \
srcs/vectors/vector_of_char_vectors/add_new_char_vec.c \
srcs/vectors/vector_of_char_vectors/add_new_char_vec_at_index.c \
srcs/vectors/vector_of_char_vectors/delete_char_vec_at_index.c \
srcs/vectors/vector_of_char_vectors/delete_last_char_vec.c \
srcs/vectors/vector_of_char_vectors/initialize_vec_of_char_vec.c \
srcs/vectors/vector_of_char_vectors/realloc_and_free_vec.c \
srcs/vectors/vector_of_chars/add_new_char.c \
srcs/vectors/vector_of_chars/add_new_char_at_index.c \
srcs/vectors/vector_of_chars/add_set_of_chars.c \
srcs/vectors/vector_of_chars/add_set_of_chars_at_index.c \
srcs/vectors/vector_of_chars/delete_char_at_index.c \
srcs/vectors/vector_of_chars/initialize_vec_of_char.c \
srcs/vectors/vector_of_chars/realloc_and_free_vec.c \
srcs/vectors/vector_of_chars/replace_char_at_index.c \
srcs/vectors/vector_of_int/add_new_int.c \
srcs/vectors/vector_of_int/add_new_int_at_index.c \
srcs/vectors/vector_of_int/delete_int_at_index.c \
srcs/vectors/vector_of_int/initialize_vec_of_int.c \
srcs/vectors/vector_of_int/pop_int.c \
srcs/vectors/vector_of_int/push_int.c \
srcs/vectors/vector_of_int/realloc_int_vector.c \
srcs/vectors/vector_of_int/replace_int_at_index.c \
srcs/vectors/vector_of_string/add_new_element.c \
srcs/vectors/vector_of_string/add_new_element_at_index.c \
srcs/vectors/vector_of_string/delete_element_at_index.c \
srcs/vectors/vector_of_string/initialize_vec_content.c \
srcs/vectors/vector_of_string/realloc_and_free_vec.c \
srcs/vectors/vector_of_string/replace_element_at_index.c

B_SRC := bonus/environment/convert_env_table_to_array_bonus.c \
bonus/environment/create_env_table_bonus.c \
bonus/environment/get_value_of_env_name_bonus.c \
bonus/execution/cd_bonus.c \
bonus/execution/echo_bonus.c \
bonus/execution/env_bonus.c \
bonus/execution/execute_w_path_bonus.c \
bonus/execution/execute_without_path_bonus.c \
bonus/execution/execution_start_bonus.c \
bonus/execution/execve2_bonus.c \
bonus/execution/execve_bonus.c \
bonus/execution/exit_bonus.c \
bonus/execution/export2_bonus.c \
bonus/execution/export3_bonus.c \
bonus/execution/export_bonus.c \
bonus/execution/file_status_check_bonus.c \
bonus/execution/redirections_bonus.c \
bonus/execution/small_bonus.c \
bonus/execution/tools_bonus.c \
bonus/execution/unset_bonus.c \
bonus/execution_loop_bonus.c \
bonus/freeing_time/free_abstract_syntax_tree_bonus.c \
bonus/freeing_time/free_array_of_pointers_bonus.c \
bonus/freeing_time/free_main_allocated_memory_bonus.c \
bonus/freeing_time/free_tokens_list_bonus.c \
bonus/get_next_line/get_next_line_bonus.c \
bonus/get_next_line/get_next_line_utils_bonus.c \
bonus/minishell_bonus.c \
bonus/parser/check_tokens_syntax/check_simple_word_syntax_bonus.c \
bonus/parser/check_tokens_syntax/check_tokens_order_bonus.c \
bonus/parser/check_tokens_syntax/check_tokens_syntax_bonus.c \
bonus/parser/create_abstract_syntax_tree/create_abstract_syntax_tree_bonus.c \
bonus/parser/create_abstract_syntax_tree/create_ast_nodes_bonus.c \
bonus/parser/create_abstract_syntax_tree/get_curr_pipeline_seq_node_bonus.c \
bonus/parser/create_abstract_syntax_tree/get_curr_smpl_cmd_node_bonus.c \
bonus/parser/create_abstract_syntax_tree/get_suitable_nodes_bonus.c \
bonus/parser/create_abstract_syntax_tree/initialize_ast_vars_bonus.c \
bonus/parser/create_abstract_syntax_tree/store_redirection_in_suitable_node_bonus.c \
bonus/parser/create_abstract_syntax_tree/store_word_in_suitable_node_bonus.c \
bonus/parser/create_abstract_syntax_tree/treat_herdocs_bonus.c \
bonus/parser/expanding/expand_dollar_variables_bonus.c \
bonus/parser/expanding/expand_quoted_var_bonus.c \
bonus/parser/expanding/expand_unquoted_var_bonus.c \
bonus/parser/expanding/expanding_bonus.c \
bonus/parser/expanding/get_dollar_name_bonus.c \
bonus/parser/expanding/get_dollar_value_bonus.c \
bonus/parser/expanding/give_quotes_special_meaning_bonus.c \
bonus/parser/expanding/remove_special_quotes_bonus.c \
bonus/parser/expanding/split_element_to_args_bonus.c \
bonus/parser/tokenization/cases_treating_bonus.c \
bonus/parser/tokenization/tokenization_bonus.c \
bonus/parser/usefull_functions/does_backslash_exist_bonus.c \
bonus/parser/usefull_functions/does_pipe_exist_bonus.c \
bonus/parser/usefull_functions/does_semicolon_exist_bonus.c \
bonus/parser/usefull_functions/open_and_close_quotes_bonus.c \
bonus/prompt/get_curr_dir_name_bonus.c \
bonus/prompt/get_prompt_name_bonus.c \
bonus/readline/clear_lines_bonus.c \
bonus/readline/create_key_seq_trie_bonus.c \
bonus/readline/detect_screen_resizing_bonus.c \
bonus/readline/erase_and_remove_char_bonus.c \
bonus/readline/exit_program_bonus.c \
bonus/readline/get_screen_width_bonus.c \
bonus/readline/initializing_bonus.c \
bonus/readline/insert_curr_line_to_history_bonus.c \
bonus/readline/key_actions_funcs/start_backspace_action_bonus.c \
bonus/readline/key_actions_funcs/start_ctl_down_arrow_action_bonus.c \
bonus/readline/key_actions_funcs/start_ctl_left_arrow_action_bonus.c \
bonus/readline/key_actions_funcs/start_ctl_right_arrow_action_bonus.c \
bonus/readline/key_actions_funcs/start_ctl_s_action_bonus.c \
bonus/readline/key_actions_funcs/start_ctl_up_arrow_action_bonus.c \
bonus/readline/key_actions_funcs/start_ctl_v_action_bonus.c \
bonus/readline/key_actions_funcs/start_ctl_x_action_bonus.c \
bonus/readline/key_actions_funcs/start_down_arrow_action_bonus.c \
bonus/readline/key_actions_funcs/start_end_action_bonus.c \
bonus/readline/key_actions_funcs/start_enter_action_bonus.c \
bonus/readline/key_actions_funcs/start_home_action_bonus.c \
bonus/readline/key_actions_funcs/start_left_arrow_action_bonus.c \
bonus/readline/key_actions_funcs/start_printable_action_bonus.c \
bonus/readline/key_actions_funcs/start_right_arrow_action_bonus.c \
bonus/readline/key_actions_funcs/start_shift_left_arrow_action_bonus.c \
bonus/readline/key_actions_funcs/start_shift_right_arrow_action_bonus.c \
bonus/readline/key_actions_funcs/start_tab_action_bonus.c \
bonus/readline/key_actions_funcs/start_up_arrow_action_bonus.c \
bonus/readline/load_history_file_to_vec_bonus.c \
bonus/readline/move_cursor_to_funcs/move_cursor_end_of_prec_line_bonus.c \
bonus/readline/move_cursor_to_funcs/move_cursor_left_or_up_bonus.c \
bonus/readline/move_cursor_to_funcs/move_cursor_left_right_bonus.c \
bonus/readline/move_cursor_to_funcs/move_cursor_right_or_down_bonus.c \
bonus/readline/move_cursor_to_funcs/move_cursor_start_of_next_line_bonus.c \
bonus/readline/move_cursor_to_funcs/move_cursor_to_colum_and_row_bonus.c \
bonus/readline/move_cursor_to_funcs/move_cursor_to_colum_bonus.c \
bonus/readline/move_cursor_to_funcs/move_cursor_to_end_of_printed_line_bonus.c \
bonus/readline/move_cursor_to_funcs/move_cursor_to_row_bonus.c \
bonus/readline/move_cursor_to_funcs/move_cursor_up_down_vertically_bonus.c \
bonus/readline/move_cursor_to_funcs/move_left_bonus.c \
bonus/readline/move_cursor_to_funcs/move_right_bonus.c \
bonus/readline/move_cursor_to_funcs/move_to_beginning_of_line_bonus.c \
bonus/readline/move_cursor_to_funcs/move_to_end_of_line_bonus.c \
bonus/readline/move_cursor_to_funcs/move_to_next_word_bonus.c \
bonus/readline/move_cursor_to_funcs/move_to_prec_word_bonus.c \
bonus/readline/move_cursor_to_funcs/move_up_down_vertically_bonus.c \
bonus/readline/open_history_file_bonus.c \
bonus/readline/overwrite_history_file_bonus.c \
bonus/readline/printing_funcs/print_after_cursor_bonus.c \
bonus/readline/printing_funcs/print_curr_char_bonus.c \
bonus/readline/printing_funcs/print_line_with_chosen_method_bonus.c \
bonus/readline/printing_funcs/print_prompt_bonus.c \
bonus/readline/printing_funcs/print_suggestions_bonus.c \
bonus/readline/printing_funcs/put_char_bonus.c \
bonus/readline/printing_funcs/put_colorful_char_bonus.c \
bonus/readline/printing_funcs/rdl_print_char_bonus.c \
bonus/readline/process_input_bonus.c \
bonus/readline/readline_bonus.c \
bonus/readline/restore_cursor_position_bonus.c \
bonus/readline/show_history_bonus.c \
bonus/readline/signals_handler_bonus.c \
bonus/readline/syntax_highlighting_funcs/check_if_cmd_exist_bonus.c \
bonus/readline/syntax_highlighting_funcs/check_if_file_exist_bonus.c \
bonus/readline/syntax_highlighting_funcs/print_with_syntax_highlighting_bonus.c \
bonus/readline/syntax_highlighting_funcs/select_printing_method_bonus.c \
bonus/readline/tab_selection_funcs/enter_tab_mode_bonus.c \
bonus/readline/tab_selection_funcs/erase_prec_file_bonus.c \
bonus/readline/tab_selection_funcs/free_tab_vars_bonus.c \
bonus/readline/tab_selection_funcs/get_dir_to_search_bonus.c \
bonus/readline/tab_selection_funcs/get_file_to_match_bonus.c \
bonus/readline/tab_selection_funcs/get_matched_files_bonus.c \
bonus/readline/tab_selection_funcs/get_max_len_bonus.c \
bonus/readline/tab_selection_funcs/initialize_tab_vars_bonus.c \
bonus/readline/tab_selection_funcs/print_list_of_matched_files_bonus.c \
bonus/readline/tab_selection_funcs/print_matched_file_bonus.c \
bonus/readline/tab_selection_funcs/select_next_file_bonus.c \
bonus/readline/text_highlighting_funcs/copy_highlighted_text_bonus.c \
bonus/readline/text_highlighting_funcs/cut_highlighted_text_bonus.c \
bonus/readline/text_highlighting_funcs/determine_beg_last_highlighted_text_index_bonus.c \
bonus/readline/text_highlighting_funcs/left_highlight_bonus.c \
bonus/readline/text_highlighting_funcs/past_highlighted_text_bonus.c \
bonus/readline/text_highlighting_funcs/quit_highlighting_mode_bonus.c \
bonus/readline/text_highlighting_funcs/right_highlight_bonus.c \
bonus/readline/text_highlighting_funcs/start_highlighting_mode_bonus.c \
bonus/readline/update_cursor_data_bonus.c \
bonus/readline/usefull_history_vec_func_bonus.c \
bonus/vectors/vector_of_char_vectors/add_new_char_vec_at_index_bonus.c \
bonus/vectors/vector_of_char_vectors/add_new_char_vec_bonus.c \
bonus/vectors/vector_of_char_vectors/delete_char_vec_at_index_bonus.c \
bonus/vectors/vector_of_char_vectors/delete_last_char_vec_bonus.c \
bonus/vectors/vector_of_char_vectors/initialize_vec_of_char_vec_bonus.c \
bonus/vectors/vector_of_char_vectors/realloc_and_free_vec_bonus.c \
bonus/vectors/vector_of_chars/add_new_char_at_index_bonus.c \
bonus/vectors/vector_of_chars/add_new_char_bonus.c \
bonus/vectors/vector_of_chars/add_set_of_chars_at_index_bonus.c \
bonus/vectors/vector_of_chars/add_set_of_chars_bonus.c \
bonus/vectors/vector_of_chars/delete_char_at_index_bonus.c \
bonus/vectors/vector_of_chars/initialize_vec_of_char_bonus.c \
bonus/vectors/vector_of_chars/realloc_and_free_vec_bonus.c \
bonus/vectors/vector_of_chars/replace_char_at_index_bonus.c \
bonus/vectors/vector_of_int/add_new_int_at_index_bonus.c \
bonus/vectors/vector_of_int/add_new_int_bonus.c \
bonus/vectors/vector_of_int/delete_int_at_index_bonus.c \
bonus/vectors/vector_of_int/initialize_vec_of_int_bonus.c \
bonus/vectors/vector_of_int/pop_int_bonus.c \
bonus/vectors/vector_of_int/push_int_bonus.c \
bonus/vectors/vector_of_int/realloc_int_vector_bonus.c \
bonus/vectors/vector_of_int/replace_int_at_index_bonus.c \
bonus/vectors/vector_of_string/add_new_element_at_index_bonus.c \
bonus/vectors/vector_of_string/add_new_element_bonus.c \
bonus/vectors/vector_of_string/delete_element_at_index_bonus.c \
bonus/vectors/vector_of_string/initialize_vec_content_bonus.c \
bonus/vectors/vector_of_string/realloc_and_free_vec_bonus.c \
bonus/vectors/vector_of_string/replace_element_at_index_bonus.c

OBJ_DIR = objs

B_OBJ_DIR = objs_bonus

OBJ := $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

B_OBJ := $(addprefix $(B_OBJ_DIR)/, $(B_SRC:.c=.o))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -ltermcap -lreadline

$(LIBFT): force
	@make -sC ./srcs/libft/

$(OBJ): $(OBJ_DIR)/%.o : %.c $(HDRS)
	mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $< -o $@

bonus : all $(B_OBJ)
	$(CC) $(CFLAGS) $(B_OBJ) $(LIBFT) -o $(NAME) -ltermcap -lreadline

$(B_OBJ): $(B_OBJ_DIR)/%.o : %.c $(B_HDRS)
	mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $< -o $@

clean :
	rm -f $(OBJ) $(B_OBJ)
	rm -rf $(OBJ_DIR) $(B_OBJ_DIR)
	make clean -sC ./srcs/libft/

fclean : clean
	rm -f $(NAME)
	make fclean -sC ./srcs/libft/

re : fclean all

.PHONY : all clean fclean re force

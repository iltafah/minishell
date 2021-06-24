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
vectors/vector_of_string/replace_element_at_index.c

OBJ_DIR = objs

OBJ := $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(OBJ) $(LIBFT) -o $(NAME) -lreadline $(LDFLAGS)

$(LIBFT): force
	make -C ./libft

$(OBJ): $(OBJ_DIR)/%.o : %.c
	mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $< -o $@ $(CPPFLAGS)

clean :
	rm -f $(OBJ)
	rm -rf $(OBJ_DIR)
	make clean -C ./libft

fclean : clean
	rm -f $(NAME)
	make fclean -C ./libft

re : fclean all

.PHONY : all clean fclean re force

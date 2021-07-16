/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 19:39:35 by iltafah           #+#    #+#             */
/*   Updated: 2021/07/16 20:36:47 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

t_tokens	*create_token_node(char *data, t_type type)
{
	t_tokens	*token_node;

	token_node = malloc(sizeof(t_tokens));
	token_node->data = data;
	token_node->type = type;
	token_node->next = NULL;
	return (token_node);
}

char	*get_token(char **line, t_type *type)
{
	char	*token;

	token = NULL;
	if (**line == '|')
		token = get_pipe(line, type);
	else if (**line == ';')
		token = get_semicolon(line, type);
	else if (**line == '>' || **line == '<')
		token = get_redirection(line, type);
	else if (**line != ' ' && **line != '\0')
		token = get_simple_word(line, type);
	return (token);
}

void	line_tokenization(char *line, t_tokens **tokens_list)
{
	char		*token;
	t_type		type;
	t_tokens	*curr_token;

			// printf("============================\n");
	*tokens_list = create_token_node(NULL, e_start);
	curr_token = *tokens_list;
	while (*line)
	{
		if (*line == ' ')
			line++;
		else
		{
			// printf("c = %c\n", *line);
			token = get_token(&line, &type);
			curr_token->next = create_token_node(token, type);
			curr_token = curr_token->next;
			// printf("token = %s, type = %d\n", curr_token->data, curr_token->type);
		}
	}
			// printf("============================\n");

	curr_token->next = create_token_node(NULL, newline);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 09:28:37 by iltafah           #+#    #+#             */
/*   Updated: 2021/06/22 18:04:53 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

/*
** ************************************************************************** **
							printing functions
** ************************************************************************** **
*/

void print_cmd_redirection(t_ast *data_node)
{
	t_redirection *curr_redir_node;
	char *input_file = "STDIN";
	char *output_file = "STDOUT";

	curr_redir_node = data_node->node.data.redirections;
	while (curr_redir_node)
	{
		if (strcmp(curr_redir_node->type, ">") == 0 || strcmp(curr_redir_node->type, ">>") == 0)
			output_file = curr_redir_node->file;
		else if (strcmp(curr_redir_node->type, "<") == 0)
			input_file = curr_redir_node->file;
		curr_redir_node = curr_redir_node->next;
	}
	printf("%sredirections:  Input file = [%s%s%s]  , Output file = [%s%s%s]\n",
		   WHT,
		   YEL, input_file, WHT,
		   YEL, output_file, WHT);
}

void print_tokens(t_tokens *tokens)
{
	int spaces = 50;
	int len;
	int spaces_time;
	char type[9][13] = {"start", "pipe", "semicolon", "word", "less",
	"great", "double_less", "double_great", "new_line"};

	while (tokens)
	{
		printf("%s", WHT);
		if (tokens->data)
		{
			if (tokens->data[0] == '\n')
				tokens->data = "\\n";
			len = strlen(tokens->data);
			spaces_time = spaces - len;
			printf("|%s%s%s| %*s type : = %s%s\n", CYN, tokens->data, WHT,
				   spaces_time, " ", YEL, type[tokens->type]);
		}
		tokens = tokens->next;
	}
}

void print_preorder(t_ast *node, int i, t_env_table env_table)
{
	if (node == NULL)
	{
		printf("\n");
		return;
	}
	if (node->tag == e_cmdline_node)
		printf("\n\n%s   »»»»» Command line «««««\n", GRN);
	else if (node->tag == e_pipeline_node)
		printf("\n\n%s█████████ [%d] pipline █████████\n", RED, i++);
	else if (node->tag == e_data_node)
	{
		int i;
		print_cmd_redirection(node);
		
		i = 0;
		if (node->node.data.args_vec.elements[i] != NULL)
			while (node->node.data.args_vec.elements[i])
				printf("%s%s \n", YEL, node->node.data.args_vec.elements[i++]);
		printf("\n");
		return;
	}
	else if (node->tag == e_simple_cmd_node)
	{
		printf("%s\n\n>>>simple command<<<    ", CYN);
		expand_curr_cmd(node);
	}
	print_preorder(node->node.dir.bottom, i, env_table);
	print_preorder(node->node.dir.next, i, env_table);
}




/*
** ************************************************************************** **
							execute_test(ast)
** ************************************************************************** **
*/
t_ast *get_curr_pipeline_seq_node(t_ast *ast)
{
	static t_ast	*curr_pipeline_seq = NULL;
	static int		first = 1;

	if (ast)
	{
		if (first == 1)
			curr_pipeline_seq = ast->node.dir.bottom;
		else if (curr_pipeline_seq != NULL)
			curr_pipeline_seq = curr_pipeline_seq->node.dir.next;
		first++;
	}
	if (curr_pipeline_seq == NULL)
		first = 1;
	return (curr_pipeline_seq);
}

t_ast *get_curr_smpl_cmd_node(t_ast *pipeline_seq)
{
	static t_ast	*curr_smpl_cmd = NULL;
	static int		first = 1;

	if (pipeline_seq)
	{
		if (first == 1)
			curr_smpl_cmd = pipeline_seq->node.dir.bottom;
		else if (curr_smpl_cmd != NULL)
			curr_smpl_cmd = curr_smpl_cmd->node.dir.next;
		first++;
	}
	if (curr_smpl_cmd == NULL)
		first = 1;
	return (curr_smpl_cmd);
}

void	print_args(t_ast *data_node)
{
	int		i;
	int		len;
	int		max_len;
	char	**args;

	i = 0;
	len = 0;
	max_len = 0;
	args = data_node->node.data.args_vec.elements;
	printf("%s[\n%s", PRP,WHT);
	while (args[i])
	{
		len = printf("  %s\n", args[i++]);
		if (max_len < len)
			max_len = len;
	}
	printf("%*s",max_len, "");
	printf("%s]\n", PRP);
	printf("---------------------------------------------------------------\n\n");
}

void	execute_test(t_ast *ast)
{
	t_ast *curr_pipeline_seq;
	t_ast *curr_simple_cmd;
	t_ast *curr_data_node;

	curr_pipeline_seq = get_curr_pipeline_seq_node(ast);
	while (curr_pipeline_seq)
	{	
		curr_simple_cmd = get_curr_smpl_cmd_node(curr_pipeline_seq);
		printf("%s ╔███████████████████████ Pipeline ███████████████████████╗\n\n",RED);
		while (curr_simple_cmd)
		{
			expand_curr_cmd(curr_simple_cmd);
			curr_data_node = curr_simple_cmd->node.dir.bottom;
			print_cmd_redirection(curr_data_node);
			print_args(curr_data_node);
			curr_simple_cmd = get_curr_smpl_cmd_node(curr_pipeline_seq);
		}
		curr_pipeline_seq = get_curr_pipeline_seq_node(ast);
	}
}
/*
** ************************************************************************** **
** ************************************************************************** **
*/

void	temp_exit(t_tokens **tokens_list, t_ast *ast, char *line, char *prompt)
{
	/////////////////////////////////
	/**		  freeing time		**///
	/////////////////////////////////
	free_tokens_list(tokens_list);//
	free_abstract_syntax_tree(ast);//
	free(line);					   //
	free(prompt);
	// free_env_table(env_table);
	/////////////////////////////////
	exit(0);
}








/*
** ************************************************************************** **
								Header
** ************************************************************************** **
*/

void print_header()
{
	printf(CYN);
	printf("███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     \n");
	printf("████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     \n");
	printf("██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     \n");
	printf("██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     \n");
	printf("██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗\n");
	printf("╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n");
}

int	main(int argc, char **argv, char **env)
{
	char		*line;
	char		*prompt;
	t_tokens	*tokens_list = NULL;
	t_ast		*ast = NULL;

	line = NULL;
	prompt = NULL;
	if (argc == 1)
	{
		(void)argv;
		g_vars.last_err_num = 0;
		create_env_table(&g_vars.env_table, env);
		while (1337)
		{
			prompt = get_prompt_name();
			line = readline(prompt);
			add_history(line);
// ////					[herdocs]						//////
			// char *herdocs_content = treat_herdocs("xd");
			// printf("{\n%s}", herdocs_content);
			// free(herdocs_content);
// ////													//////
			line_tokenization(line, &tokens_list);
			print_tokens(tokens_list);
			if (check_tokens_syntax(tokens_list) == ERROR)
			{
				free_tokens_list(&tokens_list);
				free(line);
				free(prompt);
				continue ;
			}
			create_abstract_syntax_tree(&ast, tokens_list);
			/////////////////////////////////
			/**				exit		**///
			if (strcmp(line, "exit") == 0)
				temp_exit(&tokens_list, ast, line, prompt);
			/////////////////////////////////
	
			// print_preorder(ast, 1, env_table);
			execute_test(ast);
			/////////////////////////////////
			/**		  freeing time		**///
			/////////////////////////////////
			free_tokens_list(&tokens_list);//
			free_abstract_syntax_tree(ast);//
			free(line);					   //
			free(prompt);				   //
			/////////////////////////////////
		}
	}
	return (0);
}


// Tests to fix

// echo hello world > file
//echo $8891
//echo $_dfedde
/*[1337] echo $"PWD" */
/*[42] $fairjfgaiejr\ "ls" */ //noice
/*[1] echo hello > "" */
/*[2] echo hello > $ */
/*[6666666666] env -i ./minishell */
/*[696] echo $@ */

/*[3] "echo $jfhjdf=kdjskdgs" */
/*[4] echo $ilias_1337_man$  */     //underscor?? dollar at the end??

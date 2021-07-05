/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iariss <iariss@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 19:32:47 by iariss            #+#    #+#             */
/*   Updated: 2021/07/03 16:30:59 by iariss           ###   ########.fr       */
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
	printf("%s===========================================================\n", YEL);
	printf("%sredirections:\n", PRP);
	while (curr_redir_node)
	{
		printf("\n");
		printf("%stype %s: {%s%s%s}\n", GRN, WHT, YEL, curr_redir_node->type, WHT);
		printf("%sfile %s: \n{%s%s%s}\n", GRN, WHT, YEL, curr_redir_node->file, WHT);
		curr_redir_node = curr_redir_node->next;
		printf("\n");
	}
	printf("%s===========================================================\n", YEL);
	printf("%s", WHT);

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
			curr_pipeline_seq = curr_pipeline_seq->node.pipe.dir.next;
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
			curr_smpl_cmd = pipeline_seq->node.pipe.dir.bottom;
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
	printf("%sArguments:\n", PRP);
	printf("%s[\n%s", PRP,WHT);
	while (args[i])
	{
		len = printf("  %s\n", args[i++]);
		if (max_len < len)
			max_len = len;
	}
	printf("%*s",max_len, "");
	printf("%s]\n", PRP);
	printf("-----------------------------CMD END-----------------------------\n\n\n");
	printf("%s", WHT);
}

void	execute_test(t_ast *ast)
{
	t_ast *curr_pipeline_seq;
	t_ast *curr_simple_cmd;
	t_ast *curr_data;
	int		num_pipes;
	int		*p;
	int		*pid;
	int		wait;
	int		pid_index;
	int		dup1;
	int		dup02;
	int		pipe_index;
	int		i;

	curr_pipeline_seq = get_curr_pipeline_seq_node(ast);
	while (curr_pipeline_seq)
	{
		curr_simple_cmd = get_curr_smpl_cmd_node(curr_pipeline_seq);
		num_pipes = curr_pipeline_seq->node.pipe.pipes_count;
		if(num_pipes)
		{
			p = malloc(sizeof(int) * num_pipes * 2);
			pid = malloc(sizeof(int) * num_pipes + 1);
			pid_index = 0;
			pipe_index = num_pipes;
			i = 0;
			while (pipe_index)
			{
				pipe(&p[i]);
				pipe_index--;
				i += 2;
			}
			pipe_index = 0;
			dup1 = dup(1);
			dup02 = dup(0);
			while (curr_simple_cmd)
			{
				pid[pid_index] = fork();
				if (pid[pid_index] == 0)
				{
					if (curr_simple_cmd->node.dir.next)
						dup2(p[pipe_index + 1], 1);
					if (pid_index != 0)
						dup2(p[pipe_index - 2], 0);
					i = 0;
					while (i < (num_pipes * 2))
					{
						close(p[i]);
						i++;
					}
					expand_curr_cmd(curr_simple_cmd);
					curr_data = curr_simple_cmd->node.dir.bottom;
					execution(curr_data, num_pipes);
					exit(g_vars.last_err_num);
				}
				curr_simple_cmd = get_curr_smpl_cmd_node(curr_pipeline_seq);
				pipe_index += 2;
				pid_index++;
			}
			i = 0;
			while (i < (num_pipes * 2))
			{
				close(p[i]);
				i++;
			}
			wait = 0;
			while(wait <= pid_index)
			{
				waitpid(pid[wait], 0, 0);
				wait++;
			}
			dup2(dup1, 1);
			dup2(dup02, 0);
			close(dup1);
			close(dup02);
			free(p);
			free(pid);
		}
		else
		{
			while(curr_simple_cmd)
			{	
				dup1 = dup(1);
				dup02 = dup(0);
				expand_curr_cmd(curr_simple_cmd);
				curr_data = curr_simple_cmd->node.dir.bottom;
				execution(curr_data, num_pipes);
				dup2(dup1, 1);
				dup2(dup02, 0);
				close(dup1);
				close(dup02);
				curr_simple_cmd = get_curr_smpl_cmd_node(curr_pipeline_seq);
			}
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

// void	signal_handler(int sig_num)
// {
// 	if (sig_num == SIGINT)
// 	{
// 		printf("\n");
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 		g_vars.last_err_num = 1;
// 	}
// }

// void	disable_echoctl_flag(void)
// {
// 	struct termios	state;
// 	char			*tty;
// 	int				fd;

// 	tty = ttyname(0);
// 	fd = open(tty, O_WRONLY);
// 	ioctl(fd,  TIOCGETA, &state);
// 	state.c_lflag &= ~(ECHOCTL);
// 	ioctl(fd, TIOCSETA, &state);
// 	close(fd);
// }

// void	enable_echoctl_flag(void)
// {
// 	struct termios	state;
// 	char			*tty;
// 	int				fd;

// 	tty = ttyname(0);
// 	fd = open(tty, O_WRONLY);
// 	ioctl(fd,  TIOCGETA, &state);
// 	state.c_lflag &= ~(IEXTEN);
// 	state.c_lflag |= ECHOCTL;
// 	ioctl(fd, TIOCSETA, &state);
// 	close(fd);
// }



int		main(int argc, char **argv, char **env)
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
			// signal(SIGINT, signal_handler);
			// signal(SIGQUIT, SIG_IGN);
			prompt = get_prompt_name();
			line = read_line(prompt);
			// add_history(line);
			line_tokenization(line, &tokens_list);
			//print_tokens(tokens_list);
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
			// if (strcmp(line, "exit") == 0)
			// 	temp_exit(&tokens_list, ast, line, prompt);
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

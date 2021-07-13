/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 13:14:43 by iariss            #+#    #+#             */
/*   Updated: 2021/07/13 14:35:06 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"
#include "./execution/file.h"

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



// void	without_pipes(t_ast *curr_simple_cmd, t_piping num, t_ast *pipeline_seq)
// {
// 	t_ast	*curr_data;

// 	while (curr_simple_cmd)
// 	{	
// 		num.dup1 = dup(1);
// 		num.dup02 = dup(0);
// 		expand_curr_cmd(curr_simple_cmd);
// 		curr_data = curr_simple_cmd->node.dir.bottom;
// 		execution(curr_data);
// 		dup2(num.dup1, 1);
// 		dup2(num.dup02, 0);
// 		close(num.dup1);
// 		close(num.dup02);
// 		curr_simple_cmd = get_curr_smpl_cmd_node(pipeline_seq);
// 	}
// }

void	loop_w_pipe(t_piping *num, t_ast *curr_simple_cmd, t_ast *pipeline_seq)
{
	t_ast	*curr_data;

	while (curr_simple_cmd)
	{			
		num->pid[num->pid_index] = fork();
		signal(SIGQUIT, handle_quit);
		signal(SIGINT, handle_c);
		if (num->pid[num->pid_index] == 0)
		{
			signal(SIGQUIT, handle_child_quit);
			signal(SIGINT, handle_child_c);
			if (curr_simple_cmd->node.dir.next)
				dup2(num->p[num->pipe_index + 1], 1);
			if (num->pid_index != 0)
				dup2(num->p[num->pipe_index - 2], 0);
			num->i = 0;
			while (num->i < (num->num_pipes * 2))
			{
				close(num->p[num->i]);
				num->i++;
			}
			expand_curr_cmd(curr_simple_cmd);
			curr_data = curr_simple_cmd->node.dir.bottom;
			execution(curr_data);
			exit(g_vars.last_err_num);
		}
		curr_simple_cmd = get_curr_smpl_cmd_node(pipeline_seq);
		num->pipe_index += 2;
		num->pid_index++;
	}
}

// void	wait_cloce_free(t_piping num)
// {
// 	num.i = 0;
// 	while (num.i < (num.num_pipes * 2))
// 	{
// 		close(num.p[num.i]);
// 		num.i++;
// 	}
// 	num.wait = 0;
// 	while (num.wait <= num.pid_index)
// 	{
// 		waitpid(num.pid[num.wait], 0, 0);
// 		num.wait++;
// 	}
// 	dup2(num.dup1, 1);
// 	dup2(num.dup02, 0);
// 	close(num.dup1);
// 	close(num.dup02);
// 	free(num.p);
// 	free(num.pid);
// }

// void	allocate_startp(t_piping *num)
// {
// 	num->p = malloc(sizeof(int) * num->num_pipes * 2);
// 	num->pid = malloc(sizeof(int) * num->num_pipes + 1);
// 	num->pid_index = 0;
// 	num->pipe_index = num->num_pipes;
// 	num->i = 0;
// 	while (num->pipe_index)
// 	{
// 		pipe(&num->p[num->i]);
// 		num->pipe_index--;
// 		num->i += 2;
// 	}
// 	num->pipe_index = 0;
// 	num->dup1 = dup(1);
// 	num->dup02 = dup(0);
// }

void	execute_test(t_ast *ast)
{
	t_ast		*curr_pipeline_seq;
	t_ast		*curr_simple_cmd;
	t_ast		*curr_data;
	t_piping	num;

	curr_pipeline_seq = get_curr_pipeline_seq_node(ast);
	while (curr_pipeline_seq)
	{
		curr_simple_cmd = get_curr_smpl_cmd_node(curr_pipeline_seq);
		num.num_pipes = curr_pipeline_seq->node.pipe.pipes_count;
		if (num.num_pipes)
		{
			allocate_startp(&num);
			loop_w_pipe(&num, curr_simple_cmd, curr_pipeline_seq);
			wait_cloce_free(num);
		}
		else
			without_pipes(curr_simple_cmd, num, curr_pipeline_seq);
		curr_pipeline_seq = get_curr_pipeline_seq_node(ast);
	}
}


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
			prompt = get_prompt_name();
			line = read_line(prompt);
			line_tokenization(line, &tokens_list);
			if (check_tokens_syntax(tokens_list) == ERROR)
			{
				free_tokens_list(&tokens_list);
				free(line);
				free(prompt);
				continue ;
			}
			create_abstract_syntax_tree(&ast, tokens_list);

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


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_loop_w_pipes.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 08:21:52 by iariss            #+#    #+#             */
/*   Updated: 2021/07/13 14:55:01 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "./file.h"

void	close_fds(t_piping *num)
{
	num->i = 0;
	while (num->i < (num->num_pipes * 2))
	{
		close(num->p[num->i]);
		num->i++;
	}
}

void	loop_w_pipe(t_piping *num, t_ast *curr_simple_cmd, t_ast *pipeline_seq)
{
	t_ast	*curr_data;

	while (curr_simple_cmd)
	{			
		num->pid[num->pid_index] = fork();
		if (num->pid[num->pid_index] == 0)
		{
			if (curr_simple_cmd->node.dir.next)
				dup2(num->p[num->pipe_index + 1], 1);
			if (num->pid_index != 0)
				dup2(num->p[num->pipe_index - 2], 0);
			close_fds(num);
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

void	wait_cloce_free(t_piping num)
{
	int	status;

	num.i = 0;
	while (num.i < (num.num_pipes * 2))
	{
		close(num.p[num.i]);
		num.i++;
	}
	num.wait = 0;
	while (num.wait <= num.pid_index)
	{
		waitpid(num.pid[num.wait], &status, 0);
		num.wait++;
	}
	if (WIFEXITED(status))
		g_vars.last_err_num = WEXITSTATUS(status);
	dup2(num.dup1, 1);
	dup2(num.dup02, 0);
	close(num.dup1);
	close(num.dup02);
	free(num.p);
	free(num.pid);
}

void	allocate_startp(t_piping *num)
{
	num->p = malloc(sizeof(int) * num->num_pipes * 2);
	num->pid = malloc(sizeof(int) * num->num_pipes + 1);
	num->pid_index = 0;
	num->pipe_index = num->num_pipes;
	num->i = 0;
	while (num->pipe_index)
	{
		pipe(&num->p[num->i]);
		num->pipe_index--;
		num->i += 2;
	}
	num->pipe_index = 0;
	num->dup1 = dup(1);
	num->dup02 = dup(0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iariss <iariss@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 11:02:18 by iariss            #+#    #+#             */
/*   Updated: 2021/07/05 15:32:58 by iariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"
#include "../minishell.h"

void	herdoc(t_redirection_vars *red)
{
	red->p = malloc(sizeof(int) * 2);
	pipe(red->p);
	write(red->p[1], red->head.redirections->file,
		ft_strlen(red->head.redirections->file));
	dup2(red->p[0], 0);
	close (red->p[1]);
	close (red->p[0]);
	free(red->p);
}

void	append(t_redirection_vars *red)
{
	red->fd = open(red->head.redirections->file,
			O_RDWR | O_APPEND | O_CREAT, 0644);
	dup2(red->fd, 1);
	close(red->fd);
}

int	red_output(t_redirection_vars *red)
{
	if (red->head.redirections->file[0] != '$')
	{	
		red->fd = open(red->head.redirections->file,
				O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (red->fd == -1)
		{
			printf("minishell: : No such file or directory\n");
			return (0);
		}
		if (red->head.args_vec.used_size)
			dup2(red->fd, 1);
		close(red->fd);
		return (1);
	}
	return (0);
}

int	red_input(t_redirection_vars *red)
{
	red->fd = open(red->head.redirections->file, O_RDONLY);
	if (red->fd == -1)
	{
		printf("minishell: %s: No such file or directory\n",
			red->head.redirections->file);
		g_vars.last_err_num = 1;
		return (0);
	}
	else
	{
		dup2(red->fd, 0);
		close(red->fd);
	}
	return (1);
}

int	check_redis(t_ast *scn)
{
	t_redirection_vars	red;

	red.head = scn->node.data;
	red.x = 1;
	while (red.head.redirections)
	{
		if (!(ft_strcmp(red.head.redirections->type, ">")))
		{
			if (!red_output(&red))
				return (0);
		}
		else if (!(ft_strcmp(red.head.redirections->type, "<")))
		{
			red_input(&red);
			return (0);
		}
		else if (!(ft_strcmp(red.head.redirections->type, ">>")))
			append(&red);
		else if (!(ft_strcmp(red.head.redirections->type, "<<")))
			herdoc(&red);
		red.head.redirections = red.head.redirections->next;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iariss <iariss@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 11:02:18 by iariss            #+#    #+#             */
/*   Updated: 2021/06/30 11:02:40 by iariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"
#include "minishell.h"

void	check_redis(t_ast *scn)
{
	int fd;
	int dep;
	t_data_content head;
	char	*input;
	char	*all;
	int		x;
	int dupp;
	int out;
	int		*p;

	head = scn->node.data;
	x = 1;
	while (head.redirections)
	{
		if(!(ft_strcmp(head.redirections->type, ">")))
		{
			fd = open(head.redirections->file, O_CREAT | O_RDWR | O_TRUNC, 0644);
			if(head.args_vec.used_size)
				dup2(fd, 1);
			close(fd);
		}
		else if(!(ft_strcmp(head.redirections->type, "<")))
		{
			fd = open(head.redirections->file, O_RDONLY);
			if(fd == -1)
			{
				printf("minishell: %s: No such file or directory\n", head.redirections->file);
				g_vars.last_err_num = 1;
			}
			else
			{
				dup2(fd, 0);
				close(fd);
			}
		}
		else if(!(ft_strcmp(head.redirections->type, ">>")))
		{
			fd = open(head.redirections->file, O_RDWR | O_APPEND | O_CREAT, 0644);
			dup2(fd, 1);
			close(fd);
		}
		else if(!(ft_strcmp(head.redirections->type, "<<")))
		{
			p = malloc(sizeof(int) * 2);
			// dupp = dup(0);
			pipe(p);
			write(p[1], head.redirections->file, ft_strlen(head.redirections->file));
			dup2(p[0], 0);
			close (p[1]);
			close (p[0]);
			free(p);
		}
		head.redirections = head.redirections->next;
	}
}
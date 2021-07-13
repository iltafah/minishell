/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_status_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iariss <iariss@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 11:04:06 by iariss            #+#    #+#             */
/*   Updated: 2021/07/13 18:20:46 by iariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"
#include "../minishell.h"

void	status_check(t_redirection_vars *red)
{
	struct stat	buff;

	if (!stat(red->head.redirections->file, &buff))
	{
		if (buff.st_mode & S_IFDIR)
			print_three("minishell:",
				red->head.redirections->file, ": Is a directory\n");
		else
			print_three("minishell:",
				red->head.redirections->file, ": Permission denied\n");
	}
	else
		print_three("minishell: ", red->head.redirections->file,
			": No such file or directory\n");
}

void	status_check_w_err(t_rand *num, t_ast *scn, struct stat buff)
{
	if (!num->tab[num->i])
	{
		num->tab[num->i] = ft_strdup(scn->node.data.args_vec.elements[0]);
	}
	if (!stat(num->tab[num->i], &buff))
	{
		if (buff.st_mode & S_IFDIR)
			print_three("minishell: ", scn->node.data.args_vec.elements[0],
				(": is a directory\n"));
		else
			print_three("minishell: ", scn->node.data.args_vec.elements[0],
				(": Permission denied\n"));
		g_vars.last_err_num = 126;
	}
	else
	{
		g_vars.last_err_num = 127;
		print_three("minishell: ", scn->node.data.args_vec.elements[0],
			": No such file or directory\n");
	}
}

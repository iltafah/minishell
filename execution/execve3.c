/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iariss <iariss@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 10:54:02 by iariss            #+#    #+#             */
/*   Updated: 2021/07/06 11:00:15 by iariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"

char	*join_free(char *s1, char *s2, int index)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	j = 0;
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i++] = s2[j];
		j++;
	}
	str[i] = '\0';
	if (index == 0)
		free(s1);
	else if (index == 1)
		free(s2);
	return (str);
}

void	ex(t_rand *num, t_varso *vars, t_ast *scn)
{
	num->pid = fork();
	if (num->pid == 0)
	{
		if (execve(num->tab[num->i], scn->node.data.args_vec.elements,
				vars->export.env) == -1)
			exit(1);
	}
	waitpid(num->pid, &num->status, 0);
	if (WIFEXITED(num->status))
		g_vars.last_err_num = WEXITSTATUS(num->status);
	if (WEXITSTATUS(num->status))
	{
		num->y = 1;
	}
}

void	execv_main_loop(t_rand *num, t_ast *scn, t_varso *vars)
{
	while (num->tab[num->i])
	{
		num->y = 0;
		num->x = 0;
		if (!check_command(scn, num->sticker, vars, num))
			return ;
		if (!stat(num->tab[num->i], &num->buff))
		{
			ex(num, vars, scn);
			break ;
		}
		num->i++;
	}
}

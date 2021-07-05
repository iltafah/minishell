/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iariss <iariss@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 10:49:58 by iariss            #+#    #+#             */
/*   Updated: 2021/07/05 11:27:10 by iariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"

int	check_args2(int lp, char **a)
{
	if (((!ft_isalpha(a[lp][0])
			|| (!ft_isalnum(a[lp][ft_strlen(a[lp]) - 1])
			&& a[lp][ft_strlen(a[lp]) - 1] != '=')))
			&& a[lp][0] != '_' && a[lp][ft_strlen(a[lp]) - 1] != '_')
	{
		printf("minishell: export: '%s': not a valid identifier\n", a[lp]);
		g_vars.last_err_num = 1;
		return (0);
	}
	return (1);
}

int	check_args(char **a, t_ast *all, int x, int lp)
{
	t_expo_vars	cv;

	cv.i = 0;
	if (a[lp][0] == '-')
	{
		cv.subbed = ft_substr(a[lp], 0, 2);
		printf("minishell: export: %s: invalid option\n", cv.subbed);
		printf("export: usage: export [-nf] [name[=value] ...] or export -p\n");
		g_vars.last_err_num = 2;
	}
	else if (ft_isdigit(a[lp][0]))
	{
		printf("minishell: export: `%s': not a valid identifier\n", a[lp]);
		g_vars.last_err_num = 1;
		return (0);
	}
	else
		return (check_args2(lp, a));
	return (1);
}

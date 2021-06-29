/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iariss <iariss@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 11:11:21 by iariss            #+#    #+#             */
/*   Updated: 2021/06/29 10:19:57 by iariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_H
# define FILE_H

#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
# include <limits.h>
#include <dirent.h>
#include "minishell.h"
#include <signal.h>
#include <sys/stat.h> 



typedef struct s_env
{
	char	**names;
	char	**values;
	char	**env;
}				t_env;

typedef struct s_varso
{
	char	*prev_path;
	t_env	export;
	int		cursed;
	// char	*pwd;
}				t_varso;

typedef struct s_args
{
	int		pipe;
	int 	semi;
	char *command;
	char **flags;
}				t_args;

char	*find_env(char *targ);
void	export(char **args, t_varso *vars, t_ast *sim_cmd_nd);
int	ft_strcmp(const char *s1, const char *s2);
char	*find_home();

#endif
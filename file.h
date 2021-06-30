/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iariss <iariss@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 11:11:21 by iariss            #+#    #+#             */
/*   Updated: 2021/06/30 11:09:36 by iariss           ###   ########.fr       */
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
int		ft_strcmp(const char *s1, const char *s2);
char	*find_home();
void	cd(char **args, t_varso *vars);
void	change_value(char *name, char *new_value);
void	check_path(char **path, t_varso *vars, int *f);
void	echo(char **v, t_varso *vars);
int		check_echo(char **v);
void	export(char **args, t_varso *vars, t_ast *sim_cmd_nd);
void	swap_values(char **s1, char **s2);
void	sort_expo(t_varso *vars);
void	empty_expo(t_varso *vars);
int		check_args(char **args, t_ast *all, int x, int lp);
void	add_to_vars(char *add, int x);
void	unset(t_ast *scn, t_varso *vars);
void	enviro();
void	exv(t_ast *scn, t_varso *vars);
void	add_one(t_varso *vars);
void	merge_env(t_ast *scn, t_varso *vars);
void	check_redis(t_ast *scn);


#endif
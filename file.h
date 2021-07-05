/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iariss <iariss@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 11:11:21 by iariss            #+#    #+#             */
/*   Updated: 2021/07/03 20:15:07 by iariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_H
# define FILE_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <limits.h>
# include <dirent.h>
# include "minishell.h"
# include <signal.h>
# include <sys/stat.h> 

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
	int		semi;
	char	*command;
	char	**flags;
}				t_args;

typedef struct s_rand
{
	int			i;
	int			x;
	char		**tab;
	int			y;
	char		*sticker;
	struct stat	buff;
	int			status;
	pid_t		pid;
}				t_rand;

typedef struct s_expo_vars
{
	int		i;
	int		j;
	int		x;
	char	*smallest;
	int		k;
	char	*subbed;
}				t_expo_vars;

typedef struct s_unset_vars
{
	int		x;
	int		i;
	char	**a;
}				t_unset_vars;

typedef struct s_exv_vars
{
	char		*path;
	char		cwd[PATH_MAX];
	int			y;
	int			i;
	pid_t		pid;
	int			status;
	struct stat	buff;
}				t_exv_vars;

typedef struct s_redirection_vars
{
	int				fd;
	int				dep;
	t_data_content	head;
	char			*input;
	char			*all;
	int				x;
	int				dupp;
	int				out;
	int				*p;
}				t_redirection_vars;

char	*find_env(char *targ);
void	export(char **args, t_varso *vars, t_ast *sim_cmd_nd);
int		ft_strcmp(const char *s1, const char *s2);
char	*find_home(void);
void	cd(char **args, t_varso *vars);
void	change_value(char *name, char *new_value);
void	check_path(char **path, t_varso *vars, int *f);
void	echo(char **v, t_varso *vars);
int		check_echo(char **v);
void	swap_values(char **s1, char **s2);
void	sort_expo(t_varso *vars);
void	empty_expo(t_varso *vars);
int		check_args(char **args, t_ast *all, int x, int lp);
void	add_to_vars(char *add, int x);
void	unset(t_ast *scn, t_varso *vars);
void	enviro(void);
void	exv(t_ast *scn, t_varso *vars);
void	add_one(t_varso *vars);
void	merge_env(t_ast *scn, t_varso *vars);
int		check_redis(t_ast *scn);
void	ft_printf_string(char *s);
void	error_msg(char *s);
void	check_exit(t_ast *scn);
int		check_exit_num(char *num, int j, t_ast *scn);
void	builtins(t_ast *scn, t_varso *vars);
void	pwd(void);
void	handle_c(int sig_num);
void	handle_quit(int sig_num);
int		ft_strcmp(const char *s1, const char *s2);
char	*find_env(char *targ);
char	*join_free(char *s1, char *s2, int index);
void	merge_env(t_ast *scn, t_varso *vars);
void	add_one(t_varso *vars);
int		check_command(t_ast *scn, char *sticker, t_varso *vars, t_rand *num);
void	execv_errors(t_rand *num, t_ast *scn, struct stat buff);

#endif
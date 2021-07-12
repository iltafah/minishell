/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 12:45:07 by iltafah           #+#    #+#             */
/*   Updated: 2021/07/12 12:45:10 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/termios.h>
# include <sys/ioctl.h>
#include "./execution/file.h"

# include "./vectors/vectors.h"
# include "./parser/parser.h"
# include "./libft/libft.h"
# include "./freeing_time/freeing_time.h"
# include "./get_next_line/get_next_line.h"
# include "./readline/readline.h"

# define CYN "\e[1;96m"
# define YEL "\e[1;93m"
# define RED "\e[1;91m"
# define RED_MAX "\e[38;5;196m"
# define GRN "\e[1;92m"
# define PRP "\e[1;95m"
# define WHT "\e[1;97m"
# define GRY "\e[38;5;245m"
# define PNK "\e[38;5;200m"
# define ORN "\e[38;5;202m"
# define L_CYN "\e[38;5;159m"

enum e_bool {false, true};

typedef struct s_gvars
{
	t_rdline		rdl_vars;
	t_env_table		env_table;
	int				last_err_num;
}				t_gvars;

extern t_gvars		g_vars;

t_gvars				g_vars;

typedef struct s_piping
{
	int		num_pipes;
	int		*p;
	int		*pid;
	int		wait;
	int		pid_index;
	int		dup1;
	int		dup02;
	int		pipe_index;
	int		i;
}				t_piping;

char	*get_prompt_name(void);
char	*get_curr_dir_name(void);
char	*treat_heredocs(char *delimiter);
t_ast	*get_curr_smpl_cmd_node(t_ast *pipeline_seq);
void	execution(t_ast *scn);
int		ft_strcmp(const char *s1, const char *s2);
void	change_value(char *name, char *new_value);
void	without_pipes(t_ast *curr_simple_cmd, t_piping num, t_ast *pipeline_seq);
void	loop_w_pipe(t_piping *num, t_ast *curr_simple_cmd, t_ast *pipeline_seq);
void	wait_cloce_free(t_piping num);
void	allocate_startp(t_piping *num);

#endif

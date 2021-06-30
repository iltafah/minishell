/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 19:36:47 by iltafah           #+#    #+#             */
/*   Updated: 2021/06/29 16:24:45 by iltafah          ###   ########.fr       */
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
	char			*pwd;
}				t_gvars;

extern t_gvars		g_vars;

t_gvars				g_vars;

char	*get_prompt_name(void);
char	*get_curr_dir_name(void);
char	*treat_heredocs(char *delimiter);
void	execution(t_ast *scn, int num_pipes);

#endif

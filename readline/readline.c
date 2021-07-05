/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 19:47:14 by iltafah           #+#    #+#             */
/*   Updated: 2021/07/04 15:10:30 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./readline.h"

void	enable_raw_mode(void)
{
	struct termios	raw;

	tcgetattr(g_vars.rdl_vars.tty_fd, &raw);
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN);
	raw.c_iflag &= ~(IXON);
	tcsetattr(g_vars.rdl_vars.tty_fd, TCSANOW, &raw);
}

void	disable_raw_mode(struct termios old_termios_state)
{
	tcsetattr(g_vars.rdl_vars.tty_fd, TCSANOW, &old_termios_state);
}

char	*read_line(char *prompt)
{
	static int	is_initialized = false;
	t_rdline	*rdl_vars;

	rdl_vars = &g_vars.rdl_vars;
	if (is_initialized == false)
	{
		initialize_rdl_vars(rdl_vars);
		initialize_tty_device(rdl_vars);
		initialize_termios_struct(&rdl_vars->original_termios_state);
		initialize_capabilities(&rdl_vars->capability);
		initialize_printing_methods(rdl_vars);
		load_history(rdl_vars);
		is_initialized = true;
	}
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signals_handler);
	signal(SIGWINCH, signals_handler);
	enable_raw_mode();
	process_input(rdl_vars, prompt);
	disable_raw_mode(rdl_vars->original_termios_state);
	return (rdl_vars->line);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_after_cursor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 19:49:29 by iltafah           #+#    #+#             */
/*   Updated: 2021/07/04 20:56:40 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../readline.h"

void	print_after_cursor(t_rdline *rdl_vars, char *str, int option)
{
	// int		i;
	int		len;

	len = ft_strlen(str);
	if (option == restore)
		save_curr_cursor_pos(rdl_vars);
	clear_curr_line_after_cursor(rdl_vars);
	write(1, str, len);
	// i = 0;
	// while (i++ < len)
	// {
	// 	rdl_vars->curs_colm_pos++;
	// 	if (rdl_vars->curs_colm_pos == rdl_vars->width_of_screen)
	// 	{
	// 		// sleep(1);
	// 		put_char(' ');
	// 		// sleep(1);
	// 		move_cursor_left(rdl_vars);
	// 		// sleep(1);
	// 		fprintf(fd1, "print_after_cursor: move to next line\n");
	// 		fflush(fd1);
	// 		rdl_vars->curs_row_pos++;
	// 		rdl_vars->curs_colm_pos = 0;
	// 		clear_curr_line_after_cursor(rdl_vars);
	// 		// sleep(3);
	// 	}
		
	// // 	else
	// }

	if (len < (rdl_vars->width_of_screen - rdl_vars->curs_colm_pos))
	{
		rdl_vars->curs_colm_pos += len;
		// fprintf(fd1, "len < w - col : curs pos (%d, %d)\n", rdl_vars->curs_colm_pos, rdl_vars->curs_row_pos);
		// fflush(fd1);
	}
	else
	{
		rdl_vars->curs_row_pos += (len + rdl_vars->curs_colm_pos) / rdl_vars->width_of_screen;
		rdl_vars->curs_colm_pos = (len + rdl_vars->curs_colm_pos) % rdl_vars->width_of_screen;
		if (rdl_vars->curs_colm_pos == 0)
		{
			put_char(' ');
			rdl_vars->curs_colm_pos++;
			move_cursor_left(rdl_vars);
		}
		// fprintf(fd1, "len > w - col : curs pos (%d, %d) <== (%d / %d) \n", rdl_vars->curs_colm_pos, rdl_vars->curs_row_pos, len, rdl_vars->width_of_screen);
		// fflush(fd1);
	}

 	// if (rdl_vars->curs_colm_pos == rdl_vars->width_of_screen)
	// {
	// 	// sleep(1);
	// 	put_char(' ');
	// 	// sleep(1);
	// 	move_cursor_left(rdl_vars);
	// 	// sleep(1);
	// 	fprintf(fd1, "print_after_cursor: move to next line\n");
	// 	fflush(fd1);
	// 	rdl_vars->curs_row_pos++;
	// 	rdl_vars->curs_colm_pos = 0;
	// 	clear_curr_line_after_cursor(rdl_vars);
	// 	// sleep(3);
	// }






	
	// if (rdl_vars->curs_colm_pos == rdl_vars->width_of_screen)
	// {
	// 	// sleep(2);
	// 	put_char('?');
	// 	// sleep(2);
	// 	move_cursor_left(rdl_vars);
	// 	// sleep(2);
	// 	rdl_vars->curs_row_pos++;
	// 	rdl_vars->curs_colm_pos = 0;
	// }
	// i = 0;
	// while (str[i])
	// {
	// 	rdl_print_char(rdl_vars, str[i], WHT);
	// 	i++;
	// }
	if (option == restore)
		restore_cursor_pos(rdl_vars);
}


//echo hello world lets see what will happen if we go like this go brrr what so ever meow mamamai I dont have any thing to say but yeah well fuck off
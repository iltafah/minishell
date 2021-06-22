/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_home_action.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 19:51:10 by iltafah           #+#    #+#             */
/*   Updated: 2021/06/20 16:32:14 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../readline.h"

void	start_home_action(t_rdline *rdl_vars)
{
	quit_highlighting_mode(rdl_vars, home);
	move_to_beginning_of_line(rdl_vars);
}

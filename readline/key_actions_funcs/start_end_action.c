/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_end_action.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 19:51:18 by iltafah           #+#    #+#             */
/*   Updated: 2021/06/13 19:51:19 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../readline.h"

void	start_end_action(t_rdline *rdl_vars)
{
	quit_highlighting_mode(rdl_vars, end);
	move_to_end_of_line(rdl_vars);
}

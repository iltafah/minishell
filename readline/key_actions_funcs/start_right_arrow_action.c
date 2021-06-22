/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_right_arrow_action.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 19:50:58 by iltafah           #+#    #+#             */
/*   Updated: 2021/06/13 19:50:59 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../readline.h"

void	start_right_arrow_action(t_rdline *rdl_vars)
{
	quit_highlighting_mode(rdl_vars, right_arrow);
	move_right(rdl_vars);
}

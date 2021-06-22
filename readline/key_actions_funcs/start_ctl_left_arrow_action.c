/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_ctl_left_arrow_action.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 19:51:44 by iltafah           #+#    #+#             */
/*   Updated: 2021/06/13 19:51:45 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../readline.h"

void	start_ctl_left_arrow_action(t_rdline *rdl_vars)
{
	quit_highlighting_mode(rdl_vars, ctl_left_arrow);
	move_to_prec_word(rdl_vars);
}

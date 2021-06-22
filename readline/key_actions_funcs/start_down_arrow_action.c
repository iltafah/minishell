/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_down_arrow_action.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 19:51:21 by iltafah           #+#    #+#             */
/*   Updated: 2021/06/13 19:51:22 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../readline.h"

void	start_down_arrow_action(t_rdline *rdl_vars)
{
	quit_highlighting_mode(rdl_vars, down_arrow);
	show_new_history(rdl_vars);
}

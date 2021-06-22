/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_up_arrow_action.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 19:50:45 by iltafah           #+#    #+#             */
/*   Updated: 2021/06/13 19:50:46 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../readline.h"

void	start_up_arrow_action(t_rdline *rdl_vars)
{
	quit_highlighting_mode(rdl_vars, up_arrow);
	show_old_history(rdl_vars);
}

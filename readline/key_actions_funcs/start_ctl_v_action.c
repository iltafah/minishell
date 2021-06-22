/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_ctl_v_action.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 19:51:28 by iltafah           #+#    #+#             */
/*   Updated: 2021/06/13 19:51:29 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../readline.h"

void	start_ctl_v_action(t_rdline *rdl_vars)
{
	quit_highlighting_mode(rdl_vars, ctl_v);
	past_highlighted_text(rdl_vars);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pop_int_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 19:43:32 by iltafah           #+#    #+#             */
/*   Updated: 2021/07/17 12:06:26 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vectors_bonus.h"

void	pop_int(t_int_vec *vec, int *num_addr)
{
	if (vec->used_size > 0)
	{
		*num_addr = vec->elements[0];
		delete_int_at_index(vec, 0);
	}
}

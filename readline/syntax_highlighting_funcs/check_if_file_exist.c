/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_file_exist.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 19:48:52 by iltafah           #+#    #+#             */
/*   Updated: 2021/06/13 19:48:54 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../readline.h"

int	check_if_file_exist(char *file)
{
	struct stat	buffer;
	int			does_exist;

	does_exist = stat(file, &buffer);
	if (does_exist == 0)
		return (EXIST);
	return (NONE);
}

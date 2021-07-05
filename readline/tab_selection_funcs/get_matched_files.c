/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_matched_files.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iltafah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 13:53:14 by iltafah           #+#    #+#             */
/*   Updated: 2021/07/05 16:15:57 by iltafah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../readline.h"

void	get_matched_files(t_tab_vars *vars)
{
	DIR				*curr_directory;
	struct dirent	*entry;
	struct stat		file_stat;
	char			*file_with_path;

	curr_directory = opendir(vars->dir_to_search);
	if (curr_directory == NULL)
		return ;
	while (true)
	{
		entry = readdir(curr_directory);
		// if (entry == NULL)
		// 	break ;
		if (vars->file_to_match != NULL)
		{
			if (entry->d_name[0] != '.'
				&& ft_strncmp(vars->file_to_match, entry->d_name, ft_strlen(vars->file_to_match)) == 0)
			{
				file_with_path = ft_strjoin(vars->dir_to_search, entry->d_name);
				stat(file_with_path, &file_stat);
				if (S_ISDIR(file_stat.st_mode))
				{
					vars->matched_files.add_new_element(&vars->matched_files, ft_strjoin(entry->d_name, "/"));
					vars->files_colors.add_new_element(&vars->files_colors, red);
				}
				else
				{
					vars->matched_files.add_new_element(&vars->matched_files, ft_strdup(entry->d_name));
					vars->files_colors.add_new_element(&vars->files_colors, white);
				}
				free(file_with_path);
			}
		}
		else if (entry->d_name[0] != '.')
		{
			file_with_path = ft_strjoin(vars->dir_to_search, entry->d_name);
			stat(file_with_path, &file_stat);
			if (S_ISDIR(file_stat.st_mode))
			{
				vars->matched_files.add_new_element(&vars->matched_files, ft_strjoin(entry->d_name, "/"));
				vars->files_colors.add_new_element(&vars->files_colors, red);
			}
			else
			{
				vars->matched_files.add_new_element(&vars->matched_files, ft_strdup(entry->d_name));
				vars->files_colors.add_new_element(&vars->files_colors, white);
			}
			free(file_with_path);
		}
	}
	closedir(curr_directory);
	return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulho <maboulho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 17:14:53 by eel-ghan          #+#    #+#             */
/*   Updated: 2022/12/15 07:08:05 by maboulho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/header.h"

t_cmd	*init_struct_cmd(void)
{
	t_cmd	*cmd_list;

	cmd_list = malloc(sizeof(t_cmd));
	if (!cmd_list)
		return (NULL);
	cmd_list->cmd = ft_calloc(1, sizeof(char *));
	if (!cmd_list->cmd)
		return (NULL);
	cmd_list->dflag = -1;
	cmd_list->index_cmd = 0;
	cmd_list->herdoc = NULL;
	cmd_list->file = NULL;
	cmd_list->next = NULL;
	return (cmd_list);
}

t_file	*init_file(char *name, int type)
{
	t_file	*file;

	file = malloc(sizeof(t_file));
	if (!file)
		return (NULL);
	file->file_name = name;
	file->type = type;
	file->next = NULL;
	return (file);
}

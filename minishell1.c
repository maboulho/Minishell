/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulho <maboulho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 05:13:08 by maboulho          #+#    #+#             */
/*   Updated: 2022/12/16 05:15:53 by maboulho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/header.h"

void	ft_free_2d(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	*find_path(t_env *enva)
{
	int		i;
	t_env	*tmp;

	tmp = enva;
	i = 0;
	while (tmp)
	{
		if (ft_strncmp("PATH", tmp->content, 4) == 0)
			return (tmp->content);
		tmp = tmp->next;
	}
	return (0);
}

char	*check_path(t_cmd *p)
{
	char	*cmd_path;
	char	*slash;
	char	**path;
	int		i;

	i = -1;
	if (access(p->cmd[0], F_OK) == -1)
	{
		cmd_path = trim_path();
		if (!cmd_path)
			return (NULL);
		path = ft_split(cmd_path, ':');
		while (path[++i])
		{
			slash = ft_strjoin1(path[i], "/");
			cmd_path = ft_strjoin1(slash, p->cmd[0]);
			if (access(cmd_path, F_OK) == 0)
				return (cmd_path);
			free(cmd_path);
			free(slash);
		}
	}
	else
		return (ft_strdup(p->cmd[0]));
	return (NULL);
}

void	ft_lstadd_back_a(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (new == NULL || lst == NULL)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	else
	{
		tmp = *lst;
		while (tmp->next != NULL)
			tmp = tmp -> next;
		tmp -> next = new;
	}
}

int	ft_cmdsize(t_cmd *lst)
{
	int		len;
	t_cmd	*tmp;

	tmp = lst;
	len = 0;
	while (tmp != NULL)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

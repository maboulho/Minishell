/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulho <maboulho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 05:04:40 by maboulho          #+#    #+#             */
/*   Updated: 2022/12/16 05:14:53 by maboulho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../Includes/struct_cmd.h"

int	ft_lstsize_a(t_env *lst)
{
	int		len;
	t_env	*tmp;

	tmp = lst;
	len = 0;
	while (tmp != NULL)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

int	ft_is_a_built_in(t_cmd *p)
{
	if (!p && !p->cmd && !*p->cmd)
		return (0);
	if (!ft_strncmp(p->cmd[0], "echo", 4))
		return (1);
	else if (!ft_strncmp(p->cmd[0], "cd", 2))
		return (1);
	else if (!ft_strncmp(p->cmd[0], "env", 3))
		return (1);
	else if (!ft_strncmp(p->cmd[0], "exit", 4))
		return (1);
	else if (!ft_strncmp(p->cmd[0], "export", 6))
		return (1);
	else if (!ft_strncmp(p->cmd[0], "pwd", 3))
		return (1);
	else if (!ft_strncmp(p->cmd[0], "unset", 5))
		return (1);
	else
		return (0);
}

void	forking_norm(t_cmd *p, int fd_save, int fd[2])
{
	if (ft_is_a_built_in(p))
		p->out = 1;
	if (p->out != 1)
		dup2(p->out, 1);
	else if (p->next)
		dup2(fd[1], 1);
	if (p->in != 0)
		dup2(p->in, 0);
	else if (fd_save != -1)
		dup2(fd_save, 0);
	close(fd[0]);
}

void	forking(t_cmd *p, int fd_save, char **env, int fd[2])
{
	pipe(fd);
	p->id = fork();
	if (p->id == 0)
	{
		forking_norm(p, fd_save, fd);
		if (ft_is_a_built_in(p))
		{
			builtins(p, env);
			exit(g_.exit_value);
		}
		else if (command_not_found(p) == 0)
		{
			execute(p);
			exit(g_.exit_value);
		}
	}
	close(fd[1]);
	if (fd_save != -1)
		close(fd_save);
	fd_save = fd[0];
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulho <maboulho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 04:19:10 by maboulho          #+#    #+#             */
/*   Updated: 2022/12/16 03:14:13 by maboulho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../Includes/struct_cmd.h"

void	herdoc(t_cmd *p)
{
	if (p->in != 0)
		close(p->in);
	p->in = p->file->fd;
}

void	wait_for_everything(t_cmd *p)
{
	int	status;

	while (p)
	{
		waitpid(p->id, &status, 0);
		if (WIFEXITED(status))
			g_.exit_value = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
				g_.exit_value = status + 128;
		p = p->next;
	}
}

int	command_not_found(t_cmd *p)
{
	if (!check_path(p))
	{
		printf("minishell: %s: command not found\n", p->cmd[0]);
		g_.exit_value = 127;
		exit(g_.exit_value);
	}
	if (is_exectable_f(p->cmd[0]))
		g_.exit_value = 126;
	else if (!access(p->cmd[0], F_OK))
		g_.exit_value = 127;
	return (0);
}

int	is_exectable_f(char *s)
{
	if (ft_strlen(s) >= 2 && s[0] == '.' && s[1] == '/')
		return (1);
	return (0);
}

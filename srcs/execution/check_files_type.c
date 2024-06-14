/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulho <maboulho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 19:53:59 by maboulho          #+#    #+#             */
/*   Updated: 2022/12/15 21:25:44 by maboulho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../Includes/header.h"

int	appand_check(t_cmd *p)
{
	if (p->out != 1)
		close(p->out);
	p->out = open(p->file->file_name, O_APPEND | O_WRONLY | O_CREAT, 0777);
	if (p->out == -1 || !p->file->file_name)
	{
		printf("minishell: syntax error near unexpected token `>'\n");
		return (0);
	}
	return (1);
}

void	hdoc_loop(int fd, t_file *p)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(p->file_name, line) == 0)
		{
			close (fd);
			exit (0);
		}
		else
			ft_putendl_fd(line, fd);
	}
}

void	open_herdoc(t_file *p, t_cmd *cmd)
{
	int		fd;
	int		pid;
	char	*number_cmd;

	if (cmd->herdoc)
		free (cmd->herdoc);
	(void)p;
	number_cmd = ft_itoa(cmd->index_cmd);
	cmd->herdoc = ft_strjoin1("/tmp/.env_", number_cmd);
	if (number_cmd)
		free (number_cmd);
		pid = fork ();
	if (pid == 0)
	{
		fd = open (cmd->herdoc, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		hdoc_loop(fd, p);
	}
	waitpid(pid, 0, 0);
}

int	redirections(t_cmd *p)
{
	int				i;
	t_file			*x;

	x = p->file;
	while (p->file)
	{
		if (p->file->type == 5)
			open_herdoc(p->file, p);
		p->file = p->file->next;
	}
	p->file = x;
	i = 1;
	i = files_int(p, i);
	p->file = x;
	if (i == 0)
		return (0);
	return (1);
}

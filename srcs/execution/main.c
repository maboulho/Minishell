/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulho <maboulho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 22:38:56 by maboulho          #+#    #+#             */
/*   Updated: 2022/12/16 05:15:14 by maboulho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/struct_cmd.h"

void	execute_norm(t_cmd *p, int i)
{
	if (is_exectable_f(p->cmd[0]))
		printf("minishell: %s: Permission denied\n", p->cmd[i]);
	else
		printf("minishell: %s: command not found\n", p->cmd[i]);
}

void	execute(t_cmd *p)
{
	char	*path;
	int		i;
	char	**args;

	i = 0;
	path = check_path(p);
	if (p->id == 0)
	{
		if (p->cmd[0] != NULL)
		{
			if (p->herdoc)
			{
				args = malloc (sizeof(char *) * 3);
				args[0] = ft_strdup(path);
				args[1] = ft_strdup(p->herdoc);
				args[2] = NULL;
				p->cmd = args;
			}
			signal(SIGQUIT, SIG_DFL);
			if (execve(path, p->cmd, envirenment()) == -1 || !path)
				execute_norm(p, i);
		}
	}
}

void	ft_multi_pipes_norm(t_cmd *p, int fd_save, int fd[2], char **env)
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

void	ft_multi_pipes_god_norm(t_cmd *p, int *fd_save, int fd[2], char **env)
{
	if (ft_is_a_built_in(p) && !p->next)
	{
		builtins(p, env);
		g_.bt_flag = 1;
	}
	else
	{
		pipe(fd);
		p->id = fork();
		if (p->id == 0)
			ft_multi_pipes_norm(p, *fd_save, fd, env);
		close(fd[1]);
		if (*fd_save != -1)
			close(*fd_save);
		*fd_save = fd[0];
	}
}

void	multi_pipes(t_cmd *p, char **env)
{
	int		i;
	int		fd_save;
	t_cmd	*cp;
	int		fd[2];

	fd_save = -1;
	i = 0;
	cp = p;
	g_.bt_flag = 0;
	while (p)
	{
		ft_multi_pipes_god_norm(p, &fd_save, fd, env);
		p = p->next;
	}
	if (!g_.bt_flag)
		wait_for_everything(cp);
}

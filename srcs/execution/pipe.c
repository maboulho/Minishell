/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulho <maboulho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 20:40:31 by maboulho          #+#    #+#             */
/*   Updated: 2022/12/16 01:30:49 by maboulho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../Includes/struct_cmd.h"

void	print_enva(t_cmd *p)
{
	t_env	*tmp;

	tmp = g_.enva;
	while (tmp)
	{
		if (tmp->value != NULL)
		{
			ft_putstr_fd(tmp->name, p->out);
			ft_putstr_fd("=", p->out);
			ft_putstr_fd(tmp->value, p->out);
			ft_putstr_fd("\n", p->out);
		}
		tmp = tmp->next;
	}
}

void	builtins(t_cmd *p, char **env)
{
	if (!ft_strncmp(p->cmd[0], "echo", 4) && ft_strlen(p->cmd[0]) == 4)
		echo(p);
	else if (!ft_strncmp(p->cmd[0], "cd", 2) && ft_strlen(p->cmd[0]) == 2)
		cd(p);
	else if (!ft_strncmp(p->cmd[0], "env", 3) && ft_strlen(p->cmd[0]) == 3)
	{
		env_int(env, 1);
		print_enva(p);
	}
	else if (!ft_strncmp(p->cmd[0], "exit", 4) && ft_strlen(p->cmd[0]) == 4)
		exit_f(p);
	else if (!ft_strncmp(p->cmd[0], "pwd", 3) && ft_strlen(p->cmd[0]) == 3)
		pwd(p);
	else if (!ft_strncmp(p->cmd[0], "export", 6) && ft_strlen(p->cmd[0]) == 6)
		export(p);
	else if (!ft_strncmp(p->cmd[0], "unset", 5) && ft_strlen(p->cmd[0]) == 5)
		unset(p);
	else
		ft_putendl_fd("Command Not Found!", 2);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

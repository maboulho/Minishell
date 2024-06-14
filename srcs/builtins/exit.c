/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulho <maboulho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:51:51 by maboulho          #+#    #+#             */
/*   Updated: 2022/12/16 00:20:45 by maboulho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../Includes/struct_cmd.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	check_num(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		else
			i++;
		return (1);
	}
	return (0);
}

int	check_sign(char *s)
{
	if (s[0] == '-' || s[0] == '+')
		return (1);
	return (0);
}

int	numeric_error(t_cmd *p)
{
	printf("minishell: exit: %s: numeric argument required\n", p->cmd[1]);
	g_.exit_value = 255;
	exit(g_.exit_value);
}

void	exit_f(t_cmd *p)
{
	printf("exit\n");
	if (p->cmd[0] && !p->cmd[1])
	{
		g_.exit_value = 0;
		exit(g_.exit_value);
	}
	else if (!check_num(p->cmd[1]) && !check_sign(p->cmd[1]))
		exit(numeric_error(p));
	else if (p->cmd[2])
	{
		printf("minishell: exit: too many arguments\n");
		g_.exit_value = 1;
		return ;
	}
	else if (check_num(p->cmd[1]) && check_sign(p->cmd[1]))
	{
		g_.exit_value = 0;
		exit(g_.exit_value);
	}
	else
	{
		g_.exit_value = atoi(p->cmd[1]) % 256;
		exit(g_.exit_value);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulho <maboulho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 22:39:44 by maboulho          #+#    #+#             */
/*   Updated: 2022/12/15 10:41:04 by maboulho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../Includes/struct_cmd.h"

void	print_echo(t_cmd *p, int i)
{
	while (p->cmd[i])
	{
		ft_putstr_fd(p->cmd[i], p->out);
		if (p->cmd[i + 1] != NULL)
			ft_putchar_fd(' ', p->out);
		i++;
	}
}

void	echo(t_cmd *p)
{
	int	i;
	int	j;
	int	is_n;

	i = 1;
	is_n = 0;
	while (p->cmd[i])
	{
		if (p->cmd[i][0] == '-' && p->cmd[i][1] != '\0')
		{
			j = 1;
			while (p->cmd[i][j] == 'n' && p->cmd[i][j])
				j++;
			if (p->cmd[i][j] != '\0')
				break ;
			is_n = 1;
		}
		else
			break ;
		i++;
	}
	print_echo(p, i);
	if (is_n == 0)
		ft_putchar_fd('\n', p->out);
}

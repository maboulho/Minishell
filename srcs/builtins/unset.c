/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulho <maboulho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 09:39:15 by maboulho          #+#    #+#             */
/*   Updated: 2022/12/16 04:00:08 by maboulho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../Includes/struct_cmd.h"

void	free_var(int i)
{
	t_env	*head;
	t_env	*tmp;

	head = g_.enva;
	tmp = g_.enva;
	if (i == 0)
	{
		g_.enva = head->next;
		free(tmp);
		tmp = NULL;
	}
	else
	{
		while (i != 0)
		{
			head = tmp;
			tmp = tmp->next;
			i--;
		}
		head->next = tmp->next;
		free(tmp);
		tmp = NULL;
	}
}

void	delete_node(char *s)
{
	t_env	*p;
	int		i;

	p = g_.enva;
	i = 0;
	while (p)
	{
		if (!ft_strcmp(s, p->name))
		{
			if (p->name)
				free(p->name);
			if (p->value)
				free(p->value);
			if (p->content)
				free(p->content);
			free_var(i);
			break ;
		}
		i++;
		p = p->next;
	}
}

int	valid(char	*str)
{
	int	j;

	j = 0;
	if (ft_isalpha(str[0]) == 0)
		return (-1);
	while (str[j])
	{
		if (ft_isalnum(str[j]) == 0)
			return (-1);
		j++;
	}
	return (1);
}

void	unset(t_cmd *p)
{
	int		i;

	if (!p->cmd[1])
		return ;
	else
	{
		i = 1;
		while (p->cmd[i])
		{
			if (valid(p->cmd[i]) == 1)
				delete_node(p->cmd[i]);
			else
			{
				ft_putstr_fd("Minishell: unset: `", 2);
				ft_putstr_fd(p->cmd[i], 2);
				ft_putstr_fd("`: not a valid identifier\n", 2);
				g_.exit_value = 1;
			}
			i++;
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulho <maboulho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:26:41 by maboulho          #+#    #+#             */
/*   Updated: 2022/12/16 04:22:32 by maboulho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include"../../Includes/struct_cmd.h"
#include"../../Includes/header.h"

void	export(t_cmd *p)
{
	int		i;
	char	*name;

	i = 1;
	if (!p->cmd[i])
		print_export(p);
	else
	{
		while (p->cmd[i])
		{
			name = export_name(p->cmd[i]);
			if (!is_valid_identifier(name))
				ft_export_norm(p, i);
			else if (check_export(p->cmd[i]))
			{
				free(name);
				return ;
			}
			else
				add_to_env(p->cmd[i]);
			i++;
			free(name);
		}
	}
}

char	*export_name(char *cont)
{
	int	i;

	i = 0;
	while (cont[i] && cont[i] != '=')
		i++;
	return (ft_substr(cont, 0, i));
}

char	*export_value(char *cont)
{
	int	i;

	i = 0;
	while (cont[i] && cont[i] != '=')
		i++;
	if (cont[i] == '\0')
		return (NULL);
	i++;
	return (ft_substr(cont, i, ft_strlen(cont) - i));
}

int	exist(t_env **tmp, char *name)
{
	while ((*tmp))
	{
		if (ft_strcmp((*tmp)->name, name) == 0)
			return (1);
		(*tmp) = (*tmp)->next;
	}
	return (0);
}

int	check_export(char *arg)
{
	t_env	*tmp;
	int		i;
	char	*name;
	char	*value;

	i = 1;
	tmp = g_.enva;
	name = export_name(arg);
	if (exist(&tmp, name) == 1)
	{
		value = export_value(arg);
		if (value)
		{
			if (tmp->value)
				free(tmp->value);
			tmp->value = value;
		}
		free(name);
		return (1);
	}
	free(name);
	return (0);
}

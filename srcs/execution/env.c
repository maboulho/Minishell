/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulho <maboulho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 04:20:12 by maboulho          #+#    #+#             */
/*   Updated: 2022/12/15 21:06:20 by maboulho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../Includes/struct_cmd.h"

int	calculate_lines(char **env)
{
	int	i;

	i = 0;
	while (env[i++])
		;
	return (i);
}

t_env	*init_node(char *s)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	new->content = ft_strdup(s);
	new->name = export_name(s);
	new->value = export_value(s);
	new->next = NULL;
	return (new);
}

void	env_int(char **env, int flag)
{
	int	i;
	int	number;

	i = 0;
	number = calculate_lines(env);
	while (env[i] && flag == 0)
	{
		ft_lstadd_back_a(&g_.enva, init_node(env[i]));
		i++;
	}
}

void	add_to_env(char *var)
{
	t_env	*ptr;

	ptr = malloc(sizeof(t_env));
	ptr->name = export_name(var);
	ptr->value = export_value(var);
	ptr->content = ft_strdup(var);
	ptr->next = NULL;
	ft_lstadd_back_a(&g_.enva, ptr);
}

int	is_valid_identifier(char *s)
{
	int	i;

	i = 0;
	if (s[i] != '_' && !ft_isalpha(s[i]))
		return (0);
	i++;
	while (s[i])
	{
		if (!(ft_isalnum(s[i]) || s[i] == '_' || s[i] == '='))
			return (0);
		i++;
	}
	return (1);
}

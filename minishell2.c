/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulho <maboulho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 04:11:03 by maboulho          #+#    #+#             */
/*   Updated: 2022/12/16 05:15:39 by maboulho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/header.h"

void	ft_strjoin_norm(char *s3, int *i, int *j, char **ret)
{
	while (s3[*j])
	{
		(*ret)[*i] = s3[*j];
		*i += 1;
		*j += 1;
	}
}

char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	ret = malloc(sizeof(char)
			* (ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1));
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		ret[i] = s2[j];
		i++;
		j++;
	}
	ft_strjoin_norm(s3, &i, &j, &ret);
	ret[i] = '\0';
	return (ret);
}

void	ft_rebuild_env(t_env *env)
{
	t_env	*temp;
	char	*t;

	t = NULL;
	temp = env;
	while (temp)
	{
		t = env->content;
		env->content = ft_strjoin3(temp->name, "=", temp->value);
		free(t);
		temp = temp->next;
	}
}

char	**to_2d(t_env *env)
{
	char	**ret;
	int		i;
	int		size;
	t_env	*temp;

	i = 0;
	size = 0;
	temp = env;
	while (temp)
	{
		size++;
		temp = temp->next;
	}
	ret = malloc(sizeof(char *) * (size + 1));
	if (!ret)
		return (NULL);
	while (env)
	{
		ret[i] = ft_strdup(env->content);
		i++;
		env = env->next;
	}
	ret[i] = NULL;
	return (ret);
}

char	*trim_path(void)
{
	char	*path;
	char	*s;

	s = find_path(g_.enva);
	if (!s)
		return (NULL);
	path = ft_strchr(s, '=');
	path++;
	return (path);
}

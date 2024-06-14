/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils00.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulho <maboulho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 21:17:23 by eel-ghan          #+#    #+#             */
/*   Updated: 2022/12/16 05:09:24 by maboulho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/header.h"

int	check_char(t_lexer *lexer)
{
	if ((lexer->c < 'a' || lexer->c > 'z')
		&& (lexer->c < 'A' || lexer->c > 'Z')
		&& (lexer->c < '0' || lexer->c > '9')
		&& lexer->c != '_' && lexer->c != '$')
		return (1);
	if (lexer->c == '>' || lexer->c == '<'
		|| lexer->c == '|')
		return (1);
	return (0);
}

char	*get_value_for_dollar(t_lexer *lexer)
{
	char	*s;
	char	*value;

	if ((lexer->c < 'a' || lexer->c > 'z')
		&& (lexer->c < 'A' || lexer->c > 'Z')
		&& (lexer->c < '0' || lexer->c > '9')
		&& lexer->c != '_')
		return (get_str2(lexer));
	s = get_str(lexer);
	value = get_env(lexer->lxenv, s);
	free(s);
	if (!value)
	{
		value = ft_calloc(1, sizeof(char));
		if (!value)
			return (NULL);
	}
	return (value);
}

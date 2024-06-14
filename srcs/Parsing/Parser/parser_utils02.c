/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils02.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulho <maboulho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:46:40 by eel-ghan          #+#    #+#             */
/*   Updated: 2022/12/16 03:00:59 by maboulho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/header.h"

int	parser_check(t_parser *parser)
{
	if (parser->token->e_type == TOKEN_OUTPUT
		|| parser->token->e_type == TOKEN_INPUT
		|| parser->token->e_type == TOKEN_APPEND
		|| parser->token->e_type == TOKEN_HERE_DOC)
		return (1);
	return (0);
}

void	parser_handle_here_dog(t_parser *parser, t_cmd *head)
{
	if (parser->token->e_type != TOKEN_RD_ERROR)
		parser_parse_redirection(parser, head);
}

int	handle_hd_error(t_parser *parser, t_cmd *head)
{
	g_.exit_value = 258;
	if (parser->token->e_type == TOKEN_RD_ERROR)
	{
		parser_handle_here_dog(parser, head);
		return (1);
	}
	return (0);
}

int	handle_rd_error(t_parser *parser)
{
	g_.exit_value = 258;
	if (parser->token->e_type == TOKEN_RD_ERROR)
		return (1);
	return (0);
}

t_token	*free_get_token(t_parser *parser)
{
	free(parser->token);
	return (lexer_get_next_token(parser->lexer));
}

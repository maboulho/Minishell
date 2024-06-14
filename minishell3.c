/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulho <maboulho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 04:28:29 by maboulho          #+#    #+#             */
/*   Updated: 2022/12/16 04:29:39 by maboulho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/header.h"

void	free_util(t_parser *parser, t_lexer *lexer,
	t_cmd *list)
{
	free(parser->token);
	free(parser);
	free(lexer->contents);
	free(lexer);
	free_list(list);
}

t_lexer	*get_lexer(char *command, t_lxenv *lxenv)
{
	t_lexer		*lexer;

	if (!command)
	{
		printf("exit\n");
		free(command);
		exit(g_.exit_value);
	}
	if (!*command || !check_space(command))
	{
		free(command);
		return (NULL);
	}
	add_history(command);
	lexer = init_lexer(command, lxenv, g_.exit_value);
	if (!lexer)
		return (NULL);
	return (lexer);
}

int	ft_2d_size(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	lxenv_int(t_lxenv *lxenv, char **env)
{
	int	i;

	lxenv->len = 0;
	while (env[lxenv->len])
		lxenv->len++;
	lxenv->env = malloc(sizeof(char *) * (lxenv->len + 1));
	if (!lxenv->env)
		return ;
	i = 0;
	while (env[i])
	{
		lxenv->env[i] = malloc(sizeof(char *) * ft_strlen(env[i]));
		if (!lxenv->env[i])
			return ;
		ft_strlcpy(lxenv->env[i], env[i], ft_strlen(env[i]) + 1);
		i++;
	}
	lxenv->env[i] = NULL;
}

void	sig_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

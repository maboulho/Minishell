/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulho <maboulho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:17:23 by eel-ghan          #+#    #+#             */
/*   Updated: 2022/12/16 05:13:26 by maboulho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/header.h"

char	**r_get_env(char **env)
{
	int		i;
	char	**ret;

	i = 0;
	ret = malloc(sizeof(char *) * (ft_2d_size(env) + 1));
	while (env[i])
	{
		ret[i] = ft_strdup(env[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

void	execution(t_cmd *list, int i, char **env)
{
	t_cmd	*tmp;

	tmp = list;
	while (tmp)
	{
		tmp->in = 0;
		tmp->out = 1;
		tmp = tmp->next;
	}
	tmp = list;
	i = 1;
	while (tmp && i > 0)
	{
		i = redirections(tmp);
		tmp = tmp->next;
	}
	if (list && list->cmd[0] != NULL && i == 1)
		multi_pipes(list, env);
}

void	expanding(int i, t_lxenv *lxenv)
{
	char		**lst_env;

	if (!lxenv)
		return ;
	i = 0;
	lst_env = envirenment();
	lxenv_int(lxenv, lst_env);
	while (lst_env[i])
		free(lst_env[i++]);
	free(lst_env);
	lst_env = NULL;
}

void	main_loop(t_lxenv *lxenv, t_lexer *lexer,
		t_parser *parser, t_cmd *list)
{
	while (1)
	{
		g_.command = readline("minihell$ ");
		if (g_.enva)
		{
			ft_free_2d(lxenv->env);
			ft_free_2d(g_.renv);
			ft_rebuild_env(g_.enva);
			lxenv->env = to_2d(g_.enva);
			lxenv->len = ft_2d_size(lxenv->env);
			g_.renv = to_2d(g_.enva);
		}
		lexer = get_lexer(g_.command, lxenv);
		if (!lexer)
			continue ;
		parser = init_parser(lexer);
		if (!parser)
			continue ;
		list = parser_parse(parser);
		execution(list, g_.i, g_.env);
		free_util(parser, lexer, list);
	}
}

int	main(int ac, char **av, char **env)
{
	t_parser	*parser;
	t_lexer		*lexer;
	t_cmd		*list;
	t_lxenv		*lxenv;

	(void) ac;
	(void) av;
	parser = NULL;
	lexer = NULL;
	list = NULL;
	lxenv = NULL;
	env_int(env, 0);
	if (!*env)
		return (0);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler);
	g_.i = 0;
	lxenv = malloc(sizeof(t_lxenv));
	expanding(g_.i, lxenv);
	g_.renv = r_get_env(env);
	g_.env = env;
	main_loop(lxenv, lexer, parser, list);
	return (0);
}

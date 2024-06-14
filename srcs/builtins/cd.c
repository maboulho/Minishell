/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulho <maboulho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 12:25:02 by maboulho          #+#    #+#             */
/*   Updated: 2022/12/16 00:23:17 by maboulho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../Includes/struct_cmd.h"

t_cmd	*craft_oldpwd_cmd(char *s)
{
	t_cmd	*tmp;
	char	*pwd;
	char	*tmp_pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		perror("SOMETHING WENT WRONG WITH PWD");
		return (0);
	}
	tmp = malloc(sizeof(t_cmd));
	tmp->cmd = (char **)malloc(sizeof(char *) * 3);
	tmp->cmd[0] = ft_strdup("export");
	tmp_pwd = ft_strdup(pwd);
	tmp->cmd[1] = ft_strjoin1(s, tmp_pwd);
	tmp->cmd[2] = NULL;
	free(pwd);
	free(tmp_pwd);
	return (tmp);
}

void	cd(t_cmd *p)
{
	int		i;
	t_cmd	*tmp;

	tmp = craft_oldpwd_cmd("OLDPWD=");
	if (!tmp)
		return ;
	export(tmp);
	if (!p->cmd[1])
	{
		i = chdir("/Users/maboulho");
	}
	else
	{
		i = chdir(p->cmd[1]);
		free_cd(tmp);
		tmp = craft_oldpwd_cmd("PWD=");
		export(tmp);
	}
	if (i < 0)
		print_cd_errors(p);
	free_cd(tmp);
}

void	print_cd_errors(t_cmd *p)
{
	ft_putstr_fd("minishell: cd: ", p->out);
	ft_putstr_fd(p->cmd[1], p->out);
	ft_putstr_fd(": Not a directory", p->out);
	ft_putstr_fd("\n", p->out);
	g_.exit_value = 1;
}

void	free_cd(t_cmd *tmp)
{
	free(tmp->cmd[0]);
	free(tmp->cmd[1]);
	free(tmp->cmd);
	free(tmp);
}

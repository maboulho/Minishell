/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulho <maboulho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 04:35:48 by maboulho          #+#    #+#             */
/*   Updated: 2022/12/16 01:30:04 by maboulho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../Includes/struct_cmd.h"

char	**envirenment(void)
{
	char	**env_a;
	int		i;
	t_env	*tmp;
	char	*tmp_name;
	char	*strname;

	i = 0;
	env_a = malloc(sizeof(char *) * (ft_lstsize_a(g_.enva) + 1));
	if (!env_a)
		return (NULL);
	tmp = g_.enva;
	while (tmp)
	{
		strname = export_name(tmp->content);
		tmp_name = ft_strjoin1(strname, "=");
		env_a[i] = ft_strjoin1(tmp_name, tmp->value);
		free(tmp_name);
		free(strname);
		i++;
		tmp = tmp->next;
	}
	env_a[i] = NULL;
	return (env_a);
}

int	files_int(t_cmd *p, int i)
{
	t_cmd	*temp;

	temp = p;
	while (temp->file)
	{
		if (temp->file->type == 2)
			i = outfile(temp);
		else if (temp->file->type == 3)
			i = infile(temp);
		else if (temp->file->type == 4)
			i = appand_check(temp);
		else if (temp->file->type == 5)
			herdoc(temp);
		temp->file = temp->file->next;
	}
	return (i);
}

int	infile(t_cmd *p)
{
	if (p->in != 0)
		close(p->in);
	p->in = open(p->file->file_name, O_RDONLY, 0644);
	if (p->in == -1 || !p->file->file_name)
	{
		printf("minishell: %s: No such file or directory\n", p->file->file_name);
		return (0);
	}
	return (1);
}

int	outfile(t_cmd *p)
{
	if (p->out != 1)
		close(p->out);
	p->out = open(p->file->file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (p->out == -1 || !p->file->file_name)
	{
		printf("p: syntax error near unexpected token `>'\n");
		return (0);
	}
	return (1);
}

void	print_export(t_cmd *p)
{
	t_env	*tmp;

	tmp = g_.enva;
	while (tmp)
	{
		if (!tmp->value)
		{
			ft_putstr_fd("declare -x ", p->out);
			ft_putstr_fd(tmp->name, p->out);
			ft_putstr_fd("=", p->out);
			ft_putstr_fd("\"\"\n", p->out);
		}
		if (tmp->value != NULL)
		{
			ft_putstr_fd("declare -x ", p->out);
			ft_putstr_fd(tmp->name, p->out);
			ft_putstr_fd("=", p->out);
			ft_putstr_fd("\"", p->out);
			ft_putstr_fd(tmp->value, p->out);
			ft_putstr_fd("\"", p->out);
			ft_putstr_fd("\n", p->out);
		}
		tmp = tmp->next;
	}
}

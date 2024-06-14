/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulho <maboulho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 11:13:18 by maboulho          #+#    #+#             */
/*   Updated: 2022/12/16 00:20:16 by maboulho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../Includes/struct_cmd.h"

void	pwd(t_cmd *p)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		perror("SOMETHING WENT WRONG WITH PWD");
		return ;
	}
	ft_putstr_fd(pwd, p->out);
	ft_putstr_fd("\n", p->out);
	free (pwd);
}

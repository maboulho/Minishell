/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulho <maboulho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 04:09:11 by maboulho          #+#    #+#             */
/*   Updated: 2022/12/16 04:22:03 by maboulho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../Includes/header.h"

void	ft_export_norm(t_cmd *p, int i)
{
	printf("minishell: export: `%s': not a valid identifier\n",
		p->cmd[i]);
	g_.exit_value = 1;
}

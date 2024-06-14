/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulho <maboulho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 23:32:40 by eel-ghan          #+#    #+#             */
/*   Updated: 2022/12/16 05:13:35 by maboulho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <dirent.h>
# include <string.h>
# include <sys/ioctl.h>
# include <termios.h>
# include "../srcs/Libft/libft.h"
# include "token.h"
# include "lexer.h"
# include "error.h"
# include "struct_cmd.h"
# include "parser.h"

int		ft_2d_size(char **str);
void	ft_export_norm(t_cmd *p, int i);
void	free_util(t_parser *parser, t_lexer *lexer, t_cmd *list);
t_lexer	*get_lexer(char *command, t_lxenv *lxenv);
int		ft_2d_size(char **str);
void	lxenv_int(t_lxenv *lxenv, char **env);
void	sig_handler(int sig);
char	*ft_strjoin3(char *s1, char *s2, char *s3);
void	ft_free_2d(char **str);
#endif
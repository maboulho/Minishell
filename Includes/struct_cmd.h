/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_cmd.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulho <maboulho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 13:15:42 by eel-ghan          #+#    #+#             */
/*   Updated: 2022/12/16 05:10:13 by maboulho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_CMD_H
# define STRUCT_CMD_H
# include "../srcs/Libft/libft.h"
# include "stdio.h"
# include <fcntl.h>
# include <stdbool.h>
# include <sys/stat.h>

typedef struct s_cmd	t_cmd;
typedef struct s_file	t_file;

struct s_file
{
	char	*file_name;
	int		type;
	int		fd;
	t_file	*next;
};

typedef struct s_env
{
	char			*name;
	char			*value;
	char			*content;
	struct s_env	*next;
}	t_env;

typedef struct s_global
{
	t_env			*enva;
	int				exit_value;
	char			**renv;
	int				bt_flag;
	int				i;
	char			*command;
	char			**env;
}	t_global;

struct s_cmd
{
	char	**cmd;
	t_file	*file;
	int		pipe_num;
	int		index_cmd;
	int		id;
	int		in;
	int		out;
	char	*herdoc;
	int		dflag;
	t_cmd	*next;
};

t_global				g_;

t_cmd	*init_struct_cmd(void);
void	print_export(t_cmd *p);
void	unset(t_cmd *p);
int		check_export(char *arg);
void	open_herdoc(t_file *p, t_cmd *cmd);
char	*export_value(char *cont);
char	*export_name(char *cont);
t_env	*init_node_split(char **s);
int		ft_lstsize_a(t_env *lst);
char	**envirenment(void);
int		ft_cmdsize(t_cmd *lst);
void	herdoc(t_cmd *p);
t_file	*init_file(char *name, int type);
t_cmd	*t_cmd_last(t_cmd *lst);
void	t_cmd_add_back(t_cmd **cmd_list, t_cmd *new);
t_file	*t_file_last(t_file *file);
void	t_file_add_back(t_file **file_list, t_file *new);
char	*find_path(t_env *enva);
char	*trim_path(void);
int		calculate_lines(char **env);
t_env	*init_node(char *s);
void	env_int(char **env, int flag);
void	ft_lstadd_back_a(t_env **lst, t_env *new);
void	multi_pipes(t_cmd *p, char **env);
void	execute(t_cmd *p);
char	*check_path(t_cmd *p);
char	*trim_path(void);
char	*find_path(t_env *enva);
int		redirections(t_cmd *p);
int		outfile(t_cmd *p);
int		infile(t_cmd *p);
int		appand_check(t_cmd *p);
int		ft_isdigit(int c);
void	export(t_cmd *p);
int		is_builtins(t_cmd *p);
void	builtins(t_cmd *p, char **env);
void	cd(t_cmd *p);
void	echo(t_cmd *p);
void	exit_f(t_cmd *p);
void	pwd(t_cmd *p);
void	wait_for_everything(t_cmd *p);
void	print_enva(t_cmd *p);
void	add_to_env(char *var);
int		is_valid_identifier(char *s);
int		ft_is_a_built_in(t_cmd *p);
void	forking(t_cmd *p, int fd_save, char **env, int fd[2]);
int		command_not_found(t_cmd *p);
int		is_exectable_f(char *s);
void	herdoc_loop(char *line, int fd);
int		files_int(t_cmd *p, int i);
void	herdoc_init(t_cmd *cmd, char *number_cmd);
int		ft_strcmp(char *s1, char *s2);
void	print_cd_errors(t_cmd *p);
void	execution(t_cmd *list, int i, char **env);
void	sig_handler(int sig);
char	**to_2d(t_env *env);
void	free_cd(t_cmd *tmp);

#endif
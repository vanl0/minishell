/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-masc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:00:09 by pde-masc          #+#    #+#             */
/*   Updated: 2024/06/06 16:25:08 by pde-masc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

# define NOT_BUILTIN -1
# define ECHO 0
# define CD 1
# define PWD 2
# define EXPORT 3
# define UNSET 4
# define ENV 5
# define EXIT 6

// BUILTINS MANAGEMENT
void			search_n_destroy(char *name, t_tools *tools);
void			set_builtin_array(t_tools *tools);
int				builtin_key(char *command);
void			set_builtin(t_simple_cmds *cmd);

// BUILTINS
int				echo(t_simple_cmds *simple_cmd);
int				cd(t_simple_cmds *simple_cmd);
int				ft_export(t_simple_cmds *cmd);
int				check_name(char *name);
int				pwd(t_simple_cmds *cmd);
int				unset(t_simple_cmds *cmd);
void			search_n_destroy(char *name, t_tools *tools);
int				env(t_simple_cmds *cmd);

// CD UTILS
char			*my_getcwd(t_tools *tools);
char			*trim_from_back(char *dir);
char			*get_next_path(char *arg);
int				env_not_set(char *env_name);
int				cd_error(char *arg, int error);

////EXPORT
void			export_error(char *name, char *content);
void			split_env(char *str, char **name, char **content);
int				check_name(char *name);
// EXIT
int				ft_exit(t_simple_cmds *cmd);
long long int	get_longlong(char *str);
int				get_module(long long int result, int sign);
int				atolonglong(char *str);
int				exit_error(char *str);
int				free_tools(t_tools *tools);
#endif

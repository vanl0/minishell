/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 pwd.c												:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: ilorenzo <ilorenzo@student.42barcel>		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/06/02 18:32:47 by ilorenzo		   #+#	  #+#			  */
/*	 Updated: 2024/06/02 18:32:47 by ilorenzo		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(t_simple_cmds *cmd)
{
	char	*pwd;

	pwd = find_env("PWD", cmd->tools->env_lst);
	if (!pwd)
		return (do_error(-1, cmd->tools));
	printf("%s\n", pwd);
	free(pwd);
	return (EXIT_SUCCESS);
}

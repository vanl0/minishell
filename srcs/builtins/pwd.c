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
	char	cwd[PATH_MAX];

	(void)cmd;
	if (getcwd(cwd, sizeof(cwd)) == NULL) {
		perror("getcwd error");
		return (EXIT_FAILURE);
	}
	printf("%s\n", cwd);
	return (EXIT_SUCCESS);
}

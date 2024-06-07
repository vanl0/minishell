/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilorenzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:18:38 by ilorenzo          #+#    #+#             */
/*   Updated: 2024/06/05 18:18:39 by ilorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*writes inside the hidden file using readline till EOF is encountered*/
int	do_heredoc(char *hd_file_name,	char *end, t_env *env_lst)
{
	char	*line;
	int		fd;

	fd = open(hd_file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	line = readline("heredoc>");
	while (line && ft_strncmp(end, line, ft_strlen(end)) \
	&& !g_signals.stop_hdoc)
	{
		line = search_env(line, env_lst);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline("heredoc>");
	}
	free(line);
	close(fd);
	if (g_signals.stop_hdoc || !line)
		return (FAIL);
	return (SUCCESS);
}

/*generates a hidden file name used as buffer for heredoc*/
char	*get_hd_name(void)
{
	static int	n = 0;
	char		*num;
	char		*name;

	num = ft_itoa(n);
	name = ft_strjoin("/tmp/hd_file_", num);
	free(num);
	n++;
	while (!access(name, F_OK))
	{
		free(name);
		n++;
		num = ft_itoa(n);
		name = ft_strjoin("/tmp/hd_file_", num);
		free(num);
	}
	return (name);
}

int	heredoc(t_simple_cmds *cmd)
{
	t_lexer	*redir_i;

	redir_i = cmd->redirections;
	while (redir_i)
	{
		if (redir_i->token == LESSLESS)
		{
			cmd->hd_file_name = get_hd_name();
			g_signals.in_hdoc = 1;
			if (do_heredoc(cmd->hd_file_name, \
			redir_i->str, cmd->tools->env_lst))
				return (EXIT_FAILURE);
			g_signals.in_hdoc = 0;
		}
		redir_i = redir_i->next;
	}
	return (EXIT_SUCCESS);
}

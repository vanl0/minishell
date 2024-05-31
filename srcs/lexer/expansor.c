/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 expansor.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: ilorenzo <ilorenzo@student.42barcel>		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/05/15 17:38:16 by ilorenzo		   #+#	  #+#			  */
/*	 Updated: 2024/05/15 17:38:17 by ilorenzo		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "../header/minishell.h"
// $ dentro de "" se expande
/*Returns malloc'd string of the word in the $variable*/
char	*get_env_name(char *env_str, char quote)
{
	int		i;
	char	*name;

	i = 1;
	if (!env_str[1] ) //if end of line
		return (""); // prints $
	if (env_str[1] == quote || ((env_str[1] == '"' || env_str[1] == '\'') && quote == 0)) //check if the current quote is closed or if new quote
		return (NULL); // prints ""
	while (env_str[i] && !is_space(env_str[i]) && env_str[i] != '"' && env_str[i] != '\'' && env_str[i] != '$' && !is_token(env_str[i]))
		i++;
	name = ft_malloc(i * sizeof(char));
	ft_strlcpy(name, env_str + 1, i);
	return (name);
}

int	get_env_name_len(char *env_str)
{
	int	i;

	i = 1;
	while (env_str[i] && !is_space(env_str[i]) && env_str[i] != '"' && env_str[i] != '\'' && env_str[i] != '$'&& !is_token(env_str[i]))
		i++;
	return (i);
}

/*Searches the variable inside the list*/
char	*find_env(char *name, t_env *env_lst)
{
	t_env	*env_i;

	env_i = env_lst;
	while (env_i)
	{
		if (!ft_strncmp(name, env_i->name, ft_strlen(env_i->name)) && !ft_strncmp(name, env_i->name, ft_strlen(name)) && env_i->content)
			return (ft_strdup(env_i->content));
		env_i = env_i->next;
	}
	return (NULL);
}

/*Returns malloc'd string with the content of the variable, if not found returns ""*/
char	*expand_env(char *env_str, t_env *env_lst, char quote)
{
	char	*env_name;
	char	*content;

	env_name = get_env_name(env_str, quote);
	if (!env_name)
		return (ft_strdup(""));
	if (env_name[0] == '\0')
		return (ft_strdup("$"));
	content = find_env(env_name, env_lst);
	free(env_name);
	if (!content || content[0] == '\0')
		return (ft_strdup(""));
	return (content);
}

char	*replace_env(char *str, int *i, t_env *env_lst, char quote)
{
	char	*new_str;
	char	*env_cont;
	int		j;
	int		k;
	int		env_len;

	j = 0;
	k = 0;
	env_cont = expand_env(&str[*i], env_lst, quote);
	env_len = ft_strlen(str) - get_env_name_len(&str[*i]) + ft_strlen(env_cont);
	new_str = ft_malloc((env_len + 1) * sizeof(char));
	while (j < env_len)
	{
		if (j == *i)
		{
			while (env_cont[k])
			{
				new_str[j] = env_cont[k];
				k++;
				j++;
			}
			k = (ft_strlen(env_cont) - get_env_name_len(&str[*i]));
		}
		new_str[j] = str[j - k];
		j++;
	}
	new_str[j] = '\0';
	free(env_cont);
	*i += ft_strlen(env_cont) - 1;
	return (new_str);
}

char	*search_env(char *str, t_env *env_lst)
{
	char	*new_str;
	char	quote;
	int		i;

	new_str = NULL;
	quote = 0;
	i = 0;
	while (str[i])
	{
		if (quote == 0 && (str[i] == '"' || str[i] == '\''))
			quote = str[i];
		else if (quote != 0 && str[i] == quote)
			quote = 0;
		if (str[i] == '$' && quote != '\'')
		{
			new_str = replace_env(str, &i, env_lst, quote);
			free(str);
			str = new_str;
		}
		i++;
	}
	if (!new_str)
		return (str);
	return (new_str);
}

t_lexer	*expand(t_lexer *lexer_lst, t_env *env_lst)
{
	t_lexer	*lexer_i;

	lexer_i = lexer_lst;
	while (lexer_i)
	{
		if (lexer_i->str)
		{
			if (ft_strchr(lexer_i->str, '$'))
				lexer_i->str = search_env(lexer_i->str, env_lst);
		}
		lexer_i = lexer_i->next;
	}
	return (lexer_lst);
}

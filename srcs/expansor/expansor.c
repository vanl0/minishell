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
	char	*env_cont;
	char	*new_str;
	int		env_len;
	int		len_after_env;

	env_cont = expand_env(&str[*i], env_lst, quote);
	len_after_env = ft_strlen(&str[*i + get_env_name_len(&str[*i])]);
	env_len = *i + ft_strlen(env_cont) + len_after_env;
	new_str = ft_malloc((env_len + 1) * sizeof(char));
	ft_strlcpy(new_str, str, *i + 1);
	ft_strlcat(new_str, env_cont, env_len + 1);
	ft_strlcat(new_str, &str[*i + get_env_name_len(&str[*i])], env_len + 1);
	*i += ft_strlen(env_cont) - 1;
	free(env_cont);
	free(str);
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
	if (!ft_strchr(str, '$'))
		return (str);
	while (str[i])
	{
		if (quote == 0 && is_quote(str[i]))
			quote = str[i];
		else if (quote != 0 && str[i] == quote)
			quote = 0;
		if (str[i] == '$' && quote != '\'')
			str = replace_env(str, &i, env_lst, quote);
		i++;
	}
	return (str);
}

/*t_lexer	*expand(t_lexer *lexer_lst, t_env *env_lst)
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

char	*replace_env2(char *str, int *i, t_env *env_lst, char quote)
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
	free(str);
	return (new_str);
}*/


#include "../header/minishell.h"

char	*join_free(char *s1, char *s2)
{
	char	*strjoin;
	int		n;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	n = ft_strlen(s1) + ft_strlen(s2) + 1;
	strjoin = malloc(n * sizeof(char));
	if (!strjoin)
    {
        free(s1);
		return (NULL);
    }
    i = 0;
	j = 0;
	while (s1[i])
	{
		strjoin[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		strjoin[i++] = s2[j++];
	}
	strjoin[i] = '\0';
	free (s1);
	return (strjoin);
}

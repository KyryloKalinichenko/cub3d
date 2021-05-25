/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalinic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 11:29:41 by kkalinic          #+#    #+#             */
/*   Updated: 2021/05/04 13:40:33 by kkalinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub_head.h"

static char	**ft_malloc_error(char **tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static unsigned int	ft_get_nb_strs(char const *s, char c)
{
	unsigned int	i;
	unsigned int	nb_strs;

	if (!s[0])
		return (0);
	i = 0;
	nb_strs = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c)
		{
			nb_strs++;
			while (s[i] && s[i] == c)
				i++;
			continue ;
		}
		i++;
	}
	if (s[i - 1] != c)
		nb_strs++;
	return (nb_strs);
}

static void	ft_get_next_str(char **next_str, unsigned int *next_str_len,
					char c)
{
	unsigned int	i;

	*next_str += *next_str_len;
	*next_str_len = 0;
	i = 0;
	while (**next_str && **next_str == c)
		(*next_str)++;
	while ((*next_str)[i])
	{
		if ((*next_str)[i] == c)
			return ;
		(*next_str_len)++;
		i++;
	}
}

char	**ft_split(char const *s, char c)
{
	char			**tab;
	char			*next_str;
	unsigned int	next_str_len;
	unsigned int	nb_strs;
	unsigned int	i;

	tab = (char **)malloc(sizeof(char *)
			* ((nb_strs = ft_get_nb_strs(s, c)) + 1));
	if (!s || !tab)
		return (NULL);
	i = 0;
	next_str = (char *)s;
	next_str_len = 0;
	while (i < nb_strs)
	{
		ft_get_next_str(&next_str, &next_str_len, c);
		if (!(tab[i]
				= (char *)malloc(sizeof(char) * (next_str_len + 1))))
			return (ft_malloc_error(tab));
		ft_strlcpy(tab[i], next_str, next_str_len + 1);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

/*
**int	ft_count(char const *s, char c)
**{
**	int i;
**	int k;
**
**	i = -1;
**	k = 0;
**	while(s[++i] != '\0')
**	{
**		if(s[i] != c && (s[i + 1] == c ||s[i + 1] == '\0'))
**			k++;
**	}
**	if (s[0] != c)
**		k -= 1;
**	printf("%i\n", k);
**	return (k);
**}
**
**char	**ft_split(char const *s, char c)
**{
**	int i;
**  	int j;
**	int	k;
**	char **splited;
**
**	k = 0;
**	j = 0;
**   	i = 0;
**	if (!(splited = (char**)malloc(sizeof(char*) * ft_count(s, c))))
**		return (NULL);
**	while (s[i] != '\0')
**	{
**		while (s[i] == c)
**			i++;
**		while(s[i] != c && s[i] != '\0')
**		{
**			j++;
**			i++;
**		}
**		if (!(splited[k] = ft_substr(s, i - j, j)))
**			return (NULL);
**		j = 0;
**		k++;
**	}
**	splited[k == 1 ? 1 : k - 1] = NULL;
**	return (splited);
*/
/*
**int	main(void)
**{
**	int i = -1;
**
**	char *string = "split   |||this|for|me|||!|";
**    char **result = ft_split(string, '|');
**
**	while (result[++i] != NULL)
**	{
**		printf("%s\n", result[i]);
**
**	}
**
**	//printf("%s\n", result[i] = NULL);
**	free (result);
**	return 0;
*/

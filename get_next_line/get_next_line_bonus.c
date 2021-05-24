/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalinic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 11:19:31 by kkalinic          #+#    #+#             */
/*   Updated: 2021/05/13 17:20:38 by kkalinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "../headers/cub_head.h"

char	*ft_strcat(char *dest, const char *src)
{
	char	*a;
	int		i;
	int		p;

	i = 0;
	a = (char *)src;
	p = ft_strlen(a) + 1;
	while (dest[i] != '\0')
		i++;
	while (--p)
	{
		dest[i] = *a;
		i++;
		a++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	int				i;
	const char		*b;

	b = (char *)src;
	i = 0;
	while (b[i] != '\0' && n)
	{
		dest[i] = b[i];
		n--;
		i++;
	}
	while (n)
	{
		dest[i] = '\0';
		i++;
		n--;
	}
	return (dest);
}

static int	ft_skip(size_t i, t_list *list, char **line, int r)
{
	if (i < ft_strlen(list->con))
	{
		*line = ft_substr(list->con, 0, i);
		list->tmp = ft_substr(list->con, i + 1, ft_strlen(list->con));
		if (!line || !list->tmp)
			exit (EXIT_FAILURE);
		free(list->con);
		if (!(list->con
				= ft_strdup(list->tmp)))
		{
			free(*line);
			free(list->tmp);
			return (-1);
		}
		free(list->tmp);
	}
	else if (r == 0)
	{
		*line = list->con;
		list->con = NULL;
		return (0);
	}
	return (1);
}

static int	ft_gnl_cond(char *content, t_list *list, char **line, int i)
{
	unsigned int	j;

	j = 0;
	if (i == -1)
		return (-1);
	if (i <= 0 && !content)
	{
		if (i == 0)
		{
			*line = ft_strdup("");
			if (!*line)
				return (-1);
		}
		return (i);
	}
	if (content)
	{
		while (content[j] != '\0' && content[j] != '\n')
			j++;
	}
	return (ft_skip(j, list, line, i));
}

int	get_next_line(int fd, char **line)
{
	static t_list	list[FOPEN_MAX];
	char			*buff;
	int				i;

	buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if ((BUFFER_SIZE + 1) <= 1 || !line || !buff)
		return (-1);
	while (reading(fd, buff, &i))
	{
		if (list[fd].con != NULL)
		{
			list[fd].tmp = ft_strjoin(list[fd].con, buff);
			if (!list[fd].tmp)
				i = -1;
			free(list[fd].con);
			list[fd].con = list[fd].tmp;
		}
		else if (NULL == (list[fd].con
				= ft_strdup(buff)))
			i = -1;
		if (ft_strchr(buff, '\n') || i == -1)
			break ;
	}
	free(buff);
	return (ft_gnl_cond(list[fd].con, &list[fd], line, i));
}
/*
**int main()
**{
**	char *line;
**	int fd;
**	int fd2;
**
**	line = "HEllo";
**	fd = open("42_with_nl", O_RDONLY);
**	fd2 = 0;
**	while (0 < (fd2 = get_next_line(fd, &line)))
**	{
**		printf("%s", line);
**		printf("\n--------------\n");
**		free(line);
**		printf("%i\n", fd2);
**	}
**	if (fd > 0)
**		free(line);
**	close(fd);
**}
*/

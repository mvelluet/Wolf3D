/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelluet <mvelluet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 21:10:23 by mvelluet          #+#    #+#             */
/*   Updated: 2017/10/17 17:40:51 by mvelluet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_exit(char **line, char *prev_line, char *buffer, int state)
{
	if (buffer && line && *line)
		free(buffer);
	if (state == -1 && line && *line)
		ft_memdel((void**)line);
	if (state <= 0 && prev_line)
		ft_memdel((void**)&prev_line);
	return (state);
}

static char		*cut_end(char *str)
{
	char	*result;
	int		i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	result = (char*)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	ft_memdel((void**)&str);
	return (result);
}

static int		alloc(int fd, char **line, char *b)
{
	char	*t;
	int		r;

	r = 1;
	if (!ft_memchr(b, '\n', BUFF_SIZE))
	{
		ft_bzero(b, BUFF_SIZE);
		while ((r = read(fd, b, BUFF_SIZE)) && !ft_memchr(b, '\n', BUFF_SIZE))
		{
			t = ft_strdup(*line);
			ft_memdel((void**)line);
			*line = ft_strjoin(t, b);
			ft_bzero(b, BUFF_SIZE);
			ft_memdel((void*)&t);
		}
	}
	if (r < 0)
		return (-1);
	t = ft_strdup(*line);
	ft_memdel((void**)line);
	*line = ft_strjoin(t, b);
	*line = cut_end(*line);
	ft_memdel((void**)&t);
	return (r);
}

int				get_next_line(int const fd, char **line)
{
	static char	*lines[1024];
	char		*buffer;
	char		c;
	int			r;

	if (fd < 0 || read(fd, &c, 0) == -1)
		return (-1);
	if (!(buffer = (char*)ft_memalloc(BUFF_SIZE + 1)))
		return (-1);
	if (lines[fd])
	{
		*line = ft_strdup(lines[fd]);
		ft_memdel((void**)&lines[fd]);
	}
	else
		*line = ft_strdup("");
	buffer = ft_memcpy(buffer, *line, ft_strlen(*line));
	r = alloc(fd, line, buffer);
	if (r < 0)
		return (ft_exit(line, lines[fd], buffer, -1));
	if (ft_memchr(buffer, '\n', ft_strlen(buffer)) && ft_strlen(buffer))
		lines[fd] = ft_strdup(ft_memchr(buffer, '\n', ft_strlen(buffer)) + 1);
	if (r == 0 && !ft_strlen(*line))
		return (ft_exit(line, lines[fd], buffer, 0));
	return (ft_exit(line, lines[fd], buffer, 1));
}

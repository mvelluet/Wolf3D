/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelluet <mvelluet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 14:59:50 by mvelluet          #+#    #+#             */
/*   Updated: 2017/10/18 13:55:27 by mvelluet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	fill_map(t_env *env, char *name)
{
	char	*line;
	int		fd;
	int		i;
	int		j;

	i = 0;
	if ((fd = open(name, O_RDONLY)) < 0)
		exit(1);
	env->map.map = (t_uchar**)malloc(sizeof(t_uchar*) * (env->map.h + 1));
	while (get_next_line(fd, &line) == 1 && i < env->map.h)
	{
		if (ft_strlen(line) != (size_t)env->map.w)
			exit(1);
		env->map.map[i] = (t_uchar*)malloc(env->map.w + 1);
		j = -1;
		while (line[++j])
			env->map.map[i][j] = (t_uchar)line[j] - '0';
		i++;
		free(line);
	}
	free(line);
}

void	verify_map(t_env *env)
{
	int		blocks;
	int		i[2];

	blocks = 0;
	while (env->blocks[blocks].name)
		blocks++;
	i[0] = 0;
	while (i[0] < env->map.h)
	{
		i[1] = 0;
		while (i[1] < env->map.w)
			if (env->map.map[i[0]][i[1]++] >= blocks)
				ft_exit(env, 1);
		i[0]++;
	}
}

void	load_map(t_env *env, char *name)
{
	static char	*map;
	char		*line;
	int			fd;

	if (name)
		map = name;
	if ((fd = open(map, O_RDONLY)) < 0)
		exit(1);
	env->map.h = 0;
	while (get_next_line(fd, &line) == 1)
	{
		env->map.h++;
		env->map.w = ft_strlen(line);
		free(line);
	}
	free(line);
	close(fd);
	fill_map(env, map);
	env->cam.x = -2;
	env->cam.y = -2;
	close(fd);
	verify_map(env);
}

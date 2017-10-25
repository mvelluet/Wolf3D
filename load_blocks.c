/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_blocks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelluet <mvelluet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 14:59:46 by mvelluet          #+#    #+#             */
/*   Updated: 2017/10/17 22:01:29 by mvelluet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		arraylen(char **array)
{
	int		len;

	len = 0;
	if (!array)
		return (0);
	while (array[len])
		len++;
	return (len);
}

void	fill_array(t_env *env, char *line, int fd, t_uchar n)
{
	char	**params;

	n = 0;
	while (get_next_line(fd, &line) == 1)
	{
		params = ft_strsplit(line, '\t');
		if (arraylen(params) != 6)
			exit(1);
		env->blocks[n].name = ft_strdup(params[0]);
		env->blocks[n].h = ft_atoi(params[1]);
		env->blocks[n].color = ft_create_color(ft_atoi(params[2]),
		ft_atoi(params[3]), ft_atoi(params[4]), ft_atoi(params[5]));
		ft_free_array((void**)params, 7);
		free(line);
		n++;
	}
	env->blocks[n].name = NULL;
	free(line);
}

void	free_blocks(t_env *env)
{
	t_uchar	n;

	n = 0;
	while (env->blocks[n].name)
	{
		free(env->blocks[n].name);
		n++;
	}
	free(env->blocks);
}

void	load_blocks(t_env *env)
{
	t_uchar	n;
	char	*line;
	int		fd;

	n = 0;
	if ((fd = open("blocks.blocks", O_RDONLY)) < 0)
		return ;
	while (get_next_line(fd, &line) == 1)
	{
		n++;
		free(line);
	}
	free(line);
	env->blocks = (t_block*)malloc(sizeof(t_block) * (n + 1));
	ft_bzero(env->blocks, sizeof(t_block) * (n + 1));
	close(fd);
	if ((fd = open("blocks.blocks", O_RDONLY)) < 0)
		return ;
	fill_array(env, line, fd, n);
	close(fd);
}

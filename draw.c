/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelluet <mvelluet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 14:30:41 by mvelluet          #+#    #+#             */
/*   Updated: 2017/10/17 22:01:16 by mvelluet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <sys/time.h>

int		convert(double n)
{
	if (n - (int)n > 0.5)
		return ((int)n + 1);
	return ((int)n);
}

void	draw_line(t_env *env, t_pixel a, t_pixel b)
{
	if (a.y < 0)
		a.y = 0;
	else if (a.y >= env->img->h)
		a.y = env->img->h - 1;
	if (b.y < 0)
		b.y = 0;
	else if (b.y >= env->img->h)
		b.y = env->img->h - 1;
	while (a.y <= b.y)
	{
		ft_pixel_put(env->img, a);
		a.y++;
	}
}

void	draw_multithread(t_env *env, void *(*function)(void*))
{
	pthread_t	thread[env->threads];
	t_thread	params[env->threads];
	int			i;

	i = 0;
	while (i < env->threads)
	{
		params[i].env = env;
		params[i].i = i * env->img->w / env->threads;
		params[i].max = (i + 1) * env->img->w / env->threads;
		pthread_create(&thread[i], NULL, function, &params[i]);
		i++;
	}
	i = 0;
	while (i < env->threads)
		pthread_join(thread[i++], NULL);
}

void	ft_clear_image(t_image *img)
{
	t_color	c;
	int		i;

	c = (t_color){0, 0, 0, 255};
	i = 0;
	while (i < img->w * img->h)
	{
		img->l[i] = c;
		i++;
	}
}

int		ft_draw(t_env *env)
{
	mlx_clear_window(env->win.mlx, env->win.win);
	ft_clear_image(env->img);
	mlx_put_image_to_window(env->win.mlx, env->win.win, env->back->img, 0, 0);
	draw_multithread(env, (void*)&draw_wolf);
	mlx_put_image_to_window(env->win.mlx, env->win.win,
	env->img->img, 0, 0);
	return (0);
}

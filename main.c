/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelluet <mvelluet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 14:56:33 by mvelluet          #+#    #+#             */
/*   Updated: 2017/10/18 13:51:02 by mvelluet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		red_cross(t_env *env)
{
	ft_free_array((void**)env->map.map, env->map.h);
	free_blocks(env);
	ft_destroy_image(&env->win, &env->img);
	ft_destroy_image(&env->win, &env->back);
	ft_destroy_window(&env->win);
	exit(0);
	return (0);
}

void	calculate_background(t_image *back)
{
	t_pixel	p;

	p.y = back->h / 2;
	p.c = (t_color){113, 204, 46, 0};
	while (p.y < back->h)
	{
		p.x = 0;
		while (p.x < back->w)
		{
			ft_pixel_put(back, p);
			p.x++;
		}
		p.y++;
	}
}

void	draw_background(t_env *env)
{
	t_pixel	p;

	p.x = 0;
	p.c = (t_color){219, 152, 52, 0};
	while (p.x < env->back->w)
	{
		p.y = 0;
		while (p.y < env->back->h / 2)
		{
			ft_pixel_put(env->back, p);
			p.y++;
		}
		p.x++;
	}
	calculate_background(env->back);
}

void	init(t_env *env)
{
	ft_init(&env->win, 1200, 900, "Wolf3d");
	env->img = ft_new_image(&env->win, env->win.w, env->win.h);
	env->back = ft_new_image(&env->win, env->win.w, env->win.h);
	env->cam.x = 2;
	env->cam.y = 2;
	env->cam.angle = 0;
	env->map.w = 8;
	env->map.h = 8;
	env->threads = 4;
	env->fov = PI / 6;
	env->field = 100;
	env->key.w = 0;
	env->key.s = 0;
	env->key.d = 0;
	env->key.a = 0;
}

int		main(int argc, char **argv)
{
	t_env	env;

	init(&env);
	draw_background(&env);
	load_blocks(&env);
	if (argc <= 1)
		load_map(&env, "map.w3d");
	else
		load_map(&env, argv[1]);
	mlx_hook(env.win.win, 2, (1L << 0), (void*)ft_keys, &env);
	mlx_hook(env.win.win, 3, (1L << 1), (void*)ft_keys_stop, &env);
	mlx_hook(env.win.win, 17, (1L << 17), &red_cross, &env);
	ft_draw(&env);
	mlx_loop(env.win.mlx);
	return (0);
}

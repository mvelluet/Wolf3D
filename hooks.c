/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelluet <mvelluet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 14:57:33 by mvelluet          #+#    #+#             */
/*   Updated: 2017/10/18 13:58:32 by mvelluet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	free_map(t_env *env)
{
	ft_free_array((void**)env->map.map, env->map.h);
}

int		ft_exit(t_env *env, int k)
{
	ft_free_array((void**)env->map.map, env->map.h);
	free_blocks(env);
	ft_destroy_image(&env->win, &env->img);
	ft_destroy_image(&env->win, &env->back);
	ft_destroy_window(&env->win);
	exit(k);
	return (0);
}

void	wolf_keys2(t_env *env)
{
	free_blocks(env);
	load_blocks(env);
	ft_free_array((void**)env->map.map, env->map.h);
	load_map(env, NULL);
	ft_putstr("blocks and map reloaded !\n");
}

void	ft_keys(int keycode, t_env *env)
{
	if (keycode == 53)
		ft_exit(env, 0);
	multi_touch(env, keycode);
	wolf_keys(env);
	if (keycode == 15)
		wolf_keys2(env);
	ft_draw(env);
}

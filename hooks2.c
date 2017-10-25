/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelluet <mvelluet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 20:46:03 by mvelluet          #+#    #+#             */
/*   Updated: 2017/10/17 22:25:10 by mvelluet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	wolf_keys(t_env *env)
{
	if (env->key.a == 1)
		env->cam.angle -= 0.03 * CAM_SPEED;
	if (env->key.s == 1)
		env->cam.angle += 0.03 * CAM_SPEED;
	if (env->key.w == 1)
		move_player(env, cos(env->cam.angle) * PLAYER_SPEED,
		sin(env->cam.angle) * PLAYER_SPEED);
	if (env->key.d == 1)
		move_player(env, -cos(env->cam.angle) * PLAYER_SPEED,
		-sin(env->cam.angle) * PLAYER_SPEED);
	env->cam.angle += (env->cam.angle < -PI) ? 2 * PI : 0;
	env->cam.angle += (env->cam.angle > PI) ? -2 * PI : 0;
}

void	multi_touch(t_env *env, int keycode)
{
	if (keycode == 13)
		env->key.w = 1;
	if (keycode == 2)
		env->key.s = 1;
	if (keycode == 1)
		env->key.d = 1;
	if (keycode == 0)
		env->key.a = 1;
}

void	ft_keys_stop(int keycode, t_env *env)
{
	if (keycode == 13)
		env->key.w = 0;
	if (keycode == 2)
		env->key.s = 0;
	if (keycode == 1)
		env->key.d = 0;
	if (keycode == 0)
		env->key.a = 0;
}

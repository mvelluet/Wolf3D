/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wolf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelluet <mvelluet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 14:59:44 by mvelluet          #+#    #+#             */
/*   Updated: 2017/10/17 22:22:02 by mvelluet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	shadow(t_color *color)
{
	color->r *= SHADOWS;
	color->g *= SHADOWS;
	color->b *= SHADOWS;
	color->a *= SHADOWS;
}

void	draw_wall(t_env *env, t_p b, int i, double angle)
{
	t_pixel	p[2];
	t_point	n;
	double	d;

	if (fabs(b.x - (int)b.x) != 0.5)
		n.x = convert(b.x);
	else
		n.x = (cos(angle) > 0) ? (int)(b.x + 0.5) : (int)(b.x - 0.5);
	if (fabs(b.y - (int)b.y) != 0.5)
		n.y = convert(b.y);
	else
		n.y = (sin(angle) > 0) ? (int)(b.y + 0.5) : (int)(b.y - 0.5);
	if (n.x < 0 || n.y < 0 || n.x >= env->map.w || n.y >= env->map.h)
		return ;
	p[0] = (t_pixel){i, 0, env->blocks[env->map.map[n.y][n.x]].color};
	if (fabs(b.x - (int)b.x) != 0.5)
		shadow(&p[0].c);
	p[1] = p[0];
	d = sqrt(pow(b.x - env->cam.x, 2) + pow(b.y - env->cam.y, 2)) * cos(angle -
	env->cam.angle);
	p[0].y = env->win.h / 2 - (env->blocks[env->map.map[n.y][n.x]].h / d);
	p[1].y = env->win.h / 2 + (env->blocks[env->map.map[n.y][n.x]].h / d);
	draw_line(env, p[0], p[1]);
}

t_p		find_vertical(t_env *env, double angle)
{
	t_point	t;
	t_p		p;
	double	max;

	p.x = (cos(angle) > 0) ? convert(env->cam.x) + 0.5 :
	convert(env->cam.x) - 0.5;
	max = (cos(angle) < 0) ? p.x - env->field : p.x + env->field;
	while (p.x != max)
	{
		p.y = env->cam.y + (p.x - env->cam.x) * tan(angle);
		t.y = convert(p.y);
		t.x = (cos(angle) > 0) ? (int)(p.x + 0.5) : (int)(p.x - 0.5);
		if (t.x < env->map.w && t.y < env->map.h && t.x >= 0 && t.y >= 0 &&
		env->map.map[t.y][t.x])
			if (p.y >= -0.5 && p.x >= -0.5 && p.y < env->map.h + 0.5 && p.x <
			env->map.w + 0.5)
				return (p);
		p.x += (p.x < max) ? 1 : -1;
	}
	p.x = -1;
	return (p);
}

t_p		find_horizontal(t_env *env, double angle)
{
	t_point	t;
	t_p		p;
	double	max;

	p.y = (sin(angle) > 0) ? convert(env->cam.y) + 0.5 :
	convert(env->cam.y) - 0.5;
	max = (sin(angle) < 0) ? p.y - env->field : p.y + env->field;
	while (p.y != max)
	{
		p.x = env->cam.x + (p.y - env->cam.y) / tan(angle);
		t.x = convert(p.x);
		t.y = (sin(angle) > 0) ? (int)(p.y + 0.5) : (int)(p.y - 0.5);
		if (t.y < env->map.h && t.x < env->map.w && t.y >= 0 && t.x >= 0 &&
		env->map.map[t.y][t.x])
			if (p.y >= -0.5 && p.x >= -0.5 && p.y < env->map.h + 0.5 && p.x <
			env->map.w + 0.5)
				return (p);
		p.y += (p.y < max) ? 1 : -1;
	}
	p.x = -1;
	return (p);
}

void	draw_wolf(t_thread *t)
{
	double	angle;
	t_p		p[2];

	while (t->i <= t->max)
	{
		angle = t->env->cam.angle +
		t->env->fov * (2 * t->i - t->env->win.w + 1) / (t->env->win.w - 1);
		p[0] = find_vertical(t->env, angle);
		p[1] = find_horizontal(t->env, angle);
		if (p[0].x != -1 && pow(p[0].x - t->env->cam.x, 2) + pow(p[0].y -
		t->env->cam.y, 2) < pow(p[1].x - t->env->cam.x, 2) + pow(p[1].y -
		t->env->cam.y, 2))
			draw_wall(t->env, p[0], t->i, angle);
		else if (p[1].x != -1)
			draw_wall(t->env, p[1], t->i, angle);
		t->i++;
	}
}

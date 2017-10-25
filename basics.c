/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basics.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelluet <mvelluet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 14:30:41 by mvelluet          #+#    #+#             */
/*   Updated: 2017/10/17 22:01:58 by mvelluet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	ft_init(t_win *win, int w, int h, char *title)
{
	w = (w > 2560) ? 2560 : w;
	w = (w < 0) ? 0 : w;
	h = (h > 1440) ? 1440 : h;
	h = (h < 0) ? 0 : h;
	title = (!title) ? "default" : title;
	win->mlx = mlx_init();
	win->win = mlx_new_window(win->mlx, w, h, title);
	win->title = ft_strdup(title);
	win->w = w;
	win->h = h;
}

void	ft_destroy_window(t_win *win)
{
	if (!win)
		return ;
	free(win->title);
	mlx_destroy_window(win->mlx, win->win);
}

t_image	*ft_new_image(t_win *win, int w, int h)
{
	t_image	*i;

	if (!win)
		return (NULL);
	if (!(i = (t_image*)malloc(sizeof(t_image))))
		return (NULL);
	i->w = w;
	i->h = h;
	if (!(i->img = mlx_new_image(win->mlx, w, h)))
		ft_destroy_image(win, &i);
	if (!i)
		return (NULL);
	i->l = (t_color*)mlx_get_data_addr(i->img, &i->bits, &i->size_l,
	&i->endian);
	if (!i->l)
		return (NULL);
	i->win = win;
	return (i);
}

void	ft_destroy_image(t_win *win, t_image **img)
{
	if (!img || !(*img))
		return ;
	if (win && (*img)->img)
		mlx_destroy_image(win->mlx, (*img)->img);
	(*img)->win = NULL;
	(*img)->img = NULL;
	(*img)->l = NULL;
	free(*img);
	*img = NULL;
}

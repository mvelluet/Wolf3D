/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basics_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelluet <mvelluet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 14:30:41 by mvelluet          #+#    #+#             */
/*   Updated: 2017/10/17 22:01:12 by mvelluet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	ft_pixel_put(t_image *img, t_pixel p)
{
	if (p.x < 0 || p.x >= img->w || p.y < 0 || p.y >= img->h)
		return ;
	img->l[p.y * img->w + p.x] = p.c;
}

t_color	ft_create_color(t_uchar r, t_uchar g, t_uchar b, t_uchar a)
{
	t_color	c;

	c.r = r;
	c.g = g;
	c.b = b;
	c.a = a;
	return (c);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelluet <mvelluet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 14:30:22 by mvelluet          #+#    #+#             */
/*   Updated: 2017/10/18 13:47:27 by mvelluet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include <mlx.h>
# include "libft/libft.h"
# include <math.h>
# include <pthread.h>
# include <stdio.h>

# define PI				3.1415926535

# define PLAYER_SPEED	0.5
# define CAM_SPEED		3
# define SHADOWS		0.7

typedef unsigned char	t_uchar;

typedef struct			s_point
{
	int					x;
	int					y;
}						t_point;

typedef struct			s_color
{
	t_uchar				b;
	t_uchar				g;
	t_uchar				r;
	t_uchar				a;
}						t_color;

typedef struct			s_pixel
{
	int					x;
	int					y;
	t_color				c;
}						t_pixel;

typedef struct			s_win
{
	void				*win;
	void				*mlx;
	char				*title;
	int					w;
	int					h;
}						t_win;

typedef struct			s_image
{
	t_win				*win;
	int					h;
	int					w;
	void				*img;
	t_color				*l;
	int					depth;
	int					bits;
	int					size_l;
	int					endian;
}						t_image;

typedef struct			s_camera
{
	double				angle;
	double				x;
	double				y;
	int					h;
	int					w;
}						t_camera;

typedef struct			s_map
{
	int					w;
	int					h;
	t_uchar				**map;
}						t_map;

typedef struct			s_p
{
	double				x;
	double				y;
}						t_p;

typedef struct			s_block
{
	char				*name;
	int					h;
	t_color				color;
}						t_block;

typedef struct			s_key
{
	int					w;
	int					s;
	int					d;
	int					a;
}						t_key;

typedef struct			s_env
{
	t_win				win;
	t_image				*img;
	t_image				*back;
	t_block				*blocks;
	t_map				map;
	t_camera			cam;
	t_uchar				threads;
	t_key				key;
	double				fov;
	int					field;
}						t_env;

typedef struct			s_thread
{
	t_env				*env;
	int					i;
	int					max;
}						t_thread;

void					ft_pixel_put(t_image *img, t_pixel p);
void					ft_init(t_win *win, int w, int h, char *title);
void					ft_destroy_window(t_win *win);
t_image					*ft_new_image(t_win *win, int w, int h);
void					ft_destroy_image(t_win *win, t_image **img);
t_color					ft_create_color(t_uchar r, t_uchar g, t_uchar b,
						t_uchar a);

void					load_map(t_env *env, char *name);
void					free_map(t_env *env);
void					load_blocks(t_env *env);
void					free_blocks(t_env *env);

void					ft_keys(int keycode, t_env *env);

void					ft_keys_stop(int keycode, t_env *env);

void					wolf_keys(t_env *env);
void					multi_touch(t_env *env, int keycode);

int						ft_exit(t_env *env, int k);
int						red_cross(t_env *env);

void					create_menu(t_env *env);
void					destroy_menu(t_env *env);

void					move_player(t_env *env, double x, double y);

void					draw_line(t_env *env, t_pixel a, t_pixel b);
void					draw_background(t_env *env);
int						ft_draw(t_env *env);
void					draw_wolf(t_thread *t);
int						convert(double n);

#endif

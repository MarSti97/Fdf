/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:29:43 by mstiedl           #+#    #+#             */
/*   Updated: 2023/02/22 17:33:10 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "mlx.h"
# include "./libft/libft.h"

# define WIDTH 1800
# define HEIGHT 900
# define ESC 65307
# define Q 113
# define W 119
# define E 101
# define A 97
# define S 115
# define D 100
# define P 112
# define C 99
# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363
# define COLOUR_ZERO 0x009900FF
# define COLOUR_TOP 0x00FFFC00
# define COLOUR_BOTTOM 0x0000FF09

typedef struct s_map
{
	int				row;
	int				col;
	int				x;
	int				y;
	int				z;
	struct s_map	*next;
	struct s_map	*down;
}				t_map;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		len;
	int		edn;
}				t_img;

struct	s_coordinates
{
	int	x_start;
	int	y_start;
	int	x_end;
	int	y_end;
};

struct	s_line
{
	int	x;
	int	y;
	int	dx;
	int	dy;
	int	endx;
	int	endy;
	int	e;
	int	err;
};

typedef struct s_dimensions
{
	int	cmax;
	int	rmax;
	int	r_xy;
	int	r_z;
	int	z_max;
	int	z_min;
	int	rad;
	int	cntrx;
	int	cntry;
	int	rotate;
	int	tilt;
	int	spin;
	int	d;
}				t_dim;

typedef struct s_fdf
{
	t_map	*map;
	t_img	*img;
	t_dim	dim;
	void	*mlx;
	void	*win;
}				t_fdf;

typedef struct s_colour
{
	int	r;
	int	g;
	int	b;
	int	s_z;
	int	e_z;
}				t_colour;

// fdf
void			draw_map(t_fdf *fdf);
struct s_line	draw_line_two(t_map *start, t_map *end);
// list_funcs
void			ft_listadd_back(t_map **lst, t_map *new);
t_map			*ft_listlast(t_map *lst);
void			free_list(t_map *lst);
// map.c
void			make_map(t_fdf **fdf, char *file);
void			add_data(t_map **map, char **data);
t_dim			get_dimensions(t_map **map);
void			linked_grid(t_map *map);
void			give_coords(t_map *map, t_dim dim);
// rotate.c
double			get_radius(t_map *start, t_map *end);
void			rotate_coord(t_map *map, double degree, t_dim dim);
int				make_grid_coord(int y, int arg, int height);
void			tilt(t_map *map, double degree, t_dim dim);
void			spin(t_map *map, double degree, t_dim dim);
// third_dim.c
void			tilt_3d(t_map *map, t_dim dim);
void			spin_3d(t_map *map, t_dim dim);
// math.c
double			pythag(int a, int b);
int				rnd(double nbr);
int				prcnt(double full, double percent);
// controls
void			controls(t_fdf *fdf);
int				keys(int keycode, t_fdf *fdf);
int				close_x(t_fdf *fdf);
// controls_utils
int				zoom(int button, int x, int y, t_fdf *fdf);
t_dim			translate(int keycode, t_dim dim);
t_dim			para_cent(int keycode, t_dim dim);
t_dim			do_tilt(int keycode, t_dim dim);
t_dim			do_spin(int keycode, t_dim dim);
// tools
int				my_ternery(int a, int b, int yes, int no);
int				get_z_max(t_map *map);
int				get_z_min(t_map *map);
void			error(char *str, t_fdf *fdf, int arg);
void			free_data(char **data);
// colour
t_colour		get_colour_dif(t_dim dim, t_colour zero, int z);
int				split_colour(t_colour start, t_colour end, t_dim dim, int i);
int				add_colour(t_colour start, t_colour i, t_dim dim, int change);
t_colour		start_colour(t_dim dim, int start_z);
t_colour		end_colour(t_dim dim, int end_z);
// colour_utils
t_colour		get_rgb(int colour);
int				calc(double dif, double radius, double inc);
int				create_trgb(int t, int r, int g, int b);
void			pixel_put(t_img *img, int x, int y, int colour);

#endif
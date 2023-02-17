/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:29:43 by mstiedl           #+#    #+#             */
/*   Updated: 2023/02/17 19:00:17 by mstiedl          ###   ########.fr       */
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
# define THETA (M_PI / 180)
# define RX 35
# define RY 35
# define RZ 35
# define COLOUR_START 0x009900FF
# define COLOUR_END 0x00FFFC00


typedef struct	s_map
{
	int				row;
	int				col;
	int				x;
	int				y;
	int				z;
	struct s_map	*next;
	struct s_map	*down;
}				t_map;

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}				t_img;

struct	s_coordinates
{
	int	x_start;
	int	y_start;
	int	x_end;
	int	y_end;
};

struct s_line
{
	int	x;
	int	y;
	int dx;
	int	dy;
	int endx;
	int endy;
	int	e;
	int	err;
};

typedef struct	s_dimensions
{
	int	cmax;
	int	rmax;
	int	rx;
	int	ry;
	int	z_max;
	int	z_min;
	int	colour_r;
	int cntrx;
	int cntry;
	int zoom;
	int rotate;
	int tilt;
	int spin;
	int	z_depth;
}				t_dim;

typedef struct	s_fdf
{
	t_map	*map;
	t_img	*img;
	t_dim	dim;
	void	*mlx;
	void	*win;
}				t_fdf;

typedef struct	s_colour
{
	int	r;
	int	g;
	int	b;
	int s_z;
	int e_z;
}				t_colour;

// fdf
void	pixel_put(t_img *img, int x, int y, int colour);
void	draw_map(t_fdf *fdf, t_img *img);
// list_funcs
void	ft_listadd_back(t_map **lst, t_map *new);
void	error(t_map *lst);
t_map	*ft_listlast(t_map *lst);
// map.c
t_dim	make_map(t_map **map, int fd);
void	add_data(t_map **map, char **data);
t_dim	get_dimensions(t_map **map);
void	linked_grid(t_map *map);
void	give_coords(t_map *map, t_dim dim);
// rotate.c
double	get_radius(t_map *start, t_map *end);
void 	rotate_coord(t_map *map, double degree, t_dim dim);
int		make_grid_coord(int y, int arg, int height);
void	tilt(t_map *map, double degree, t_dim dim);
void	spin(t_map *map, double degree, t_dim dim);
// third_dim.c
void	add_dimention(t_map *map, t_dim dim);
// math.c
double	pythag(int a, int b);
int		rnd(double nbr);
int		percentage(double full, double percent);
// controls
void	controls(t_fdf *fdf, t_img *img);
int		zoom(int button, int x, int y, t_fdf *fdf);
t_dim	translate(int keycode, t_dim dim);
t_dim	para_cent(int keycode, t_dim dim);
int keys(int keycode, t_fdf *fdf);
// tools
int		my_ternery(int a, int b, int yes, int no);
//  colour
int		colour_iter(t_map *start, t_map *end, int radius, int i);
int		get_dif(int start, int end, int radius, int ratio);
int		create_trgb(int t, int r, int g, int b);
int 	colour_loop(int i);
// colour alt
int add_colour(t_colour start, t_colour i, t_dim dim, int change);
t_colour	get_rgb(int colour);
t_colour	get_colour_dif(t_dim dim);
t_colour	start_colour(t_colour dif, int start_z, int end_z);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:29:43 by mstiedl           #+#    #+#             */
/*   Updated: 2023/02/14 15:51:47 by mstiedl          ###   ########.fr       */
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
# define Q 65307
# define W 119
# define E 101
# define A 97
# define S 115
# define D 100
# define THETA (M_PI / 180)
# define RX 35
# define RY 35
# define RZ 2


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

struct	coordinates
{
	int	x_start;
	int	y_start;
	int	x_end;
	int	y_end;
};

struct line
{
	int	x;
	int	y;
	int dx;
	int	dy;
	int endx;
	int endy;
};

typedef struct	dimensions
{
	int	cmax;
	int	rmax;
	int	rx;
	int	ry;
	int	rz;
	int cntrx;
	int cntry;
	int rotate;
}				t_dim;

typedef struct	s_fdf
{
	t_map	*map;
	t_img	*img;
	t_dim	dim;
	void	*mlx;
	void	*win;
}				t_fdf;

// fdf
void	draw_map(t_fdf *fdf, t_img *img);
// list_funcs
void	ft_listadd_back(t_map **lst, t_map *new);
void	error(t_map *lst);
t_map	*ft_listlast(t_map *lst);
// map.c
t_dim   make_map(t_map **map, int fd);
void    add_data(t_map **map, char **data);
t_dim    get_dimensions(t_map **map);
void	linked_grid(t_map *map);
void	give_coords(t_map *map, t_dim dim);
// rotate.c
void	start_coord(t_map *map, double degree);
void	pixel_put(t_img *img, int x, int y, int colour);
double	get_radius(t_map *start, t_map *end);
void 	rotate_coord(t_map *map, double degree);
int make_grid_coord(int y, int arg);
// void	test_rotating(t_img *img);
// third_dim.c
void    add_dimention(t_map *map, int ratio);
int 	add_colour(t_map *start, t_map *end, int radius, int i);
// math.c
double	pythag(int a, int b);
int rnd(double nbr);
// controls
void controls(t_fdf *fdf, t_img *img);
int zoom(int button, int x, int y, void *param);
#endif
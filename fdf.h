/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:29:43 by mstiedl           #+#    #+#             */
/*   Updated: 2023/02/08 21:10:17 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "./libft/libft.h"

#ifndef WIDTH
# define WIDTH 1080
#endif

#ifndef HEIGHT
# define HEIGHT 640
#endif

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
	int cntrx;
	int cntry;
}				t_dim;

// fdf
// list_funcs
void	ft_listadd_back(t_map **lst, t_map *new);
void	error(t_map *lst);
t_map	*ft_listlast(t_map *lst);
// map.c
void    make_map(t_map **map, int fd);
void    add_data(t_map **map, char **data);
t_dim    get_dimensions(t_map **map);
void	linked_grid(t_map *map);
void	give_coords(t_map *map, t_dim dim);
// rotate.c
void	rotate_coord(t_map *map, int degree);
void	pixel_put(t_img *img, int x, int y, int colour);
int	get_radius(int x, int y);
void	test_rotating(t_img *img);
// third_dim.c
void    add_dimention(t_map *map);
#endif
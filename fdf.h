/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:29:43 by mstiedl           #+#    #+#             */
/*   Updated: 2023/02/05 09:21:44 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct	s_map
{
	struct s_map	*next;
	struct s_map	*down;
	int				row;
	int				col;
	int				x;
	int				y;
	int				z;
}				t_map;

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}				t_img;

struct	s_coordinate
{
	int	x_start;
	int	y_start;
	int	x_end;
	int	y_end;
	int z;
}		coord;

#endif
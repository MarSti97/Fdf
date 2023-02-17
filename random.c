void	reverse_line(t_img *img, t_map *start, t_map *end, int dx)
{
	struct line	line;

	line.dy = start->y - end->y;
	line.x = (end->x > start->x ? start->x : end->x);
	line.y = (end->x > start->x ? start->y : end->y);
	line.d = 2 * (line.dy - dx);
	line.finishx = (end->x > start->x ?  end->x : start->x);
	line.finishy = (end->x > start->x ?  end->y : start->y);
	while(line.x < line.finishx)
	{
		if (line.d >= 0)
		{
			pixel_put(img, line.x, line.y, 0x009900FF);
			line.y--;
			line.d = line.d + 2 * line.dy - 2 * dx;
		}
		else
		{
			pixel_put(img, line.x, line.y, 0x009900FF);
			line.d = line.d + 2 * line.dy;	
		}
		line.x++;
	}
	while (line.y != line.finishy)
		pixel_put(img, line.x, line.y--, 0x009900FF);
}

void	bresenham_line(t_img *img, t_map *start, t_map *end)
{
	struct line	line;

	line.dx = (end->x > start->x ? (end->x - start->x) : (start->x - end->x));
	if (end->y < start->y)
		return (reverse_line(img, start, end, line.dx));
	line.dy = end->y - start->y;
	line.x = (end->x > start->x ? start->x : end->x);
	line.y = (end->x > start->x ? start->y : end->y);
	// line.y = start->y;
	line.d = 2 * (line.dy - line.dx);
	line.finishx = (end->x > start->x ?  end->x : start->x);
	line.finishy = (end->x > start->x ?  end->y : start->y);
	while(line.x < line.finishx)
	{
		if (line.d >= 0)
		{
			pixel_put(img, line.x, line.y, 0x009900FF);
			line.y++;
			line.d = line.d + 2 * line.dy - 2 * line.dx;
		}
		else
		{
			pixel_put(img, line.x, line.y, 0x009900FF);
			line.d = line.d + 2 * line.dy;	
		}
		line.x++;
	}
	while (line.y < line.finishy)
		pixel_put(img, line.x, line.y++, 0x009900FF);
	while (line.y > line.finishy)
		pixel_put(img, line.x, line.y--, 0x009900FF);
}

void	test_grid(t_map *map)
{
	// t_map *temp = map;
	while (map)
	{
		ft_printf("Node: row:%i, col:%i x:%i y:%i  -> ", map->row, map->col, map->x, map->y);
		ft_printf("Node: row:%i, col:%i x:%i y:%i  -> ", map->next->row, map->next->col, map->next->x, map->next->y);
		ft_printf("Node: row:%i, col:%i x:%i y:%i  -> ", map->next->next->row, map->next->next->col, map->next->next->x, map->next->next->y);
		ft_printf("\n----\n");
		map = map->down;
	}
	// ft_printf("\n");
	// while (temp)
	// {
	// 	ft_printf("Node %i: z:%i row:%i, col:%i  ->  ", i++, temp->down->z, temp->down->row, temp->down->col);
	// 	temp = temp->next;
	// }
}

double	which_quadrent(int x, int y, double i)
{
	if ((x > WIDTH / 2) && (y > HEIGHT / 2))
		return (i);
	if ((x <= WIDTH / 2) && (y > HEIGHT / 2))
		return (180 - i);
	if ((x <= WIDTH / 2) && (y <= HEIGHT / 2))
		return (180 + i);
	if ((x > WIDTH / 2) && (y <= HEIGHT / 2))
		return (360 - i);
	return (0);
}

double	find_start_angle(int x, int y, double hypot)
{
	double PI = 3.1415926535;
	double degree;
	int opposite;
	double sin;
	
	if (y <= (HEIGHT / 2))
		opposite = (HEIGHT / 2) - y;
	else
		opposite = y - (HEIGHT / 2);
	sin = (double)opposite / hypot;
	degree = asin(sin) * 180 / PI;
	degree = which_quadrent(x, y, degree);
	return (rnd(degree));
}

void	start_coord(t_map *map, double degree)
{
	map->x = map->x - (WIDTH / 2);
	map->y = make_grid_coord(map->y, 1);
	map->x = rnd((map->x * cos(degree)) - (map->y * sin(degree)));
	map->y = rnd((map->x * sin(degree)) + (map->y * cos(degree)));
	map->x = map->x + (WIDTH / 2);
	map->y = make_grid_coord(map->y, 0);
}

void	calculate_down(t_map *map, t_dim dim, int degree, int first)
{
	double x = 0;
	double y = 0;
	int i_down;

	i_down = 1;
	x = ((dim.ry * i_down) * sin(degree));
	while (map->down)
	{
		printf("x%i y%i\n", map->x, map->y);
		y = pythag(x, (dim.ry * i_down++));
		// printf("the difference: x%i y%i\n", x, y);
		map = map->down;
		map->x = map->x - rnd(x);
		map->y = first + rnd(y);
		x += x;
	}
}

void	calculate_next(t_map *map, t_dim dim, int degree)
{
	double x = 0;
	double y = 0;
	static int i_next;

	printf("next :x%i y%i\n", map->x, map->y);
	y = map->y - ((dim.rx * ++i_next) * sin(degree));
	x = map->x + pythag(y, (dim.rx * i_next));
	map->next->y = rnd(y);
	map->next->x = rnd(x);
	// printf("the difference: x%i y%i\n", x, y);
	printf("-----NODE------\n|row(%i)col(%i)|\n---------------\n", map->row, map->col);
	printf("original: x%i y%i\n", map->x, map->y);
	printf("after: x%i y%i\n", map->x, map->y);
}
// void	reverse_line(t_img *img, t_map *start, t_map *end, int dx)
// {
// 	struct line	line;

// 	line.dy = start->y - end->y;
// 	line.x = (end->x > start->x ? start->x : end->x);
// 	line.y = (end->x > start->x ? start->y : end->y);
// 	line.d = 2 * (line.dy - dx);
// 	line.finishx = (end->x > start->x ?  end->x : start->x);
// 	line.finishy = (end->x > start->x ?  end->y : start->y);
// 	while(line.x < line.finishx)
// 	{
// 		if (line.d >= 0)
// 		{
// 			pixel_put(img, line.x, line.y, 0x009900FF);
// 			line.y--;
// 			line.d = line.d + 2 * line.dy - 2 * dx;
// 		}
// 		else
// 		{
// 			pixel_put(img, line.x, line.y, 0x009900FF);
// 			line.d = line.d + 2 * line.dy;	
// 		}
// 		line.x++;
// 	}
// 	while (line.y != line.finishy)
// 		pixel_put(img, line.x, line.y--, 0x009900FF);
// }

// void	bresenham_line(t_img *img, t_map *start, t_map *end)
// {
// 	struct line	line;

// 	line.dx = (end->x > start->x ? (end->x - start->x) : (start->x - end->x));
// 	if (end->y < start->y)
// 		return (reverse_line(img, start, end, line.dx));
// 	line.dy = end->y - start->y;
// 	line.x = (end->x > start->x ? start->x : end->x);
// 	line.y = (end->x > start->x ? start->y : end->y);
// 	// line.y = start->y;
// 	line.d = 2 * (line.dy - line.dx);
// 	line.finishx = (end->x > start->x ?  end->x : start->x);
// 	line.finishy = (end->x > start->x ?  end->y : start->y);
// 	while(line.x < line.finishx)
// 	{
// 		if (line.d >= 0)
// 		{
// 			pixel_put(img, line.x, line.y, 0x009900FF);
// 			line.y++;
// 			line.d = line.d + 2 * line.dy - 2 * line.dx;
// 		}
// 		else
// 		{
// 			pixel_put(img, line.x, line.y, 0x009900FF);
// 			line.d = line.d + 2 * line.dy;	
// 		}
// 		line.x++;
// 	}
// 	while (line.y < line.finishy)
// 		pixel_put(img, line.x, line.y++, 0x009900FF);
// 	while (line.y > line.finishy)
// 		pixel_put(img, line.x, line.y--, 0x009900FF);
// }

// // void	test_grid(t_map *map)
// {
// 	// t_map *temp = map;
// 	while (map)
// 	{
// 		ft_printf("Node: row:%i, col:%i x:%i y:%i  -> ", map->row, map->col, map->x, map->y);
// 		ft_printf("Node: row:%i, col:%i x:%i y:%i  -> ", map->next->row, map->next->col, map->next->x, map->next->y);
// 		ft_printf("Node: row:%i, col:%i x:%i y:%i  -> ", map->next->next->row, map->next->next->col, map->next->next->x, map->next->next->y);
// 		ft_printf("\n----\n");
// 		map = map->down;
// 	}
// 	// ft_printf("\n");
// 	// while (temp)
// 	// {
// 	// 	ft_printf("Node %i: z:%i row:%i, col:%i  ->  ", i++, temp->down->z, temp->down->row, temp->down->col);
// 	// 	temp = temp->next;
// 	// }
// }
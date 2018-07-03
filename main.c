/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atikhono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 17:03:26 by atikhono          #+#    #+#             */
/*   Updated: 2018/07/03 10:45:27 by atikhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include <stdio.h>

int		main(void)
{
	void	*win;
	void	*mlx;
	int		height;
	int		width;
	int		i;
	int		j;
	int		n;
	int		lim;
	double	x;
	double	y;
	double	w;
	double	h;
	double	xmin;
	double	ymin;
	double	xmax;
	double	ymax;
	double	dx;
	double	dy;
	double	a;
	double	aa;
	double	b;
	double	bb;
	double	twoab;

	height = 1200;
	width = 1200;

	mlx = mlx_init();
	win = mlx_new_window(mlx, height, width, "start");

	w = 5;
	h = (w * height) / width;

	xmin = -w / 2;
	ymin = -h / 2;

	xmax = xmin + w;
	ymax = ymin + h;

	dx = (xmax - xmin) / width;
	dy = (ymax - ymin) / height;

	lim = 100;
	y = ymin;
	j = 0;
	while (j < height)
	{
		x = xmin;
		i = 0;
		while (i < width)
		{
			a = x;
			b = y;
			n = 0;
			while (n < lim)
			{
				aa = a * a;
				bb = b * b;
				twoab = 2.0 * a * b;
				a = aa - bb + x;
				b = twoab + y;
				if (a * a + b * b > 16.0)
					break;
				++n;
			}
			if (n == lim)
				mlx_pixel_put(mlx, win, i, j, 0);
			else
			{
				//mlx_pixel_put(mlx, win, i, j, 0xFFFFFF);
				mlx_pixel_put(mlx, win, i, j, 0xFFFFFF / lim * (double) (n));
				//printf("%f\n", 0xFFFFFF / lim * (double) (n));
			}
			x += dx;
			++i;
		}
		y += dy;
		++j;
	}
	mlx_loop(mlx);
	return (0);
}

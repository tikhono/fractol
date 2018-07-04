/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atikhono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 17:03:26 by atikhono          #+#    #+#             */
/*   Updated: 2018/07/04 11:33:34 by atikhono         ###   ########.fr       */
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
	double	off_x;
	double	y;
	double	off_y;
	double	scale;
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

	height = 750;
	width = 1200;
	mlx = mlx_init();
	win = mlx_new_window(mlx, width, height, "start");
	off_x = 0.0;
	off_y = 0.0;
	scale = 1.0;
	scale = 2.0 / scale;
	xmin = -scale;
	xmax = scale;
	ymin = -scale * height / width;
	ymax = scale * height / width;
	dx = (xmax - xmin) / width;
	dy = (ymax - ymin) / height;
	lim = 1000;
	y = ymin + off_y;
	j = 0;
	while (j < height)
	{
		x = xmin + off_x;
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
				if (a * a + b * b > 4.0)
					break;
				++n;
			}
			if (n == lim)
				mlx_pixel_put(mlx, win, i, j, 0);
			else
				mlx_pixel_put(mlx, win, i, j, 0x0F0F0F * (double) (n + 1));
			x += dx;
			++i;
		}
		y += dy;
		++j;
	}
	mlx_loop(mlx);
	return (0);
}

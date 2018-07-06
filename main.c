/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atikhono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 17:03:26 by atikhono          #+#    #+#             */
/*   Updated: 2018/07/06 14:43:55 by atikhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		exit_mouse(void)
{
	exit(0);
	return (0);
}

void    complex_pow(double power, double *x, double *y)
{
	double	z;
	double	phi_x;
	double	phi_y;
	double	res_z;
	double	kek;
	double	lol;

	if (*x != 0.0 || *y != 0.0)
	{
		if (*x == 0.0)
			z = fabs(*y);
		else if (*y == 0.0)
			z = fabs(*x);
		else
			z = sqrt(*x * *x + *y * *y);
		res_z = pow(z, power);
		kek = (*y >= 0 ? 1.0 : -1.0);
		lol = 1.0;
		if (*x > 0.0)
			lol = 0.0;
		if (*x < 0.0)
			lol = 2.0;
		phi_x = M_PI / 2.0 * lol * kek + atan(*y / *x);
		*x = res_z * cos(power * phi_x);
		*y = res_z * sin(power * phi_x);
	}
}

void	calc(t_mlx *p)
{
	int		i;
	int		j;
	int		n;
	double	x;
	double	y;
	double	a;
	double	b;

	p->xmin = -p->scale;
	p->xmax = p->scale;
	p->ymin = -p->scale * p->height / p->width;
	p->ymax = p->scale * p->height / p->width;
	p->dx = (p->xmax - p->xmin) / p->width;
	p->dy = (p->ymax - p->ymin) / p->height;

	y = p->ymin + p->off_y;
	j = 0;
	while (j < p->height)
	{
		x = p->xmin + p->off_x;
		i = 0;
		while (i < p->width)
		{
			a = x;
			b = y;
			n = 0;
			while (n < p->lim)
			{
				complex_pow(p->power, &a, &b);
				a += x;
				b += y;	
				if (a * a + b * b > 4.0)
					break;
				++n;
			}
			if (n == p->lim)
				mlx_pixel_put(p->mlx, p->win, i, j, 0);
			else
				mlx_pixel_put(p->mlx, p->win, i, j, 0x0F0F0F * (double) (n + 1));
			x += p->dx;
			++i;
		}
		y += p->dy;
		++j;
	}
}

int		call_hookers(int key, t_mlx *p)
{
	if (key == 123)
		p->off_x -= 0.1; 
	if (key == 124)
		p->off_x += 0.1;
	if (key == 125)
		p->off_y += 0.1;
	if (key == 126)
		p->off_y -= 0.1;
	if (key == 0)
		p->scale += 0.1;
	if (key == 1)
		p->scale -= 0.1;
	if (key == 12)
		p->power += 0.001;
	if (key == 13)
		p->power -= 0.001;
	if (key == 53)
		exit (0);
	calc(p);
	return (0);
}

void	initialise(t_mlx *p)
{
	p->height = 750;
	p->width = 1200;
	p->mlx = mlx_init();
	p->win = mlx_new_window(p->mlx, p->width, p->height, "start");
	p->lim = 50;
	p->power = 2.0;
	p->off_x = 0.0;
	p->off_y = 0.0;
	p->scale = 1.0;
	p->scale = 2.0 / p->scale;
	p->xmin = -p->scale;
	p->xmax = p->scale;
	p->ymin = -p->scale * p->height / p->width;
	p->ymax = p->scale * p->height / p->width;
	p->dx = (p->xmax - p->xmin) / p->width;
	p->dy = (p->ymax - p->ymin) / p->height;
	calc(p);
}

int		main(void)
{
	t_mlx	p;
	initialise(&p);
	mlx_hook(p.win, 2, 5, call_hookers, &p);
	mlx_hook(p.win, 17, 1L << 17, exit_mouse, &p);
	mlx_loop(p.mlx);
	return (0);
}

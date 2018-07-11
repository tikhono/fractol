/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atikhono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 17:03:26 by atikhono          #+#    #+#             */
/*   Updated: 2018/07/11 12:23:10 by atikhono         ###   ########.fr       */
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
	double	res_z;
	double	phi;
	double	pi;

	if (*x != 0.0 || *y != 0.0)
	{
		if (*x == 0.0)
			z = fabs(*y);
		else if (*y == 0.0)
			z = fabs(*x);
		else
			z = sqrt(*x * *x + *y * *y);
		pi = *y < 0.0 ? - M_PI : M_PI;
		if (*x > 0.0)
			pi = 0.0;
		if (*x == 0.0)
			pi /= 2.0;
		phi = (atan(*y / *x) * (*x == 0.0 ? 0.0 : 1.0) + pi) * power;
		res_z = pow(z, power);
		*x = res_z * cos(phi);
		*y = res_z * sin(phi);
	}
}

void	calc(t_mlx *p)
{
	int			i;
	int			j;
	double		x;
	double		y;
	double		a;
	double		b;
	uint64_t	t1;
	uint64_t	t2;

	p->xmin = -p->scale;
	p->xmax = p->scale;
	p->ymin = -p->scale * p->height / p->width;
	p->ymax = p->scale * p->height / p->width;
	p->d = 2.0 * p->scale / p->width;
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
			t1 = mach_absolute_time();
			while ((t2 = (mach_absolute_time()) - t1) < p->lim)
			{
				a = p->abs_x == 'y' ? fabs(a) : a;
				b = p->abs_y == 'y' ? fabs(b) : b;
				a = p->sign_x == '+' ? a : -a;
				b = p->sign_y == '+' ? b : -b;
				complex_pow(p->power, &a, &b);
				a += x;//or julia point
				b += y;	
				if (a * a + b * b > 4.0)
					break;
			}
			if (t2 >= p->lim)
				p->addr[j * p->width + i] = 0;
			else
				p->addr[j * p->width + i] = 0xFFFFFF / (p->lim / 1000) * (t2 / 1000);
			//	p->addr[j * p->width + i] = 0xFFFFFF;
			x += p->d;
			++i;
		}
		y += p->d;
		++j;
	}
	mlx_put_image_to_window(p->mlx, p->win, p->img, 0, 0);
}

int		call_hookers(int key, t_mlx *p)
{
	if (key == 123)
		p->off_x -= 0.1 * p->scale; 
	if (key == 124)
		p->off_x += 0.1 * p->scale;
	if (key == 125)
		p->off_y += 0.1 * p->scale;
	if (key == 126)
		p->off_y -= 0.1 * p->scale;
	if (key == 0)
		p->scale += 0.1 * p->scale;
	if (key == 1)
		p->scale -= 0.1 * p->scale;
	if (key == 12)
		p->power += 0.1;
	if (key == 13)
		p->power -= 0.1;
	if (key == 18)
		p->sign_x = p->sign_x == '+' ? '-' : '+';
	if (key == 19)
		p->abs_x = p->abs_x == 'y' ? 'n' : 'y';
	if (key == 20)
		p->sign_y = p->sign_y == '+' ? '-' : '+';
	if (key == 21)
		p->abs_y = p->abs_y == 'y' ? 'n' : 'y';
	if (key == 53)
		exit (0);
	calc(p);
	return (0);
}

void	initialise(t_mlx *p)
{
//	p->height = 1080;
//	p->width = 1920;
	p->height = 600;
	p->width = 600;
	p->mlx = mlx_init();
	p->win = mlx_new_window(p->mlx, p->width, p->height, "start");
	p->img = mlx_new_image(p->mlx, p->width, p->height);
	p->addr = (int *) mlx_get_data_addr(p->img, &p->a, &p->b, &p->c);
	p->lim = 10000;
	p->abs_x = 'n';
	p->abs_y = 'n';
	p->sign_x = '+';
	p->sign_y = '+';
	p->power = 2.0;
	p->off_x = 0.0;
	p->off_y = 0.0;
	p->scale = 1.0;
	p->scale = 2.0 / p->scale;
	p->xmin = -p->scale;
	p->xmax = p->scale;
	p->ymin = -p->scale * p->height / p->width;
	p->ymax = p->scale * p->height / p->width;
	p->d = 2.0 * p->scale / p->width;
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

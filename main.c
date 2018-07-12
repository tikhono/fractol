/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atikhono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 17:03:26 by atikhono          #+#    #+#             */
/*   Updated: 2018/07/12 14:39:55 by atikhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		exit_mouse(void)
{
	exit(0);
	return (0);
}

	//
	//mlx_put_image_to_window(p->mlx, p->win, p->img, 0, 0);

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
	p->scale = 2.0;
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

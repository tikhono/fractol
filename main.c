/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atikhono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 17:03:26 by atikhono          #+#    #+#             */
/*   Updated: 2018/08/09 11:35:43 by atikhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		call_hookers(int key, t_all *a)
{
	if (key == 123)
		a->d.off_x -= 0.1 * a->d.scale; 
	if (key == 124)
		a->d.off_x += 0.1 * a->d.scale;
	if (key == 125)
		a->d.off_y += 0.1 * a->d.scale;
	if (key == 126)
		a->d.off_y -= 0.1 * a->d.scale;
	if (key == 0)
		a->d.scale += 0.1 * a->d.scale;
	if (key == 1)
		a->d.scale -= 0.1 * a->d.scale;
	if (key == 12)
		a->d.power -= 0.01;
	if (key == 13)
		a->d.power += 0.01;
	if (key == 18)
		a->d.sign_x = a->d.sign_x == '+' ? '-' : '+';
	if (key == 19)
		a->d.abs_x = a->d.abs_x == 'y' ? 'n' : 'y';
	if (key == 20)
		a->d.sign_y = a->d.sign_y == '+' ? '-' : '+';
	if (key == 21)
		a->d.abs_y = a->d.abs_y == 'y' ? 'n' : 'y';
	if (key == 48)
		a->d.constant = a->d.constant == 'y' ? 'n' : 'y';
	if (key == 53)
		exit (0);
	run_kernel(a);
	return (0);
}

int		mouse_click(int key, int x, int y, t_all *a)
{
	if (key == 1)
		a->fix = a->fix == 'y' ? 'n' : 'y';
	if (a->fix == 'n')
	{
		a->d.m_pos_x = x;
		a->d.m_pos_y = y;
	}
	if (a->d.constant == 'y')
		run_kernel(a);
	return (0);
}

int		mouse_move(int x, int y, t_all *a)
{
	if (a->fix == 'n')
	{
		a->d.m_pos_x = x;
		a->d.m_pos_y = y;
	}
	if (a->d.constant == 'y')
		run_kernel(a);
	return (0);
}

int		exit_mouse(void)
{
	exit(0);
	return (0);
}

void	initialise(t_all *a)
{
	int		x;
	int		y;
	int		z;

	a->d.width = 300;
	a->d.height = 300;
	a->p.mlx = mlx_init();
	a->p.win = mlx_new_window(a->p.mlx, a->d.width, a->d.height, "start");
	a->p.img = mlx_new_image(a->p.mlx, a->d.width, a->d.height);
	a->addr = (int *) mlx_get_data_addr(a->p.img, &x, &y, &z);
	a->d.abs_x = 'n';
	a->d.abs_y = 'n';
	a->d.sign_x = '+';
	a->d.sign_y = '+';
	a->d.constant = 'n';
	a->fix = 'n';
	a->d.power = 2.0;
	a->d.off_x = 0.0;
	a->d.off_y = 0.0;
	a->d.scale = 2.0;
	a->d.m_pos_x = 0.0;
	a->d.m_pos_y = 0.0;
	start_kernel(a);
	run_kernel(a);
}

int		main(int ac, char **av)
{
	t_mlx	p;
	t_data	d;
	t_all	a;

	while (ac > 2)
		if (fork() != 0)
			--ac;
		else
			break ;
	--ac;
	a.p = p;
	a.d = d;
	initialise(&a);
	mlx_hook(a.p.win, 2, 5, call_hookers, &a);
	mlx_hook(a.p.win, 4, 1L << 2, mouse_click, &a);
	mlx_hook(a.p.win, 6, 1L << 6, mouse_move, &a);
	mlx_hook(a.p.win, 17, 1L << 17, exit_mouse, 0);
	mlx_loop(a.p.mlx);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atikhono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 17:03:26 by atikhono          #+#    #+#             */
/*   Updated: 2018/08/10 11:30:22 by atikhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"


void	initialise(t_all *a)
{
	int		x;
	int		y;
	int		z;

	a->d.width = 512;
	a->d.height = 512;
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

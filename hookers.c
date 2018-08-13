/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hookers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atikhono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 11:27:07 by atikhono          #+#    #+#             */
/*   Updated: 2018/08/13 13:07:48 by atikhono         ###   ########.fr       */
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
		exit(0);
	return (run_kernel(a));
}

int		mouse_click(int key, int x, int y, t_all *a)
{
	if (key == 1)
		a->fix = a->fix == 'y' ? 'n' : 'y';
	if (key == 2)
		a->d.state = a->d.state == 'y' ? 'n' : 'y';
	if (key == 4)
		a->d.scale -= 0.1 * a->d.scale;
	if (key == 5)
		a->d.scale += 0.1 * a->d.scale;
	if (a->fix == 'n')
	{
		a->d.m_pos_x = x;
		a->d.m_pos_y = y;
	}
	return (run_kernel(a));
}

int		mouse_move(int x, int y, t_all *a)
{
	if (a->fix == 'n')
	{
		a->d.m_pos_x = x;
		a->d.m_pos_y = y;
	}
	return (run_kernel(a));
}

int		exit_mouse(void)
{
	exit(0);
	return (0);
}

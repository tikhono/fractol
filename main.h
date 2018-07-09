/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atikhono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 17:41:57 by atikhono          #+#    #+#             */
/*   Updated: 2018/07/09 11:45:25 by atikhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# include <fcntl.h>
# include <mlx.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <unistd.h>

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
	void		*img;
	double		xmin;
	double		xmax;
	double		ymin;
	double		ymax;
	double		lim;
	double		power;
	double		off_x;
	double		off_y;
	double		dx;
	double		dy;
	double		scale;
	int			height;
	int			width;
	int			*addr;
	int			a;
	int			b;
	int			c;
	char		abs_x;
	char		abs_y;
	char		sign_x;
	char		sign_y;
}				t_mlx;

#endif

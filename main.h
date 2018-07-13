/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atikhono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 17:41:57 by atikhono          #+#    #+#             */
/*   Updated: 2018/07/13 13:20:20 by atikhono         ###   ########.fr       */
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
# include <assert.h>
# include <CoreServices/CoreServices.h>
# include <mach/mach.h>
# include <mach/mach_time.h>
# include <unistd.h>
# include <OpenCL/cl.h>

typedef struct	s_kernel
{
	cl_kernel			kernel;
	cl_command_queue	queue;
	cl_mem				input_buffer;
	cl_mem				res_buffer;
	size_t				global_size;
	size_t				local_size;
}						t_kernel;

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
	void		*img;
}				t_mlx;

typedef struct	s_data
{
	int			height;
	int			width;
	int			*addr;
	char		abs_x;
	char		abs_y;
	char		sign_x;
	char		sign_y;
	double		power;
	double		off_x;
	double		off_y;
	double		scale;
}				t_data;

typedef struct	s_all
{
	t_mlx		*p;
	t_data		*d;
	t_kernel	*k;
}				t_all;

void	start_kernel(t_all *a);
void	run_kernel(t_all *a);

#endif

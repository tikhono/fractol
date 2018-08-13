/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atikhono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 17:41:57 by atikhono          #+#    #+#             */
/*   Updated: 2018/08/13 13:04:36 by atikhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# include <mlx.h>
# include <math.h>
# include <stdio.h>
# include <OpenCL/cl.h>
# include "./libft/libft.h"

typedef struct			s_kernel
{
	cl_kernel			kernel;
	cl_command_queue	queue;
	cl_mem				input_buffer;
	cl_mem				res_buffer;
	size_t				global_size;
	size_t				local_size;
}						t_kernel;

typedef struct			s_mlx
{
	void				*mlx;
	void				*win;
	void				*img;
}						t_mlx;

typedef struct			s_data
{
	int					width;
	int					height;
	int					m_pos_x;
	int					m_pos_y;
	double				power;
	double				scale;
	double				off_x;
	double				off_y;
	char				sign_x;
	char				sign_y;
	char				abs_x;
	char				abs_y;
	char				constant;
	char				state;
}						t_data;

typedef struct			s_all
{
	t_mlx				p;
	t_data				d;
	t_kernel			k;
	int					*addr;
	char				fix;
}						t_all;

int						call_hookers(int key, t_all *a);
int						mouse_click(int key, int x, int y, t_all *a);
int						mouse_move(int x, int y, t_all *a);
int						exit_mouse(void);
void					start_kernel(t_all *a);
int						run_kernel(t_all *a);

#endif

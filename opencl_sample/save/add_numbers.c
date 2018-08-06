/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_numbers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atikhono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 15:32:35 by atikhono          #+#    #+#             */
/*   Updated: 2018/08/03 14:21:32 by atikhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define PROGRAM_FILE "add_numbers.cl"
#define KERNEL_FUNC "add_number"
#include "main.h"
#include <OpenCL/cl.h>

cl_device_id	create_device()
{
	cl_platform_id	platform;
	cl_device_id	dev;
	int				err;

	err = clGetPlatformIDs(1, &platform, NULL);
	if (err < 0) {
		printf("Couldn't identify a platform");
		exit(1);
	} 
	err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, 1, &dev, NULL);
	if (err == CL_DEVICE_NOT_FOUND) {
		err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &dev, NULL);
	}
	if (err < 0) {
		printf("Couldn't access any devices");
		exit(1);
	}
	return dev;
}

cl_program build_program(cl_context ctx, cl_device_id dev, const char* filename)
{
	cl_program	program;
	FILE		*program_handle;
	char		*program_buffer, *program_log;
	size_t		program_size, log_size;
	int			err;

	program_handle = fopen(filename, "r");
	if (program_handle == NULL) {
		printf("Couldn't find the program file");
		exit(1);
	}
	fseek(program_handle, 0, SEEK_END);
	program_size = ftell(program_handle);
	rewind(program_handle);
	program_buffer = (char*)malloc(program_size + 1);
	program_buffer[program_size] = '\0';
	fread(program_buffer, sizeof(char), program_size, program_handle);
	fclose(program_handle);
	program = clCreateProgramWithSource(ctx, 1, 
		(const char**)&program_buffer, &program_size, &err);
	if (err < 0) {
		printf("Couldn't create the program");
		exit(1);
	}
	free(program_buffer);
	err = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
	if (err < 0) {
		clGetProgramBuildInfo(program, dev, CL_PROGRAM_BUILD_LOG, 
			0, NULL, &log_size);
		program_log = (char*) malloc(log_size + 1);
		program_log[log_size] = '\0';
		clGetProgramBuildInfo(program, dev, CL_PROGRAM_BUILD_LOG, 
			log_size + 1, program_log, NULL);
		printf("%s\n", program_log);
		free(program_log);
		exit(1);
	}
	return program;
}

int main()
{
	cl_device_id		device;
	cl_context			context;
	cl_program			program;
	cl_kernel			kernel;
	cl_command_queue	queue;
	size_t				local_size, global_size;
	t_data				data;
	int					err;
	cl_mem				input_buffer, res_buffer;
	cl_int				num_groups;
	void				*mlx;
	void				*win;
	void				*img;
	int					a;
	int					b;
	int					c;
	int					*addr;

	data.width = 1200;
	data.height = 600;
	data.power = 2.0;
	data.scale = 5.0;
	data.off_x = 0.0;
	data.off_y = 0.0;
	data.sign_x = '+';
	data.sign_y = '+';
	data.abs_x = 'n';
	data.abs_y = 'n';

	mlx = mlx_init();
	win = mlx_new_window(mlx, data.width, data.height, "lol");
	img = mlx_new_image(mlx, data.width, data.height);
	addr = (int *)mlx_get_data_addr(img, &a, &b, &c);
	device = create_device();
	context = clCreateContext(NULL, 1, &device, NULL, NULL, &err);
	if (err < 0) {
		printf("Couldn't create a context");
		exit(1);	
	}
	program = build_program(context, device, PROGRAM_FILE);
	global_size = 1200*600;
	local_size = 1;
	num_groups = global_size/local_size;
	input_buffer = clCreateBuffer(context, CL_MEM_READ_ONLY |
		 CL_MEM_COPY_HOST_PTR, sizeof(t_data), &data, &err);
	res_buffer = clCreateBuffer(context, CL_MEM_READ_WRITE |
		 CL_MEM_COPY_HOST_PTR, sizeof(int) * 1200 * 600, addr, &err);
	if (err < 0) {
		printf("Couldn't create a buffer");
		printf("\n%d\n", err);
		exit(1);	
	};
	queue = clCreateCommandQueue(context, device, 0, &err);
	if (err < 0) {
		printf("Couldn't create a command queue");
		printf("\n%d\n", err);
		exit(1);	
	};
	kernel = clCreateKernel(program, KERNEL_FUNC, &err);
	if (err < 0) {
		printf("Couldn't create a kernel");
		printf("\n%d\n", err);
		exit(1);
	};
	err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &input_buffer);
	err |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &res_buffer);
	if (err < 0) {
		printf("Couldn't create a kernel argument");
		printf("\n%d\n", err);
		exit(1);
	}
	err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &global_size, 
		 &local_size, 0, NULL, NULL); 
	if (err < 0) {
		printf("Couldn't enqueue the kernel: %d", err);
		printf("\n%d\n", err);
		exit(1);
	}
	err = clEnqueueReadBuffer(queue, res_buffer, CL_TRUE, 0, 
		 sizeof(int) * 1200 * 600, addr, 0, NULL, NULL);
	if (err < 0 ) {
		printf("Couldn't read the buffer");
		printf("\n%d\n", err);
		exit(1);
	}

	mlx_put_image_to_window(mlx, win, img, 0, 0);
	mlx_loop(mlx);
	clReleaseKernel(kernel);
	clReleaseMemObject(res_buffer);
	clReleaseMemObject(input_buffer);
	clReleaseCommandQueue(queue);
	clReleaseProgram(program);
	clReleaseContext(context);
	return 0;
}

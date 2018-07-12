/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_numbers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atikhono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 15:32:35 by atikhono          #+#    #+#             */
/*   Updated: 2018/07/12 14:46:32 by atikhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define PROGRAM_FILE "add_numbers.cl"
#define KERNEL_FUNC "add_number"

#include "main.h"

#ifdef MAC
#include <OpenCL/cl.h>
#else
#include <CL/cl.h>
#endif

/* Find a GPU or CPU associated with the first available platform       */
cl_device_id	create_device()
{
	cl_platform_id	platform;
	cl_device_id	dev;
	int				err;

	/* Identify a platform */
	err = clGetPlatformIDs(1, &platform, NULL);
	if (err < 0) {
		perror("Couldn't identify a platform");
		exit(1);
	} 
	/* Access a device */
	err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, 1, &dev, NULL);
	if (err == CL_DEVICE_NOT_FOUND) {
		err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &dev, NULL);
	}
	if (err < 0) {
		perror("Couldn't access any devices");
		exit(1);
	}
	return dev;
}

/* Create program from a file and compile it */
cl_program build_program(cl_context ctx, cl_device_id dev, const char* filename) {
	cl_program	program;
	FILE		*program_handle;
	char		*program_buffer, *program_log;
	size_t		program_size, log_size;
	int			err;

	/* Read program file and place content into buffer */
	program_handle = fopen(filename, "r");
	if (program_handle == NULL) {
		perror("Couldn't find the program file");
		exit(1);
	}
	fseek(program_handle, 0, SEEK_END);
	program_size = ftell(program_handle);
	rewind(program_handle);
	program_buffer = (char*)malloc(program_size + 1);
	program_buffer[program_size] = '\0';
	fread(program_buffer, sizeof(char), program_size, program_handle);
	fclose(program_handle);
	/* Create program from file */
	program = clCreateProgramWithSource(ctx, 1, 
		(const char**)&program_buffer, &program_size, &err);
	if (err < 0) {
		perror("Couldn't create the program");
		exit(1);
	}
	free(program_buffer);
	/* Build program */
	err = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
	if (err < 0) {
		/* Find size of log and print to std output */
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

int main() {
	/* OpenCL structures */
	cl_device_id		device;
	cl_context			context;
	cl_program			program;
	cl_kernel			kernel;
	cl_command_queue	queue;
	size_t				local_size, global_size;
	/* Data and buffers */
	t_data				data;
	int					res[1200 * 600];
	int					err = 0;
	cl_mem				input_buffer, res_buffer;
	cl_int				num_groups;

	/* Initialize data */
	data.width = 1200;
	data.height = 600;
	data.power = 2.0;
	data.scale = 0.5;
	data.off_x = 0.0;
	data.off_y = 0.0;
	data.sign_x = '+';
	data.sign_y = '+';
	data.abs_x = 'n';
	data.abs_y = 'n';
	/* Create device and context */
	device = create_device();
	context = clCreateContext(NULL, 1, &device, NULL, NULL, &err);
	if (err < 0) {
		perror("Couldn't create a context");
		exit(1);	
	}
	/* Build program */
	program = build_program(context, device, PROGRAM_FILE);
	/* Create data buffer */
	global_size = 8;
	local_size = 4;
	num_groups = global_size/local_size;
	input_buffer = clCreateBuffer(context, CL_MEM_READ_ONLY |
		 CL_MEM_COPY_HOST_PTR, sizeof(t_data), &data, &err);
	res_buffer = clCreateBuffer(context, CL_MEM_READ_WRITE |
		 CL_MEM_COPY_HOST_PTR, sizeof(int[1200*600]), &res, &err);
	if (err < 0) {
		perror("Couldn't create a buffer");
		exit(1);	
	};
	/* Create a command queue */
	queue = clCreateCommandQueue(context, device, 0, &err);
	if (err < 0) {
		perror("Couldn't create a command queue");
		exit(1);	
	};
	/* Create a kernel */
	kernel = clCreateKernel(program, KERNEL_FUNC, &err);
	if (err < 0) {
		perror("Couldn't create a kernel");
		exit(1);
	};
	/* Create kernel arguments */
	err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &input_buffer);
	err |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &res_buffer);
	if (err < 0) {
		perror("Couldn't create a kernel argument");
		exit(1);
	}
	/* Enqueue kernel */
	err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &global_size, 
		 &local_size, 0, NULL, NULL); 
	if (err < 0) {
		perror("Couldn't enqueue the kernel");
		exit(1);
	}
	/* Read the kernel's output */
	err = clEnqueueReadBuffer(queue, res_buffer, CL_TRUE, 0, 
		 sizeof(res), res, 0, NULL, NULL);
	if (err < 0) {
		printf("%d", err);	
		perror("Couldn't read the buffer");
		exit(1);
	}
	/* Check result */
	int i;
	 	i = 0;
	while (i < 1200 * 600)
	{
		printf("%d  ", res[i]);
		if (i % 1200 == 0)
			printf("\n");
		++i;
	}
	printf("%d\n\n", res[0]);
	/* Deallocate resources */
	clReleaseKernel(kernel);
	clReleaseMemObject(res_buffer);
	clReleaseMemObject(input_buffer);
	clReleaseCommandQueue(queue);
	clReleaseProgram(program);
	clReleaseContext(context);
	return 0;
}

#define PROGRAM_FILE "add_numbers.cl"
#define KERNEL_FUNC "add_number"
#include "main.h"

/* Find a GPU or CPU associated with the first available platform       */
cl_device_id	create_device()
{
	cl_platform_id	platform;
	cl_device_id	dev;
	int				err;

	err = clGetPlatformIDs(1, &platform, NULL);
	if (err < 0) {
		perror("Couldn't identify a platform");
		exit(1);
	} 
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

cl_program build_program(cl_context ctx, cl_device_id dev, const char* filename)
{
	cl_program	program;
	FILE		*program_handle;
	char		*program_buffer, *program_log;
	size_t		program_size, log_size;
	int			err;

	program_handle = fopen(filename, "r");
	if (program_handle == NULL)
	{
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
	program = clCreateProgramWithSource(ctx, 1, 
		(const char**)&program_buffer, &program_size, &err);
	if (err < 0)
	{
		perror("Couldn't create the program");
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

void	start_kernel(t_all *a)
{
	t_kernel			k;
	cl_device_id		device;
	cl_context			context;
	cl_program			program;
	int					err;

	a->k = &k;
	device = create_device();
	context = clCreateContext(NULL, 1, &device, NULL, NULL, &err);
	if (err < 0)
	{
		perror("Couldn't create a context");
		exit(1);	
	}
	program = build_program(context, device, PROGRAM_FILE);
	a->k->global_size = 256;
	a->k->local_size = 256;
	a->k->input_buffer = clCreateBuffer(context, CL_MEM_READ_ONLY |
		 CL_MEM_COPY_HOST_PTR, sizeof(t_data), a->d, &err);
	a->k->res_buffer = clCreateBuffer(context, CL_MEM_READ_WRITE |
		 CL_MEM_COPY_HOST_PTR, sizeof(int) * 256, a->d->addr, &err);
	if (err < 0)
	{
		perror("Couldn't create a buffer");
		exit(1);	
	}
	a->k->queue = clCreateCommandQueue(context, device, 0, &err);
	if (err < 0)
	{
		perror("Couldn't create a command queue");
		exit(1);	
	}
	a->k->kernel = clCreateKernel(program, KERNEL_FUNC, &err);
	if (err < 0)
	{
		perror("Couldn't create a kernel");
		exit(1);
	}
}

void	run_kernel(t_all *a)
{
	int		err;

	err = clSetKernelArg(a->k->kernel, 0, sizeof(cl_mem), &a->k->input_buffer);
	err |= clSetKernelArg(a->k->kernel, 1, sizeof(cl_mem), &a->k->res_buffer);
	if (err < 0)
	{
		perror("Couldn't create a kernel argument");
		exit(1);
	}
	printf("lol kek u have seg\n");


	err = clEnqueueNDRangeKernel(a->k->queue, a->k->kernel, 1, NULL,\
		   	(size_t *) (a->k->global_size), NULL, 0, NULL, NULL); 
	
	
	printf("lol kek u have seg\n");
	if (err < 0)
	{
		perror("Couldn't enqueue the kernel");
		exit(1);
	}
	err = clEnqueueReadBuffer(a->k->queue, a->k->res_buffer, 1, 0, 
		 sizeof(a->d->addr), a->d->addr, 0, NULL, NULL);
	if (err < 0)
	{
		perror("Couldn't read the buffer");
		exit(1);
	}
	mlx_put_image_to_window(a->p->mlx, a->p->win, a->p->img, 0, 0);
}
/*	
 *	Deallocate resources 
 *	clReleaseKernel(kernel);
 *	clReleaseMemObject(res_buffer);
 *	clReleaseMemObject(input_buffer);
 *	clReleaseCommandQueue(queue);
 *	clReleaseProgram(program);
 *	clReleaseContext(context);
 */

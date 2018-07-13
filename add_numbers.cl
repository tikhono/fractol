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

__kernel void add_number(__global t_data *input,
						 __global int *output)
{
	int		n;
	int		id;
	double	x;
	double	y;
	double	a;
	double	b;
	double	d;
	double	phi;
	double	pii;

	id = get_global_id(0);
	if (id < (input->height * input->width))
	{
		d = 2.0 * input->scale / input->width;
		y = -input->scale * input->height / input->width + input->off_x + (id / input->width) * d;
		x = -input->scale + input->off_x + (id % input->width) * d;
		a = x;
		b = y;
		n = 0;
		while (n <= 1000)
		{
			a = input->abs_x == 'y' ? fabs(a) : a;
			b = input->abs_y == 'y' ? fabs(b) : b;
			a = input->sign_x == '+' ? a : -a;
			b = input->sign_y == '+' ? b : -b;
			if (a != 0.0 || b != 0.0)
			{
				pii = b < 0.0 ? - M_PI_F : M_PI_F;
				if (a > 0.0)
					pii = 0.0;
				if (a == 0.0)
					pii /= 2.0;
				phi = (atan(b / a) * (a == 0.0 ? 0.0 : 1.0) + pii) * input->power;
				a = pow(sqrt(a * a + b * b), input->power) * cos(phi);
				b = pow(sqrt(a * a + b * b), input->power) * sin(phi);
			}
			a += x;//or julia point
			b += y;	
			if (a * a + b * b > 4.0)
				break;
			++n;
		}
		if (n == 1000)
			output[id] = 0;
		else
			output[id] = 0xFFFFFF / 1000 * n;
	}
}

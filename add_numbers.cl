typedef struct	s_data
{
	int			width;
	int			height;
	double		power;
	double		scale;
	double		off_x;
	double		off_y;
	char		sign_x;
	char		sign_y;
	char		abs_x;
	char		abs_y;
}				t_data;

__kernel void add_number(t_data input, __global int *output)
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
	double	z;

	id = get_global_id(0);
	d = 2.0 * input.scale / input.width;
	y = -input.scale * input.height / input.width + input.off_y + (id / input.width) * d;
	x = -input.scale + input.off_x + (id % input.width) * d;
	a = x;
	b = y;
	n = 0;
	while (n < 100)
	{
		a = input.abs_x == 'y' ? fabs(a) : a;
		b = input.abs_y == 'y' ? fabs(b) : b;
		a = input.sign_x == '+' ? a : -a;
		b = input.sign_y == '+' ? b : -b;
		if (a != 0.0 || b != 0.0)
		{
			pii = b < 0.0 ? -M_PI_F : M_PI_F;
			if (a > 0.0)
				pii = 0.0;
			if (a == 0.0)
				pii /= 2.0;
			z = pow(sqrt(a * a + b * b), input.power);
			phi = (atan2(b, a) * (a == 0.0 ? 0.0 : 1.0) + pii) * input.power;
			a = z * cos(phi);
			b = z * sin(phi);
		}
		a += x;//or julia point
		b += y;	
		if (a * a + b * b > 4.0)
			break;
		++n;
	}
	if (n == 100)
		output[id] = 0;
	else
		output[id] = 0xFFFFFF / 100 * n;
}

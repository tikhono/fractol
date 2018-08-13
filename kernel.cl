typedef struct	s_data
{
	int			width;
	int			height;
	int			m_pos_x;
	int			m_pos_y;
	double		power;
	double		scale;
	double		off_x;
	double		off_y;
	char		sign_x;
	char		sign_y;
	char		abs_x;
	char		abs_y;
	char		con;
	char		state;
}				t_data;

__kernel void add_number(t_data input, __global int *output)
{
	int		n;
	int		lim;
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
	x = -input.scale + input.off_x + (id % input.width) * d;
	y = -input.scale * input.height / input.width + input.off_y + (id / input.width) * d;
	a = x;
	b = y;
	if (input.con == 'y')
	{
		if (input.state == 'y')
		{
			x = -input.scale + (input.off_x + input.m_pos_x) * d;
			y = -input.scale * input.height / input.width + (input.off_y + input.m_pos_y) * d;
		}
		else
		{
			x = input.off_x * d + (input.m_pos_x * 4.0  / input.width -  2.0);	
			y = input.off_y * d + (input.m_pos_y * 4.0  / input.height -  2.0);
		}
	}
	n = 0;
	lim = 50;
	while (n < lim)
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
			phi = (atan(b / a) * (a == 0.0 ? 0.0 : 1.0) + pii) * input.power;
			a = z * cos(phi);
			b = z * sin(phi);
		}
		a += x;
		b += y;	
		if (a * a + b * b > 4.0)
			break;
		++n;
	}
	if (n == lim)
		output[id] = 0;
	else
		output[id] = 0xFFFFFF / lim * n;
}

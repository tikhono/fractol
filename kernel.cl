typedef struct	s_data
{
	int			width;
	int			height;
	int			m_pos_x;
	int			m_pos_y;
	int			lim;
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
			x = input.off_x * d + (input.m_pos_x * 4.0  / input.width - 2.0);	
			y = input.off_y * d + (input.m_pos_y * 4.0  / input.height - 2.0);
		}
	}
	n = 0;
	while (n < input.lim)
	{
		a = input.abs_x == 'y' ? fabs(a) : a;
		b = input.abs_y == 'y' ? fabs(b) : b;
		a = input.sign_x == '+' ? a : -a;
		b = input.sign_y == '+' ? b : -b;
		z = pow(sqrt(a * a + b * b), input.power);
		phi = atan2(b, a) * input.power;
		a = z * cos(phi);
		b = z * sin(phi);
		a += x;
		b += y;	
		if (a * a + b * b > 4.0)
			break;
		++n;
	}
	if (n == input.lim)
		output[id] = 0;
	else
		output[id] = 0x0F0F0F * 0x0F0F0F / input.lim  * (n + 1);
}

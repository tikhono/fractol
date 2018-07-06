#include <math.h>
#include <stdio.h>
#include <complex.h>

void    complex_pow(double power, double *x, double *y)
{
	double	z;
	double	res_z;
	double	phi;
	double	pi;

	if (*x != 0.0 || *y != 0.0)
	{
		if (*x == 0.0)
			z = fabs(*y);
		else if (*y == 0.0)
			z = fabs(*x);
		else
			z = sqrt(*x * *x + *y * *y);
		pi = *y < 0.0 ? - M_PI : M_PI;
		if (*x > 0.0)
			pi = 0.0;
		if (*x == 0.0)
			pi /= 2.0;
		phi = atan(*y / *x) * (*x == 0.0 ? 0.0 : 1.0) + pi;
		res_z = pow(z, power);
		*x = res_z * cos(power * phi);
		*y = res_z * sin(power * phi);
		//printf("z: %f\nphi_x: %f\nphi_y: %f\nres_z: %f\nx: %f\ny: %f\n\n", z, phi, phi, res_z, *x, *y);
	}
}

int	main(void)
{
	double	x;
	double	y;
	double	a;
	double	b;
	double complex	lol;

	x = -10.0;
	while (x <= 10.0)
	{
		y = -10.0;
		while (y <= 10.0)
		{
			a = x;
			b = y;
			complex_pow(3.3, &a, &b);
			lol = cpow(x+y*I, 3.3);
			if (creal(lol) != a || cimag(lol) != b)
				printf("%f : %f and %f : %f\n", a, creal(lol), b, cimag(lol));
			y += 0.01;
		}
		x += 0.01;
	}

	return (0);
}

#ifndef MAIN_H
# define MAIN_H
# include <fcntl.h>
# include <mlx.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <unistd.h>
# include <assert.h>
# include <CoreServices/CoreServices.h>
# include <mach/mach.h>
# include <mach/mach_time.h>
# include <unistd.h>

typedef struct	s_data
{
	int			width;
	int			height;
	double		power;//try float later
	double		scale;
	double		off_x;
	double		off_y;
	char		sign_x;
	char		sign_y;
	char		abs_x;
	char		abs_y;
}				t_data;

#endif

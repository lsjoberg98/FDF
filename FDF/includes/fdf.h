/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsjoberg <lsjoberg@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 14:31:24 by lsjoberg          #+#    #+#             */
/*   Updated: 2020/02/22 19:46:51 by lsjoberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <time.h>

# include "mlx.h"
# include "keys.h"
# include "libft.h"

/*
**	Macros for the max value of x coordinate
*/

# define MAX_X			(10)
# define MAX_ZOOM		(5)
# define MAGIC_ZOOM		(2)
# define WIN_WIDTH		(1280)
# define WIN_HEIGHT		(720)
# define TITLE(file)	(ft_strjoin("fdf - ", file))

/*
**	Required minilibx arguments
*/

typedef	struct	s_mlx
{
	void	*init;
	void	*win;
	void	*img;
}				t_mlx;

/*
**	Variables to be used for creation of the image
*/

typedef struct	s_image
{
	char	*data;
	int		size;
	int		storepxc;
	int		pxc;
}				t_image;

/*
**	Values used to manipulate the fdf map
*/

typedef	struct	s_map
{
	int		**values;
	int		width;
	int		height;
	int		coordinate_y;
	int		coordinate_z;
	int		y0;
	int		y1;
	int		z0;
	int		z1;
	int		zoom;
	int		isometric;
	double	x_value;
	double	angle_y;
	double	angle_z;
}				t_map;

/*
**	Define the color, rgb value (24-bits)
*/

typedef	struct	s_color
{
	int		red;
	int		green;
	int		blue;
}				t_color;

/*
**	Nested structure that calls other structures
*/

typedef	struct	s_fdf
{
	t_mlx	mlx;
	t_map	map;
	t_image	image;
	t_color	color;
}				t_fdf;

void			fdf_read(char *av, t_fdf *fdf);
int				fdf_draw(t_fdf *fdf);
char			*remove_extension(char *filename);
void			errorkill(char *reason, int ret);
char			*program_name(char const *av0);

#endif

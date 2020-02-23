/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsjoberg <lsjoberg@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 14:26:53 by lsjoberg          #+#    #+#             */
/*   Updated: 2020/02/22 18:27:12 by lsjoberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/*
**	Display how to use controls for fdf.
*/

static void	fdf_usage(char *av0)
{
	ft_putstr("Usage:\t");
	ft_putstr(program_name(av0));
	ft_putstr("\n");
	ft_putstr("Controls:\n");
	ft_putstr("\t\t[Esc]        -> Exit.\n");
	ft_putstr("\t\t[R]          -> Reset.\n");
	ft_putstr("\t\t[C]          -> Colorize.\n");
	ft_putstr("\t\t[Q][E]       -> Zoom in/out.\n");
	ft_putstr("\t\t[Z][X]       -> Spikes!\n");
	ft_putstr("\t\t[Space]      -> Camera. (isometric <-> plain)\n");
	ft_putstr("\t\t[W][A][S][D] -> Move.\n");
}

/*
**	Resets map to initial values.
*/

static void	reset_map(t_fdf *fdf)
{
	fdf->map.coordinate_z = 0;
	fdf->map.coordinate_y = 0;
	fdf->map.x_value = 1.00;
	fdf->map.angle_y = cos(M_PI / 3);
	fdf->map.angle_z = fdf->map.angle_y * sin(M_PI / 6);
	fdf->map.zoom = ceil((fdf->map.width > fdf->map.height)) \
		? (WIN_WIDTH / fdf->map.width) + MAGIC_ZOOM \
		: (WIN_HEIGHT / fdf->map.height) + MAGIC_ZOOM;
	fdf->map.isometric = 1;
	fdf->color.red = 0x4F;
	fdf->color.green = 0x4F;
	fdf->color.blue = 0x4F;
}

/*
**	Colorize the map with random color.
*/

static void	random_color(t_fdf *fdf)
{
	fdf->color.red = (rand() % 0x7F);
	fdf->color.green = (rand() % 0x7F);
	fdf->color.blue = (rand() % 0x7F);
}

/*
**	Assign a key code (defined in includes/keys.h) to a specific task
*/

static int	fdf_keys(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_ESCAPE)
		exit(0);
	else if (keycode == KEY_ANSI_R)
		reset_map(fdf);
	else if (keycode == KEY_ANSI_C)
		random_color(fdf);
	else if (keycode == KEY_ANSI_W || keycode == KEY_UPARROW)
		fdf->map.coordinate_z -= 1;
	else if (keycode == KEY_ANSI_S || keycode == KEY_DOWNARROW)
		fdf->map.coordinate_z += 1;
	else if (keycode == KEY_ANSI_D || keycode == KEY_RIGHTARROW)
		fdf->map.coordinate_y -= 1;
	else if (keycode == KEY_ANSI_A || keycode == KEY_LEFTARROW)
		fdf->map.coordinate_y += 1;
	else if (keycode == KEY_SPACE)
		fdf->map.angle_z *= (fdf->map.isometric++ % 2) ? 0.2 : 5;
	else if (keycode == KEY_ANSI_Q)
		fdf->map.zoom += 1;
	else if ((keycode == KEY_ANSI_E) && (fdf->map.zoom > MAX_ZOOM))
		fdf->map.zoom -= 1;
	else if ((keycode == KEY_ANSI_Z) && (fdf->map.x_value < MAX_X))
		fdf->map.x_value += 0.25;
	else if ((keycode == KEY_ANSI_X) && (fdf->map.x_value > -MAX_X))
		fdf->map.x_value -= 0.25;
	return (0);
}

/*
**	Creates the fdf structure and makes it possible to draw on the screen.
**	Also getting the keyboard inputs.
**	Didn't use mlx_key_hook, because I wanted to press and hold the keys.
*/

int			main(int ac, char *av[])
{
	t_fdf	*fdf;

	if (ac == 2)
	{
		if (!(fdf = (t_fdf *)malloc(sizeof(t_fdf))))
			errorkill("Memory Allocation failed!", 3);
		fdf_read(av[1], fdf);
		reset_map(fdf);
		fdf->mlx.init = mlx_init();
		fdf->mlx.win = mlx_new_window(fdf->mlx.init, WIN_WIDTH, WIN_HEIGHT, \
			TITLE(remove_extension(av[1])));
		mlx_hook(fdf->mlx.win, 2, 3, fdf_keys, fdf);
		mlx_loop_hook(fdf->mlx.init, fdf_draw, fdf);
		mlx_loop(fdf->mlx.init);
	}
	else
		fdf_usage(av[0]);
	return (0);
}

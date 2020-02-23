/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsjoberg <lsjoberg@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 15:41:30 by lsjoberg          #+#    #+#             */
/*   Updated: 2020/02/22 15:50:33 by lsjoberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/*
**	Gets the number values in each line from the fdf file.
**	if there is an invalid character in the line, print an error message
*/

static int	count_values(char *line)
{
	int		len;

	len = 0;
	while (*line)
	{
		if (ft_isdigit(*line))
		{
			len += 1;
			while (ft_isdigit(*line))
				line += 1;
		}
		else if (*line != ' ' && *line != '-')
			errorkill("Invalid characters or Error reading", 5);
		line += 1;
	}
	return (len);
}

/*
**	Count and returns the number of lines (rows) that the file has.
**	This is used to allocate the correct memory size for the array.
**	If the values from every line is not equal to the other lines,
** there is an error with the fdf file.
*/

static int	count_lines(t_fdf *fdf, char *av)
{
	int		fd;
	int		len;
	int		rows;
	int		cols;
	char	*line;

	if ((fd = open(av, O_RDONLY)) < 0)
		errorkill("Error opening file! :(", 1);
	rows = 0;
	cols = 0;
	while (get_next_line(fd, &line) == 1)
	{
		if (*line == '\0')
			break ;
		if ((len = count_values(line)) > cols)
			cols = len;
		(cols == len) ? rows += 1 : errorkill("Not a valid file!", 4);
		free(line);
	}
	if (close(fd) < 0)
		errorkill("Error closing file!?", 2);
	if (!(fdf->map.width = cols))
		errorkill("Not a valid file!", 4);
	return (rows);
}

/*
**	Gets and stores the values from the file into a two dimensional array,
**	by atoi-ing everything
*/

static void	get_values(t_fdf *fdf, int y, int z, char *line)
{
	int		i;
	char	**split;

	if ((split = ft_strsplit(line, ' ')))
	{
		i = 0;
		while (split[i] && (y != fdf->map.width))
		{
			fdf->map.values[z][y] = ft_atoi(split[i++]);
			y += 1;
		}
		free(split);
	}
}

/*
**	Read from the file, allocates in memory the correct size of the hight
**	and width of the map.
*/

void		fdf_read(char *av, t_fdf *fdf)
{
	int		y;
	int		z;
	int		fd;
	char	*line;

	y = 0;
	z = 0;
	fdf->map.height = count_lines(fdf, av);
	if ((fd = open(av, O_RDONLY)) < 0)
		errorkill("Error opening file! :(", 1);
	if (!(fdf->map.values = (int **)malloc(sizeof(int *) * fdf->map.height)))
		errorkill("Memory Allocation failed!", 3);
	while (get_next_line(fd, &line) == 1 && z != fdf->map.height)
	{
		if (!(fdf->map.values[z] = (int *)malloc(sizeof(int) * fdf->map.width)))
			errorkill("Memory Allocation failed!", 3);
		get_values(fdf, y, z, line);
		y = 0;
		z += 1;
		free(line);
	}
	if (close(fd) < 0)
		errorkill("Error closing file!", 2);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsjoberg <lsjoberg@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:56:50 by lsjoberg          #+#    #+#             */
/*   Updated: 2020/02/22 18:25:54 by lsjoberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

/*
**	Outputs the string msg to the standard output followed by an exit of the
**	program with a custom return value
*/

void	errorkill(char *reason, int ret)
{
	ft_putendl(reason);
	exit(ret);
}

/*
**	Removes the extension (type) of a filename, returning its basename
*/

char	*remove_extension(char *filename)
{
	char	*base_name;
	char	*dot;
	char	*sep;

	if (!filename)
		return (NULL);
	if (!(base_name = (char *)malloc(sizeof(char) * ft_strlen(filename) + 1)))
		return (NULL);
	ft_strcpy(base_name, filename);
	if ((dot = ft_strrchr(base_name, '.')))
	{
		if ((sep = ft_strrchr(base_name, '/')))
			(sep < dot) ? *dot = '\0' : *dot;
		else
			*dot = '\0';
	}
	return (base_name);
}

/*
**	Gets the name of the program (av[0]).
*/

char	*program_name(char const *av0)
{
	char	*name;

	name = (char *)av0;
	while (*name && *name != '/')
		name += 1;
	if (!name)
		return ((char *)av0);
	return (name + 1);
}

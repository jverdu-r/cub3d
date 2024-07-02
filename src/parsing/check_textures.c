/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <jverdu-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:55:23 by jverdu-r          #+#    #+#             */
/*   Updated: 2024/06/25 18:09:19 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	check_valig_rgb(int *rgb)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (rgb[i] < 0 || rgb[i] > 255)
			return (err_msg(rgb[i], ERR_TEX_RGB_VAL, FAILURE));
		i++;
	}
	return (SUCCESS);
}

static unsigned long	convert_rgb_to_hex(int *rgb_tab)
{
	unsigned long	result;
	int				r;
	int				g;
	int				b;

	r = rgb_tab[0];
	g = rgb_tab[1];
	b = rgb_tab[2];
	result = ((r & 0xff) << 16) + ((g & 0xff) << 8) + ((b & 0xff));
	return (result);
}

int	check_textures_validity(t_data *data, t_texinfo *textures)
{
	if (!textures->north || !textures->south || !textures->west \
		|| !textures->east)
		return (err_msg(data->mapinfo.path, ERR_TEX_MISSING, FAILURE));
	if (!textures->floor || !textures->ceiling)
		return (err_msg(data->mapinfo.path, ERR_COLOR_MISSING, FAILURE));
	if (check_file(textures->north, false) == FAILURE \
		|| check_file(textures->south, false) == FAILURE \
		|| check_file(textures->west, false) == FAILURE \
		|| check_file(textures->east, false) == FAILURE \
		|| check_valid_rgb(textures->floor) == FAILURE \
		|| check_valid_rgb(textures->ceiling) == FAILURE)
		return (FAILURE);
	textures->hex_floor = convert_rgb_to_hex(textures->floor);
	textures->hex_ceiling =  convert_rgb_to_hex(textures->ceiling);
	return (SUCCESS);
}

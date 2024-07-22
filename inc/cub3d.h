/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <jverdu-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:50:25 by jverdu-r          #+#    #+#             */
/*   Updated: 2024/07/22 12:03:38 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <fcntl.h>
# include <math.h>
# include <errno.h>
# include "../mlx/mlx.h"
# include "libft/libft.h"
# include "structs.h"
# include "colors.h"

# ifndef DEBUG_MSG
#  define DEBUG_MSG 0
# endif

# ifndef MMAP_DEBUG_MSG
#  define MMAP_DEBUG_MSG 0
# endif

# ifndef O_DIRECTORY
#  define O_DIRECTORY 00200000
# endif

# ifndef BONUS
#  define BONUS 1
# endif

# define WIN_WIDTH 1200
# define WIN_HEIGHT 920
# define TEX_SIZE 64
# define MOVESPEED 0.125
# define ROTSPEED 0.15
# define DIST_EDGE_MOUSE_WRAP 20

# define MMAP_PIXEL_SIZE 128
# define MMAP_VIEW_DIST 4
# define MMAP_COLOR_PLAYER 0x00FF00
# define MMAP_COLOR_WALL 0x808080
# define MMAP_COLOR_FLOOR 0xE6E6E6
# define MMAP_COLOR_SPACE 0x404040

# define ERR_USAGE "usage: ./cub3d <path/to/map.cub>"
# define ERR_FILE_NOT_CUB "Not a .cub file"
# define ERR_FILE_NOT_XPM "Not an .xpm file"
# define ERR_FILE_IS_DIR "Is a directory"
# define ERR_FLOOR_CEILING "Invalid floor/ceiling RGB color(s)"
# define ERR_COLOR_FLOOR "Invalid floor RGB color"
# define ERR_COLOR_CEILING "Invalid ceiling RGB color"
# define ERR_INVALID_MAP "Map description is either wrong or incomplete"
# define ERR_INV_LETTER "Invalid character in map"
# define ERR_NUM_PLAYER "Map has more than one player"
# define ERR_TEX_RGB_VAL "Invalid RGB value (min: 0, max: 255)"
# define ERR_TEX_MISSING "Missing texture(s)"
# define ERR_TEX_INVALID "Invalid texture(s)"
# define ERR_COLOR_MISSING "Missing color(s)"
# define ERR_MAP_MISSING "Missing map"
# define ERR_MAP_TOO_SMALL "Map is not at least 3 lines high"
# define ERR_MAP_NO_WALLS "Map is not surrounded by walls"
# define ERR_MAP_LAST "Map is not the last element in file"
# define ERR_PLAYER_POS "Invalid player position"
# define ERR_PLAYER_DIR "Map has no player position (expected N, S, E or W)"
# define ERR_MALLOC "Could not allocate memory"
# define ERR_MLX_START "Could not start mlx"
# define ERR_MLX_WIN "Could not create mlx window"
# define ERR_MLX_IMG "Could not create mlx image"

void	init_data(t_data *data);
void	init_img_clean(t_img *img);
void	init_ray(t_ray *ray);

/* init/init_mlx.c */
void	init_mlx(t_data *data);
void	init_img(t_data *data, t_img *image, int width, int height);
void	init_texture_img(t_data *data, t_img *image, char *path);

/* init/init_textures.c */
void	init_textures(t_data *data);
void	init_texinfo(t_texinfo *textures);

/* parsing/check_args.c */
int		check_file(char *arg, bool cub);

/* parsing/parse_data.c */
void	parse_data(char *path, t_data *data);

/* parsing/get_file_data.c */
int		get_file_data(t_data *data, char **map);

/* parsing/fill_color_textures.c */
int		fill_color_textures(t_data *data, t_texinfo *textures,
			char *line, int j);

/* parsing/create_game_map.c */
int		create_map(t_data *data, char **map, int i);

/* parsing/check_textures.c */
int		check_textures_validity(t_data *data, t_texinfo *textures);

/* parsing/check_map.c */
int		check_map_validity(t_data *data, char **map_tab);

/* parsing/check_map_borders.c */
int		check_map_sides(t_mapinfo *map, char **map_tab);

/* parsing/parsing_utils.c */
int		is_a_white_space(char c);
size_t	find_biggest_len(t_mapinfo *map, int i);

/* render/render.c */
int		render(t_data *data);
void	render_images(t_data *data);

/* render/raycasting.c */
int		raycasting(t_player *player, t_data *data);

/* render/texture.c */
void	init_texture_pixels(t_data *data);
void	update_texture_pixels(t_data *data, t_texinfo *tex, t_ray *ray, int x);

/* render/image_utils.c */
void	set_image_pixel(t_img *image, int x, int y, int color);

/* render/minimap_render.c */
void	render_minimap(t_data *data);

/* render/minimap_image.c */
void	render_minimap_image(t_data *data, t_minimap *minimap);

/* movement/input_handler.c */
void	listen_for_input(t_data *data);

/* movement/player_dir.c */
void	init_player_direction(t_data *data);

/* movement/player_pos.c */
int		validate_move(t_data *data, double new_x, double new_y);

/* movement/player_move.c */
int		move_player(t_data *data);

/* movement/player_rotate.c */
int		rotate_player(t_data *data, double rotdir);

/* exit/exit.c */
void	clean_exit(t_data *data, int code);
int		quit_cub3d(t_data *data);

/* exit/free_data.c */
void	free_tab(void **tab);
int		free_data(t_data *data);

/* error.c */
int		err_msg(char *detail, char *str, int code);
int		err_msg_val(int detail, char *str, int code);

/* debug/debug.c */
void	debug_display_data(t_data *data);
void	debug_display_minimap(t_minimap *minimap);
void	debug_display_player(t_data *data);
void	debug_print_char_tab(char **tab);
#endif

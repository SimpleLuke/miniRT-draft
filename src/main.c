/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:43:24 by llai              #+#    #+#             */
/*   Updated: 2024/04/20 14:10:46 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	main(void)
{
	// void	*mlx;
	// void	*mlx_win;
	// t_data	img;
	t_data	data;
	t_win	win;

	data.base_image.win = new_window(1920, 1080, "miniRT");
	win = data.base_image.win;
	data.base_image = new_img(1920, 1080, data.base_image.win);
	put_pixel_img(data.base_image, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(data.base_image.win.mlx,
		data.base_image.win.win_ptr, data.base_image.img_ptr, 0, 0);
	mlx_hook(win.win_ptr, 2, 1L << 0, esc_close_win, &data);
	mlx_hook(win.win_ptr, 17, 0, cross_close_win, &data);
	mlx_loop(data. base_image.win.mlx);
}

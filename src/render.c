/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:47:31 by llai              #+#    #+#             */
/*   Updated: 2024/04/26 15:05:45 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	clear_image(t_data *data)
{
	for (int x = (-1 * WIDTH / 2); x <= WIDTH / 2; x++)
	{
		for (int y = (-1 * HEIGHT / 2); y <= HEIGHT / 2; y++)
		{
			put_pixel(data->base_image, x, y, BG_COLOR);
			// put_pixel(data.base_image, x, y, 0xFFFFFFFF);
		}
	}

	mlx_put_image_to_window(data->base_image.win.mlx,
		data->base_image.win.win_ptr, data->base_image.img_ptr, 0, 0);

}

void	render(t_data *data)
{
	for (int x = (-1 * WIDTH / 2); x <= WIDTH / 2; x++)
	{
		for (int y = (-1 * HEIGHT / 2); y <= HEIGHT / 2; y++)
		{
			// data.D = scalar_mul_vec3(data.camera.rotation, canvas_to_viewport(x, y, &data));
			data->D = canvas_to_viewport(x, y, data);
			int		color = traceray(data, data->camera.position, data->D, 1, INFINITY, 3);
			// int		color = traceray(&data, 1, INFINITY, 3);
			put_pixel(data->base_image, x, y, color);
			// put_pixel(data.base_image, x, y, 0xFFFFFFFF);
		}
	}

	mlx_put_image_to_window(data->base_image.win.mlx,
		data->base_image.win.win_ptr, data->base_image.img_ptr, 0, 0);
}

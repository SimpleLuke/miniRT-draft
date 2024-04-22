/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:43:24 by llai              #+#    #+#             */
/*   Updated: 2024/04/23 00:44:39 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include <math.h>
#include <stdlib.h>

int	main(void)
{
	t_data	data;
	t_win	win;

	data.base_image.win = new_window(WIDTH, HEIGHT, "miniRT");
	win = data.base_image.win;
	data.base_image = new_img(WIDTH, HEIGHT, data.base_image.win);

	data.camera = set_vec3(0, 0, 0);
	data.v_width = 1;
	data.v_height = 1;
	data.distance = 1;

	data.sphere_nb = 4;
	data.spheres = malloc(data.sphere_nb * sizeof(t_sphere));
	data.spheres[0].radius = 1;
	data.spheres[0].center.x = 0;
	data.spheres[0].center.y = -1;
	data.spheres[0].center.z = 3;
	data.spheres[0].color = create_trgb(0, 255, 0, 0);
	data.spheres[1].radius = 1;
	data.spheres[1].center.x = 2;
	data.spheres[1].center.y = 0;
	data.spheres[1].center.z = 4;
	data.spheres[1].color = create_trgb(0, 0, 0, 255);
	data.spheres[2].radius = 1;
	data.spheres[2].center.x = -2;
	data.spheres[2].center.y = 0;
	data.spheres[2].center.z = 4;
	data.spheres[2].color = create_trgb(0, 0, 255, 0);
	data.spheres[3].radius = 5000;
	data.spheres[3].center.x = 0;
	data.spheres[3].center.y = -5001;
	data.spheres[3].center.z = 0;
	data.spheres[3].color = create_trgb(0, 255, 255, 255);

	data.light_nb = 3;
	data.lights = malloc(data.light_nb * sizeof(t_light));
	data.lights[0].type = AMBIENT;
	data.lights[0].intensity = 0.2;
	data.lights[1].type = POINT;
	data.lights[1].intensity = 0.6;
	data.lights[1].position.x = 2;
	data.lights[1].position.y = 1;
	data.lights[1].position.z = 0;
	data.lights[2].type = DIRECTIONAL;
	data.lights[2].intensity = 0.2;
	data.lights[2].direction.x = 1;
	data.lights[2].direction.y = 4;
	data.lights[2].direction.z = 4;

	for (int x = (-1 * WIDTH / 2); x <= WIDTH / 2; x++)
	{
		for (int y = (-1 * HEIGHT / 2); y <= HEIGHT / 2; y++)
		{
			data.D = canvas_to_viewport(x, y, &data);
			int		color = traceray(&data, 1, INFINITY);
			put_pixel(data.base_image, x, y, color);
			// put_pixel(data.base_image, x, y, 0xFFFFFFFF);
		}
	}

	mlx_put_image_to_window(data.base_image.win.mlx,
		data.base_image.win.win_ptr, data.base_image.img_ptr, 0, 0);
	mlx_hook(win.win_ptr, 2, 1L << 0, esc_close_win, &data);
	mlx_hook(win.win_ptr, 17, 0, cross_close_win, &data);
	mlx_loop(data. base_image.win.mlx);
}

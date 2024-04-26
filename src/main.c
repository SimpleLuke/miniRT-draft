/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:43:24 by llai              #+#    #+#             */
/*   Updated: 2024/04/26 15:43:21 by llai             ###   ########.fr       */
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

	data.camera.position = set_vec3(0, 0, 0);
	data.camera.rotation = 1;
	data.v_width = 1;
	data.v_height = 1;
	data.distance = 1;

	data.sphere_nb = 4;
	data.spheres = malloc(data.sphere_nb * sizeof(t_sphere));
	data.spheres[0].radius = 1;
	data.spheres[0].center = set_vec3(0, -1, 3);
	data.spheres[0].color = create_trgb(0, 255, 0, 0);
	data.spheres[0].specular = 500; // Shiny
	data.spheres[0].reflective = 0.2; // A bit reflective
	data.spheres[1].radius = 1;
	data.spheres[1].center = set_vec3(2, 0, 4);
	data.spheres[1].color = create_trgb(0, 0, 0, 255);
	data.spheres[1].specular = 500; // Shiny
	data.spheres[1].reflective = 0.3; // A bit more reflective
	data.spheres[2].radius = 1;
	data.spheres[2].center = set_vec3(-2, 0, 4);
	data.spheres[2].color = create_trgb(0, 0, 255, 0);
	data.spheres[2].specular = 10; // Somewhat Shiny
	data.spheres[2].reflective = 0.4; // Even more reflective
	data.spheres[3].radius = 5000;
	data.spheres[3].center = set_vec3(0, -5001, 0);
	data.spheres[3].color = create_trgb(0, 255, 255, 0);
	data.spheres[3].specular = 1000; // Very Shiny
	data.spheres[3].reflective = 0; // Half reflective

	data.light_nb = 3;
	data.lights = malloc(data.light_nb * sizeof(t_light));
	data.lights[0].type = AMBIENT;
	data.lights[0].intensity = 0.2;
	data.lights[1].type = POINT;
	data.lights[1].intensity = 0.6;
	data.lights[1].position = set_vec3(2, 1, 0);
	data.lights[2].type = DIRECTIONAL;
	data.lights[2].intensity = 0.2;
	data.lights[2].direction = set_vec3(1, 4, 4);

	render(&data);

	mlx_hook(win.win_ptr, 2, 1L << 0, esc_close_win, &data);
	// mlx_hook(win.win_ptr, 2, 1L << 0, key_down, &data);
	mlx_key_hook(win.win_ptr, key_down, &data);
	mlx_hook(win.win_ptr, 17, 0, cross_close_win, &data);
	mlx_loop(data. base_image.win.mlx);
}

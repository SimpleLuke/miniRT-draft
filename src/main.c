/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:43:24 by llai              #+#    #+#             */
/*   Updated: 2024/04/22 13:15:39 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include <math.h>
#include <stdlib.h>

t_vec3	canvas_to_viewport(double x, double y, t_data *data)
{
	t_vec3	D;

	D.x = x * data->v_width / WIDTH;
	D.y = y * data->v_height / HEIGHT;
	D.z = data->distance;
	return (D);
}

void	intersect_ray_sphere(t_data *data, t_sphere sphere, double *t1, double *t2)
{
	double	r = sphere.radius;
	t_vec3	co = minus_vec3(data->camera, sphere.center);

	double	a = dot(data->D, data->D);
	double	b = 2 * dot(co, data->D);
	double	c = dot(co, co) - sphere.radius * sphere.radius;

	double	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
	{
		*t1 = INFINITY;
		*t2 = INFINITY;
	}

	*t1 = (-b + sqrt(discriminant)) / (2 * a);
	*t2 = (-b - sqrt(discriminant)) / (2 * a);
}


int	traceray(t_data *data, double t_min, double t_max)
{
	double		closest_t = INFINITY;
	t_sphere	*closest_sphere = NULL;
	double		t1;
	double		t2;

	int	i = -1;
	while (++i < data->sphere_nb)
	{
		intersect_ray_sphere(data, data->spheres[i], &t1, &t2);
		if (t1 >= t_min && t1 <= t_max && t1 < closest_t)
		{
			closest_t = t1;
			closest_sphere = &data->spheres[i];
		}
		if (t2 >= t_min && t2 <= t_max && t2 < closest_t)
		{
			closest_t = t2;
			closest_sphere = &data->spheres[i];
		}
	}
	if (closest_sphere == NULL)
	{
		return (0xFFFFFFFF);
	}
	return (closest_sphere->color);
}

int	main(void)
{
	// void	*mlx;
	// void	*mlx_win;
	// t_data	img;
	t_data	data;
	t_win	win;

	data.base_image.win = new_window(WIDTH, HEIGHT, "miniRT");
	win = data.base_image.win;
	data.base_image = new_img(WIDTH, HEIGHT, data.base_image.win);

	data.camera = set_vec3(0, 0, 0);
	data.v_width = 1;
	data.v_height = 1;
	data.distance = 1;

	data.sphere_nb = 3;
	data.spheres = malloc(3 * sizeof(t_sphere));
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

	for (int x = (-1 * WIDTH / 2); x <= WIDTH / 2; x++)
	{
		for (int y = (-1 * HEIGHT / 2); y <= HEIGHT / 2; y++)
		{
			data.D = canvas_to_viewport(x, y, &data);
			int		color = traceray(&data, 1, INFINITY);
			put_pixel(data.base_image, x, y, color);
		}
	}

	// put_pixel(data.base_image, 0, 0, 0x00FF0000);
	// for (int y = 0; y < 100; y++)
	// 	for (int x = 0; x < 100; x++)
	// 		put_pixel(data.base_image, 0 + x, 0 - y, create_trgb(0, 255, 0, 128));
			// put_pixel_img(data.base_image, 100 + x, 100 + y, 0x00FF0000);
	mlx_put_image_to_window(data.base_image.win.mlx,
		data.base_image.win.win_ptr, data.base_image.img_ptr, 0, 0);
	mlx_hook(win.win_ptr, 2, 1L << 0, esc_close_win, &data);
	mlx_hook(win.win_ptr, 17, 0, cross_close_win, &data);
	mlx_loop(data. base_image.win.mlx);
}

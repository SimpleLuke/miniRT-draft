/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:50:15 by llai              #+#    #+#             */
/*   Updated: 2024/04/25 15:10:37 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include <math.h>

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
	double	c = dot(co, co) - r * r;

	double	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
	{
		*t1 = INFINITY;
		*t2 = INFINITY;
	}

	*t1 = (-b + sqrt(discriminant)) / (2 * a);
	*t2 = (-b - sqrt(discriminant)) / (2 * a);
}

double	compute_lighting(t_data *data, t_vec3 P, t_vec3 N, t_vec3 V, double specular)
{
	t_vec3	L;
	double	i = 0.0;
	int	idx = -1;
	while (++idx < data->light_nb)
	{
		if (data->lights[idx].type == AMBIENT)
		{
			i += data->lights[idx].intensity;
		}
		else
		{
			if (data->lights[idx].type == POINT)
			{
				L = minus_vec3(data->lights[idx].position, P);
			}
			else if (data->lights[idx].type == DIRECTIONAL)
			{
				L = data->lights[idx].direction;
			}

			// Diffuse
			double	n_dot_l = dot(N, L);
			if (n_dot_l > 0)
			{
				i += data->lights[idx].intensity * n_dot_l / (v_length(N) * v_length(L));
			}

			// Specular
			if (specular != -1)
			{
				t_vec3	R = scalar_mul_vec3(2 * dot(N, L), N);
				// R = scalar_mul_vec3(dot(N, L), R);
				R = minus_vec3(R, L);
				double	r_dot_v = dot(R, V);
				if (r_dot_v > 0)
				{
					// double tmp = i;
					i += data->lights[idx].intensity * pow(r_dot_v / (v_length(R) * v_length(V)), specular);
			// 		if (tmp != i)
			// 		{
			// printf("before: %f\n", tmp);
			// printf("after: %f\n", i);
			// 		}
				}
			}
		}
	}
	return (i);
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

	t_vec3	P = plus_vec3(data->camera, scalar_mul_vec3(closest_t, data->D));
	t_vec3	N = minus_vec3(P, closest_sphere->center);
	N = scalar_dev_vec3(N, v_length(N));

	double light = compute_lighting(data, P, N, scalar_mul_vec3(-1, data->D), closest_sphere->specular);
	int	t = get_t(closest_sphere->color) * light;
	int	r = get_r(closest_sphere->color) * light;
	int	g = get_g(closest_sphere->color) * light;
	int	b = get_b(closest_sphere->color) * light;
	if (t > 255)
		t = 255;
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	if (t < 0)
		t = 0;
	if (r < 0)
		r = 0;
	if (g < 0)
		g = 0;
	if (b < 0)
		b = 0;
	// if (closest_sphere == &data->spheres[0])
	// {
	// printf("light: %f ", light);
	// printf("T: %d ", t);
	// printf("R: %d ", r);
	// printf("G: %d ", g);
	// printf("B: %d\n", b);
	// }
	
	return (create_trgb(t, r, g, b));
}

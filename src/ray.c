/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:50:15 by llai              #+#    #+#             */
/*   Updated: 2024/04/26 15:01:42 by llai             ###   ########.fr       */
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

void	intersect_ray_sphere(t_data *data, t_vec3 O, t_vec3 D, t_sphere sphere)
{
	double	r = sphere.radius;
	t_vec3	co = minus_vec3(O, sphere.center);

	double	a = dot(D, D);
	double	b = 2 * dot(co, D);
	double	c = dot(co, co) - r * r;

	double	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
	{
		data->t1 = INFINITY;
		data->t2 = INFINITY;
	}

	data->t1 = (-b + sqrt(discriminant)) / (2 * a);
	data->t2 = (-b - sqrt(discriminant)) / (2 * a);
}

t_sphere	*closest_intersection(t_data *data, t_vec3 O, t_vec3 D, double t_min, double t_max)
{
	t_sphere	*closest_sphere = NULL;

	data->closest_t = INFINITY;

	int	i = -1;
	while (++i < data->sphere_nb)
	{
		intersect_ray_sphere(data, O, D, data->spheres[i]);
		if (data->t1 >= t_min && data->t1 <= t_max && data->t1 < data->closest_t)
		{
			data->closest_t = data->t1;
			closest_sphere = &data->spheres[i];
		}
		if (data->t2 >= t_min && data->t2 <= t_max && data->t2 < data->closest_t)
		{
			data->closest_t = data->t2;
			closest_sphere = &data->spheres[i];
		}
	}
	return (closest_sphere);
}

double	compute_lighting(t_data *data, t_vec3 P, t_vec3 N, t_vec3 V, double specular)
{
	t_vec3	L;
	double	i = 0.0;
	int	idx = -1;
	double	t_max;

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
				t_max = 1;
			}
			else if (data->lights[idx].type == DIRECTIONAL)
			{
				L = data->lights[idx].direction;
				t_max = INFINITY;
			}

			// Shadow check
			t_sphere	*shadow_sphere = closest_intersection(data, P, L, 0.001, t_max);
			if (shadow_sphere != NULL)
			{
				continue;
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

t_vec3	reflect_ray(t_vec3 R, t_vec3 N)
{
	t_vec3	v_tmp;
	double	v_dot_r;

	v_tmp = scalar_mul_vec3(2, N);
	v_dot_r = dot(v_tmp, R);
	v_tmp = scalar_mul_vec3(v_dot_r, v_tmp);
	v_tmp = minus_vec3(v_tmp, R);
	return (v_tmp);
}

int	traceray(t_data *data, t_vec3 O, t_vec3 D, double t_min, double t_max, int recursion_depth)
{
	t_sphere	*closest_sphere = NULL;

	closest_sphere = closest_intersection(data, O, D, t_min, t_max);
	if (closest_sphere == NULL)
	{
		// return (0xFFFFFFFF);
		return (BG_COLOR);
	}

	t_vec3	P = plus_vec3(O, scalar_mul_vec3(data->closest_t, D));
	t_vec3	N = minus_vec3(P, closest_sphere->center);
	N = scalar_dev_vec3(N, v_length(N));

	// double light = compute_lighting(data, P, N, scalar_mul_vec3(-1, data->D), closest_sphere->specular);
	double light = compute_lighting(data, P, N, scalar_mul_vec3(-1, D), closest_sphere->specular);

	int	local_color = mul_color(closest_sphere->color, light);
	// (void)recursion_depth;
	double refl = closest_sphere->reflective;
	if (recursion_depth <= 0 || refl <= 0)
	{
		return (local_color);
	}

	// Compute the reflectived color
	t_vec3	R = reflect_ray(scalar_mul_vec3(-1, D), N);
	int	refl_color = traceray(data, P, R, 0.001, INFINITY, recursion_depth - 1);
	local_color = mul_color(local_color, (1 - refl));
	refl_color = mul_color(refl_color, refl);
	return (sum_color(local_color, refl_color));
}

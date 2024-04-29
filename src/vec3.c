/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:08:55 by llai              #+#    #+#             */
/*   Updated: 2024/04/26 16:06:35 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include <math.h>
#include "../includes/vec3.h"

t_vec3	set_vec3(double x, double y, double z)
{
	return ((t_vec3){x, y, z});
}

t_vec3	set_viewport(double x, double y, t_data *data)
{
	double	v_x;
	double	v_y;
	double	v_z;

	v_x = x * (data->v_width / WIDTH);
	v_y = y * (data->v_height / HEIGHT);
	v_z = data->distance;
	return ((t_vec3){v_x, v_y, v_z});
}

t_vec3	minus_vec3(t_vec3 lhs, t_vec3 rhs)
{
	t_vec3	result;

	result.x = lhs.x - rhs.x;
	result.y = lhs.y - rhs.y;
	result.z = lhs.z - rhs.z;
	return (result);
}

t_vec3	plus_vec3(t_vec3 lhs, t_vec3 rhs)
{
	t_vec3	result;

	result.x = lhs.x + rhs.x;
	result.y = lhs.y + rhs.y;
	result.z = lhs.z + rhs.z;
	return (result);
}

t_vec3	scalar_mul_vec3(double lhs, t_vec3 rhs)
{
	t_vec3	result;

	// if (lhs == -1)
	// 	printf("x: %f y: %f z: %f\n", rhs.x, rhs.y, rhs.z);
	result.x = lhs * rhs.x;
	result.y = lhs * rhs.y;
	result.z = lhs * rhs.z;
	// if (lhs == -1)
	// 	printf("res: x: %f y: %f z: %f\n", result.x, result.y, result.z);
	return (result);
}

t_vec3	scalar_dev_vec3(t_vec3 lhs, double rhs)
{
	t_vec3	result;

	// printf("len: %f\n", rhs);
	result.x = lhs.x / rhs;
	result.y = lhs.y / rhs;
	result.z = lhs.z / rhs;
	return (result);
}

double	dot(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

double	v_length(t_vec3 v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

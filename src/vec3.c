/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:08:55 by llai              #+#    #+#             */
/*   Updated: 2024/04/22 13:05:03 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
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

double	dot(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

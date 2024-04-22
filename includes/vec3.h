/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:08:12 by llai              #+#    #+#             */
/*   Updated: 2024/04/23 00:42:39 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

#include "minirt.h"

typedef struct s_data t_data;

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

t_vec3	set_vec3(double x, double y, double z);
t_vec3	set_viewport(double x, double y, t_data *data);
t_vec3	minus_vec3(t_vec3 lhs, t_vec3 rhs);
double	dot(t_vec3 v1, t_vec3 v2);
double	v_length(t_vec3 v);
t_vec3	plus_vec3(t_vec3 lhs, t_vec3 rhs);
t_vec3	scalar_mul_vec3(double lhs, t_vec3 rhs);
t_vec3	scalar_dev_vec3(t_vec3 lhs, double rhs);

#endif // !VEC3_H

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:49:48 by llai              #+#    #+#             */
/*   Updated: 2024/04/23 01:51:17 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include "vec3.h"
# include "shape.h"
# include "light.h"
# include <math.h>

# define ESC_KEY 0xff1b
# define HEIGHT 1080
# define WIDTH 1080

// typedef struct s_vec3 t_vec3;

typedef struct s_win
{
	void	*mlx;
	void	*win_ptr;
	int		width;
	int		height;
}	t_win;

typedef struct s_img
{
	t_win	win;
	void	*img_ptr;
	char	*addr;
	int		h;
	int		w;
	int		bpp;
	int		endian;
	int		line_len;
}	t_img;

typedef struct s_data
{
	t_img	base_image;
	t_vec3	camera;
	double	v_width;
	double	v_height;
	double	c_width;
	double	c_height;
	double	distance;
	int		sphere_nb;
	t_sphere	*spheres;
	int		light_nb;
	t_light		*lights;
	t_vec3	D; //ray
}	t_data;

t_win	new_window(int w, int h, char *str);

int		create_trgb(int t, int r, int g, int b);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);

void	put_pixel(t_img img, int x, int y, int color);
void	put_pixel_img(t_img img, int x, int y, int color);
t_img	new_img(int width, int height, t_win window);

t_vec3	canvas_to_viewport(double x, double y, t_data *data);
void	intersect_ray_sphere(t_data *data, t_sphere sphere, double *t1, double *t2);
int		traceray(t_data *data, double t_min, double t_max);

int		esc_close_win(int keycode, t_data *data);
int		cross_close_win(t_data *data);


#endif // !MINIRT_H

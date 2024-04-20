/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:49:48 by llai              #+#    #+#             */
/*   Updated: 2024/04/20 14:08:55 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"

# define ESC_KEY 0xff1b
# define HEIGHT 1080
# define WIDTH 1920

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
}	t_data;

t_win	new_window(int w, int h, char *str);
void	put_pixel_img(t_img img, int x, int y, int color);
t_img	new_img(int width, int height, t_win window);

int		esc_close_win(int keycode, t_data *data);
int		cross_close_win(t_data *data);


#endif // !MINIRT_H

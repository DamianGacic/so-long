// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../lib/MLX42/include/MLX42/MLX42.h"
#define WIDTH 512
#define HEIGHT 512

static mlx_image_t* image;

// -----------------------------------------------------------------------------

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}


void ft_randomize(void* param)
{
    mlx_t *mlx;

    mlx = param;
	for (uint32_t i = 0; i < image->width; ++i)
	{
		for (uint32_t y = 0; y < image->height; ++y)
		{
			uint32_t color = ft_pixel(
				rand() % 0xFF, // R
				rand() % 0xFF, // G
				rand() % 0xFF, // B
				rand() % 0xFF  // A
			);
			mlx_put_pixel(image, i, y, color);
		}
	}
}
void my_key_func(mlx_key_data_t keydata ,void* param)
{
if ((keydata.key) ==  257)
	mlx_close_window(param);
if ((keydata.key) ==  265 && (keydata.action) ==  0)
	image->instances[0].y -= 64;
if ((keydata.key) ==  264 && (keydata.action) ==  0)
	image->instances[0].y += 64;
if ((keydata.key) ==  263 && (keydata.action) ==  0)
	image->instances[0].x -= 64;
if ((keydata.key) ==  262 && (keydata.action) ==  0)
	image->instances[0].x += 64;
}
void ft_hook(void* param)
{
	mlx_t* mlx = param;
	mlx_key_hook(mlx,my_key_func,mlx);
}

// -----------------------------------------------------------------------------

int32_t main(void)
{
	mlx_t* mlx;

	// Gotta error check this stuff
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "Prototype", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(image = mlx_new_image(mlx, 64, 64)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
    mlx_loop_hook(mlx, ft_randomize, mlx);
	mlx_loop_hook(mlx, mlx_key_hook, mlx);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

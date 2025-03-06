/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:51:16 by nkiampav          #+#    #+#             */
/*   Updated: 2025/02/27 09:51:17 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Color creation
t_color color_create(int r, int g, int b)
{
    t_color color;

    color.r = r;
    color.g = g;
    color.b = b;
    return (color);
}

// Basic color operations
t_color color_add(t_color c1, t_color c2)
{
    t_color result;

    result.r = c1.r + c2.r;
    result.g = c1.g + c2.g;
    result.b = c1.b + c2.b;
    return (color_clamp(result));
}

t_color color_multiply(t_color c, double scalar)
{
    t_color result;

    result.r = (int)(c.r * scalar);
    result.g = (int)(c.g * scalar);
    result.b = (int)(c.b * scalar);
    return (color_clamp(result));
}

t_color color_multiply_colors(t_color c1, t_color c2)
{
    t_color result;

    result.r = (c1.r * c2.r) / 255;
    result.g = (c1.g * c2.g) / 255;
    result.b = (c1.b * c2.b) / 255;
    return (result);
}

// Color conversion
int color_to_int(t_color c)
{
    // Convert RGB components to a single integer (0xRRGGBB format)
    return ((c.r & 0xFF) << 16) | ((c.g & 0xFF) << 8) | (c.b & 0xFF);
}

t_color int_to_color(int rgb)
{
    t_color c;

    // Extract RGB components from integer
    c.r = (rgb >> 16) & 0xFF;
    c.g = (rgb >> 8) & 0xFF;
    c.b = rgb & 0xFF;
    return (c);
}

// Color utilities
t_color color_clamp(t_color c)
{
    t_color result;

    // Clamp RGB values to 0-255 range
    result.r = (c.r < 0) ? 0 : ((c.r > 255) ? 255 : c.r);
    result.g = (c.g < 0) ? 0 : ((c.g > 255) ? 255 : c.g);
    result.b = (c.b < 0) ? 0 : ((c.b > 255) ? 255 : c.b);
    return (result);
}

t_color color_lerp(t_color c1, t_color c2, double t)
{
    t_color result;

    // Linear interpolation between two colors
    if (t < 0)
        t = 0;
    if (t > 1)
        t = 1;
    result.r = (int)(c1.r * (1 - t) + c2.r * t);
    result.g = (int)(c1.g * (1 - t) + c2.g * t);
    result.b = (int)(c1.b * (1 - t) + c2.b * t);
    return (result);
}

// Parse color from string "r,g,b" format
t_color color_parse(char *str)
{
    t_color color;
    char    *token;
    char    *saveptr;

    color = color_black();
    if (!str)
        return (color);

    // Parse red component
    token = strtok_r(str, ",", &saveptr);
    if (token)
        color.r = ft_atoi(token);

    // Parse green component
    token = strtok_r(NULL, ",", &saveptr);
    if (token)
        color.g = ft_atoi(token);

    // Parse blue component
    token = strtok_r(NULL, ",", &saveptr);
    if (token)
        color.b = ft_atoi(token);
    
    return (color_clamp(color));
}

// Predefined colors
t_color color_black(void)
{
    return (color_create(0, 0, 0));
}

t_color color_white(void)
{
    return (color_create(255, 255, 255));
}

t_color color_red(void)
{
    return (color_create(255, 0, 0));
}

t_color color_green(void)
{
    return (color_create(0, 255, 0));
}

t_color color_blue(void)
{
    return (color_create(0, 0, 255));
}

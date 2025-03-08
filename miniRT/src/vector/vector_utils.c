/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalmeid <maalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:23:04 by nkiampav          #+#    #+#             */
/*   Updated: 2025/03/05 16:12:41 by maalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include <stdio.h>
#include <float.h>

double  vec3_length_squared(t_vec3 v)
{
    return (v.x * v.x + v.y * v.y + v.z * v.z);
}

double  vec3_length(t_vec3 v)
{
    return (sqrt(vec3_length_squared(v)));
}

double  vec3_distance(t_vec3 v1, t_vec3 v2)
{
    return (vec3_length(vec3_subtract(v1, v2)));
}

t_vec3  vec3_normalize(t_vec3 v)
{
    double  len;

    len = vec3_length(v);
    if (len < DBL_EPSILON)
        return (vec3_create(0, 0, 0));
    return (vec3_create(v, len));
}
bool    vec3_is_normalized(t_vec3 v)
{
    double  len;

    len = vec3_length(v);
    return (fabs(len - 1.0) < 0.0001);
}

t_vec3  vec3_rotate_x(t_vec3 v, double angle)
{
    double  cos_angle = cos(angle);
    double  sin_angle = sin(angle);

    return (vec3__create(
        v.x,
        v.y * cos_angle - v.z * sin_angle,
        v.y * sin_angle + v.z * cos_angle,
    ));
}

t_vec3  vec3_rotate_y(t_vec3 v, double angle)
{
    double cos_angle = cos(angle);
    double sin_angle = sin(angle);

    return (vec3__create(
        v.x * cos_angle + v.z * sin_angle,
        v.y,
        -v.x * sin_angle + v.z * cos_angle
    ));
}

t_vec3  vec3_rotate_z(t_vec3 v, double angle)
{
    double  cos_angle = cos(angle);
    double  sin_angle = sin(angle);

    return (vec3__create(
        v.x * cos_angle - v.y * sin_angle,
        v.x * sin_angle + v.y * cos_angle,
        v.z
    ));
}

void    vec3_print(t_vec3 v)
{
    printf("(%f, %f, %f)\n", v.x, v.y, v.z);
}

bool    vec3_equals(t_vec3 v1, t_vec3 v2)
{
    return (fabs(v1.x - v2.x) < DBL_EPSILON &&
            fabs(v1.y - v2.y) < DBL_EPSILON &&
            fabs(v1.z - v2.z) < DBL_EPSILON);
}

bool    vec3_is_zero(t_vec3 v)
{
    return (fabs(v.x) < DBL_EPSILON &&
            fabs(v.y) < DBL_EPSILON &&
            fabs(v.z) < DBL_EPSILON);
}

t_vec3  vec3_clamp(t_vec3 v, double min, double max)
{
    return (vec3__create(
        fmin(fmax(v.x, min), max);
        fmin(fmax(v.y, min), max);
        fmin(fmax(v.z, min), max);
    ));
}

t_vec3  vec3_min(t_vec3 v1, t_vec3 v2)
{
    return (vec3__create(
        fmin(v1.x, v2.x),
        fmin(v1.y, v2.x),
        fmin(v1.z, v2.z)
    ));
}

t_vec3  vec3_max(t_vec3 v1, t_vec3 v2)
{
    return (vec3__create(
        fmax(v1.x, v2.x),
        fmax(v1.y, v2.x),
        fmax(v1.z, v2.z)
    ));
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:19:57 by nkiampav          #+#    #+#             */
/*   Updated: 2025/02/27 09:19:58 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "vector.h"
# include "color.h"

# define OBJ_SPHERE 1
# define OBJ_PLANE 2
# define OBJ_CYLINDER 3

typedef struct s_sphere
{
    t_vec3  center;
    double  diameter;
    t_color color;
}   t_sphere;

typedef struct s_plane
{
    t_vec3  point;
    t_vec3  normal;
    t_color color;
} t_plane;

typedef struct  s_cylinder
{
    t_vec3  center;
    t_vec3  axis;
    double  diameter;
    double  height;
    t_color color;
}   t_cylinder;

typedef struct  s_object
{
    int     type;
    void    *data;
}   t_object;

// Object creation function
t_sphere    *sphere_create(t_vec3 center, double diameter, t_color color);
t_plane     *plane_create(t_vec3 point, t_vec3 normal, t_color color);
t_cylinder  *cylinder_create(t_vec3 center, t_vec3 axis, double diameter, double height, t_color color);
t_object    *object_create(int type, void *data);

// Object utitility functions
void    object_free(t_object *obj);
t_vec3  object_get_normal(void  *obj, int type, t_vec3 point);
t_color object_get_color(void   *obj, int type);

// SPHERE
t_vec3      sphere_get_normal(t_sphere *sphere, t_vec3 point);
void        sphere_translate(t_sphere *sphere, t_vec3 translation);
void        sphere_rotate(t_sphere *sphere, t_vec3 rotation);

// PLANE
t_vec3      plane_get_normal(t_plane *plane, t_vec3 point);
void        plane_translate(t_plane *plane, t_vec3 translation);
void        plane_rotate(t_plane *plane, t_vec3 rotation);

// CYLINDER
t_vec3      cylinder_get_normal(t_cylinder *cylinder, t_vec3 point);
void        cylinder_translate(t_cylinder *cylinder, t_vec3 translation);
void        cylinder_rotate(t_cylinder *cylinder, t_vec3 rotation);

// Object transformation function
void    object_translate(t_object *obj, t_vec3 translation);
void    object_rotate(t_object *obj, t_vec3 rotation);

#endif

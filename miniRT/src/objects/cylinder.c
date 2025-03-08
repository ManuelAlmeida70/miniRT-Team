/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalmeid <maalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:50:05 by nkiampav          #+#    #+#             */
/*   Updated: 2025/03/07 07:55:14 by maalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minirt.h"

// Verifica se um ponto está dentro do cilindro
bool cylinder_contains_point(t_cylinder *cylinder, t_vec3 point)
{
    // Vetor do centro ao ponto
    t_vec3 center_to_point = vec3_subtract(point, cylinder->center);
    
    // Projeção do ponto no eixo do cilindro
    double proj_length = vec3_dot(center_to_point, cylinder->axis);
    
    // Verifica se o ponto está dentro da altura do cilindro
    if (proj_length < 0 || proj_length > cylinder->height)
        return (false);
    
    // Distância do ponto ao eixo do cilindro
    t_vec3 proj = vec3_multiply(cylinder->axis, proj_length);
    t_vec3 dist_from_axis = vec3_subtract(center_to_point, proj);
    
    // Verifica se a distância está dentro do raio do cilindro
    return (vec3_length(dist_from_axis) <= cylinder->diameter / 2.0);
}

// Calcula a normal de um ponto na superfície do cilindro
t_vec3 cylinder_normal_at(t_cylinder *cylinder, t_vec3 point)
{
    // Vetor do centro ao ponto
    t_vec3 center_to_point = vec3_subtract(point, cylinder->center);
    
    // Projeção do ponto no eixo do cilindro
    double proj_length = vec3_dot(center_to_point, cylinder->axis);
    t_vec3 proj = vec3_multiply(cylinder->axis, proj_length);
    
    // Vetor do eixo ao ponto
    t_vec3 normal = vec3_subtract(center_to_point, proj);
    
    return (vec3_normalize(normal));
}

// Verificação de interseção do raio com o cilindro
bool cylinder_intersect(t_cylinder *cylinder, t_vec3 ray_origin, t_vec3 ray_direction, double *t)
{
    // Implementação simplificada de intersecção de raio com cilindro
    // Esta é uma versão básica e pode precisar de refinamentos
    
    t_vec3 oc = vec3_subtract(ray_origin, cylinder->center);
    
    double a = vec3_dot(ray_direction, ray_direction) - 
               pow(vec3_dot(ray_direction, cylinder->axis), 2);
    double b = 2.0 * (vec3_dot(ray_direction, oc) - 
                      vec3_dot(ray_direction, cylinder->axis) * 
                      vec3_dot(oc, cylinder->axis));
    double c = vec3_dot(oc, oc) - 
               pow(vec3_dot(oc, cylinder->axis), 2) - 
               pow(cylinder->diameter / 2.0, 2);
    
    double discriminant = b * b - 4 * a * c;
    
    if (discriminant < 0)
        return (false);
    
    double sqrt_disc = sqrt(discriminant);
    double t0 = (-b - sqrt_disc) / (2.0 * a);
    double t1 = (-b + sqrt_disc) / (2.0 * a);
    
    if (t0 > t1)
    {
        double temp = t0;
        t0 = t1;
        t1 = temp;
    }
    
    // Verificar limites de altura do cilindro
    t_vec3 hit_point0 = vec3_add(ray_origin, vec3_multiply(ray_direction, t0));
    t_vec3 hit_point1 = vec3_add(ray_origin, vec3_multiply(ray_direction, t1));
    
    double proj0 = vec3_dot(vec3_subtract(hit_point0, cylinder->center), cylinder->axis);
    double proj1 = vec3_dot(vec3_subtract(hit_point1, cylinder->center), cylinder->axis);
    
    if (proj0 >= 0 && proj0 <= cylinder->height)
    {
        *t = t0;
        return (true);
    }
    
    if (proj1 >= 0 && proj1 <= cylinder->height)
    {
        *t = t1;
        return (true);
    }
    
    return (false);
}
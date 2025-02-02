/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_wall_objects_init.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 09:21:18 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/23 16:39:59 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void		wall_objects_init(t_engine *eng)
{
	int			i;
	int			j;
	t_object	*obj;
	t_sector	*sect;

	i = 0;
	while (i < eng->world->sectors_count)
	{
		j = 0;
		sect = &eng->world->sectors_array[i];
		while (j < sect->objects_count)
		{
			obj = &sect->objects_array[j];
			wall_object_init(eng, obj, obj->wallobjects_array,
			(t_point_3d){0, 0, 0, sect->floor});
			j++;
		}
		i++;
	}
}

void		instant_close_door(t_sector *sect)
{
	int			i;

	i = 0;
	sect->opening.delta = 10;
	sect->opening.range = sect->ceil - sect->floor;
	while (close_door(&sect->opening, sect) == 0)
		i++;
}

void		wall_object_init(t_engine *eng, t_object *obj,
			t_wobj *particlestack, t_point_3d particle)
{
	t_sh_part	data;
	t_wobj		*txtr;
	int			i;

	i = 0;
	if ((obj->stuff = (t_wallobj *)
	ft_memalloc(sizeof(t_wallobj) * obj->wallobjects_num)) == NULL)
		util_malloc_error("stuff");
	while (i < obj->wallobjects_num)
	{
		txtr = &obj->wallobjects_array[i];
		init_wobj_help(obj, &particle);
		init_wobj_help2(obj, txtr, &particle, &data);
		obj->stuff[i] = data.w_partcle;
		obj->stuff[i].type = txtr->enum_type;
		obj->stuff[i].red = txtr->red_key;
		obj->stuff[i].blue = txtr->blue_key;
		obj->stuff[i].yellow = txtr->yellow_key;
		if (obj->stuff[i].type == BT_DOOR)
			instant_close_door(&eng->world->sectors_array[txtr->sector_id]);
		i++;
	}
}

void		init_wobj_help(t_object *obj, t_point_3d *particle)
{
	float		min;
	float		max;

	min = obj->polies_array[0].vertices_array[0].x <
	obj->polies_array[0].vertices_array[1].x
	? obj->polies_array[0].vertices_array[0].x
	: obj->polies_array[0].vertices_array[1].x;
	max = obj->polies_array[0].vertices_array[0].x >
	obj->polies_array[0].vertices_array[1].x
	? obj->polies_array[0].vertices_array[0].x
	: obj->polies_array[0].vertices_array[1].x;
	particle->x = min + (max - min) / 2;
	min = obj->polies_array[0].vertices_array[0].y <
	obj->polies_array[0].vertices_array[1].y
	? obj->polies_array[0].vertices_array[0].y
	: obj->polies_array[0].vertices_array[1].y;
	max = obj->polies_array[0].vertices_array[0].y >
	obj->polies_array[0].vertices_array[1].y
	? obj->polies_array[0].vertices_array[0].y
	: obj->polies_array[0].vertices_array[1].y;
	particle->y = min + (max - min) / 2;
}

void		init_wobj_help2(t_object *obj, t_wobj *txtr,
			t_point_3d *particle, t_sh_part *data)
{
	data->dx1 = obj->polies_array[0].vertices_array[0].x - particle->x;
	data->dy1 = obj->polies_array[0].vertices_array[0].y - particle->y;
	data->dx2 = particle->x - obj->polies_array[0].vertices_array[1].x;
	data->dy2 = particle->y - obj->polies_array[0].vertices_array[1].y;
	data->dist1 = sqrtf(data->dx1 * data->dx1 + data->dy1 * data->dy1);
	data->dist2 = sqrtf(data->dx2 * data->dx2 + data->dy2 * data->dy2);
	data->half_w = txtr->type->anmtn[0]->surface[0]->w / 8;
	data->w_partcle.texture = txtr->type->anmtn[0];
	data->w_partcle.a.x = particle->x - ((data->half_w * (particle->x
	- obj->polies_array[0].vertices_array[0].x)) / data->dist1);
	data->w_partcle.a.y = particle->y - ((data->half_w * (particle->y
	- obj->polies_array[0].vertices_array[0].y)) / data->dist1);
	data->w_partcle.b.x = particle->x - ((data->half_w * (particle->x
	- obj->polies_array[0].vertices_array[1].x)) / data->dist2);
	data->w_partcle.b.y = particle->y - ((data->half_w * (particle->y
	- obj->polies_array[0].vertices_array[1].y)) / data->dist2);
	data->w_partcle.id = 1;
	data->w_partcle.z = particle->z + txtr->height;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapeditor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmith <fsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 14:45:37 by fsmith            #+#    #+#             */
/*   Updated: 2019/09/08 17:32:56 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mapeditor.h>

int		main(int argc, char **argv)
{
	t_editor editor;

	me_init(&editor);
	SDL_UpdateWindowSurface(editor.win);
	SDL_RenderDrawPoint(editor.ren, 70, 90);
	while(editor.run)
	{
		me_keyboard_handler(&editor);
	}
	me_quit(&editor);
	return 0;
}

void me_quit(t_editor *editor)
{
	SDL_DestroyWindow(editor->win);
	SDL_Quit();
}

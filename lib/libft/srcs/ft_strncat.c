/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 22:28:52 by zytrams           #+#    #+#             */
/*   Updated: 2019/08/30 20:08:29 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	char	*t;

	t = s1;
	while (*t)
		t++;
	while (*s2 && n > 0)
	{
		*t++ = *s2++;
		n--;
	}
	*t = '\0';
	return (s1);
}

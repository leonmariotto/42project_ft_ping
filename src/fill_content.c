/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_content.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 16:40:17 by lmariott          #+#    #+#             */
/*   Updated: 2020/09/04 23:05:44 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int					fill_content(void)
{
	int		j;
	int		offset;

	if (g_myping->opt.ip6)
		offset = ICMPHDRLEN;
	else
		offset = IPHDRLEN + ICMPHDRLEN;
	j = -1;
	while (++j < DATALEN)
	{
		if (!g_myping->opt.f)
			((char*)(g_myping->datagram + offset))[j] = 16 + j;
		else
			((char*)(g_myping->datagram + offset))[j] = g_myping->opt.f;
	}
	return (0);
}

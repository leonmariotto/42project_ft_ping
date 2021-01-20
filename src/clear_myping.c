/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_myping.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 15:09:42 by lmariott          #+#    #+#             */
/*   Updated: 2021/01/07 16:20:00 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include "g_myping.h"

void				clear_myping(void)
{
	close(g_myping->socket);
	free(g_myping->datagram);
	free(g_myping->dstname);
	free(g_myping->dstaddr);
	free(g_myping->fromaddr);
	freeaddrinfo(g_myping->dst_ai);
	ft_lstdel(&g_myping->ltime, &default_del);
	free(g_myping);
}

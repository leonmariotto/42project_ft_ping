/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_myping.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 15:09:42 by lmariott          #+#    #+#             */
/*   Updated: 2020/06/07 23:07:21 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void				clear_myping(void)
{
	close(myping->socket);
	free(myping->datagram);
	free(myping->dstname);
	free(myping->dstaddr);
	free(myping->fromaddr);
	freeaddrinfo(myping->dst_ai);
	ft_lstdel(&myping->ltime, &default_del);
	free(myping);
}

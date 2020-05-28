/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_myping.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 15:09:42 by lmariott          #+#    #+#             */
/*   Updated: 2020/05/26 15:12:47 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void				clear_myping(void)
{
	close(myping->socket);
	free(myping->datagram);
	free(myping->dstname);
	free(myping->dstaddr);
	free(myping);
}

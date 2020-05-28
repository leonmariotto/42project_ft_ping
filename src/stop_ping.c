/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_ping.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 15:03:41 by lmariott          #+#    #+#             */
/*   Updated: 2020/05/26 17:37:14 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include <stdio.h>
#include <sys/time.h>

static int		timeval(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((int)((tv.tv_usec - myping->init_tv) * 1000));
}

void					stop_ping(void)
{
	printf("--- %s ping statistics ---\n", myping->dstname);
	printf("%ld packets transmitted, %ld received, %.1f%% packet loss, time %dms\n"
				 , myping->npsend, myping->nprcv
				 , (float)(myping->nprcv == 0 ? 100
									 : (myping->npsend / myping->nprcv) - 1)
				 , timeval());
	printf("rtt min/avg/max/mdev = %f/%f/%f/%f ms\n"
				 , 0., 0., 0.,0.);
	clear_myping();
	exit(0);
}

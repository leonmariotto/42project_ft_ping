/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diff_timeval.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 20:02:59 by lmariott          #+#    #+#             */
/*   Updated: 2020/09/04 22:04:36 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include <sys/time.h>
#include <stdio.h>

float		diff_timeval_now(struct timeval first)
{
	struct timeval			tv;
	long int				dsec;
	float					dusec;

	gettimeofday(&tv, NULL);
	dsec = (tv.tv_sec - first.tv_sec) * 1000;
	dusec = (float)(tv.tv_usec - first.tv_usec) / 1000;
	return ((float)dsec + dusec);
}

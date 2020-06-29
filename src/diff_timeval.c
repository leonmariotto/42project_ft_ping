/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diff_timeval.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 20:02:59 by lmariott          #+#    #+#             */
/*   Updated: 2020/05/28 21:09:14 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include <sys/time.h>
#include <stdio.h>

float		diff_timeval_now(struct timeval first)
{
	struct timeval	tv;
	long int				dsec;
	float				dusec;

	gettimeofday(&tv, NULL);
	dsec = (tv.tv_sec - first.tv_sec) * 1000;
	dusec = (float)(tv.tv_usec - first.tv_usec) / 1000;
	//fprintf(stderr, "init_tv.usec = %ld\n", first.tv_usec);
	//fprintf(stderr, "now_tv.usec = %ld\n", tv.tv_usec);
	//fprintf(stderr, "init_tv.sec = %ld\n", first.tv_sec);
	//fprintf(stderr, "now_tv.sec = %ld\n", tv.tv_sec);
	//fprintf(stderr, "dsec = %ld\n", dsec); 
	//fprintf(stderr, "dusec = %f\n", dusec); 
	//fprintf(stderr, "return = %f\n", (float)(dsec + dusec)); 
	return ((float)dsec + dusec);
}

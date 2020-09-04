/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_ping.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 15:03:41 by lmariott          #+#    #+#             */
/*   Updated: 2020/09/04 23:06:56 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include <stdio.h>
#include <math.h>

static float		getmin(void)
{
	float		min;
	t_list		*head;

	head = g_myping->ltime;
	min = 0.0;
	if (head)
		min = *(float*)head->content;
	while (head)
	{
		if (min > *(float*)head->content)
			min = *(float*)head->content;
		head = head->next;
	}
	return (min);
}

static float		getmax(void)
{
	float		min;
	t_list		*head;

	head = g_myping->ltime;
	min = 0.0;
	if (head)
		min = *(float*)head->content;
	while (head)
	{
		if (min < *(float*)head->content)
			min = *(float*)head->content;
		head = head->next;
	}
	return (min);
}

static float		getavg(void)
{
	float		sum;
	int			c;
	t_list		*head;

	head = g_myping->ltime;
	sum = 0.0;
	c = 0;
	while (head)
	{
		sum += *(float*)head->content;
		c++;
		head = head->next;
	}
	if (!c)
		return (0.0);
	return (sum / (float)c);
}

static float		getstddev(void)
{
	float		avg;
	float		sum;
	int			c;
	t_list		*head;

	head = g_myping->ltime;
	sum = 0.0;
	c = 0;
	avg = getavg();
	while (head)
	{
		sum += ((*(float*)head->content - avg) *
				(*(float*)head->content - avg));
		c++;
		head = head->next;
	}
	if (c)
		sum = sqrt(sum / c);
	return (sum);
}

void				stop_ping(void)
{
	printf("--- %s ping statistics ---\n", g_myping->dstname);
	printf("%d packets transmitted, %d received, "
			, (int)g_myping->p_count[0], (int)g_myping->p_count[1]);
	if (g_myping->p_count[2])
		printf("+%d errors, ", (int)g_myping->p_count[2]);
	printf("%.1f%% packet loss, time %dms\n"
			, (g_myping->p_count[1] == 0 || g_myping->p_count[0] == 0 ? 100
				: ((g_myping->p_count[1] / g_myping->p_count[0]) - 1) * 100)
			, g_myping->t_count);
	printf("rtt min/avg/max/stddev = %f/%f/%f/%f ms\n"
			, getmin()
			, getavg()
			, getmax()
			, getstddev());
	clear_myping();
	exit(0);
}

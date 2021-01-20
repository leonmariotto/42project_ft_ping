/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 14:58:06 by lmariott          #+#    #+#             */
/*   Updated: 2021/01/07 16:19:28 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include "g_myping.h"
#include <signal.h>

void			signal_handler(int sign)
{
	if (sign == SIGINT)
		stop_ping();
}

void			signal_(void)
{
	signal(SIGINT, signal_handler);
}

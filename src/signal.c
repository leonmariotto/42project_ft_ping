/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 14:58:06 by lmariott          #+#    #+#             */
/*   Updated: 2020/05/26 15:20:05 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
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

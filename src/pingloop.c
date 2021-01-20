/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pingloop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 17:09:43 by lmariott          #+#    #+#             */
/*   Updated: 2021/01/07 16:18:18 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include "g_myping.h"
#include <sys/time.h>
#include <stdio.h>
#include <signal.h>

/*
** New pingloop :
** Le packet est envoyé toutes les secondes avec SIGALRM
** Le recvmsg est placé dans un while (42)
**
** inet_ntop((g_myping->opt.ip6 ? AF_INET6 : AF_INET),
**		(const void *)&((struct sockaddr_in*)&src_addr)->sin_addr,
**		g_myping->fromaddr, srcaddrsize);
*/

int								rcv_(void)
{
	struct sockaddr_in				src_addr;
	socklen_t						srcaddrsize;
	struct iovec					iov[1];
	struct msghdr					message;
	int								r;

	srcaddrsize = (g_myping->opt.ip6 ? INET6_ADDRSTRLEN : INET_ADDRSTRLEN);
	iov[0].iov_base = g_myping->rcv_buff;
	iov[0].iov_len = sizeof(g_myping->rcv_buff);
	message.msg_name = &src_addr;
	message.msg_namelen = srcaddrsize;
	message.msg_iov = iov;
	message.msg_iovlen = 1;
	message.msg_control = 0;
	message.msg_controllen = 0;
	r = recvmsg(g_myping->socket, &message, 0);
	if (!g_myping->opt.ip6)
		inet_ntop(AF_INET,
			(const void *)&((struct sockaddr_in*)&src_addr)->sin_addr,
			g_myping->fromaddr, INET_ADDRSTRLEN);
	else
		inet_ntop(AF_INET6,
			(const void *)&((struct sockaddr_in6*)&src_addr)->sin6_addr,
			g_myping->fromaddr, INET6_ADDRSTRLEN);
	return (r);
}

int								is_mine6(void)
{
	struct icmp6_hdr *icmphdr;

	icmphdr = (struct icmp6_hdr*)(g_myping->rcv_buff);
	if (icmphdr->icmp6_type == ICMP6_ECHO_REPLY)
	{
		if (icmphdr->icmp6_id !=
		((struct icmp6_hdr*)(g_myping->datagram + IPHDRLEN))->icmp6_id)
			return (0);
		return (1);
	}
	else if (icmphdr->icmp6_type < 128)
	{
		if ((icmphdr + 6)->icmp6_id !=
		((struct icmp6_hdr*)(g_myping->datagram + IPHDRLEN))->icmp6_id)
			return (0);
		return (1);
	}
	return (0);
}

int								is_mine(void)
{
	if (g_myping->opt.ip6)
		return (is_mine6());
	if (((struct icmp*)
			(g_myping->rcv_buff + IPHDRLEN))->icmp_type == ICMP_ECHOREPLY)
	{
		if (((struct icmp*)(g_myping->rcv_buff + IPHDRLEN))->icmp_id
				== ((struct icmp*)(g_myping->datagram + IPHDRLEN))->icmp_id)
			return (1);
	}
	else
	{
		if (((struct icmp*)(g_myping->rcv_buff + 48))->icmp_id
				== ((struct icmp*)(g_myping->datagram + IPHDRLEN))->icmp_id)
			return (1);
	}
	return (0);
}

int								pingloop(void)
{
	int				r;
	float			time_diff;

	if (g_myping->opt.ip6)
		send_packet6(0);
	else
		send_packet(0);
	signal(SIGALRM, (g_myping->opt.ip6 ? send_packet6 : send_packet));
	while (42)
	{
		r = rcv_();
		time_diff = diff_timeval_now(g_myping->t_send);
		if (r < 0)
			return (-1);
		if (r > 0 && is_mine())
		{
			ft_lstadd(&g_myping->ltime, ft_lstnew(&time_diff, sizeof(float)));
			if (g_myping->opt.ip6)
				print_ping6(time_diff);
			else
				print_ping(time_diff);
		}
	}
}

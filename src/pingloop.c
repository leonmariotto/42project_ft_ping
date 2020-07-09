/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pingloop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 17:09:43 by lmariott          #+#    #+#             */
/*   Updated: 2020/07/02 11:41:31 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include <sys/time.h>
#include <stdio.h>
#include <signal.h>

/*
** New pingloop :
** Le packet est envoyé toutes les secondes avec SIGALRM
** Le recvmsg est placé dans un while (42)
*/

/*
** send_packet :
** - Prepare le nouveau packet (nouveau id, checksum, ...)
** - Sauvegarde le icmp_seq, et la timeval dans une seule structure dans uneliste chainée.
** - Update p_count[0]
** - ON NE COMPARE PAS LA SEQUENCE POUR L'INSTANT TROP GALERE
*/
void							send_packet(int sign)
{
	(void)sign;
	myping->icmphdr->icmp_seq += 1;
	myping->icmphdr->icmp_cksum = 0;
	myping->icmphdr->icmp_cksum = checksum((unsigned short*)myping->icmphdr,
																ICMPHDRLEN + DATALEN);
	myping->t_count = (int)diff_timeval_now(myping->init_tv);
	gettimeofday(&myping->t_send, 0);
	myping->p_count[0]++;
	sendto(myping->socket,myping->datagram, IPHDRLEN + ICMPHDRLEN + DATALEN, 0,
						 myping->dst_ai->ai_addr, myping->dst_ai->ai_addrlen);
	alarm(1);
}

int								rcv_(void)
{
	struct sockaddr_in	src_addr;
	socklen_t						srcaddrsize;
	struct iovec iov[1];
	struct msghdr message;
	int r;
	
	srcaddrsize = myping->dst_ai->ai_addrlen;
	iov[0].iov_base = myping->rcv_buff;
	iov[0].iov_len = sizeof(myping->rcv_buff);
	message.msg_name = &src_addr;
	message.msg_namelen = srcaddrsize;
	message.msg_iov = iov;
	message.msg_iovlen = 1;
	message.msg_control = 0;
	message.msg_controllen = 0;
	r = recvmsg(myping->socket,&message,0);
	inet_ntop(AF_INET,
						(const void *)&((struct sockaddr_in*)&src_addr)->sin_addr,
						myping->fromaddr, srcaddrsize);
	return (r);
}

int								is_mine(void)
{
	//printf("\n\ngo\n");
	//int i;
	//for ( i=0; i < 48;i++)
	//	printf("%.2X ",*((char*)myping->rcv_buff + i));
	//printf("\n");
	if (((struct icmp*)
			(myping->rcv_buff + IPHDRLEN))->icmp_type == ICMP_ECHOREPLY)
	{
		if (((struct icmp*)(myping->rcv_buff + IPHDRLEN))->icmp_id
				== myping->icmphdr->icmp_id)
			return (1);
	}
	else
	{
		if (((struct icmp*)(myping->rcv_buff + 48))->icmp_id
				== myping->icmphdr->icmp_id)
			return (1);
	}
	return (0);
}

void							print_ping(float time_diff)
{
	int type;

	type = (int)((struct icmp*)(myping->rcv_buff + IPHDRLEN))->icmp_type;
	if (type != ICMP_ECHOREPLY)
	{
		myping->p_count[2]++;
		printf("From %s: icmp_seq=%-3d ",
				 myping->fromaddr,
				 ((struct icmp*)(myping->datagram + IPHDRLEN))->icmp_seq);
		if (type == ICMP_TIME_EXCEEDED)
			printf("Time to Live Exceeded\n");
		if (type == ICMP_DEST_UNREACH)
			printf("Destination Unreachable\n");
	}
	else
	{
		myping->p_count[1]++;
		printf("%d bytes from %s: icmp_seq=%-3d ttl=%d time=%f ms\n",
				 DATALEN + ICMPHDRLEN,
				 myping->fromaddr,
				 ((struct icmp*)(myping->datagram + IPHDRLEN))->icmp_seq,
				 ((struct ip*)myping->rcv_buff)->ip_ttl,
				 time_diff);
	}
}

int								pingloop(void)
{
	int				r;
	float			time_diff;

	send_packet(0);
	signal(SIGALRM, send_packet);
	while(42)
	{
		r = rcv_();
		time_diff = diff_timeval_now(myping->t_send);
		if (r < 0)
			return (-1);
		else if (r > 0 && is_mine())
		{
			ft_lstadd(&myping->ltime, ft_lstnew(&time_diff, sizeof(float)));
			print_ping(time_diff);
		}
	}
}

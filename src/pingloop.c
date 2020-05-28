/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pingloop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmariott <lmariott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 19:39:42 by lmariott          #+#    #+#             */
/*   Updated: 2020/05/26 17:18:27 by lmariott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include <sys/time.h>
#include <stdio.h>

char							*sendandrecv(void)
{
	char								*buffer;
	socklen_t						sizerecvfrom;
	struct sockaddr_in	fromaddr;

	if (!(buffer = (char*)malloc(DATALEN + IPHDRLEN + ICMPHDRLEN)))
		return (NULL);
	ft_bzero(buffer, DATALEN + IPHDRLEN + ICMPHDRLEN);
	sendto(myping->socket,myping->datagram, IPHDRLEN + ICMPHDRLEN + DATALEN, 0,
						 myping->dst_ai->ai_addr, myping->dst_ai->ai_addrlen);
	sizerecvfrom = myping->dst_ai->ai_addrlen;
	recvfrom(myping->socket, buffer, DATALEN + IPHDRLEN + ICMPHDRLEN,
							 0, (struct sockaddr*)&fromaddr, &sizerecvfrom);
	if (!ft_strcmp(inet_ntoa(fromaddr.sin_addr), myping->dstaddr))
		return (buffer);
	free(buffer);
	return (NULL);
	//perror("recvfrom");
	//printf("addrrecvfrom = %s\n", );
	//printf("addrsendto = %s\n", myping->dstaddr);
	//int i;
  //for ( i=0; i < IPHDRLEN+ICMPHDRLEN+DATALEN;i++)
	//	printf("%.2X ",*((char*)myping->datagram + i));
	//printf("\n");
}

int										pingloop(void)
{
	struct timeval		before;
	struct timeval		after;
	char							*buffer;

	// TODO count
	while (1)
	{
		// TODO check timeout
		myping->npsend++;
		update_icmp_seq();
		gettimeofday(&before, NULL);
		if ((buffer = sendandrecv()))
		{
			myping->nprcv++;
			gettimeofday(&after, NULL);
			printf("%d bytes from %s: icmp_seq=%ld ttl=%d time=%f ms\n",
						 DATALEN + ICMPHDRLEN,
						 myping->dstaddr,
						 myping->nprcv,
						 ((struct ip*)buffer)->ip_ttl,
						 (float)((long int)(after.tv_usec - before.tv_usec) / 1000));
			free(buffer);
		}
	}
}

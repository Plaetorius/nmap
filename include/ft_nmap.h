/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nmap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguiard <nguiard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 08:55:53 by nguiard           #+#    #+#             */
/*   Updated: 2024/06/25 19:02:16 by nguiard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NMAP_H
#define FT_NMAP_H

#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <pcap.h>
#include <pthread.h>
#include <errno.h>
#include <fcntl.h>

#include "libft.h"

typedef char *	str;

#define WARNING	"\033[33mWarning:\033[0m "
#define ERROR	"\033[31mError:\033[0m "

// Options

typedef	struct host_data {
	str				basename;
	struct addrinfo	info;
} host_data;

typedef struct options {
	host_data		*host;
	uint32_t		host_len;
	uint8_t			scans;
	uint8_t			threads;
	uint16_t		*port;
	uint32_t		port_len;
} options;

#define IS_SCAN_NOTHING(x)	(x == 0)
#define IS_SCAN_SYN(x)		((x & 0b00000001) == 0b00000001)
#define IS_SCAN_NULL(x)		((x & 0b00000010) == 0b00000010)
#define IS_SCAN_ACK(x)		((x & 0b00000100) == 0b00000100)
#define IS_SCAN_FIN(x)		((x & 0b00001000) == 0b00001000)
#define IS_SCAN_XMAS(x)		((x & 0b00010000) == 0b00010000)
#define IS_SCAN_UDP(x)		((x & 0b00100000) == 0b00100000)
#define IS_SCAN_ALL(x)		((x & 0b10111111) == 0b10111111)

options options_handling(int argc, char **argv);
void	free_options(options *opts);
void	free_host_data(host_data data);

// Threads

#define NEVER_ZERO(x) (x ? x : 1)

typedef struct host_and_port {
	host_data	host;
	uint16_t	port;
} host_and_port;

typedef struct tdata_out {
	str	data;
} tdata_out;

typedef struct tdata_in {
	host_and_port	*hnp;
	uint32_t		hnp_len;
	uint8_t			scans;
	uint8_t			id;
	tdata_out		*output;
} tdata_in;

void	threads(const options opt);

#endif
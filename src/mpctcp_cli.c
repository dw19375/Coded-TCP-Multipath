/*
 * mpctcp_cli.c
 * 
 * While the proxy is bidirectional, this handles the "client" side
 * of things.
 * 
 * Functions to receive and decode packets.
 */

#include <stdlib.h>
#include <stdint.h>
#include "mpctcp_cli.h"

/*
 * handle_packet
 * 
 * Handles incoming packets.  Packets should include the CTCP header
 * but be stripped of any IP or UDP headers.  Everything should be in
 * network byte order.
 * 
 * Parameters:
 *    buf     Pointer to packet (header + payload)
 *            Assumed to be in network byte order
 *    len     Length of packet (header + payload) in bytes
 */
void handle_packet( void* buf, size_t len )
{
  
  
}


/*
 * net_util.h 
 * 
 * Contains various network related utilities.
 */

#ifndef NET_UTIL_H
#define NET_UTIL_H

#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <ifaddrs.h>
#include <string.h>
#include <stdint.h>

typedef int socket_t;

#define NETIFDOWN	0
#define NETIFUP		1

// CTCP Header size in bytes.
#define CTCP_HDR_SIZE 24

// We have to take into account the IP+UDP header
// Max IP header is 24B, UDP header is 8B 
#define IPUDP_HEADER_SIZE 32 

// Flags for Data_Pckt
// Currently, this is an int32_t, but gcc can use
// __attribute__ ((__packed__)) to reduce it to one byte.
// Affects the size/packing of the packet header as well.
typedef enum 
{
  NORMAL=0, 
  SYN, 
  SYN_ACK, 
  FIN, 
  FIN_ACK, 
  CODED
}flag_t;


struct addr_list
{
	int active;
	char if_name[10];
	struct sockaddr_in addr;
	struct addr_list * next;
	int sk;
};

/*
 * Packet header struct.  If you change this, be sure to update
 * pack_hdr and unpack_hdr functions and CTCP_HDR_SIZE.
 */
typedef struct
{
  double tstamp;        // Time stamp
  flag_t flag;          // Flag indicating packet type
  uint32_t seqno;       // Normal packet - sequence number
                        // ACK - packet being acknowledged
                        // Coded - beginning of coding window
                        
  uint32_t len;         // Length of payload (excludes header)
  
  uint16_t num_packets; // Coded - Number of packets in coding window
                        // ACK - Number of dofs requested
                        // Normal Packet - unused
  
  uint16_t coeff_seed;  // Seed for coefficients of coded packets
                        // Used only for coded packets
} Pckt_Header;

typedef struct
{
  Pckt_Header hdr;
  char* buf;        // Payload - allocate MSS - sizeof(header)
                    // Don't statically allocate here so we can 
                    // dynamically set MSS
} Data_Pckt;

// All information an ACK needs to carry is in the header
typedef struct
{
  Pckt_Header hdr;
} Ack_Pckt;

typedef struct
{
  uint16_t payload_size;
  char* payload;
} Bare_Pckt; // This is the datastructure for holding packets before encoding


/* Function declarations */
void htonpData(Data_Pckt *msg);
void htonpAck(Ack_Pckt *msg);
void ntohpData(Data_Pckt *msg);
void ntohpAck(Ack_Pckt *msg);
void prettyPrint(char** coeffs, int window);
int pack_hdr( char* buf, Pckt_Header hdr );
int unpack_hdr( char* buf, Pckt_Header* hdr );
int pack_Data_Pckt( char* buf, Data_Pckt pkt );
int pack_Ack_Pckt( char* buf, Ack_Pckt pkt );

#endif

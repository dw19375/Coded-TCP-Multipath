/*
 * net_util.c
 * 
 * Contains various network related utility functions
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <assert.h>
#include <math.h>
#include "net_util.h"
#include "util.h"

void
htonpData(Data_Pckt* msg){
  msg->flag    = (flag_t) htonl(msg->flag);
  msg->seqno   = htonl(msg->seqno);
  msg->blockno = htonl(msg->blockno);
}

void
htonpAck(Ack_Pckt* msg){
  msg->flag    = (flag_t) htonl(msg->flag);
  msg->ackno   = htonl(msg->ackno);
  msg->blockno = htonl(msg->blockno);
}

void
ntohpData(Data_Pckt* msg){
  msg->flag    = (flag_t) ntohl(msg->flag);
  msg->seqno   = ntohl(msg->seqno);
  msg->blockno = ntohl(msg->blockno);
}

void
ntohpAck(Ack_Pckt* msg){
  msg->flag    = (flag_t) ntohl(msg->flag);
  msg->ackno   = ntohl(msg->ackno);
  msg->blockno = ntohl(msg->blockno);
}

void
prettyPrint(char** coeffs, int window){
  int i,j;
  printf("\n\n**Matrix**\n");
  for(i = 0; i < BLOCK_SIZE; i++){
    for(j = 0; j < BLOCK_SIZE; j++){
      if(j < i || j >= i + window){
        printf("0 ");
      }else{
        printf("%d ", (uint8_t) coeffs[i][j-i]);
      }
    }
    printf("\n");
  }
}



/************* UDP SERVER CODE *******************/

#include <stdio.h>
#include <winsock2.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <Ws2tcpip.h>
#pragma comment(lib, "wsock32.lib")
#pragma comment(lib, "Ws2_32.lib")


int main(){
  int udpSocket, nBytes;
  char buffer[1024];
  struct sockaddr_in serverAddr, clientAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size, client_addr_size;
  const int serPort=7000;


  /*Create UDP socket*/
  udpSocket = socket(PF_INET, SOCK_DGRAM, 0);

  /*Configure settings in address struct*/
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(serPort);
  serverAddr.sin_addr.s_addr = inet_addr("0.0.0.0");
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  /*Bind socket with address struct*/
  bind(udpSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
  
//  printf("UDP server run at port: %s\n",serPort);

  /*Initialize size variable to be used later on*/
  addr_size = sizeof serverStorage;

  while(1){
//  	buffer[0-1024] = 0;
    /* Try to receive any incoming UDP datagram. Address and port of 
      requesting client will be stored on serverStorage variable */
    nBytes = recvfrom(udpSocket,buffer,1024,0,(struct sockaddr *)&serverStorage, &addr_size);
//    printf("Received from server: %s\n",buffer);

    /*Convert message received to uppercase*/
 //   for(i=0;i<nBytes-1;i++)
//      buffer[i] = toupper(buffer[i]);

    /*Send uppercase message back to client, using serverStorage as the address*/
    sendto(udpSocket,buffer,nBytes,0,(struct sockaddr *)&serverStorage,addr_size);
    
  }

  return 0;
}

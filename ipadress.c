#include <net/if.h>
#include <sys/ioctl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>


int getIpAddress(int iNetType, char chIP[16]);
int main(void) 

{
char chDOC[16];
int ret;
ret=getIpAddress(0,chDOC);

printf ("Return %d mac %x",ret,chDOC[0]);
}

int getIpAddress(int iNetType, char chIP[16])
{

 struct ifreq ifr;
  int sock = 0;
 
  sock = socket(AF_INET, SOCK_DGRAM, 0);
  if(iNetType == 0) {
    strcpy(ifr.ifr_name, "enp0s3");
  } else {
    strcpy(ifr.ifr_name, "wlan0");
  }
  if (ioctl(sock, SIOCGIFADDR, &ifr) < 0) {
    strcpy(chIP, "0.0.0.0");
    return -1;
 }
 sprintf(chIP, "%s", inet_ntoa(((struct sockaddr_in *) & (ifr.ifr_addr))->sin_addr));
 close(sock);
 return 0;
}

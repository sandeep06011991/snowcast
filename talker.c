/*
** talker.c -- a datagram "client" demo
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>


struct talker_arg{
  char *listenerport; int *channel;
} ;


void broadcastmp3(int sockfd,struct addrinfo* p,int *channel){
  FILE *fp;int numbytes;int t=0;
	int buffersz=1000;
	char buffer[buffersz];
  int bfread=buffersz;
	//char out[]="hello";
	fp=NULL;

  int prev=-1;
	while(bfread== buffersz){
  if(prev!=*channel){
      prev=*channel;
      printf("%d setting channel",prev);
      if(fp!=NULL){fclose(fp);}
      switch(prev){
        case 0: fp=fopen("akon.mp3","r");
                printf("akon opened\n");
                break;
        case 1:fp=fopen("lakshya.mp3","r");
                fseek(fp,0,0);
                break;
        default:printf("Channel not found");
                exit(1);

        }
  }
  else{
    bfread=fread(buffer,1,buffersz,fp);
    if ((numbytes = sendto(sockfd, buffer, bfread , 0,
             p->ai_addr, p->ai_addrlen)) == -1) {
        perror("talker: sendto");
        exit(1);
    }
    t=t+numbytes;
    printf("Bytes transferred:%d% d\n",numbytes,bfread);
  	usleep(20000);
		}

	//printf("hwllo world\n");
	}
  if(fp!=NULL)fclose(fp);
}



int talkerfunc(struct talker_arg *arg){
    char *listenerport=arg->listenerport;
    int *channel=arg->channel;
    printf("Talker thread started with port:%s,channer: %d\n",listenerport,*channel);

    int sockfd;
    struct addrinfo hints, *servinfo, *p;
    int rv;
    int numbytes;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;

    if ((rv = getaddrinfo("localhost", listenerport, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and make a socket
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("talker: socket");
            continue;
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "talker: failed to create socket\n");
        return 2;
    }

    broadcastmp3(sockfd,p,channel);


    //
    // if ((numbytes = sendto(sockfd, argv[2], strlen(argv[2]), 0,
    //          p->ai_addr, p->ai_addrlen)) == -1) {
    //     perror("talker: sendto");
    //     exit(1);
    // }
    //
    // freeaddrinfo(servinfo);
    //
    // printf("talker: sent %d bytes to %s\n", numbytes, argv[1]);

  //  close(sockfd);

    return 0;
}

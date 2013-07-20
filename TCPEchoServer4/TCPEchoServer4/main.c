//
//  main.c
//  TCPEchoServer4
//
//  Created by Rohit Priyadarshi on 7/5/13.
//  Copyright (c) 2013 Rohit Priyadarshi. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFSIZE 2048
#define MAXPENDING 5

void DieWithUserMessage(const char *msg, const char *detail) {
    fputs(msg, stderr);
    fputs(": ", stderr);
    fputs(detail, stderr);
    fputc('\n', stderr);
    exit(1);
}

void DieWithSystemMessage(const char *msg) {
    perror(msg);
    exit(1);
}

void HandleTCPClient(int clntSocket)
{
    char buffer[BUFSIZE];
    
    ssize_t numBytesRcvd = recv(clntSocket, buffer, BUFSIZE, 0);
    if (numBytesRcvd < 0) {
        DieWithSystemMessage("recv() failed");
    }
    
    while (numBytesRcvd > 0) {
        ssize_t numBytesSent = send(clntSocket, buffer, numBytesRcvd, 0);
        if (numBytesSent < 0) {
            DieWithSystemMessage("send() failed");
        } else if (numBytesSent != numBytesRcvd) {
            DieWithUserMessage("send()", "sent unexpected number of bytes");
        }
        numBytesRcvd = recv(clntSocket, buffer, BUFSIZE, 0);
        if (numBytesRcvd < 0) {
            DieWithSystemMessage("recv() failed");
        }
    }
    close(clntSocket);
}

int main(int argc, const char * argv[])
{
    if (argc != 2) {
        DieWithUserMessage("Parameter(s)", "<Server Port>");
    }
    
    in_port_t servPort = atoi(argv[1]);
    int servSock;
    if ((servSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        DieWithSystemMessage("socket() failed");
    }
    
    struct sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(servPort);
    
    if (bind(servSock, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0) {
        DieWithSystemMessage("bind() failed");
    }
    if (listen(servSock, MAXPENDING) < 0) {
        DieWithSystemMessage("listen() failed");
    }
    
    for (;;) {
        struct sockaddr_in clntAddr;
        socklen_t clntAddrLen = sizeof(clntAddr);
        int clntSock = accept(servSock, (struct sockaddr *) &clntAddr, &clntAddrLen);
        if (clntSock < 0) {
            DieWithSystemMessage("accept() failed");
        }
        
        char clntName[INET_ADDRSTRLEN];
        if (inet_ntop(AF_INET, &clntAddr.sin_addr.s_addr, clntName, sizeof(clntName)) != NULL) {
            printf("Handling client %s/%d\n", clntName, ntohs(clntAddr.sin_port));
        } else {
            puts("Unable to get client address");
        }
        HandleTCPClient(clntSock);
    }
}


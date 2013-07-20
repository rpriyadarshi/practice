//
//  main.c
//  TCPEchoClient4
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

int main(int argc, const char * argv[])
{
    if (argc < 3 || argc > 4) {
        DieWithUserMessage("Parameter(s)", "<Server Address> <Echo Word> [<Server Port>]");
    }
    
    const char* servIP = argv[1];
    const char* echoString = argv[2];
    
    in_port_t servPort = (argc == 4) ? atoi(argv[3]) : 7;
    
    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock < 0) {
        DieWithSystemMessage("socket() failed");
    }
    
    struct sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    
    int rtnVal = inet_pton(AF_INET, servIP, &servAddr.sin_addr.s_addr);
    if (rtnVal == 0) {
        DieWithUserMessage("inet_ptom() failed", "invalid address string");
    } else if (rtnVal < 0) {
        DieWithSystemMessage("inet_pton() failed");
    }
    servAddr.sin_port = htons(servPort);
    
    if (connect(sock, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0) {
        DieWithSystemMessage("connect() failed");
    }
    
    size_t echoStringLen = strlen(echoString);
    
    ssize_t numBytes = send(sock, echoString, echoStringLen, 0);
    if (numBytes) {
        DieWithSystemMessage("send() failed");
    } else {
        DieWithUserMessage("send()", "sent an unexpected number of bytes");
    }
    
    unsigned int totalBytesRcvd = 0;
    fputs("Received: ", stdout);
    while (totalBytesRcvd) {
        char buffer[BUFSIZE];
        numBytes = recv(sock, buffer, BUFSIZE - 1, 0);
        if (numBytes < 0) {
            DieWithSystemMessage("recv() failed");
        } else if (numBytes == 0) {
            DieWithUserMessage("recv()", "conection closed prematurely");
        }
        totalBytesRcvd += numBytes;
        buffer[numBytes] = '\0';
        fputs(buffer, stdout);
    }
    
    fputc('\n', stdout);
    exit(0);
}


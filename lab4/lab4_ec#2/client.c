//written by Junhyeok Jeong

// client code for UDP socket programming 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h> 
  
#define IP_PROTOCOL 0 
#define IP_ADDRESS "127.0.0.1" // localhost 
#define PORT_NO 5000 
#define NET_BUF_SIZE 32 
#define cipherKey 'S' 
#define sendrecvflag 0 
  
// function to clear buffer 
void clearBuf(char* b) 
{ 
    int i; 
    for (i = 0; i < NET_BUF_SIZE; i++) 
        b[i] = '\0'; 
} 
  
// function for decryption 
char Cipher(char ch) 
{ 
    return ch ^ cipherKey; 
} 
  
// function to receive file 
int recvFile(char* buf, int s, FILE *write_file) 
{ 
    int i; 
    char ch;
 
    for (i = 0; i < s; i++) { 
        ch = buf[i]; 
        ch = Cipher(ch); 
        if (ch == EOF) 
            return 1; 
        else
            fprintf(write_file, "%c", ch);
            printf("%c", ch); 
    } 
    return 0; 
} 
  
// driver code 
int main() 
{ 
    int sockfd, nBytes; 
    struct sockaddr_in addr_con; 
    int addrlen = sizeof(addr_con); 
    addr_con.sin_family = AF_INET; 
    addr_con.sin_port = htons(PORT_NO); 
    addr_con.sin_addr.s_addr = inet_addr(IP_ADDRESS); 
    char net_buf[NET_BUF_SIZE]; 
    FILE *write_file;
  
    // socket() 
    sockfd = socket(AF_INET, SOCK_DGRAM, 
                    IP_PROTOCOL); 
  
    if (sockfd < 0) 
        printf("\nError: check your socket!!\n"); 
    else
        printf("\nfile will be received on socketfd %d\n", sockfd); 
  
    while (1) { 
        printf("\nPlease enter file name to receive:\n"); 
        scanf("%s", net_buf);
        write_file = fopen(net_buf, "w");

        sendto(sockfd, net_buf, NET_BUF_SIZE, 
               sendrecvflag, (struct sockaddr*)&addr_con, 
               addrlen); 
  
        printf("\n---------Data Received---------\n"); 
  
        while (1) { 
            // receive 
            clearBuf(net_buf); 
            nBytes = recvfrom(sockfd, net_buf, NET_BUF_SIZE, 
                              sendrecvflag, (struct sockaddr*)&addr_con, 
                              &addrlen); 
  
            // process 
            if (recvFile(net_buf, NET_BUF_SIZE, write_file)) { 
                break; 
            } 
        } 
        printf("\n-------------------------------\n"); 

        printf("\nthe requested file is received and stored successfully! And socket connection is end\n");
        break;
    }

     
    return 0; 
} 

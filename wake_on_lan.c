// Description: This program sends a Wake-on-LAN magic packet to wake up a machine on the local network.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/types.h>

int main()
{
    int i;
    unsigned char toSend[102], mac[6];
    struct sockaddr_in udpClient, udpServer;
    int broadcast = 1;

    // Create a UDP socket
    int udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (udpSocket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set the socket to allow broadcast
    if (setsockopt(udpSocket, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof broadcast) == -1) {
        perror("setsockopt (SO_BROADCAST)");
        close(udpSocket);
        exit(EXIT_FAILURE);
    }


    udpClient.sin_family = AF_INET;
    udpClient.sin_addr.s_addr = INADDR_ANY;
    udpClient.sin_port = 0;

    
    if (bind(udpSocket, (struct sockaddr*)&udpClient, sizeof(udpClient)) < 0) {
        perror("Bind failed");
        close(udpSocket);
        exit(EXIT_FAILURE);
    }


    // First 6 bytes are 0xFF
    for (i = 0; i < 6; i++)
        toSend[i] = 0xFF;


    // Replace with the actual MAC address of the target machine
    mac[0] = 0xAB;
    mac[1] = 0xCD;
    mac[2] = 0xEF;
    mac[3] = 0x12; // Replace with valid hex values
    mac[4] = 0x34;
    mac[5] = 0x56;

   // Fill the next 16 * 6 bytes with the MAC address
    for (i = 1; i <= 16; i++)
        memcpy(&toSend[i * 6], mac, 6 * sizeof(unsigned char));

    
    udpServer.sin_family = AF_INET;
    udpServer.sin_addr.s_addr = inet_addr("xxx.xxx.xxx.xxx"); // MODIFY, Use correct broadcast address
    udpServer.sin_port = htons(9); // Standard Wake-on-LAN port


    if (sendto(udpSocket, &toSend, sizeof(toSend), 0, (struct sockaddr*)&udpServer, sizeof(udpServer)) < 0) {
        perror("sendto failed");
        close(udpSocket);
        exit(EXIT_FAILURE);
    }

    printf("Magic packet sent successfully!\n");

    close(udpSocket);

    return 0;
}
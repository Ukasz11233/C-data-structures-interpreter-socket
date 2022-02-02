#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include "x_o.h"
int check(char (*)[]);
int generator(char (*)[], int, int *, int *);
void Print_array(char (*)[]);



int main(void)
{
    int socket_desc = socket(AF_INET, SOCK_STREAM, 0), new_socket, c, xy[2], counter = 0, result, x, y;
    char array[3][3] = {{' ', ' ', ' '},
                        {' ', ' ', ' '},
                        {' ', ' ', ' '}};

    if(socket_desc < 0)
    {
        printf("Could not create a socket.");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server, client;

    server.sin_port = htons(8520);
    server.sin_addr.s_addr = inet_addr("10.204.32.206");  //tutaj wpisz swoj adres ip
    server.sin_family = AF_INET;

    if(bind(socket_desc, (struct sockaddr *) &server, sizeof server) < 0)
    {
        printf("Could not bind.");
        exit(EXIT_FAILURE);
    }

    printf("Bind done\n");
    printf("Waiting for incoming connections...\n");

    //listen
    listen(socket_desc, 3);

    c = sizeof(struct sockaddr_in);


    while((new_socket = accept(socket_desc, (struct sockaddr *) &client, (socklen_t *) &c)))
    {
        printf("Connection accepted\n");
        while(counter < 5)
        {
            if (send(new_socket, array, sizeof(array), 0) < 0) {
                printf("Send array failure\n");
                exit(EXIT_FAILURE);
            }

            if(recv(new_socket, xy, sizeof(xy), 0) < 0)
            {
                printf("Receive XY failure.");
                exit(EXIT_FAILURE);
            }

            printf("%d %d\n", xy[0], xy[1]);
            array[xy[0]][xy[1]] = 'o';
            result = generator(array, 10, &x, &y);
            array[x][y] = 'x';
            counter++;
        }
        if (send(new_socket, array, sizeof(array), 0) < 0) {
            printf("Send array failure\n");
            exit(EXIT_FAILURE);
        }
        printf("Game over\n");
        counter = 0;
        for(int i = 0; i < 3; i++)
            for(int j = 0; j < 3; j++)
                array[i][j] = ' ';

    }

    return 0;
}
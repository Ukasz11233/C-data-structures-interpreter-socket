#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#define N 256

int main(void)
{
    int socket_desc;
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server;
    char buf[N], file_name[N];

    //FILE *wf;


    //Create socket
    if(socket_desc == -1)
    {
        printf("Couldn't create a socket.");
        exit(EXIT_FAILURE);
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(8006);
    server.sin_addr.s_addr = inet_addr("192.168.43.201");  //here you have to paste your IP adress

    if(connect(socket_desc, (struct sockaddr *) &server , sizeof (server)) < 0)
    {
        printf("Couldn't connect to the server.");
        exit(EXIT_FAILURE);
    }

    printf("Connected.\n");
    printf("Podaj nazwe pliku: ");
    fgets(file_name, N, stdin);

    if(send(socket_desc, file_name, strlen(file_name), 0) < 0)
    {
        printf("Send file name failure\n");
        exit(EXIT_FAILURE);
    }

    while(recv(socket_desc, buf, sizeof(buf), 0) > 0)
    {
        //printf("Otrzymalem buf:\n");
        fputs(buf, stdout);
        /*
        for(int i = 0; i < strlen(buf); i++)
        {
            if(buf[i] == '\n')
                break;
            if(buf[i] == EOF)
            {
                printf("Koniec pliku.\n");
                exit(EXIT_SUCCESS);
            }
            putchar(buf[i]);
        }
         */

    }
    printf("koniec pliku.\n");
    close(socket_desc);
    //printf("Send error.");
    return 0;
}

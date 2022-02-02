#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#define N 256

int main(void)
{
    int socket_desc = socket(AF_INET, SOCK_STREAM, 0), new_socket, c;
    char buf[N], file_name[N];
    FILE *wf;


    if(socket_desc < 0)
    {
        printf("Could not create a socket.\n");
        exit(EXIT_FAILURE);
    }

    //create server
    struct sockaddr_in server, client;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("192.168.43.201");  //here you have to paste your IP adress
    server.sin_port = htons(8006);

    //bind
    if(bind(socket_desc, (struct sockaddr *) &server, sizeof server) < 0)
    {
        printf("Could not bind.\n");
        exit(EXIT_FAILURE);
    }
    printf("Bind done\n");
    printf("Waiting for incoming connections...\n");

    //listen
    listen(socket_desc, 3);

    //accept incoming connection
    c = sizeof(struct sockaddr_in);
    while((new_socket = accept(socket_desc, (struct sockaddr *) &client, (socklen_t *) &c)))
    {
        printf("Connection accepted\n");

        if (recv(new_socket, file_name, sizeof(file_name), 0) < 0) {
            printf("Receive file name failure.\n");
            fflush(stdout);
            exit(EXIT_FAILURE);
        }

        for(int i = 0; i < N; i++)
            if (file_name[i] == '\n')
                file_name[i] = '\0';
        fputs(file_name, stdout);
        putchar('\n');

        if((wf = fopen(file_name, "r")) == NULL)
        {
            printf("Nie udalo sie otworzyc pliku.\n");
            exit(EXIT_FAILURE);
        }

        int status;

        while(fgets(buf, N, wf) != NULL)
        {
            /*
            here = strchr(buf, '\0');
            if(here)
            {
                *here = '\n';
                *(here + 1) = '\0';
            }
            */
            //printf("%d\n", strlen(buf));
            if((status = send(new_socket, buf, strlen(buf), 0)) < 0)
            {
                printf("Send failure.\n");
                exit(EXIT_FAILURE);
            }
            //printf("status: %d\n", status);
        }
        printf("Koniec pliku\n");
        close(new_socket);
    }


    printf("Done.\n");

    return 0;
}

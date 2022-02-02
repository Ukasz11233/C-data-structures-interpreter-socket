#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include "x_o.h"
void Print_array(char (*)[]);


int main(void)
{
    int socket_desc = socket(AF_INET, SOCK_STREAM, 0), counter = 0, xy[2], input_counter = 0;
    struct sockaddr_in client;
    char array[3][3], ch;

    if(socket_desc == -1)
    {
        printf("Couldn't create a socket.");
        exit(EXIT_FAILURE);
    }

    client.sin_addr.s_addr = inet_addr("10.204.32.206");  // tutaj wpisz swoj adres ip
    client.sin_port = htons(8520);
    client.sin_family = AF_INET;


    if(connect(socket_desc, (struct sockaddr *) &client , sizeof (client)) < 0)
    {
        printf("Couldn't connect to the server.");
        exit(EXIT_FAILURE);
    }

    printf("Connected.\n");
    int result;
    while(counter < 5)
    {
        if(recv(socket_desc, array, sizeof(array), 0) < 0)
        {
            printf("Error while receiving array.");
            exit(EXIT_FAILURE);
        }

        Print_array(array);
        result = check(array);
        printf("\n%d", result);

        if (result == MINIMUM)
        {
            printf("WYGRALES choc to niemozliwe..!\n");
            close(socket_desc);
            break;
        }
        else if (result == MAXIMUM)
        {
            system("clear");
            Print_array(array);
            printf("PRZEGRANA!\n");
            send(socket_desc, xy, sizeof(xy), 0);
            close(socket_desc);
            break;
        }

        printf("Podaj wspolrzedne x i y: ");
        input_counter = 0;
        while((ch = getchar()) != EOF && input_counter < 2)
        {
            if(ch == ' ')
                continue;

            if(ch >= '0' && ch <= '2')
            {
                if(input_counter == 0)
                    xy[0] = ch - '0';
                else
                    xy[1] = ch - '0';

                input_counter++;
            }
            if(input_counter == 2 && (array[xy[0]][xy[1]] == 'x' || array[xy[0]][xy[1]] == 'o'))
            {
                puts("To pole jest juz zajete! Podaj x i y: ");
                input_counter = 0;
                while(getchar() != '\n');
            }

        }

        if(send(socket_desc, xy, sizeof(xy), 0) < 0)
        {
            printf("XY send failure.");
            exit(EXIT_FAILURE);
        }
        counter++;
    }
    array[xy[0]][xy[1]] = 'o';
    Print_array(array);
    printf("Game over");
    close(socket_desc);


    return 0;
}
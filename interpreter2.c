#include <stdio.h>
#include <string.h>
#define N 100

void formula(double *, char *);
void doif(const char *, const int, double *);
void dowhile( char *, const int, double *);
int check_condition(double *, char *);


int check_condition(double *zmienne, char *arr)
{
    int k = 0;
    char zm1, zm2;
    if(strncmp(arr, "while", 5) == 0)
    {
        while (arr[k] != '\0')
        {
            if (arr[k] == '<')
            {
                if (arr[k + 1] == '=')
                {
                    sscanf(arr, "while(%c<=%c)", &zm1, &zm2);
                    if (zmienne[zm1] <= zmienne[zm2])
                        return 1;
                    else
                        return 0;
                }
                else
                {
                    sscanf(arr, "while(%c<%c)", &zm1, &zm2);
                    if (zmienne[zm1] < zmienne[zm2])
                        return 1;
                    else
                        return 0;
                }
            }
            else if (arr[k] == '>')
            {
                if (arr[k + 1] == '=')
                {
                    sscanf(arr, "while(%c>=%c)", &zm1, &zm2);
                    if (zmienne[zm1] >= zmienne[zm2])
                        return 1;
                    else
                        return 0;
                }
                else
                {
                    sscanf(arr, "while(%c>%c)", &zm1, &zm2);
                    if (zmienne[zm1] > zmienne[zm2])
                        return 1;
                    else
                        return 0;
                }
            }
            else if (arr[k] == '=')
            {
                if (arr[k + 1] == '=')
                {
                    sscanf(arr, "while(%c==%c)", &zm1, &zm2);
                    if (zmienne[zm1] == zmienne[zm2])
                        return 1;
                    else
                        return 0;
                }
            }
            k++;
        }
    }
    return 0;
}


void dowhile(char *str, const int flag, double *zmienne)
{
    if(flag == 1)
    {
        printf("PRAWDA\n");
        int a = 1;
        char  *beg, *end;
        printf("%s\n", str);
        beg = strchr(str, '{') + sizeof(char);
        while(a)
        {
            printf("%s\n", beg);
            end = strchr(beg, ';') + sizeof(char);
            if(strncmp(beg, "}elihw", 6) == 0)
            {
                printf("ZNALAZLEM KONIEC: %s\n", beg);
                if((a = check_condition(zmienne, str)) == 1)
                {
                    beg = str;
                    continue;
                }
                else if(a == 0)
                {
                   break;
                }
            }

            formula(zmienne, beg);
            beg = end;
        }
    }
    else
    {
        printf("nieprawda - %s\n", str);
        while(*str != '\0')
            str++;
    }

}


void doif(const char *str, const int flag, double *zmienne)
{
    if (flag == 1)
    {
        char *tmp, *beg, *end, *line_end;
        printf("prawda\n");
        beg = strchr(str, '{');
        end = strchr(str, '}');
        //printf("%c, %c\n", *end, *beg);
        while(1)
        {
            if((line_end = strchr(beg+1, ';')) == NULL)
                break;
            //fputs(beg+1, stdout);
            //putchar('\n');
            formula(zmienne, beg+1);
            beg = line_end;
        }
    }
    else
    {
        printf("nieprawda\n");
        while(*str != 'f' && *(str+1) != 'i')
            str++;
    }
}

void formula(double *zmienne, char *arr)
{
    //printf("%s\n", arr);
    char zm1, zm2, zm3;
    int j, k=0;
    if((j = sscanf(arr, "%c=%c+%c", &zm1, &zm2, &zm3)) == 3)
        zmienne[zm1] = zmienne[zm2] + zmienne[zm3];

    else if((j = sscanf(arr, "%c=%c*%c", &zm1, &zm2, &zm3)) == 3)
        zmienne[zm1] = zmienne[zm2] * zmienne[zm3];

    else if((j = sscanf(arr, "%c=%c/%c", &zm1, &zm2, &zm3)) == 3)
        zmienne[zm1] = zmienne[zm2] / zmienne[zm3];

    else if((j = sscanf(arr, "%c=%c-%c", &zm1, &zm2, &zm3)) == 3)
        zmienne[zm1] = zmienne[zm2] - zmienne[zm3];

    else if((j = sscanf(arr, "%c=-%c;", &zm1, &zm2)) == 2)
    {
        if(zm2 >= 'a' && zm2 <= 'z')
        {
            zmienne[zm1] = zmienne[zm2];
        }
        else
        {
            zmienne[zm2] = -(zm2 - '0');
            zmienne[zm1] = zmienne[zm2];
        }
    }
    else if((j = sscanf(arr, "%c=%c", &zm1, &zm2)) == 2)
    {
        if(zm2 >= 'a' && zm2 <= 'z')
        {
            zmienne[zm1] = zmienne[zm2];
        }
        else
        {
            zmienne[zm2] = zm2 - '0';
            zmienne[zm1] = zmienne[zm2];
        }
    }
    else if((j = sscanf(arr, "wypisz(%c)", &zm1)) == 1)
        printf("%lf\n", zmienne[zm1]);
    else if((j = sscanf(arr, "wczytaj(%c)", &zm1)) == 1)
        scanf("%lf", &zmienne[zm1]);


    else if(arr[0] == 'i' && arr[1] == 'f')
    {
        while(arr[k] != '\0')
        {
            if(arr[k] == '<')
            {
                if(arr[k+1] == '=')
                {
                    sscanf(arr, "if(%c<=%c)", &zm1, &zm2);
                    if(zm1 <= zm2)
                        doif(arr, 1, zmienne);
                    else
                        doif(arr, 0, zmienne);
                }
                else
                {
                    sscanf(arr, "if(%c<%c)", &zm1, &zm2);
                    if(zm1 < zm2)
                        doif(arr, 1, zmienne);
                    else
                        doif(arr, 0, zmienne);
                }
            }
            else if(arr[k] == '>')
            {
                if(arr[k+1] == '=')
                {
                    sscanf(arr, "if(%c>=%c)", &zm1, &zm2);
                    if(zm1 >= zm2)
                        doif(arr, 1, zmienne);
                    else
                        doif(arr, 0, zmienne);
                }
                else
                {
                    sscanf(arr, "if(%c>%c)", &zm1, &zm2);
                    if(zm1 > zm2)
                        doif(arr, 1, zmienne);
                    else
                        doif(arr, 0, zmienne);
                }
            }
            else if(arr[k] == '=')
                if(arr[k+1] == '=')
                {
                    sscanf(arr, "if(%c==%c)", &zm1, &zm2);
                    if (zm1 == zm2)
                        doif(arr, 1, zmienne);
                    else
                        doif(arr, 0, zmienne);
                }
            k++;
        }
    }

    else if(strncmp(arr, "while", 5) == 0)
    {
        while (arr[k] != '\0')
        {
            if (arr[k] == '<')
            {
                if (arr[k + 1] == '=')
                {
                    sscanf(arr, "while(%c<=%c)", &zm1, &zm2);
                    if (zmienne[zm1] <= zmienne[zm2])
                        dowhile(arr, 1, zmienne);
                    else
                        dowhile(arr, 0, zmienne);
                }
                else
                {
                    sscanf(arr, "while(%c<%c)", &zm1, &zm2);
                    if (zmienne[zm1] < zmienne[zm2])
                        dowhile(arr, 1, zmienne);
                    else
                        dowhile(arr, 0, zmienne);
                }
            }
            else if (arr[k] == '>')
            {
                if (arr[k + 1] == '=')
                {
                    sscanf(arr, "while(%c>=%c)", &zm1, &zm2);
                    if (zmienne[zm1] >= zmienne[zm2])
                        dowhile(arr, 1, zmienne);
                    else
                        dowhile(arr, 0, zmienne);
                }
                else
                {
                    sscanf(arr, "while(%c>%c)", &zm1, &zm2);
                    if (zmienne[zm1] > zmienne[zm2])
                        dowhile(arr, 1, zmienne);
                    else
                        dowhile(arr, 0, zmienne);
                }
            }
            else if (arr[k] == '=')
            {
                if (arr[k + 1] == '=')
                {
                    sscanf(arr, "while(%c==%c)", &zm1, &zm2);
                    if (zmienne[zm1] == zmienne[zm2])
                        dowhile(arr, 1, zmienne);
                    else
                        dowhile(arr, 0, zmienne);
                }
            }
            k++;
        }
    }
}



int main(void)
{
    char arr[N][N] = {"a=-5", "c=4", "while(a<=c){a=5;c=2;while(a<=c){a=0;}elihw}elihw", "wypisz(a)"};  // zagniezdzenia nie dzialaja.
    //char arr[N][N] = {"a=-5", "c=4", "b=a-c", "d=a*c", "e=b", "wypisz(a)", "if(a<c){g=b;a=c*e;wypisz(a);wypisz(c);if(a<c){g=8;}fi}fi"};
    double zmienne[256];
    for(char i = '0'; i < '0' + 10; i++)
        zmienne[i] = i - '0';
    for(int i = 0; i < N; i++)
    {
        if(arr[i][0] == '\0')
            continue;
        formula(zmienne, arr[i]);
    }
    return 0;
}
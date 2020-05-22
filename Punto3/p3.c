#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        printf("El programa acepta unicamente dos parametros, el numero de lines y en nombre del archivo \n");
        return -1;
    }

    char* fileName = argv[2];
    int lines = atoi(argv[1]);
    int size = 0;
    char *character, *buf, *begin;
    FILE* file;
    if (NULL == (file = fopen(fileName, "r")))
    {
            printf("Error al abrir el archivo: %s\n", fileName);
            return -1;
    }
    fseek(file, 0, SEEK_END);
    size = ftell(file) - 1;
    character = (char *)malloc(2);
    buf = (char *)malloc(80 * lines);
    memset(buf, 0, 80 * lines);
    begin = buf;
    *buf++ = 0;
    while(size && lines)
    {
            size--;
            fseek(file, size , SEEK_SET);
            fread(character, 1, 1, file);
            *buf++ = *character;
            if(*character == '\n')
            {
                lines--;
            }
    }
    fclose (file);
    while (begin != buf)
    {
        printf ("%c", *buf--);
    }
    printf ("\n");
    return 0;
}

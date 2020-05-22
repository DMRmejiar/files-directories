#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

char* format_time(time_t);

int main(int argc, char* argv[])
{
    struct stat stat_struct;
    char* fileType;
    if (argc > 2) 
    {
        printf ("El programa solo acepta un parametro \n");
        return 1;
    }
    else if (argc < 2)
    {
        printf ("El programa requiere de un parametro \n");
        return 1;
    }

    char* fileName = argv[1];

    if (stat(argv[1], &stat_struct) < 0)
    {
        printf ("Error leyendo el archivo \n");
        return 1;
    }

    if (S_ISDIR(stat_struct.st_mode)) 
    {
        fileType = "Directory";
    } 
    else if (S_ISLNK(stat_struct.st_mode)) 
    {
        fileType =  "Symbolic Link";
    } 
    else 
    {
        fileType = "File";
    }

    printf ("Permissions:\t");
    printf ( (S_ISDIR(stat_struct.st_mode))  ? "d" : "-");
    printf ( (stat_struct.st_mode & S_IRUSR) ? "r" : "-");
    printf ( (stat_struct.st_mode & S_IWUSR) ? "w" : "-");
    printf ( (stat_struct.st_mode & S_IXUSR) ? "x" : "-");
    printf ( (stat_struct.st_mode & S_IRGRP) ? "r" : "-");
    printf ( (stat_struct.st_mode & S_IWGRP) ? "w" : "-");
    printf ( (stat_struct.st_mode & S_IXGRP) ? "x" : "-");
    printf ( (stat_struct.st_mode & S_IROTH) ? "r" : "-");
    printf ( (stat_struct.st_mode & S_IWOTH) ? "w" : "-");
    printf ( (stat_struct.st_mode & S_IXOTH) ? "x" : "-");
    printf ("\n");

    printf ("File:\t\t%s\n",                          fileName);
    printf ("File type:\t%s\n",                     fileType);
    printf ("Size:\t\t%ld bytes\n",                    stat_struct.st_size);
    printf ("Blocks:\t\t%ld\n",                        stat_struct.st_blocks);
    printf ("Block size:\t%ld\n",                     stat_struct.st_blksize);
    printf ("Links:\t\t%ld\n",                          stat_struct.st_nlink);
    printf ("User (ID):\t%d\n",                     stat_struct.st_uid);
    printf ("Group (ID):\t%d\n",                    stat_struct.st_gid);
    printf ("Time of last access:\t\t%s",             format_time(stat_struct.st_atime));
    printf ("Time of creation:\t\t%s",             format_time(stat_struct.st_ctime));
    printf ("Time of last modification:\t%s\n",     format_time(stat_struct.st_mtime));
    return 0;
}

char* format_time(time_t time) 
{
    return ctime(&time);
}

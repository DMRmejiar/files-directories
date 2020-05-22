#include <stddef.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <time.h>

char* format_time(time_t);

int main(int argc, char *argv[]) 
{
    struct dirent* structDirent;
    DIR* dir;
    struct stat structStat;
    int flag = 0;
    
    if (argc > 2)
    {
        printf("El programa solo puede recibir un parametro como maximo \n");
        return -1;
    }

    switch (argc)
    {
        case 2:
        if (strcmp(argv[1],"-l") != 0)
        {
            printf ("El programa solo puede aceptar como parametro -l o ningun parametro \n");
            return -1;
        }
        flag = 1;
        break;

        default:
        break;
    }

    dir = opendir(".");
    while ((structDirent = readdir(dir)) != NULL)
    {
        printf("%s\n", structDirent->d_name);
        if ( (strcmp(structDirent->d_name, ".")!=0) && (strcmp(structDirent->d_name, "..")!=0) )
        {
            if (flag == 1)
            {
                if (stat(structDirent->d_name, &structStat) < 0)
                {
                    printf ("Error leyendo el archivo \n");
                    return -1;
                }
                struct passwd* pwd = getpwuid(structStat.st_uid);
                struct group* grp = getgrgid(structStat.st_gid);

                printf("Permissions\tLinks\tUser\t\tGroup\t\tSize\tLast time of modification\n");

                printf ( (S_ISDIR(structStat.st_mode))  ? "d" : "-");
                printf ( (structStat.st_mode & S_IRUSR) ? "r" : "-");
                printf ( (structStat.st_mode & S_IWUSR) ? "w" : "-");
                printf ( (structStat.st_mode & S_IXUSR) ? "x" : "-");
                printf ( (structStat.st_mode & S_IRGRP) ? "r" : "-");
                printf ( (structStat.st_mode & S_IWGRP) ? "w" : "-");
                printf ( (structStat.st_mode & S_IXGRP) ? "x" : "-");
                printf ( (structStat.st_mode & S_IROTH) ? "r" : "-");
                printf ( (structStat.st_mode & S_IWOTH) ? "w" : "-");
                printf ( (structStat.st_mode & S_IXOTH) ? "x" : "-");
                
                printf("\t%ld", structStat.st_nlink);
                printf("\t%u (%s)", structStat.st_uid, pwd->pw_name);
                printf("\t%u (%s)", structStat.st_gid, grp->gr_name);
                printf("\t%ld", structStat.st_size);
                printf("\t%s", format_time(structStat.st_mtime));
                
            }
        }
    }
    closedir(dir);
    return 0;
}

char* format_time(time_t time) 
{
    return ctime(&time);
}
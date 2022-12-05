#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <time.h>
#include <fcntl.h>
// TODO chdir("./js")
void menu(char* dir_name)  {
    char * time_buffer[100], * dir_buffer;
    DIR *dir;
    struct dirent *ent;
    struct stat file_stat;
    int ret;
    int dir_name_size = strlen(dir_name);
    if ((dir = opendir(dir_name)) != NULL)
    {
        /*
        ret = stat(buffer, &file_stat);
        printf("%s\n", buffer);
        strftime(time_buffer, sizeof(time_buffer), "%D %T", gmtime(&file_stat.st_atim.tv_sec));
        printf("%s\n", time_buffer);*/
        while ((ent = readdir(dir)) != NULL)
        {
            if(strcmp(ent->d_name, "..") != 0 && strcmp(ent->d_name, ".") != 0) {
                dir_buffer = malloc(dir_name_size+strlen(ent->d_name)+2);
                strcpy(dir_buffer, dir_name);
                dir_buffer[dir_name_size] = '/';
                strcpy(dir_buffer+dir_name_size+1, ent->d_name);
                if (ent->d_type == DT_DIR){
                    menu(dir_buffer);
                } else {
                    ret = stat(dir_buffer, &file_stat);
                    if ((file_stat.st_mode | S_IEXEC) == file_stat.st_mode)
                    {
                        printf("%s\n", ent->d_name);
                    }
                }
                free(dir_buffer);
                
            }
            
        }
        closedir(dir);
    }
    return;
}
int main(int argc, char **argv)
{
    char *last_dir = "\0";
    char *cur_dir = getcwd(NULL, PATH_MAX);
    char time_buffer[100];
    DIR *dir;
    struct dirent *ent;
    struct stat file_stat;
    int ret;
    if ((dir = opendir(cur_dir)) != NULL)
    {
        while ((ent = readdir(dir)) != NULL)
        {
            if(strcmp(ent->d_name, "..") != 0 && strcmp(ent->d_name, ".") != 0) {
                if (ent->d_type == DT_DIR){
                    ret = stat(ent->d_name, &file_stat);
                    printf("%s\n", ent->d_name);
                    strftime(time_buffer, sizeof(time_buffer), "%D %T", gmtime(&file_stat.st_atim.tv_sec));
                    printf("%s\n", time_buffer);
                }
                
            }
            
        }
        closedir(dir);
    }
    
    menu(cur_dir);
    free(cur_dir);
}

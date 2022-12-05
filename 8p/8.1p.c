#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
int main(int argc, char **argv)
{
    if(argc < 2){
        return 0;
    }
    DIR *dir;
    struct dirent *ent;
    char buff[PATH_MAX];
    int fd, inode, bufsize, path_len = strlen(argv[1]); 
    if ((dir = opendir(argv[1])) != NULL)
    {
        while ((ent = readdir(dir)) != NULL)
        {
            chdir(argv[1]);
            if(ent->d_type == DT_LNK){
                printf("%s %ld ", ent->d_name, ent->d_ino);
                bufsize = readlink(ent->d_name, buff, sizeof(buff)-1);
                buff[bufsize] = '\0';
                int fd, inode, ret;
                struct stat file_stat;
                ret = stat(buff, &file_stat);
                if (ret < 0)
                {
                    continue;
                }
                printf("%s %ld\n", buff ,file_stat.st_ino);
            }
        }
        closedir(dir);
    } else {
        char *buffer = malloc(path_len+4);
        strcpy(buffer, argv[1]);
        strcpy(buffer+path_len, "new");
        printf("%s\n", buffer);
        FILE *infile = fopen(argv[1], "r");
        int disc = open(buffer, O_CREAT|O_RDWR|O_EXCL, S_IRWXU);
        int n = 1;
        if(disc < 0){
            printf("U want to rewrite file?\n");
            scanf("%d", &n);
            getchar();
            if(n == 0){
                return 0;
            } else {
                disc = open(buffer, O_CREAT|O_RDWR, S_IRWXU);
            }
        }
        close(disc);
        FILE *file = fopen(buffer, "w");
        int begin = 0, end = 0, main = 0, bflag = 1, prevflag = 1, mflag = 0, last;
        int i = 0;
        char c;
        while((c = fgetc(infile)) != EOF){
            if(c == ' ' || c == '\n' || c == '\t'){
                if(prevflag == 0 && mflag == 1){
                    mflag = 0;
                    main = i;
                }
                prevflag = 1;
            } else {
                if(bflag){
                    begin  = i;
                    mflag = 1;
                    bflag = 0;
                }
                if(prevflag){
                    end = i;
                    prevflag = 0;
                }
            }
            i++;
        }
        int counter;
        printf("%d %d %d\n", begin, end, main);
        fseek(infile, 0, SEEK_SET);
        if(begin == end) { //одно слово
            while((c = fgetc(infile)) != EOF){
                fputc(c, file);
            }
            fclose(file);
            fclose(infile);
            
            return 0;
        }
        if(begin != end){ //два слова и более
            c = fgetc(infile);
            while(c == ' '|| c == '\n' || c == '\t'){ // до первого слова
                fputc(c, file);
                c = fgetc(infile);
            }
            counter = end;
            fseek(infile, end, SEEK_SET);
            c = fgetc(infile);
            while(c != ' '&& c != '\n' && c != '\t'){ // последнее слово
                fputc(c, file);
                c = fgetc(infile);
                counter ++;
            }
            last = counter;
            fseek(infile, main, SEEK_SET);
            counter = main;
            c = fgetc(infile);
            while(counter < end){ // все в середине
                fputc(c, file);
                c = fgetc(infile);
                counter ++;
            }
            fseek(infile, begin, SEEK_SET);
            c = fgetc(infile);
            while(c != ' '&& c != '\n' && c != '\t'){ // первое слово
                fputc(c, file);
                c = fgetc(infile);
            }
            fseek(infile, last, SEEK_SET);
            c = fgetc(infile);
            while(c != EOF){ // последние пробелы
                fputc(c, file);
                c = fgetc(infile);
            }
        }
    }
}
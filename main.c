#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include <string.h>
#include <dirent.h>

void newName(char *, int, char);

int main(int argc, char * argv[]) {
    char * defaultWay = "E:/folder";
    char numbersFlag = 0;
    DIR * dir;
    struct dirent * A;

    char * way = defaultWay;
    char old_way[255], new_way[255];
    char name[12], format[10];
    char * temp = NULL;

    srand(time(NULL));

    int i;
    for(i = 0; i < argc; i++) {
        if(!strcmp(argv[i], "-numbers"))
            numbersFlag = 1;
        if(!strcmp(argv[i], "-way")) {
            if(argc <= i + 1 || argv[i + 1][0] == '-') {
                printf("wrong arguments\n");
                return 0;
            }
            way = argv[i + 1];
            i++;
        }
    }

    if(dir = opendir(way)) {
        while(A = readdir(dir)) {
            memset(old_way, 0, 255);
            memset(new_way, 0, 255);

            strcat(old_way, way);
            strcat(old_way, "/");
            strcat(old_way, A->d_name);

            strcat(new_way, way);
            strcat(new_way, "/");

            if(numbersFlag) newName(name, 8, 1);
            else newName(name, 11, 0);

            strcat(new_way, name);

            temp = strrchr(A->d_name, '.');
            if(temp) {
                memset(format, 0, 10);
                strcat(format, temp + 1);
                strcat(new_way, ".");
                strcat(new_way, format);

                rename(old_way, new_way);
            }
        }
        closedir(dir);
    } else printf("Folder isn't find\n");

    return 0;
}

void newName(char * str, int lenght, char numbersFlag) {
    int newSym;
    str[lenght] = 0;
    while(lenght--)
        if(numbersFlag) *str++ = rand() % 10 + '0';
        else *str++ = (newSym = rand() % 62) < 10 ? newSym + '0' : newSym < 36 ? newSym + 'A' - 10 : newSym + 'a' - 36;
        //*str++ = (newSym = rand() % 64) < 10 ? newSym + '0' : newSym < 36 ? newSym + 'A' - 10 : newSym < 62 ? newSym + 'a' - 36 : newSym == 63 ? '-' : '_';
}

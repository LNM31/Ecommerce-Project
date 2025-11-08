#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <time.h>
#include <dirent.h>
#include <fcntl.h>
#include <ctype.h>

#define MAX_USERS 100
#define BRED "\e[1;31m"
#define BGRN "\e[1;32m"
#define reset "\e[0m"

typedef struct {
    int id;
    char name[32];
    float x,y;
    char clue[128];
    int value;
}treasure;

typedef struct {
    char name[32];
    int total;
}score;

void init_score(score *v,int max_size)
{
   for(int i=0;i<max_size;i++)
   {
      strcpy(v[i].name,"");
      v[i].total=0;
   }
}
void score_hunt(const char * hunt_id)
{
   char file_path[256];
     snprintf(file_path,sizeof(file_path),"%s/treasures.dat",hunt_id);

     struct stat info;
     //1.Verificare existenta director
     if(stat(hunt_id,&info)!=0)
     {
        printf("This hunt doesn't exist!\n");
        return;
     }
     else if(S_ISDIR(info.st_mode)==0)
     {
        printf("It is not a directory!\n");
        return;
     }

     //2.Deschidere fisier treasure.dat
     int fd=open(file_path,O_RDONLY);
     if(fd==-1)
     {
        perror("The file couldn't be opened or it doesn't exist!");
        exit(-1);
     }

     //3.Citire
     score array[MAX_USERS];
     init_score(array,MAX_USERS);
     int size=0; //number of users initially
     treasure t;
     ssize_t bytes;
     while((bytes=read(fd,&t,sizeof(treasure)))==sizeof(treasure))
     {
        int ok=0;
        for(int i=0;i<size;i++)
        {
            if(strcmp(t.name,array[i].name)==0)
            {
               ok=1;
               array[i].total+=t.value;
               break;
            }
        }
        if(ok==0)
        {
         strcpy(array[size].name,t.name);
         array[size++].total=t.value;
        }

     }
     if(bytes!=0)
     {
         printf("Error at reading!\n");
         return;
     }
     

     if(close(fd)!=0)
     {
        perror("Error at closing!");
        exit(-1);
     }
     printf(BGRN "The scores for %s:\n" reset,hunt_id);
     for(int i=0;i<size;i++)
     {
      printf("NAME:%s TOTAL:%d\n",array[i].name,array[i].total);
     }

}

int main(int argc,char **argv)
{
    if(argc!=2)
    {
      perror("Not enough arguments!");
      exit(-1);
    }
    score_hunt(argv[1]);
    return 0;
}
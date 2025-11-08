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

#define COMMAND_FILE "comand.txt"
#define BMAG "\e[1;35m"
#define reset "\e[0m"

typedef struct {
    int id;
    char name[32];
    float x,y;
    char clue[128];
    int value;
}treasure;

int pipe_main_monitor[2]; //the pipe that connects the proccesses to the main proccess

pid_t monitor_pid=-1;
int monitor_running=0;
int monitor_stopping=0;

void remove_final_spaces(char *str) 
{
   int len = strlen(str);
   while (len > 0 && isspace((unsigned char)str[len - 1])) 
   {
       str[--len] = '\0';
   }
}
//=================================List_Hunts_Begin=================================================================
int number_of_treasures(const char * hunt_id)
{
   char file_path[256];
     snprintf(file_path,sizeof(file_path),"%s/treasures.dat",hunt_id);

     struct stat info;
     //1.Verificare existenta director
     if(stat(hunt_id,&info)!=0)
     {
        perror("This hunt doesn't exist!");
        exit(-2);
     }
     else if(S_ISDIR(info.st_mode)==0)
     {
        perror("It is not a directory!");
        exit(-1);
     }

     //2.Deschidere fisier treasure.dat
     int fd=open(file_path,O_RDONLY);
     if(fd==-1)
     {
        perror("The file couldn't be opened or it doesn't exist!");
        exit(-1);
     }

     //3.Citire
     treasure t;
     ssize_t bytes;
     int count=0;
     while((bytes=read(fd,&t,sizeof(treasure)))==sizeof(treasure))
     {
        count++;
     }
     if(bytes!=0)
     {
         perror("Error at reading!");
         exit(-2);
     }
     

     if(close(fd)!=0)
     {
        perror("Error at closing!");
        exit(-1);
     }

     return count;
}
void list_hunts()
{
    DIR *dir=opendir(".");
    if(dir==NULL)
    {
        perror("Error opening directory!");
        exit(-1);
    }
    
    struct dirent *info;
    int ok=0;
    
    while((info=readdir(dir))!=NULL)
    {
        if(strcmp(info->d_name,".")==0 || strcmp(info->d_name,"..")==0)
        continue;
        
        if(info->d_type == DT_DIR)
        {
            ok=1;
            printf("Hunt_Name:%s  Number of treasures:%d\n",info->d_name,number_of_treasures(info->d_name));
        }
        
    }
    if(ok==0)
    {
      printf("There are not any hunts!\n");
    }
    closedir(dir);
}
//=================================List_Hunts_END=================================================================
//=================================List_Treasures_BEGIN=================================================================
void display_treasure(const treasure *t)
{
    char str[512];
    snprintf(str,sizeof(str),"ID:%d,User_Name:%s,Lat:%f,Long:%f,Clue:%s,Value:%d;\n",t->id,t->name,t->x,t->y,t->clue,t->value);
    write(1,str,strlen(str));
}
void list_treasures(char *hunt_id)
{
     char file_path[256];
     snprintf(file_path,sizeof(file_path),"%s/treasures.dat",hunt_id);

     struct stat info;
     //1.Verificare existenta director
     if(stat(hunt_id,&info)!=0)
     {
        printf("That hunt doesn't exist!\n");
        return;
     }
     else if(S_ISDIR(info.st_mode)==0)
     {
        printf("It isn't a directory.The hunt must be a directory!\n");
        return;
     }

     //2.Nume
     write(1,"Hunt Name: ",11);
     write(1,hunt_id,strlen(hunt_id));

     //3.Verificare existenta treasure.dat 
     if(stat(file_path,&info)!=0)
     {
        printf("The file treasure.dat doesn't exist!\n");
        return;
     }
     else if(S_ISREG(info.st_mode)==0)
     {
        printf("The file treasure is not a regular file!\n");
        return;
     }

     //4.Total size
     char total_size[128];
     snprintf(total_size,sizeof(total_size),"\nTotal size in bytes: %ld\n",info.st_size);
     write(1,total_size,strlen(total_size));

     //5.Last modification
     char last_modification[128];
     snprintf(last_modification,sizeof(last_modification),"Last modification : %s",ctime(&info.st_mtime));
     write(1,last_modification,strlen(last_modification));

     //6.List of treasures
     treasure t;
     int fd=open(file_path,O_RDONLY);
     if(fd==-1)
     {
        perror("Eroare deschidere fisier");
        exit(-1);
     }
     ssize_t bytes_read;
     while((bytes_read=read(fd,&t,sizeof(treasure))) == sizeof(treasure))
     {
        display_treasure(&t);
     }
     
     if(bytes_read!=0)
     {
        printf("An error ocurred at reading treasures!\n");
     }

     if(close(fd)!=0)
     {
        perror("Error at closing file");
        exit(-1);
     }
}
//=================================List_Treasures_END=================================================================
//==================================View_Treasure_BEGIN=================================================================
void view_treasure(const char *hunt_id,int id)
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
        printf("It's not a directory.The hunt must be a directory!\n");
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
     treasure t;
     ssize_t bytes;
     int found=0;
     while((bytes=read(fd,&t,sizeof(treasure)))==sizeof(treasure))
     {
        if(t.id==id)
        {
            found=1;
            break;
        }
     }
     if(found==1)
     {
        display_treasure(&t);
     }
     else
     {
        write(1,"This treasure hasn't been found!\n",34);
        if(close(fd)!=0)
            {
                perror("Error closing file!");
                exit(-1);
            }
        return;
     }

     if(close(fd)!=0)
     {
        perror("Error closing!");
        exit(-1);
     }
}
//==================================View_Treasure_END=================================================================
void calculate_score()
{
   DIR *dir=opendir(".");
    if(dir==NULL)
    {
        perror("Error opening directory!");
        exit(-1);
    }
    
    struct dirent *info;
    
    int pipe_monitor_nephews[2];
    
    if(pipe(pipe_monitor_nephews)<0)
    {
      perror("Error creating pipe");
      exit(-1);
    }

    while((info=readdir(dir))!=NULL)
    {
        if(strcmp(info->d_name,".")==0 || strcmp(info->d_name,"..")==0)
        continue;
        
        if(info->d_type == DT_DIR)
        {
            pid_t pid=fork();
            if(pid<0)
            {
               perror("Error creating proccess");
               exit(-1);
            }
            else if(pid==0)
            {
               close(pipe_monitor_nephews[0]); //doesn't read
               dup2(pipe_monitor_nephews[1],1);
               close(pipe_monitor_nephews[1]);

               execlp("./score_program","./score_program",info->d_name,NULL);
               perror("Error execlp");
               exit(-1);
            }
        }
    }

    close(pipe_monitor_nephews[1]);
    
    while(wait(NULL) > 0); //waits for all nephews to end

    char buffer[512];
    ssize_t bytes;
    while((bytes=read(pipe_monitor_nephews[0],buffer,sizeof(buffer)-1)))
    {
       buffer[bytes]='\0';
       printf("%s",buffer);
    }
    close(pipe_monitor_nephews[0]);
    closedir(dir);
}
void handler1(int sig)
{
   char buffer[256];
   int fd=open(COMMAND_FILE,O_RDONLY);
   if(fd==-1)
   {
      perror("Error opening comand_file");
      exit(-1);
   }

   int bytes=read(fd,buffer,sizeof(buffer)-1);
   if(bytes<=0)
   {
      perror("Error reading");
      close(fd);
      return;
   }
   buffer[bytes]='\0';

   if(close(fd)!=0)
   {
      perror("Error closing comand_file");
      exit(-2);
   }


   char *p=strtok(buffer," \n");
   if(p==NULL)
      return;
   if(strcmp(p,"list_hunts")==0)
   {
      list_hunts();
   }
   else if(strcmp(p,"list_treasures")==0)
   {
      char *hunt_id=strtok(NULL," \n");
      if(hunt_id) list_treasures(hunt_id);
      else printf("Missing hund_id\n");
   }
   else if(strcmp(p,"view_treasure")==0)
   {
      char *hunt_id=strtok(NULL," \n");
      char *id=strtok(NULL," \n");
      if(hunt_id && id) view_treasure(hunt_id,strtol(id,NULL,10));
      else printf("Missing hunt_id or id\n");
   }
   else if(strcmp(p,"calculate_score")==0)
   {
      calculate_score();
   }
   else
   {
      printf("Unkown command\n");
   }
}
void handler2(int sig)
{
   printf("Stopping monitor...\n");
   usleep(3000000);
   exit(0);
}
void handler_sigchld(int sig)
{
   int status;
   waitpid(monitor_pid,&status,0);
   printf("\nMonitor ended with code %d\n",WEXITSTATUS(status));
   monitor_running=0;
   monitor_pid=-1;
   monitor_stopping=0;
}
void monitor_loop()  //child procces
{
   struct sigaction act1,act2;
   act1.sa_handler=handler1;
   sigemptyset(&act1.sa_mask);
   act1.sa_flags=0;
   sigaction(SIGUSR1,&act1,NULL);

   act2.sa_handler=handler2;
   sigemptyset(&act2.sa_mask);
   act2.sa_flags=0;
   sigaction(SIGUSR2,&act2,NULL);

   struct sigaction act_chld;
   act_chld.sa_handler = SIG_IGN; // ignores the SIGCHLD from nephews
   sigemptyset(&act_chld.sa_mask);
   act_chld.sa_flags = 0;
   sigaction(SIGCHLD, &act_chld, NULL);


   while(1)
   {
      pause(); //waits for signals
   } 
}
//=================================Start_Monitor_BEGIN=================================================================
void start_monitor()
{
    if(monitor_running)
    {
        printf("Monitor is already running\n");
        return;
    }

    if(pipe(pipe_main_monitor)<0)
    {
      perror("Error at creating the pipe");
      exit(-1);
    }

    pid_t pid=fork();

    if(pid<0)
    {
        perror("Child not created.Error!\n");
        exit(-1);
    }
    else if (pid==0)
    {
        close(pipe_main_monitor[0]);// closes reading side
        dup2(pipe_main_monitor[1],1); 
        close(pipe_main_monitor[1]);// closes pipe_main_monitor[1](initially the writting side of the pipe was refferd by pipe_main_monitor[1] and 1),now 1 refers to the writting side of the pipe
        monitor_loop();
        exit(0);
    }
    else
    {
        close(pipe_main_monitor[1]); //the main proccess doesn't write
        monitor_pid=pid;
        monitor_running=1;
        monitor_stopping=0;
        printf("Monitor has started with pid %d\n",monitor_pid);
    }
}
//=================================Start_Monitor_END=================================================================
void write_command(const char *linie)
{
   int fd=open(COMMAND_FILE,O_WRONLY | O_CREAT | O_TRUNC,0777);
   if(fd<0)
   {
      perror("Error opening for writting");
      exit(-2);
   }
   write(fd,linie,strlen(linie));
   kill(monitor_pid,SIGUSR1);
   usleep(50000);

   char buffer[8192];
   ssize_t bytes;
   if((bytes=read(pipe_main_monitor[0],buffer,sizeof(buffer)-1)) > 0)
   {
      buffer[bytes]='\0';
      printf("%s",buffer);
   }

   if(close(fd)!=0)
   {
      perror("Error closing file for writting");
      exit(-1);
   }

}

void prompt_runner()
{
   struct sigaction sa;
   sa.sa_handler=handler_sigchld;
   sigemptyset(&sa.sa_mask);
   sa.sa_flags=0;
   sigaction(SIGCHLD,&sa,NULL);

   char input[256];

    while(1)
    {

      printf(BMAG "prompt > " reset);
      fflush(stdout);

      if (fgets(input, sizeof(input), stdin) == NULL)
      {
        clearerr(stdin); //It avoids an infinte loop of empty prompts
        continue;
      }
      input[strcspn(input,"\n")]='\0';
      remove_final_spaces(input);

      if(strcmp(input,"start_monitor")==0)
      {
         start_monitor();
      }
      else if(strcmp(input,"list_hunts")==0)
      {
         if(monitor_running==0) printf("Monitor not running\n");
         else if(monitor_stopping==1) printf("Monitor is stopping.You cannot type any other command!\n");
         else write_command("list_hunts");
      }
      else if(strncmp(input,"list_treasures",14)==0)
      {
         if(monitor_running==0) printf("Monitor not running\n");
         else if(monitor_stopping==1) printf("Monitor is stopping.You cannot type any other command!\n");
         else write_command(input);
      }
      else if(strncmp(input,"view_treasure",13)==0)
      {
         if(monitor_running==0) printf("Monitor not running\n");
         else if(monitor_stopping==1) printf("Monitor is stopping.You cannot type any other command!\n");
         else write_command(input);
      }
      else if(strncmp(input,"calculate_score",15)==0)
      {
         if(monitor_running==0) printf("Monitor not running\n");
         else if(monitor_stopping==1) printf("Monitor is stopping.You cannot type any other command!\n");
         else write_command(input);
      }
      else if(strcmp(input,"stop_monitor")==0)
      {
         if(monitor_running==0) printf("Monitor not running\n");
         else
         {
            kill(monitor_pid,SIGUSR2);
            usleep(1000);

            char buffer[128];
            ssize_t bytes;
            if((bytes=read(pipe_main_monitor[0],buffer,sizeof(buffer)-1)) > 0)
            {
               buffer[bytes]='\0';
               printf("%s",buffer);
            }

            monitor_stopping=1;
         }
      }
      else if(strcmp(input,"exit")==0)
      {
         if(monitor_running) printf("Monitor is still running\n");
         else break;
      }
      else
      {
         printf("Unkown command!\n");
      }
    }
}
int main()
{
    prompt_runner();
    return 0;
}
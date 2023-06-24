emon.c//C
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int getfreememory()
{

  int returnValue;
  const int BUFFER_SIZE = 1000;
  char buffer[BUFFER_SIZE];
  FILE *fInput;
  int loop;
  int len;
  char ch;
  returnValue = -1;
  fInput = fopen("/proc/meminfo","r");
  
  
  if (fInput != NULL)
  {
    while (!feof(fInput))
    {
      fgets(buffer,BUFFER_SIZE-1,fInput);
      
      if (feof(fInput))
      {
        break;
      }
      buffer[BUFFER_SIZE-1] = 0;
      
      if (strncmp(buffer,"MemFree:",8)==0)
      {
      
        for(loop=0;loop<BUFFER_SIZE;loop++)
        {
          ch = buffer[loop];
          
          if (ch == ':')
          {
             returnValue = 0;
             continue;
          }
          
          if (ch == 0)
          {
              break;
          }
          
          if (returnValue >=0)
          {
             if (ch >='A')
             {
                break;
             }
             if ((ch >='0') && (ch <='9'))
             {
                returnValue = returnValue * 10 + (ch-'0');
             }
          }
          
        }
        break;
      }
    } 
    
    fclose(fInput);
  }
  
  return returnValue;
}

int main()
{
	FILE* file = fopen("daemon.txt", "a");
	if (file == NULL)
	{
		printf("error file\n");
		return 1;
	}


	time_t start = time(NULL);
	time_t mytime = time(NULL);
	int k = 0;
	float d = 0.0;
	float limit = 1;
	
	
	while (1)
	{
		k = getfreememory();
		d=k/1024.0/1024.0/1024.0;
		if (d < limit)
		{
			fprintf(file, "Malo operativku: %f Gb\t", d);
			mytime = time(NULL);
			struct tm* now = localtime(&mytime);
			fprintf(file, "Date: %d.%d.%d\t", now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);
			fprintf(file, "Time: %d:%d:%d\n", now->tm_hour, now->tm_min, now->tm_sec);
			fflush(file);
		}

		start = time(NULL);
		while (time(NULL) - start < 3)
		{}
	}

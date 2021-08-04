#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define total_processes 20
#define processor_count 4


struct processor{
    int proc_ETs[5];
    int proc_id;
}processor;

void* process (void *args)
{
 
    struct processor *data = args;
    int processor_no= data->proc_id;
    int n=5,i=0;
    while(n>0)
    {
        if(data->proc_ETs[i]!=0)
        {data->proc_ETs[i]=data->proc_ETs[i]-1;
        
        printf("Process %d from Processor %d has remaining %d ET\n",i+1,processor_no+1,data->proc_ETs[i]);
           if(data->proc_ETs[i]==0)
             n--;
        }
        if(i<4)
          i++;
        else
          i=0;
        
    }
    printf("Processor %d has completed all assigned processes\n",data->proc_id+1);
    pthread_exit(NULL);
}

int main()
{
  pthread_t threads[processor_count];
  int i, k=0, j, rc;

  
  struct processor proc_struct [processor_count];
 
 for(i=0;i<processor_count;i++)
 {
     for(j=0;j<5;j++)
     {
         proc_struct[i].proc_ETs[j]= (k%4)+1;
         k++;
     }
 }
  
  for (i = 0; i < processor_count; ++i) {
    proc_struct[i].proc_id = i;
    if ((rc = pthread_create(&threads[i], NULL, process, &proc_struct[i]))) {
      printf(stderr, "error: pthread_create, rc: %d\n", rc);
      return EXIT_FAILURE;
    }
  }
  /* block until all threads complete */
  for (i = 0; i < processor_count; ++i) {
    pthread_join(threads[i], NULL);
  }
 
  return EXIT_SUCCESS;

    return 0;
}


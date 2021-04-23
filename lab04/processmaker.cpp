#include <sys/shm.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h>  
void *allocateSharedMemory(size_t memSize, int &memId) {     
    memId = shmget(IPC_PRIVATE, memSize, 0600|IPC_CREAT|IPC_EXCL);     
  if (memId <= 0)   
  {         
        perror("error with memId");         
        return NULL;    
  }         
void *mem = shmat(memId, 0, 0);    
  if (NULL == mem)     {        
        perror("error with shmat");   
  }        
  return mem; 
    }
void print()
    {
        for(int i=0;i<20;i++)
        printf(*mem[i])
    } 
void childMainCode(int *sharedMem) {
    qsort(sharedMem, 20, 4,c_sort);
    print (sharedMem); 
    exit(0);

}  

int main() {
            int memId; 
            int *sharedMem = (int *)allocateSharedMemory(1024, memId);    
  printf("memId = %d\n", memId);  
srand(time(0));	

for(int i=0;i<20;i++)
	*(sharedMem +i)=rand() % 100;
    print(sharedMem);	
    pid_t childId = fork();                 
  if (childId < 0)   
  {        
        perror("error with fork()\n");
  }     
else if (childId > 0)    
    {     
        childMainCode(sharedMem);              
    }   
else  
  { 
    sprintf(sharedMem, "init value for shared memory");             
    printf("Parent: This is main process. Child id = %d\n", childId);         
    printf("Parent: awaiting for child.\n");        
    waitpid(childId, NULL, 0);   
    printf("%6d proc: Process is finished.\n", curId); 
  }  
	char shared_mem_delete_command[124]; 
	sprintf(shared_mem_delete_command, "ipcrm -m %i", mem_id); 
	system(shared_mem_delete_command);
      return 0; 
}
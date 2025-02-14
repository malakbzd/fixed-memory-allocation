
#include <stdio.h>
#define s 30

// Memory information
typedef struct pdt
{
    int id;
    int size;
    int status;
} pdt;
struct pdt t[s],temp;

// Process information
typedef struct process
{
    int id;
    int size;
    int status;
} process;
struct process a[s];

// Waiting queue
typedef struct wait_q
{
    int id;
    int size;
    int status;
} wait_q;
struct wait_q w[s];

// Input memory information
void partition (int p ,struct pdt d[s]) 
{
    int i;
    for (i = 0; i < p; i++) 
    {
        printf("Enter the ID and size of memory %d: ", i + 1);
        scanf("%d %d",&d[i].id , &d[i].size);
        d[i].status = 0; //1 allocated 0 not allocated
    }
}

// Input process information
void partition_p (int k,struct process b[s]) 
{
    int i;
    for (i = 0; i < k; i++) 
    {
        printf("Enter the ID and size of process %d: ", i + 1);
        scanf("%d %d", &b[i].id , &b[i].size);
        b[i].status = 0;//1 allocated 0 not allocated
    }
}

// Waiting queue
void wq (struct process r[s], struct wait_q w[s], int n) 
{
    int i;
    for (i = 0; i < n; i++) 
    {
        w[i].id = r[i].id;
        w[i].size = r[i].size;
        w[i].status=1;
    }    
}

// First fit
void f_fit (int k, int p, struct pdt d[s], struct process b[s],struct wait_q w_q[s]) 
{
    int i, j;
    int external_fragmentation = 0;
    for (i = 0; i < k; i++)//for each process
    {
        for (j = 0; j < p; j++)//for each block 
        {
            if (d[j].status == 0 && d[j].size >= b[i].size) 
            {
                b[i].status = d[j].id;
                d[j].status = 1;
                external_fragmentation += d[j].size-b[i].size; //internal and external fregmentation  

              break;// Break the loop once a fit is found
            }
              if (d[j].status == 0 && d[j].size < b[i].size) // If no fit is found add the process to the waiting queue
              {
                wq(b,w_q,p);
              }
        }
    }

    printf("Process\t\tPlace in memory\n");
    for (i = 0; i < k; i++) 
    {
        printf("%d\t\t%d\n", b[i].id, b[i].status);
    }
    printf("external Fragmentation: %d\n", external_fragmentation);
}

// Best fit
void b_fit(int k, int p, struct pdt d[s], struct process b[s], struct wait_q Wq[s]) 
{
    int i, j;
    int external_fragmentation = 0;
    // Sort the blocks based on the block size
    for (i = 0; i < p - 1; i++) 
    {
        for (j = 0; j < p - i - 1; j++) 
        {
            if (d[j].size > d[j + 1].size) 
            {
                temp = d[j];
                d[j] = d[j + 1];
                d[j + 1] = temp;
            }
        }
    }
    for (i = 0; i < k; i++)//for each process
    {
        for (j = 0; j < p; j++) //for each block
        {
            if (d[j].status == 0 && d[j].size >= b[i].size)
             {
                b[i].status = d[j].id;
                d[j].status = 1;
                external_fragmentation += d[j].size - b[i].size;
                break;
            }
             if (d[j].status == 0 && d[j].size < b[i].size) // If no fit is found add the process to the waiting queue
              {
                wq(b,Wq,p);
              }
        }
    }
    printf("Process\t\tPlace in memory\n");
    for (i = 0; i < k; i++) 
    {
        printf("%d\t\t%d\n", b[i].id, b[i].status);
    }
    printf("external Fragmentation: %d\n", external_fragmentation);
}

//process delete
void delet_process (int pid , int p , struct pdt d[s], struct process b[s])
{  
   int i;
  for(i=0;i<p;i++)//for each process
  {
         if(b[i].id == pid )
         {
            d[i].status = 0;//free memory
            d[i].id = 0;
            b[i].id = 0;
            b[i].status = 0 ;//update process status         
         } 
  }
     printf("Process\t\tPlace in memory after deleting\n");
    for (i = 0; i < p; i++) 
    {
        printf("%d\t\t%d\n", b[i].id, b[i].status);
    }
  }
  
//main
int main() 
{
    int m, n, y,k,p,w,v,l;
    pdt t[s];
    process a[s];
    wait_q wq[s];

    // Number of memory blocks
    printf("Enter the number of pdt blocks: ");
    scanf("%d", &m);

    // Procedure memory call
    partition(m, t);

    // Number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Procedure process call
    partition_p(n,a);

    // First fit or best fit selection
    printf("Choose 1 for First Fit or 2 for Best Fit: ");
    scanf("%d", &y);

    if (y == 1) 
    {
        f_fit(n, m, t, a, wq);
    } else if (y == 2) 
    {
        b_fit(n, m, t, a, wq);
    } else 
    {
        printf("Invalid choice\n");
    }
     printf("do u want to delete a process ? 1/0");
     scanf("%d",&w);
     
     if (w == 1)
     {
       printf("enter the pid of the process u want to delete");
       scanf("%d",&v);
       delet_process(v,n,t,a);
     }   
}
 

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>

void main()
{
    int n,i;
    printf("Enter thenumber of array\n");
    scanf("%d",&n);
    int a[n];
    printf("Enter the array elements:\n");
    for(i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
    }

    void ascending(int *a,int n);
    void descending(int *a,int n);

    pid_t pid;
    pid=fork();

    if(pid<0)
    {
        printf("fork() error\n");
        exit(-1);
    }

    else if(pid==0)
    {
        printf("\n Child Process\n");
        descending(a,n);
        printf("Array elements in descending order\n ");
        for(i=0;i,n;i++)
        {
            printf("%d\n",a[i]);
        }
        printf("\n");
        exit(0);
    }

    else
    {
        int status;
        wait(NULL);
        printf("Parent Process\n");
        if(WIFEXITED(status))
        {
            printf("Child Process Exit ");
        }
        ascending(a,n);
        printf("\n Array Elemets in sort");
        for(i=0;i<n;i++)
        {
            printf("%d\n",a[i]);
        }
        printf("\n");
        exit(0);
    }

    void ascending(int *a,int n)
    {
        int i,j,temp;
        for(i=0;i<n;i++)
        {
            for(j=0;j<n-1;j++)
            {
                if(a[j+1]<a[j])
                {
                    temp=a[j];
                    a[j]=a[j+1];
                    a[j+1]=temp;
                }
            }
        }
    }

    void descending(int *a,int n)
    {
        int i,j,temp;
        for(i=0;i<n;i++)
        {
            for(j=0;j<n-1-i;j++)
            {
                if(a[j+1]>a[j])
                {
                    temp=a[j];
                    a[j]=a[j+1];
                    a[j+1]=temp;
                }
            }
        }
    }
}

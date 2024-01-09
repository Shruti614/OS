/*
Q.1) Write the simulation program to implement demand paging and show the page
scheduling and total number of page faults for the following given page reference string.
Give input n as the number of memory frames.

Reference String : 12,15,12,18,6,8,11,12,19,12,6,8,12,15,19,8
1) Implement OPT
2) Implement MFU
*/
//Program OPT :
/*
#include<stdio.h>
int main()
{
    int no_of_frames, no_of_pages, frames[10], pages[30], temp[10], flag1, flag2, flag3, i, j, k, pos, max, faults = 0;
    printf("Enter number of frames: ");
    scanf("%d", &no_of_frames);
    
    printf("Enter number of pages: ");
    scanf("%d", &no_of_pages);
    
    printf("Enter page reference string: ");
    
    for(i = 0; i < no_of_pages; ++i){
        scanf("%d", &pages[i]);
    }
    
    for(i = 0; i < no_of_frames; ++i){
        frames[i] = -1;
    }
    
    for(i = 0; i < no_of_pages; ++i){
        flag1 = flag2 = 0;
        
        for(j = 0; j < no_of_frames; ++j){
            if(frames[j] == pages[i]){
                   flag1 = flag2 = 1;
                   break;
               }
        }
        
        if(flag1 == 0){
            for(j = 0; j < no_of_frames; ++j){
                if(frames[j] == -1){
                    faults++;
                    frames[j] = pages[i];
                    flag2 = 1;
                    break;
                }
            }    
        }
        
        if(flag2 == 0){
         flag3 =0;
        
            for(j = 0; j < no_of_frames; ++j){
             temp[j] = -1;
            
             for(k = i + 1; k < no_of_pages; ++k){
             if(frames[j] == pages[k]){
             temp[j] = k;
             break;
             }
             }
            }
            
            for(j = 0; j < no_of_frames; ++j){
             if(temp[j] == -1){
             pos = j;
             flag3 = 1;
             break;
             }
            }
            
            if(flag3 ==0){
             max = temp[0];
             pos = 0;
            
             for(j = 1; j < no_of_frames; ++j){
             if(temp[j] > max){
             max = temp[j];
             pos = j;
             }
             }            
            }
frames[pos] = pages[i];
faults++;
        }
        
        printf("\n");
        
        for(j = 0; j < no_of_frames; ++j){
            printf("%d\t", frames[j]);
        }
    }
    
    printf("\n\nTotal Page Faults = %d", faults);
    
    return 0;
}
/*
Output
Enter number of frames: 4
Enter number of pages: 12 15 12 18 6 8 11 12 19 12 6 8 12 15 19 8
Enter page reference string: 
15	-1	-1	-1	
15	12	-1	-1	
15	12	18	-1	
15	12	18	6	
8	12	18	6	
8	12	11	6	
8	12	11	6	
8	12	19	6	
8	12	19	6	
8	12	19	6	
8	12	19	6	
8	12	19	6	

Total Page Faults = 7

*/

//MFU :

#include<stdio.h>
#define MAX 20

int frames[MAX],ref[MAX],mem[MAX][MAX],faults,
 sp,m,n,count[MAX];

void accept()
{
 int i;

 printf("Enter no.of frames:");
 scanf("%d", &n);

 printf("Enter no.of references:");
 scanf("%d", &m);

 printf("Enter reference string:\n");
 for(i=0;i<m;i++)
 {
  printf("[%d]=",i);
  scanf("%d",&ref[i]);
 }
}

void disp()
{
 int i,j;

 for(i=0;i<m;i++)
  printf("%3d",ref[i]);

 printf("\n\n");

 for(i=0;i<n;i++)
 {
  for(j=0;j<m;j++)
  {
   if(mem[i][j])
    printf("%3d",mem[i][j]);
   else
    printf("   ");
  }
  printf("\n");
 }

 printf("Total Page Faults: %d\n",faults);
}

int search(int pno)
{
 int i;

 for(i=0;i<n;i++)
 {
  if(frames[i]==pno)
   return i;
 }

 return -1;
}

int get_mfu(int sp)
{
 int i,max_i,max=-9999;

 i=sp;
 do
 {
  if(count[i]>max)
  {
   max = count[i];
   max_i = i;
  }
  i=(i+1)%n;
 }while(i!=sp);

 return max_i;
}

void mfu()
{
 int i,j,k;

 for(i=0;i<m && sp<n;i++)
 {
  k=search(ref[i]);
  if(k==-1)
  {
   frames[sp]=ref[i];
   count[sp]++;
   faults++;
   sp++;

   for(j=0;j<n;j++)
    mem[j][i]=frames[j];
  }
  else
   count[k]++;
  
 }

 sp=0;
 for(;i<m;i++)
 {
  k = search(ref[i]);
  if(k==-1)
  {
   sp = get_mfu(sp);
   frames[sp] = ref[i];
   count[sp]=1;
   faults++;
   sp = (sp+1)%n;

   for(j=0;j<n;j++)
    mem[j][i] = frames[j];
  }
  else
   count[k]++;
 }
}
      

int main()
{
 accept();
 mfu();
 disp();

 return 0;
}
/*
Output :
Enter no.of frames:4
Enter no.of references:12 15 12 18 6 8 11 12 19 12 6 8 12 15 19 8
Enter reference string:
[0]=[1]=[2]=[3]=[4]=[5]=[6]=[7]=[8]=[9]=[10]=[11]= 15 12 18  6  8 11 12 19 12  6  8 12

 15 15 15 15  8  8  8  8     8    12
    12 12 12 12 11 11 11    11    11
       18 18 18 18 12 12     6     6
           6  6  6  6 19    19    19
Total Page Faults: 10
*/
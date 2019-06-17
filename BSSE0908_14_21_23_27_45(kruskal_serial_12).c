#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int arr[12][12]={{0,1,2,0,0,0,0,0,0,0,0,0},
             {1,0,0,1,0,0,0,0,0,0,0,0},
             {2,0,0,3,0,0,0,0,0,0,0,0},
             {0,1,3,0,3,4,0,0,1,2,0,0},
             {0,0,0,3,0,0,0,0,0,0,0,0},
             {0,0,0,4,0,0,2,0,5,0,0,0},
             {0,0,0,0,0,2,0,3,4,0,0,0},
             {0,0,0,0,0,0,3,0,0,0,0,0},
             {0,0,0,1,0,5,4,0,0,0,0,1},
             {0,0,0,2,0,0,0,0,0,0,3,0},
             {0,0,0,0,0,0,0,0,0,3,0,2},
             {0,0,0,0,0,0,0,0,1,0,2,0}};




int parent[12];
int visit[12];
int main(){


    clock_t start=clock();



    int u=0,v=0,min=999,mincost=0,ne=1,a=0,b=0,n=12;
    for(int i=0;i<12;i++){
         parent[i]=-1;
         visit[i]=0;
        for(int j=0;j<12;j++){

             printf("%d,",arr[i][j]);

        }
        printf("\n");
    }

    while(ne < n)
    {
    		for(int i=0;i<n;i++)
    		{
    			for(int j=0;j<n;j++)
    			{

    				if(arr[i][j] < min&&arr[i][j]!=0&&i!=j)
    				{
    					min=arr[i][j];
    					a=u=i;
    					b=v=j;
    				}
    			}
    		}
    		u=find(u);
    		v=find(v);
    		if(uni(u,v))
    		{
    			printf("%d edge (%d,%d) =%d\n",ne++,a,b,min);
    			mincost +=min;
    		}


    		arr[a][b]=arr[b][a]=999;
    		min=999;


    }
    clock_t end=clock();
    printf("\n\tMinimum cost = %d\n",mincost);
    printf("\n\tExecution time = %.10f\n",(double)(end-start)/CLOCKS_PER_SEC);




}

int find(int i)
{
    	while(parent[i]!=-1){
            i=parent[i];

    	}
    	return i;
}
int uni(int i,int j)
{
    	if(i!=j)
    	{
    		parent[j]=i;
    		return 1;
    	}
    	return 0;
}

#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
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
 
int main (int argc, char *argv[])
{
        MPI_Init(&argc, &argv);
        double start = MPI_Wtime();
        int world_rank; //process rank
        MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
        int world_size;
        MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	int slot=12/(world_size-1); //per process row
        int tag1 = 1; //
        int tag2 = 2;
	int tag3 = 3;
	int tag4 = 4;
	int tag5 = 5;
	int tag6 = 6;

        int index; // track
        int source = 0; // root
       	int minCost; // final mincost
        
        if (world_rank == 0)
        {

		for(int i=0;i<12;i++) parent[i]=-1;
		index = 0;
		minCost=0;
		int sum=0;
		for(int i=1;i<world_size;i++){

		    MPI_Send(&index, 1, MPI_INT, i, tag1, MPI_COMM_WORLD);
		    MPI_Send(&arr, 2, MPI_INT, i, tag2, MPI_COMM_WORLD);
	            MPI_Send(&parent, 20, MPI_INT, i, tag3, MPI_COMM_WORLD);
		    index+=slot;

		    MPI_Recv(&sum,1, MPI_INT,i, tag4, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		    MPI_Recv(&arr,40, MPI_INT,i, tag5, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		    MPI_Recv(&parent,20,MPI_INT,i, tag6, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		    minCost+=sum;
		    printf("process: %d\n",i);
		    printf("Minimum Cost: %d\n",minCost);

		}

		double end = MPI_Wtime();

		printf("Execution Time: %.10f\n",end-start);


        }
        
        else
        {
            int sum = 0;
            int i;
            MPI_Recv(&index, 1, MPI_INT, source, tag1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(&arr, 40, MPI_INT, source, tag2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	    MPI_Recv(&parent, 20, MPI_INT, source, tag3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("process: %d index is: %d\n", world_rank, index);

	    int u=0,v=0,min=999,ne=0,a=0,b=0,n=0;

	     while(ne<slot && n<12){

		    for(i = index; i<index+slot; i++)
		    {
			for(int j=0;j<12;j++){

			   if(arr[i][j] < min&&arr[i][j]!=0&&i!=j)
	    		  {
	    			min=arr[i][j];
	    			a=u=i;
	    			b=v=j;
	    		  }
	    		}
	    	    }
	    	    u=find(u,&parent);
	    	    v=find(v,&parent);
	    	    if(uni(u,v,&parent))
	    	    {
	    		printf("%d edge (%d,%d) =%d\n",ne++,a,b,min);
	    		sum+=min;

	    	    }


	    	    arr[a][b]=arr[b][a]=999;
	    	    min=999;
	    	    n++;
	   }
	   MPI_Send(&sum,1,MPI_INT, source, tag4, MPI_COMM_WORLD);
	   MPI_Send(&arr, 2, MPI_INT, source, tag5, MPI_COMM_WORLD);
	   MPI_Send(&parent, 20, MPI_INT,source, tag6, MPI_COMM_WORLD);

	}

        MPI_Finalize();


}
int find(int i,int *parent)
{
    	while(parent[i]!=-1){
            i=parent[i];
    	}
    	return i;
}
int uni(int i,int j,int *parent)
{
    	if(i!=j)
    	{
    		parent[j]=i;
    		return 1;
    	}
    	return 0;
}



#include <iostream>

using namespace std;

void checkNeighbor(int M,int N, int map[][15], int visit[][15], int pt[], int neighbor[])
{
    int maxN=-1;
    int i=pt[0];
    int j=pt[1];
    int a=-1,b=-1;
    
    if(i-1>=0 && visit[i-1][j]==0 && map[i-1][j]>maxN)
    {
        maxN=map[i-1][j];
        a=i-1;
        b=j;
    }
    
    if(j-1>=0 && visit[i][j-1]==0 && map[i][j-1]>maxN)
    {
        maxN=map[i][j-1];
        a=i;
        b=j-1;
    }
    
    if(i+1<M && visit[i+1][j]==0 && map[i+1][j]>maxN)
    {
        maxN=map[i+1][j];
        a=i+1;
        b=j;
    }
    
    if(j+1<N && visit[i][j+1]==0 && map[i][j+1]>maxN)
    {
        maxN=map[i][j+1];
        a=i;
        b=j+1;
    }
    
    
    //even
    if(j%2==0)
    {
        if(i-1>=0 && j-1>=0 && visit[i-1][j-1]==0 && map[i-1][j-1]>maxN)
        {
            maxN=map[i-1][j-1];
            a=i-1;
            b=j-1;
        }
        if(i-1>=0 && j+1<N && visit[i-1][j+1]==0 && map[i-1][j+1]>maxN)
        {
            maxN=map[i-1][j+1];
            a=i-1;
            b=j+1;
        }
    }
    
    //odd i
    if(i%2==1)
    {
        if(i+1<M && j-1>=0 && visit[i+1][j-1]==0 && map[i+1][j-1]>maxN)
        {
            maxN=map[i+1][j-1];
            a=i+1;
            b=j-1;
        }
        if(i+1<M && j+1<N && visit[i+1][j+1]==0 && map[i+1][j+1]>maxN)
        {
            maxN=map[i+1][j+1];
            a=i+1;
            b=j+1;
        }
    }
    
    neighbor[0]=a;
    neighbor[1]=b;
}

struct node{
    int I;
    int J;
};

struct list{
    struct node* head;
};

void basestations(int M, int N, int map[][15])
{
    int i,j,k,l,x,y,cover;
    int pt[2];
    int neighbor[2];
    int cost=0;
    int maxCost=-1;
    
    struct node array[4];
    int visit[M][15];
    
    for(i=0;i<M;i++)
    {
        for(j=0;j<N;j++)
        {
            visit[i][j]=0;
            cout<<map[i][j]<<" ";
        }
        cout<<endl;
    }
    
    for(i=0;i<M;i++)
    {
        for(j=0;j<N;j++)
        {
            for(k=0;k<4;k++)array[k].I=array[k].J=-1;
            
            array[0].I=i;
            array[0].J=j;
            visit[i][j]=1;
            for(k=1;k<4;k++)
            {
                cover=-1;
                x=-1;
                y=-1;
                for(l=0;l<k;l++)
                {
                    pt[0]=array[l].I;
                    pt[1]=array[l].J;
                    
                    checkNeighbor(M,N,map,visit,pt,neighbor);
                    
                    if(map[neighbor[0]][neighbor[1]]>cover)
                    {
                        x=neighbor[0];
                        y=neighbor[1];
                        cover=map[neighbor[0]][neighbor[1]];
                    }
                }
                array[k].I=x;
                array[k].J=y;
                visit[x][y]=1;
            }
            
            cost=map[array[0].I][array[0].J]+map[array[1].I][array[1].J]+map[array[2].I][array[2].J]+map[array[3].I][array[3].J];
            if(cost>maxCost)maxCost=cost;
            cout<<i<<" "<<j<<" cost : "<<cost<<endl;
            cout<<map[array[0].I][array[0].J]<<" "<<map[array[1].I][array[1].J]<<" "<<map[array[2].I][array[2].J]<<" "<<map[array[3].I][array[3].J]<<endl;
            visit[array[0].I][array[0].J]=visit[array[1].I][array[1].J]=visit[array[2].I][array[2].J]=visit[array[3].I][array[3].J]=0;
        }
    }
    cout<<"maxCost : "<<maxCost;
}

int main() {
	int M,N;
	int map[15][15];
	cin>>M>>N;
	for(int i=0;i<M;i++)
	{
	    for(int j=0;j<N;j++)
	        cin>>map[i][j];
	}
	basestations(M,N,map);
	return 0;
}

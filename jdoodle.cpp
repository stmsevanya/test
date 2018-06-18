#include <iostream>

using namespace std;

void openGate(int array[],int spots,int f,int g, int lastPos[])
{
    int select,j,k;
    j=k=g;
    
    while(f)
    {
        while(j>=0 && array[j]>-1)j--;
        while(k<spots && array[k]>-1)k++;
        
        if(j<0 || (g-j)>(k-g))select=k;
        else if(k>=spots || (g-j)<(k-g))select=j;
        else if(f>1)select=j;
        else
        {                                                  
            lastPos[0]=j;
            lastPos[1]=k;
            return;
        }
        
        array[select]=g;
        f--;
        //cout<<select<<" ";
    }
    lastPos[0]=select;
    lastPos[1]=-1;
}

int estimateCost(int array[], int g[],int N)
{
    int cost=0;
    int c;
    int l;
                for(l=0;l<N;l++)
                {
                    cout<<array[l]<<" ";
                    if(array[l]<0)continue;
                    if(array[l]==g[0])
                        c=g[0]-l;
                    else if(array[l]==g[1])
                        c=(g[1]-l);
                    else if(array[l]==g[2])
                        c=(g[2]-l);
                    
                    if(c<0)c*=-1;
                    cost+=(c+1);
                }
    return cost;
}

int fishing(int N, int g[], int f[])
{
    int minCost=100000;
    int i,j,k,l,r1,r2,r3,cost,a1,a2,a3,b1,b2,b3;
    int array[N];
    for(i=0;i<N;i++)array[i]=-1;
    int lastPos[2];
    
    for(i=0;i<3;i++)
    {
        openGate(array,N,f[i],g[i],lastPos);
        
            a1=lastPos[0];
            b1=lastPos[1];
        
        for(r1=0;r1<2;r1++)
        {
            if(r1==0)array[a1]=g[i];
            else if(b1==-1)continue;
            else
            {
                array[b1]=g[i];
                array[a1]=-1;
            }
            cout<<i<<" -> ";
            for(j=0;j<3;j++)
            {
                if(i==j)continue;
                
                openGate(array,N,f[j],g[j],lastPos);
                
                    a2=lastPos[0];
                    b2=lastPos[1];
                for(r2=0;r2<2;r2++)
                {
                    if(r2==0)array[a2]=g[j];
                    else if(b2==-1)continue;
                    else
                    {
                        array[b2]=g[j];
                        array[a2]=-1;
                    }
                    cout<<j<<" -> ";
                    for(k=0;k<3;k++)
                    {
                        if(k==i || k==j)continue;
                        
                        openGate(array,N,f[k],g[k],lastPos);
                        
                            a3=lastPos[0];
                            b3=lastPos[1];
                            
                        for(r3=0;r3<2;r3++)
                        {
                            if(r3==0)array[a3]=g[k];
                            else if(b3==-1)continue;
                            else
                            {
                                array[b3]=g[j];
                                array[a3]=-1;
                                cout<<"yay"<<endl;
                            }
                            cout<<k<<endl;
                            //calc cost
                            cost=estimateCost(array,g,N);
                            cout<<endl<<cost<<endl;
                            if(cost<minCost)minCost=cost;
                        }
                        
                        for(l=0;l<N;l++)
                        {
                            if(array[l]==g[k])array[l]=-1;
                        }
                        
                    }
                    
                }
                
                for(l=0;l<N;l++)
                {
                    if(array[l]==g[j])array[l]=-1;
                }
            }
            
        }
        
        for(l=0;l<N;l++)
        {
            if(array[l]==g[i])array[l]=-1;
        }
    }
    return minCost;
}

int main() {
	
	int N=10;
	int g[3]={3,5,9};
	int f[3]={5,2,2};
	int c=fishing(N,g,f);
	cout<<"\nminCost : "<<c<<endl;
	
	return 0;
}

#include <iostream>
using namespace std;

  
long long  pos(long long dp[], long long l,long long r,long long key)
{
    while(r-l>1)
    {
        long long m=l+(r-l)/2;
        if(dp[m]>=key){
        	r=m;
		}
        else{
        	l=m;
		}
    }
    return r;
}

long long lis(long long a[], long long  l)
{
    long long len,i;
    long long dp[10001];
    for(i=0;i<10001;++i){
    	dp[i]=0;
	}
    dp[0]=a[0];
    len=1;
    for(i=1;i<l;i++)
    {
        if(a[i]<dp[0]){
        	dp[0]=a[i];
		}
        else if(a[i]>dp[len-1]){
        	dp[len++]=a[i];
		}
        else{
        	dp[pos(dp,-1,len-1,a[i])]=a[i];
		}   
    }
    return len;
} 

int main()
{
	long long ans,t,n,i,a[20010];
    cin>>t;
    while(t--)
    {
    	cin>>n;
        for(i=0;i<n;i++){
        	cin>>a[i];
        	a[i+n]=a[i];
        }
        ans=0;
        for(i=0;i<n;i++){
        	ans=max(ans,lis(a+i,n));
        }
        cout<<ans<<endl;
    }
    return 0;
}
 

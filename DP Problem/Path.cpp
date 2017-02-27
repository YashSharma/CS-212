#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main()
{
	int m,n;
	string s;
	cin>>m>>n;
	cin.ignore();
	getline(cin, s);

	vector< vector<int> >safe(m+1, vector<int>(n+1,0));
	int i=0,j,k;
	int len = s.length();
	
	i = 0;
	while(i<len)
	{
		if(isdigit(s[i]))
		{
			int first = s[i]-'0';
			i++;
			while(isdigit(s[i]))
			{
				first = first*10 + (s[i]-'0');
				i++;
			}
			i++;

			int second = (s[i]-'0');
			i++;
			while(isdigit(s[i]))
			{
				second = second*10 + (s[i]-'0');
				i++;
			}
			i++;

			int third = (s[i]-'0');
			i++;
			while(isdigit(s[i]))
			{
				third = third*10 + (s[i]-'0');
				i++;
			}
			i++;

			int fourth = (s[i]-'0');
			i++;
			while(isdigit(s[i]))
			{
				fourth = fourth*10 + (s[i]-'0');
				i++;
			}
			i++;

			
			safe[first][second] = -1;
			safe[third][fourth] = -1;
		}
		i++;
	}


	vector< vector<int> >count(m+1, vector<int>(n+1,0));
	count[0][0] = 1;
	for (int i = 1; i <= m; i++)
    {
    	if(safe[i][0]==-1 && safe[i-1][0]==-1)
 		{
 			count[i][0] = 0;
 		}
 		else
       		count[i][0] = count[i-1][0];
 	}

    for (int j = 1; j <= n; j++)
    {
    	if(safe[0][j]==-1 && safe[0][j-1]==-1)
    	{
    		count[0][j] = 0;
    	}else
	    	count[0][j] = count[0][j-1];
 	}

    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
 		{
 			if(safe[i][j]==-1)
 			{
 				if(safe[i-1][j]==-1 && safe[i][j-1]==-1)
 					count[i][j] = 0;
 				else if(safe[i-1][j]==-1)
 					count[i][j] = count[i][j-1];
 				else if(safe[i][j-1]==-1)
 					count[i][j] = count[i-1][j];

 			}
 			else
				count[i][j] = count[i-1][j] + count[i][j-1]; 
 		}
 
    }

   	cout<<count[m][n]<<endl;
   	return 0;

}
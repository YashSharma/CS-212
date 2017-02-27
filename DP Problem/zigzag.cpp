#include <iostream>
#include <vector>
using namespace std;

int max(int a, int b) 
{
	if(a>=b)
		return a;
	else 
		return b;
}

int zigzag(vector<int>a, int n) {
    int seq[n][2], i = 0, j = 0, result = 1;
    
    for (i = 0; i < n; i++)
		seq[i][0] = seq[i][1] = 1;

    for (i = 1; i < n; i++) {
        for (j = 0; j < i; j++) {
            if (a[j] < a[i] && seq[i][0] < seq[j][1] + 1)
                seq[i][0] = seq[j][1] + 1;
 
            if( a[j] > a[i] && seq[i][1] < seq[j][0] + 1)
                seq[i][1] = seq[j][0] + 1;
        }

        if (result < max(seq[i][0], seq[i][1]))
            result = max(seq[i][0], seq[i][1]);
    }

    return result;
}

int main() {
	
	vector<int> numbers;

	int num;

	while(true)
	{
		cin>>num;
		numbers.push_back(num);
		if (cin.get() == '\n')
			break;
	}

	cout<<zigzag(numbers,numbers.size())<<endl;

	return 0;
}

 

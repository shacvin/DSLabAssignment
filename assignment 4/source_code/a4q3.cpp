#include <iostream>
#include <unordered_map>
using namespace std;


void maxLengthSubArray(int arr[], int n, int S)
{
	
	unordered_map<int, int> map;

	map[0] = -1;

	int sum = 0;
	int len = 0;
	int ending_index = -1;
	
	for (int i = 0; i < n; i++)
	{
		
		sum += arr[i];

		
		if (map.find(sum) == map.end()) {
			map[sum] = i;
		}

		
		if (map.find(sum - S) != map.end() && len < i - map[sum - S])
		{	
			len =  i - map[sum - S];
			ending_index = i;
		}
	}
    if(len!=0){
	cout<<"Length of longest subarray is "<< len <<"\n";
	cout << "Index from " << (ending_index - len + 1) << " to " << ending_index <<"\n";
}
    else{
    	cout<<"Not Found"<<"\n";
    }
}

int main()
{
	int n = 0;
	cout<<"Enter the number of elements in the array"<<"\n"; 
	cin>>n;

    int arr[n];
    cout<<"Enter the elements"<<"\n";
    for(int i = 0; i<n; i++){
       cin>>arr[i];
    }

    int sum = 0;
    cout<<"Enter the sum"<<"\n";
    cin>>sum;

	maxLengthSubArray(arr, n, sum);

	return 0;
}
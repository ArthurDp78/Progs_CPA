#include <iostream>
#include <vector>
using namespace std;


void maxSubarraySum(vector<int> &arr,int route) {
    int res = arr[0];
    int final =0;
    int inicio = 0;
    int tamanhoMaximo = 0;
    // Outer loop for starting point of subarray
  	for(int i = 0; i < arr.size(); i++) {
    	int currSum = 0;
      
        // Inner loop for ending point of subarray
        for(int j = i; j < arr.size(); j++) {
        	currSum = currSum + arr[j];
            
            // Update res if currSum is greater than res
            if(res < currSum){
                res = currSum;
                final = j;
                inicio = i;
                tamanhoMaximo = j-i;
            }
            else if(res == currSum && tamanhoMaximo < j-i){
                res = currSum;
                final = j;
                inicio = i;
                tamanhoMaximo = j-i;
            }
        }
    }
    if(res <= 0){
        cout << "Route "<< route << " has no nice parts" << endl;
    }
    else cout << "The nicest part of route " << route<< " is between stops " << inicio+1 << " and " << final+2 << endl;
}


int main(){
    int b = 0;
    cin >> b;
    if (b >= 1 && b <= 100) {
        int s = 0;
        int valor;
        for (int i = 0; i < b; i++) {
            cin >> s;
            vector<int> v;
            for (int j = 0; j < s - 1; j++) {
                cin >> valor;
                v.push_back(valor);
            }
            maxSubarraySum(v,i+1);
        }
    }
    return 0;
}

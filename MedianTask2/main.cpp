#include "alg.h"

int main(){
int arr[]={1,2,3,10,8,6,9};

int * p = Transformations(begin(arr), end(arr),
[](const int x, const int y){return x + y;});
cout<<arr[0]<<","<<arr[1]<<","<<arr[2]<<","<<arr[3]<<","<<arr[4]<<","<<arr[5]<<","<<arr[6]<<endl;
cout<<*p<<endl;
}
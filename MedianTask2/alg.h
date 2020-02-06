using namespace std;
#include <iostream>
#include <algorithm>

template <typename T>
T Median(T begin, T end, int n){
    T new_begin=begin;
    int count=count_if(begin,end,[](decltype(*begin) x){
        return true;
    });

    if((begin==end)||(n==1)||count%n!=0) return end;
    
    while(begin!=end){
       
        T segment_begin=begin;
        for(int i=0; i<n; i++){
            begin++;
        }
        T segment_end=begin;
        sort(segment_begin,segment_end);
        T median=segment_end-1-(n/2); //when there are odd numbers of values

        if(n%2==1){//odd
            *new_begin=*median;
        }
        if(n%2==0){//even
            *new_begin=(((*median)+*(median+1))/2);
        }
        new_begin++;
    }
    return new_begin;
}


template <typename T>

T Transpose(T begin, T end){ //const? or "&"
    int count=0;
    T it_begin=begin;
    while (it_begin !=end){
        it_begin++;
        count++;
    }
    if(count%2==1){

        end--;
        count--;
    }
    
    for(int i=0;i<count;i=i+2){
        iter_swap(begin,begin+1);
        begin=begin+2;
        
    }

    return end;
}

template <typename T ,typename F>
T Transformations (T begin, T end,F f){
    int count=0;
    T it_begin=begin;
    while (it_begin !=end){
        it_begin++;
        count++;
    }
    if((count%2==1)||(begin==end)){
        return end;
    }
    
    T it_b=begin;
    for(int i=0;i<count;i=i+2){
        *(it_b)= f(*begin,*(begin+1));
        begin=begin+2;
        (it_b)++;
    }
    return it_b;
}
#include <iostream>
#include "timultimap.h"
#include "timultiset.h"
#include "timap.h"
#include "tiset.h"
#include <random>
using namespace std;

int randomnumber() {
    return rand()%10000;
}

int randomly_change(int){
    return randomnumber();
}

bool isodd(int a){
    return a%2;
}

int double_it(const int x){
    return 2*x;
}

int main(int argc, char** argv){
    srand(unsigned(time(NULL)));

    TIMultiMap<int,int> map = TIMultiMap<int,int>();
    for(int i=0;i<20;i++)
    {
        int random_number = randomnumber();
        //if(!map.containsKey(random_number)){
            map.insert(random_number,randomnumber());
        //}
    }
    for(int i=0;i<2;i++)
    {
        int random_number = randomnumber();
        if(map.containsKey(random_number)){
            map.remove_all(random_number);
        }
    }
    if(!map.containsKey(10)){
        map.insert(10,10);
    }
    cout <<map[10]<<endl;
    map.apply(randomly_change);
    cout <<map[10]<<endl;

    TIMultiMap<int,int> map2 = TIMultiMap<int,int>(map);
    cout<<map.size()<<endl;
    cout<<map2.size()<< endl;

    map.filter(isodd);

    map.dump("multimap.dot");
    return 0;
}
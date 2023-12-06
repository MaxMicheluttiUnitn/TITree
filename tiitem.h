#ifndef _TURQUOISE_INDIGO_ITEM_H__
#define _TURQUOISE_INDIGO_ITEM_H__

#include <iostream>

template <typename K,typename V> class TIItem;

template <typename K,typename V> std::ostream& operator<<(std::ostream& os,const TIItem<K,V>& tree);

template <typename K,typename V> class TIItem{
    K key;
    V value;

    public:
    TIItem(K key,V value){
        this->key = key;
        this->value = value;
    }
    TIItem(const TIItem<K,V>& item){
        this->key = item.key;
        this->value = item.value;
    }
    TIItem(TIItem<K,V>&& item){
        this->key = item.key;
        this->value = item.value;
    }
    ~TIItem(){}
    TIItem<K,V>& operator=(const TIItem<K,V>& item){
        this->key = item.key;
        this->value = item.value;
        return *this;
    }
    TIItem<K,V>& operator=(TIItem<K,V>&& item){
        this->key = item.key;
        this->value = item.value;
        return *this;
    }
    K getKey()const{return this->key;}
    V getValue()const{return this->value;}
    V& getValueReference(){return this->value;}
    void setValue(V value){this->value = value;}
    void setKey(K key){this->key = key;}

    friend std::ostream& operator<< <>(std::ostream& os,const TIItem<K,V>& node);
};

template <typename K,typename V> std::ostream& operator<<(std::ostream& os,const TIItem<K,V>& item){
    os<<"K: "<<item.getKey()<<" V: "<<item.getValue();
    return os;
}

#endif
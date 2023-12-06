#ifndef _TURQUOISE_INDIGO_TREE_H__
#define _TURQUOISE_INDIGO_TREE_H__

#include <string>
#include <exception>
#include <iostream>
#include <sstream>
#include <fstream>
#include <utility>
#include "tiset.h"
#include "timultiset.h"
#include "tiitem.h"
#include "tiexceptions.h"
#include "tiutil.h"

template <typename K,typename V> class TINode;
template <typename K,typename V> class TIMap;

template <typename K,typename V> class TIMapIter{
    TINode<K,V>* current;
    protected:
    friend TIMap<K,V>;
    friend TINode<K,V>;
    TIMapIter(){
        this->current=nullptr;
    }
    TIMapIter(TINode<K,V>* current){
        this->current = current;
    }
    public:
    TIMapIter<K,V>& operator++(){
        this->current = this->current->successor();
        return *this;
    }
    TIMapIter<K,V>& operator++(int){
        this->current = this->current->successor();
        return *this;
    }
    TIMapIter<K,V>& operator--(){
        this->current = this->current->predecessor();
        return *this;
    }
    TIMapIter<K,V>& operator--(int){
        this->current = this->current->predecessor();
        return *this;
    }
    std::pair<K,V&> operator*(){
        return std::pair<K,V&>(this->current->getKey(),this->current->getValueReference());
    }
    bool operator==(const TIMapIter<K,V>& iter)const{
        return this->current == iter.current;
    }
    bool operator!=(const TIMapIter<K,V>& iter)const{
        return this->current != iter.current;
    }
    TIMapIter<K,V>& operator=(const TIMapIter<K,V>& iter){
        this->current = iter.current;
        return *this;
    }
    TIMapIter<K,V>& operator=(TIMapIter<K,V>&& iter){
        this->current = iter.current;
        iter.current = nullptr;
        return *this;
    }
};

template <typename K,typename V> class TIMapIterConst{
    TINode<K,V>* current;
    protected:
    friend TIMap<K,V>;
    friend TINode<K,V>;
    TIMapIterConst(){
        this->current=nullptr;
    }
    TIMapIterConst(TINode<K,V>* current){
        this->current = current;
    }
    public:
    TIMapIterConst<K,V>& operator++(){
        this->current = this->current->successor();
        return *this;
    }
    TIMapIterConst<K,V>& operator++(int){
        this->current = this->current->successor();
        return *this;
    }
    TIMapIterConst<K,V>& operator--(){
        this->current = this->current->predecessor();
        return *this;
    }
    TIMapIterConst<K,V>& operator--(int){
        this->current = this->current->predecessor();
        return *this;
    }
    std::pair<K,V> operator*(){
        return std::pair<K,V>(this->current->getKey(),this->current->getValue());
    }
    bool operator==(const TIMapIterConst<K,V>& iter)const{
        return this->current == iter.current;
    }
    bool operator!=(const TIMapIterConst<K,V>& iter)const{
        return this->current != iter.current;
    }
    TIMapIterConst<K,V>& operator=(const TIMapIterConst<K,V>& iter){
        this->current = iter.current;
        return *this;
    }
    TIMapIterConst<K,V>& operator=(TIMapIterConst<K,V>&& iter){
        this->current = iter.current;
        iter.current = nullptr;
        return *this;
    }
};

template <typename K,typename V> class TIMapIterReverse{
    TINode<K,V>* current;
    protected:
    friend TIMap<K,V>;
    friend TINode<K,V>;
    TIMapIterReverse(){
        this->current=nullptr;
    }
    TIMapIterReverse(TINode<K,V>* current){
        this->current = current;
    }
    public:
    TIMapIterReverse<K,V>& operator++(){
        this->current = this->current->predecessor();
        return *this;
    }
    TIMapIterReverse<K,V>& operator++(int){
        this->current = this->current->predecessor();
        return *this;
    }
    TIMapIterReverse<K,V>& operator--(){
        this->current = this->current->successor();
        return *this;
    }
    TIMapIterReverse<K,V>& operator--(int){
        this->current = this->current->successor();
        return *this;
    }
    std::pair<K,V&> operator*(){
        return std::pair<K,V&>(this->current->getKey(),this->current->getValueReference());
    }
    bool operator==(const TIMapIterReverse<K,V>& iter)const{
        return this->current == iter.current;
    }
    bool operator!=(const TIMapIterReverse<K,V>& iter)const{
        return this->current != iter.current;
    }
    TIMapIterReverse<K,V>& operator=(const TIMapIterReverse<K,V>& iter){
        this->current = iter.current;
        return *this;
    }
    TIMapIterReverse<K,V>& operator=(TIMapIterReverse<K,V>&& iter){
        this->current = iter.current;
        iter.current = nullptr;
        return *this;
    }
};

template <typename K,typename V> class TIMapIterConstReverse{
    TINode<K,V>* current;
    protected:
    friend TIMap<K,V>;
    friend TINode<K,V>;
    TIMapIterConstReverse(){
        this->current=nullptr;
    }
    TIMapIterConstReverse(TINode<K,V>* current){
        this->current = current;
    }
    public:
    TIMapIterConstReverse<K,V>& operator++(){
        this->current = this->current->predecessor();
        return *this;
    }
    TIMapIterConstReverse<K,V>& operator++(int){
        this->current = this->current->predecessor();
        return *this;
    }
    TIMapIterConstReverse<K,V>& operator--(){
        this->current = this->current->successor();
        return *this;
    }
    TIMapIterConstReverse<K,V>& operator--(int){
        this->current = this->current->successor();
        return *this;
    }
    std::pair<K,V> operator*(){
        return std::pair<K,V>(this->current->getKey(),this->current->getValue());
    }
    bool operator==(const TIMapIterConstReverse<K,V>& iter)const{
        return this->current == iter.current;
    }
    bool operator!=(const TIMapIterConstReverse<K,V>& iter)const{
        return this->current != iter.current;
    }
    TIMapIterConstReverse<K,V>& operator=(const TIMapIterConstReverse<K,V>& iter){
        this->current = iter.current;
        return *this;
    }
    TIMapIterConstReverse<K,V>& operator=(TIMapIterConstReverse<K,V>&& iter){
        this->current = iter.current;
        iter.current = nullptr;
        return *this;
    }
};

template <typename K,typename V> std::ostream& operator<<(std::ostream& os,const TIMap<K,V>& tree);
template <typename K,typename V> std::ostream& operator<<(std::ostream& os,const TINode<K,V>& node);

template <typename K,typename V> class TINode{
    private:
    TIColor color;
    TINode<K,V>* left;
    TINode<K,V>* right;
    TINode<K,V>* parent;
    TIItem<K,V>* item;
    bool nil;

    TINode<K,V>* getNode(K key){
        if(this->getKey() == key)
            return this;
        if(key > this->getKey()){
            if(this->hasRight())
                return this->getRight()->getNode(key);
            return nullptr;
        }
        if(this->hasLeft())
            return this->getLeft()->getNode(key);
        return nullptr;
    }

    TINode<K,V>* removeFixup(TINode<K,V>* root){
        TINode<K,V>* x = this;
        while(x!=root && x->getColor()==INDIGO){
            if(x->isLeftChild()){
                TINode<K,V>* w = x->getSibling();
                if(w->getColor()==TURQUIOISE){
                    w->setColor(INDIGO);
                    x->getParent()->setColor(TURQUIOISE);
                    root = x->getParent()->leftRotate(root);
                    w = x->getParent()->getRight();
                }
                if(w->getLeft()->getColor()==INDIGO && w->getRight()->getColor()==INDIGO){
                    w->setColor(TURQUIOISE);
                    x = x->getParent();
                }else{
                    if(w->getRight()->getColor()==INDIGO){
                        w->getLeft()->setColor(INDIGO);
                        w->setColor(TURQUIOISE);
                        root = w->rightRotate(root);
                        w = x->getParent()->getRight();
                    }
                    w->setColor(x->getParent()->getColor());
                    x->getParent()->setColor(INDIGO);
                    w->getRight()->setColor(INDIGO);
                    root = x->getParent()->leftRotate(root);
                    x = root;
                }
            }else{
                TINode<K,V>* w = x->getSibling();
                if(w->getColor()==TURQUIOISE){
                    w->setColor(INDIGO);
                    x->getParent()->setColor(TURQUIOISE);
                    root = x->getParent()->rightRotate(root);
                    w = x->getParent()->getLeft();
                }
                if(w->getRight()->getColor()==INDIGO && w->getLeft()->getColor()==INDIGO){
                    w->setColor(TURQUIOISE);
                    x = x->getParent();
                }else{
                    if(w->getLeft()->getColor()==INDIGO){
                        w->getRight()->setColor(INDIGO);
                        w->setColor(TURQUIOISE);
                        root = w->leftRotate(root);
                        w = x->getParent()->getLeft();
                    }
                    w->setColor(x->getParent()->getColor());
                    x->getParent()->setColor(INDIGO);
                    w->getLeft()->setColor(INDIGO);
                    root = x->getParent()->rightRotate(root);
                    x = root;
                }
            }
        }
        x->setColor(INDIGO);
        root->setColor(INDIGO);
        if(root->isNil())
            return nullptr;
        return root;
    }
    TINode<K,V>* leftRotate(TINode<K,V>* root){
        if(!this->hasRight()){return root;}
        // temp is never nil
        TINode<K,V>* temp = this->getRight();
        this->setRight(temp->getLeft());
        if(temp->getLeft()!=nullptr){
            temp->getLeft()->setParent(this);
        }
        temp->setParent(this->getParent());
        if(this->getParent() == nullptr){
            root = temp;
        }else if(this->isLeftChild()){
            this->getParent()->setLeft(temp);
        }else{
            this->getParent()->setRight(temp);
        }
        temp->setLeft(this);
        this->setParent(temp);
        return root;
    }
    TINode<K,V>* rightRotate(TINode<K,V>* root){
        if(!this->hasLeft()){return root;}
        // temp is never nil
        TINode<K,V>* temp = this->getLeft();
        this->setLeft(temp->getRight());
        if(temp->getRight()!=nullptr){
            temp->getRight()->setParent(this);
        }
        temp->setParent(this->getParent());
        if(this->getParent() == nullptr){
            root = temp;
        }else if(this->isLeftChild()){
            this->getParent()->setLeft(temp);
        }else{
            this->getParent()->setRight(temp);
        }
        temp->setRight(this);
        this->setParent(temp);
        return root;
    }
    TINode<K,V>* tree_insert(K key,V value){
        if(this->getKey() == key)
            throw KeyAlreadyPresentException("insertion");
        if(key > this->getKey()){
            if(this->hasRight())
                return this->getRight()->tree_insert(key,value);
            delete this->getRight();
            auto new_node = new TINode<K,V>(key,value,TURQUIOISE,this);
            if(new_node == nullptr)
                throw MemoryException("insertion");
            this->setRight(new_node);
            return this->getRight();
        }
        if(this->hasLeft())
            return this->getLeft()->tree_insert(key,value);
        delete this->getLeft();
        auto new_node = new TINode<K,V>(key,value,TURQUIOISE,this);
        if(new_node == nullptr)
            throw MemoryException("insertion");
        this->setLeft(new_node);
        return this->getLeft();
    }

    void dotnames(std::string& s)const{
        if(this->isNil())
            return;
        s += this->dotname()+
            " [label=\"<L>"+
            to_string(this->getKey())+
            " |<R>"+
            to_string(this->getValue())+
            "\", shape=record, style=filled, fillcolor=";
        if (this->getColor()==TURQUIOISE)
            s+="turquoise, fontcolor=black";
        else
            s+="indigo fontcolor=white";
        s += "];\n";
        this->getLeft()->dotnames(s);
        this->getRight()->dotnames(s);
    }

    std::string dotname()const{
        if(this->isNil())
            return "nil";
        return "n_"+to_string(this->getKey());
    }

    void dotedges(std::string& s)const{
        if(this->isNil())
            return;
        if(this->hasLeft())
            s += this->dotedge(this->getLeft())+";\n";
        if(this->hasRight())
            s += this->dotedge(this->getRight())+";\n";
        this->getLeft()->dotedges(s);
        this->getRight()->dotedges(s);
    }

    std::string dotedge(TINode<K,V>* dest)const{
        return this->dotname()+" -> "+dest->dotname();
    }

    protected:
    friend TIMapIter<K,V>;
    friend TIMapIterConst<K,V>;
    friend TIMapIterReverse<K,V>;
    friend TIMapIterConstReverse<K,V>;
    friend TIMap<K,V>;
    
    TINode(){
        this->item = nullptr;
        this->color = INDIGO;
        this->left = nullptr;
        this->right = nullptr;
        this->parent = nullptr;
        this->nil = true;
    }
    TINode(TINode<K,V>* parent){
        this->item = nullptr;
        this->color = INDIGO;
        this->left = nullptr;
        this->right = nullptr;
        this->parent = parent;
        this->nil = true;
    }
    TINode(K key,V value){
        this->item = new TIItem<K,V>(key,value);
        if(this->item==nullptr)
            throw MemoryException("constructor");
        this->color = TURQUIOISE;
        this->left = new TINode<K,V>(this);
        if(this->left==nullptr)
            throw MemoryException("constructor");
        this->right = new TINode<K,V>(this);
        if(this->right==nullptr)
            throw MemoryException("constructor");
        this->parent = nullptr;
        this->nil = false;
    }
    TINode(K key,V value,TIColor node_color){
        this->item = new TIItem<K,V>(key,value);
        if(this->item==nullptr)
            throw MemoryException("constructor");
        this->color = node_color;
        this->left = new TINode<K,V>(this);
        if(this->left==nullptr)
            throw MemoryException("constructor");
        this->right = new TINode<K,V>(this);
        if(this->right==nullptr)
            throw MemoryException("constructor");
        this->parent = nullptr;
        this->nil = false;
    }
    TINode(K key,V value,TINode<K,V>* parent){
        this->item = new TIItem<K,V>(key,value);
        if(this->item==nullptr)
            throw MemoryException("constructor");
        this->color = TURQUIOISE;
        this->left = new TINode<K,V>(this);
        if(this->left==nullptr)
            throw MemoryException("constructor");
        this->right = new TINode<K,V>(this);
        if(this->right==nullptr)
            throw MemoryException("constructor");
        this->parent = parent;
        this->nil = false;
    }
    TINode(K key,V value,TIColor node_color,TINode<K,V>* parent){
        this->item = new TIItem<K,V>(key,value);
        if(this->item==nullptr)
            throw MemoryException("constructor");
        this->color = node_color;
        this->left = new TINode<K,V>(this);
        if(this->left==nullptr)
            throw MemoryException("constructor");
        this->right = new TINode<K,V>(this);
        if(this->right==nullptr)
            throw MemoryException("constructor");
        this->parent = parent;
        this->nil = false;
    }
    TINode(const TINode& node){
        this->color = node.color;
        if(node.left == nullptr)
            this->left = node.left;
        else{
            this->left =new TINode<K,V>(*node.left,this);
            if(this->left==nullptr)
                throw MemoryException("constructor");
        }
        if(node.right == nullptr)
            this->right = node.right;
        else{
            this->right =new TINode<K,V>(*node.right,this);
            if(this->right==nullptr)
                throw MemoryException("constructor");
        }
        this->parent = nullptr;
        if(node.item == nullptr)
            this->item = node.item;
        else{
            this->item =new TIItem<K,V>(*node.item);
            if(this->item==nullptr)
                throw MemoryException("constructor");
        }
        this->nil = node.nil;
    }
    TINode(const TINode& node,TINode<K,V>* parent){
        this->color = node.color;
        if(node.left == nullptr)
            this->left = node.left;
        else{
            this->left =new TINode<K,V>(*node.left,this);
            if(this->left==nullptr)
                throw MemoryException("constructor");
        }
        if(node.right == nullptr)
            this->right = node.right;
        else{
            this->right =new TINode<K,V>(*node.right,this);
            if(this->right==nullptr)
                throw MemoryException("constructor");
        }
        this->parent = parent;
        if(node.item == nullptr)
            this->item = node.item;
        else{
            this->item =new TIItem<K,V>(*node.item);
            if(this->item==nullptr)
                throw MemoryException("constructor");
        }
        this->nil = node.nil;
    }
    TINode(TINode<K,V>&& node){
        this->color = node.color;
        this->left = node.left;
        this->right = node.right;
        this->parent = node.parent;
        this->item = node.item;
        this->nil = node.nil;
        node.left = nullptr;
        node.right = nullptr;
        node.parent = nullptr;
        node.item = nullptr;
    }
    ~TINode(){
        if(this->left != nullptr)
            delete this->left;
        if(this->right != nullptr)
            delete this->right;
        if(this->item != nullptr)
            delete this->item;
    }
    TINode<K,V>& operator=(const TINode& node){
        this->color = node.color;
        this->left = node.left;
        this->right = node.right;
        this->parent = nullptr;
        this->item = node.item;
        this->nil = node.nil;
        return *this;
    }
    TINode<K,V>& operator=(TINode&& node){
        this->color = node.color;
        this->left = node.left;
        this->right = node.right;
        this->parent = node.parent;
        this->item = node.item;
        this->nil = node.nil;
        node.left = nullptr;
        node.right = nullptr;
        node.parent = nullptr;
        node.item = nullptr;
        return *this;
    }
    void setColor(TIColor color){if(!this->isNil())this->color = color;}
    void setLeft(TINode<K,V>* node){this->left = node;}
    void setRight(TINode<K,V>* node){this->right = node;}
    void setParent(TINode<K,V>* node){this->parent = node;}
    void setValue(V value){this->item->setValue(value);}
    void setValue(K key,V value){
        if(this->isNil())
            throw ItemNotFoundException("set value");
        if(this->getKey()==key)
            this->setValue(value);
        if(key > this->getKey()){
            this->getRight()->setValue(key,value);
        }else{
            this->getLeft()->setValue(key,value);
        }
    }
    void setKey(K key){this->item->setKey(key);}
    bool isNil()const{return this->nil;}
    TIColor getColor()const{return this->color;}
    TINode<K,V>* getLeft()const{return this->left;}
    TINode<K,V>* getRight()const{return this->right;}
    TINode<K,V>* getParent()const{return this->parent;}
    TINode<K,V>* getSibling()const{
        if(this->getParent()==nullptr)
            return nullptr;
        if(this->isLeftChild())
            return this->getParent()->getRight();
        return this->getParent()->getLeft();
    }
    TINode<K,V>* getGrandparent()const{
        if(this->getParent()==nullptr)
            return nullptr;
        return this->getParent()->getParent();
    }
    bool contains(K key){
        if(this->isNil())
            return false;
        if(key == this->item->getKey())
            return true;
        if(key > this->item->getKey())
            return this->getRight()->contains(key);
        return this->getLeft()->contains(key);
    }
    V getValue(K key)const{
        if(this->isNil())
            throw ItemNotFoundException("get value");
        if(key == this->item->getKey())
            return this->item->getValue();
        if(key > this->item->getKey())
            return this->getRight()->getValue(key);
        return this->getLeft()->getValue(key);
    }
    TIMapIter<K,V> find(K key){
        if(this->isNil())
            return this->end();
        if(key == this->item->getKey())
            return TIMapIter<K,V>(this);
        if(key > this->item->getKey())
            return this->getRight()->find(key);
        return this->getLeft()->find(key);
    }
    V& getValueReference(K key){
        if(this->isNil())
            throw ItemNotFoundException("get value reference");
        if(key == this->item->getKey())
            return this->item->getValueReference();
        if(key > this->item->getKey())
            return this->getRight()->getValueReference(key);
        return this->getLeft()->getValueReference(key);
    }
    K getKey()const{return this->item->getKey();}
    V getValue()const{return this->item->getValue();}
    V& getValueReference(){return this->item->getValueReference();}
    bool containsValue(V value)const{
        if(value == this->item->getValue())
            return true;
        return (this->hasLeft() && this->getLeft()->containsValue(value)) || 
            (this->hasRight() && this->getRight()->containsValue(value));
    }
    K keyOf(V value)const{
        if(value == this->item->getValue())
            return this->item->getKey();
        else if (this->getLeft()->containsValue(value)){
            this->getLeft()->keyOf(value);
        }else if (this->getRight()->containsValue(value)){
            this->getRight()->keyOf(value);
        }
        throw ItemNotFoundException("key of value");
    }
    bool hasLeft()const{return this->left != nullptr && ! this->left->isNil();}
    bool hasRight()const{return this->right != nullptr && ! this->right->isNil();}
    bool hasParent()const{return this->parent != nullptr;}
    unsigned int size()const{return this->isNil()?0:(this->getLeft()->size() + this->getRight()->size() + 1);}
    bool hasGrandparent()const{return this->hasParent()?this->parent->hasParent():false;}
    bool isLeftChild()const{return this->hasParent()?(this->parent->getLeft() == this):false;}
    bool isRightChild()const{return this->hasParent()?(this->parent->getRight() == this):false;}
    bool hasChildren()const{return this->hasLeft()||this->hasRight();}
    TINode<K,V>* insert(K key,V value,TINode<K,V>* root){
        TINode<K,V>* node = this->tree_insert(key,value);
        while(node!=root && node->getParent()->getColor()==TURQUIOISE){
            // father is never nullptr
            TINode<K,V>* father = node->getParent();
            TINode<K,V>* grandfather = father->getParent();
            TINode<K,V>* uncle = father->getSibling();
            if(uncle->getColor()==TURQUIOISE){
                father->setColor(INDIGO);
                uncle->setColor(INDIGO);
                // grandfather is not nullptr because uncle is not nullptr
                grandfather->setColor(TURQUIOISE);
                node = grandfather;
            }else{
                if(father->isLeftChild()){
                    if(node->isRightChild()){
                        node = father;
                        root = node->leftRotate(root);
                    }
                    node->getParent()->setColor(INDIGO);
                    grandfather->setColor(TURQUIOISE);
                    root = grandfather->rightRotate(root);
                }else{
                    if(node->isLeftChild()){
                        node = father;
                        root = node->rightRotate(root);
                    }
                    node->getParent()->setColor(INDIGO);
                    grandfather->setColor(TURQUIOISE);
                    root = grandfather->leftRotate(root);
                }
            }
        }
        root->setColor(INDIGO);
        return root;
    }
    TINode<K,V>* min()const{
        if(this->hasLeft())
            return this->getLeft()->min();
        return this;
    }
    TINode<K,V>* max()const{
        if(this->hasRight())
            return this->getRight()->max();
        return this;
    }
    TINode<K,V>* successor(){
        if(this->hasRight())
            return this->getRight()->min();
        if(this->isLeftChild())
            return this->getParent();
        if(this->isRightChild()){
            TINode<K,V>* parent = this->getParent();
            while(parent!=nullptr && parent->isRightChild()){
                parent = parent->getParent();
            }
            if(parent == nullptr)
                return nullptr;
            else
                return parent->getParent();
        }
        return nullptr;
    }
    TINode<K,V>* predecessor(){
        if(this->hasLeft())
            return this->getLeft()->max();
        if(this->isRightChild())
            return this->getParent();
        if(this->isLeftChild()){
            TINode<K,V>* parent = this->getParent();
            while(parent!=nullptr && parent->isLeftChild()){
                parent = parent->getParent();
            }
            if(parent == nullptr)
                return nullptr;
            else
                return parent->getParent();
        }
        return nullptr;
    }

    std::pair<TINode<K,V>*,TINode<K,V>*> remove(K key,TINode<K,V>* root){
        TINode<K,V>* node_to_remove = this->getNode(key);
        if(node_to_remove==nullptr)
            throw ItemNotFoundException("remove");
        TINode<K,V>* y = node_to_remove;
        TINode<K,V>* x = node_to_remove;
        if(node_to_remove->hasLeft() && node_to_remove->hasRight()){
            y = node_to_remove->successor();
        }
        if(y->hasLeft()){
            x = y->getLeft();
            y->setLeft(nullptr);
        }else{
            x = y->getRight();
            y->setRight(nullptr);
        }
        //x may be nil
        x->setParent(y->getParent());
        if(y->getParent()==nullptr){
            root = x;
        }else{
            if(y->isLeftChild()){
                x->getParent()->setLeft(x);
            }else{
                x->getParent()->setRight(x);
            }
        }
        if(y != node_to_remove){
            node_to_remove->setKey(y->getKey());
            node_to_remove->setValue(y->getValue());
        }
        if(y->getColor()==INDIGO){
            root = x->removeFixup(root);
        }
        return std::pair<TINode<K,V>*,TINode<K,V>*>(root,y);
    }

    std::string dot()const{
        std::string res ="digraph G{\n";
        this->dotnames(res);
        this->dotedges(res);
        return res+"}";
    }

    TIMapIter<K,V> begin(){return TIMapIter<K,V>(this->min());}
    TIMapIter<K,V> end(){return TIMapIter<K,V>();}
    TIMapIterConst<K,V> cbegin()const{return TIMapIterConst<K,V>(this->min());}
    TIMapIterConst<K,V> cend()const{return TIMapIterConst<K,V>();}
    TIMapIterReverse<K,V> rbegin(){return TIMapIterReverse<K,V>(this->max());}
    TIMapIterReverse<K,V> rend(){return TIMapIterReverse<K,V>();}
    TIMapIterConstReverse<K,V> crbegin()const{return TIMapIterConstReverse<K,V>(this->max());}
    TIMapIterConstReverse<K,V> crend()const{return TIMapIterConstReverse<K,V>();}
    void apply(V (*func)(V)){
        for(auto it=this->begin();it!=this->end();it++){
            (*it).second=func((*it).second);
        }
    }
    V accumulate(V (*func)(const V&,const V&), V init_value)const{
        for(auto iter=this->cbegin(); iter != this->cend(); iter++){
            init_value = func(init_value,*iter);
        } 
        return init_value;
    }
    TIMap<K,V> map(V (*func)(V))const{
        TIMap<K,V> res(*this);
        res.apply(func);
        return res;
    }
    TINode<K,V>* filter(bool (*func)(K), TINode<K,V>* root){
        TISet<K> keys = this->keys();
        keys.antifilter(func);
        for(auto it=keys.cbegin();it!=keys.cend();it++){
            root = (root->remove(*it,root)).first;
        }
        return root;
    }
    TISet<K> keys()const{
        TISet<K> res = TISet<K>();
        for(auto it=this->cbegin();it!=this->cend();it++){
            res.insert((*it).first);
        }
        return res;
    }
    TIMultiSet<V> values()const{
        TIMultiSet<K> res = TIMultiSet<K>();
        for(auto it=this->cbegin();it!=this->cend();it++){
            res.insert((*it).second);
        }
        return res;
    }
    friend std::ostream& operator<< <>(std::ostream& os,const TINode<K,V>& node);
};

template <typename K,typename V> class TIMap{
    private:
    TINode<K,V>* root;

    public:
    TIMap(){
        this->root = new TINode<K,V>();
        if(this->root == nullptr)
            throw MemoryException("constructor");
    }

    TIMap(const TIMap<K,V>& tree){
        if(!tree->isEmpty())
            this->root = new TINode<K,V>(*(tree->root));
        else
            this->root = new TINode<K,V>();
        if(this->root == nullptr)
            throw MemoryException("constructor");
    }

    TIMap(TIMap<K,V>&& tree){
        this->root = tree->root;
        tree.root = nullptr;
    }

    ~TIMap(){
        if(this->root != nullptr)
            delete this->root;
    }

    TIMap<K,V>& operator=(const TIMap& tree){
        if(!tree->isEmpty())
            this->root = new TINode<K,V>(*(tree->root));
        else
            this->root = new TINode<K,V>();
        if(this->root == nullptr)
            throw MemoryException("operator =");
        return *this;
    }

    TIMap<K,V>& operator=(TIMap&& tree){
        this->root = tree->root;
        tree.root = nullptr;
        return *this;
    }
    bool isEmpty()const{return this->root == nullptr || this->root->isNil();}
    unsigned int size()const{return this->isEmpty()?0:this->root->size();}
    bool containsKey(K key)const{return !this->isEmpty() && this->root->contains(key);}
    bool containsValue(V value)const{return !this->isEmpty() && this->root->containsValue(value);}
    K keyOf(V value)const{return !this->isEmpty() && this->root->keyOf(value);}

    void insert(K key,V value){
        if(this->isEmpty()){
            if(this->root!=nullptr)
                delete this->root;
            this->root = new TINode<K,V>(key,value);
            if(this->root == nullptr)
                throw MemoryException("insert");
            this->root->setColor(INDIGO);
        }else
            this->root = this->root->insert(key,value,this->root);
    }

    V remove(K key){
        if(this->isEmpty()){
            throw ItemNotFoundException("remove");
        }else{
            std::pair<TINode<K,V>*,TINode<K,V>*> answer = this->root->remove(key,this->root);
            this->root = answer.first;
            V result = (answer.second)->getValue();
            delete answer.second;
            return result;
        }
    }

    V get(K key)const{
        if(this->isEmpty())
            throw ItemNotFoundException("get");
        return this->root->getValue(key);
    }

    V& getReference(K key){
        if(this->isEmpty())
            throw ItemNotFoundException("get ref");
        return this->root->getValueReference(key);
    }

    V& operator[](K key){
        if(this->isEmpty())
            throw ItemNotFoundException("operator []");
        return this->root->getValueReference(key);
    }

    TIMapIter<K,V> find(K key){
        if(this->isEmpty())
            return this->end();
        return this->root->find(key);
    }

    void update(K key,V value){
        if(this->isEmpty){
            if(this->root != nullptr)
                delete this->root;
            this->root = new TINode<K,V>(key,value);
            if(this->root == nullptr)
                throw MemoryException("update");
        }else{
            if(this->containsKey(key))
                this->root->setValue(key,value);
            else
                this->root->insert(key,value,this->root);
        }
    }

    void safeInsert(K key,V value){
        if(this->isEmpty() || !this->root->contains(key))
            this->insert(key,value);
    }

    std::pair<bool,V> safeRemove(K key,V value){
        if(!this->isEmpty() && this->root->contains(key))
            return std::pair<bool,V>(true,this->remove(key,value));
        return std::pair<bool,V>(false,V());
    }

    std::string dot()const{
        if(this->isEmpty())
            return "digraph G{}";
        return this->root->dot();
    }

    void dump(std::string filename)const{
        std::string dot_content = this->dot();
        std::ofstream output_file;
        output_file.open(filename);
        output_file << dot_content;
        output_file.close();
    }

    TIMapIter<K,V> begin(){
        if(this->isEmpty())
            return TIMapIter<K,V>();
        return this->root->begin();
    }

    TIMapIter<K,V> end(){
        if(this->isEmpty())
            return TIMapIterConst<K,V>();
        return this->root->end();
    }

    TIMapIterConst<K,V> cbegin()const{
        if(this->isEmpty())
            return TIMapIterConst<K,V>();
        return this->root->cbegin();
    }

    TIMapIterConst<K,V> cend()const{
        if(this->isEmpty())
            return TIMapIterConst<K,V>();
        return this->root->cend();
    }

    TIMapIterReverse<K,V> rbegin(){
        if(this->isEmpty())
            return TIMapIterReverse<K,V>();
        return this->root->rbegin();
    }

    TIMapIterReverse<K,V> rend(){
        if(this->isEmpty())
            return TIMapIterReverse<K,V>();
        return this->root->rend();
    }

    TIMapIterConstReverse<K,V> crbegin()const{
        if(this->isEmpty())
            return TIMapIterConstReverse<K,V>();
        return this->root->crbegin();
    }

    TIMapIterConstReverse<K,V> crend()const{
        if(this->isEmpty())
            return TIMapIterConstReverse<K,V>();
        return this->root->crend();
    }

    void apply(V (*func)(V)){
        if(this->isEmpty())
            return;
        this->root->apply(func);
    }
    V accumulate(V (*func)(const V&,const V&), V init_value)const{
        if(this->isEmpty())
            return init_value;
        return this->root->accumulate(func,init_value);
    }
    V accumulate(V (*func)(const V&,const V&))const{
        return this->accumulate(func,V());
    }
    TIMap<K,V> map(V (*func)(V))const{
        if(this->isEmpty()){
            return TIMap<K,V>();
        }
        return this->root->map(func);
    }
    void filter(bool (*func)(K), TINode<K,V>* root){
        if(this->isEmpty()){
            return;
        }
        return this->root->filter(func,this->root);
    }
    TISet<K> keys()const{
        if(this->isEmpty())
            return TISet<K>();
        return this->root->keys();
    }
    TISet<V> values()const{
        if(this->isEmpty())
            return TISet<V>();
        return this->root->values();
    }

    friend std::ostream& operator<< <>(std::ostream& os,const TIMap<K,V>& node);
};

template <typename K,typename V> std::ostream& operator<<(std::ostream& os,const TIMap<K,V>& tree){
    if(tree.isEmpty())
        return os<<"Empty tree\n";
    os<<*(tree.root)<<"\n";
    return os;
}
template <typename K,typename V> std::ostream& print_with_depth(std::ostream& os,const TINode<K,V>& node, unsigned int depth){
    if(node.isNil()){
        for(int i=0;i<depth;i++)
            os<<"\t";
        return os<<"Nil\n";
    }
    print_with_depth(os,*node.getLeft(),depth+1);
    for(int i=0;i<depth;i++)
        os<<"\t";
    os<<"K: "<<node.getKey()<<" V: "<<node.getValue();
    if(node.getColor()==TURQUIOISE)
        os<<" TURQUOISE\n";
    else
        os<<" INDIGO\n";
    print_with_depth(os,*node.getRight(),depth+1);
    return os;
}
template <typename K,typename V> std::ostream& operator<<(std::ostream& os,const TINode<K,V>& node){
    if(node.isNil())
        return os<<"Nil\n";
    return print_with_depth<K,V>(os,node,0);
}

#endif
#ifndef _TURQUOISE_INDIGO_MULTI_TREE_H__
#define _TURQUOISE_INDIGO_MULTI_TREE_H__

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <utility>
#include "tiset.h"
#include "timultiset.h"
#include "tiitem.h"
#include "tiexceptions.h"
#include "tiutil.h"

template <typename K,typename V> class TIMultiNode;
template <typename K,typename V> class TIMultiMap;

template <typename K,typename V> class TIMultiMapIter{
    TIMultiNode<K,V>* current;
    protected:
    friend TIMultiMap<K,V>;
    friend TIMultiNode<K,V>;
    TIMultiMapIter(){
        this->current=nullptr;
    }
    TIMultiMapIter(TIMultiNode<K,V>* current){
        this->current = current;
    }
    public:
    TIMultiMapIter<K,V>& operator++(){
        this->current = this->current->successor();
        return *this;
    }
    TIMultiMapIter<K,V>& operator++(int){
        this->current = this->current->successor();
        return *this;
    }
    TIMultiMapIter<K,V>& operator--(){
        this->current = this->current->predecessor();
        return *this;
    }
    TIMultiMapIter<K,V>& operator--(int){
        this->current = this->current->predecessor();
        return *this;
    }
    std::pair<K,V&> operator*(){
        return std::pair<K,V&>(this->current->getKey(),this->current->getValueReference());
    }
    bool operator==(const TIMultiMapIter<K,V>& iter)const{
        return this->current == iter.current;
    }
    bool operator!=(const TIMultiMapIter<K,V>& iter)const{
        return this->current != iter.current;
    }
    TIMultiMapIter<K,V>& operator=(const TIMultiMapIter<K,V>& iter){
        this->current = iter.current;
        return *this;
    }
    TIMultiMapIter<K,V>& operator=(TIMultiMapIter<K,V>&& iter){
        this->current = iter.current;
        iter.current = nullptr;
        return *this;
    }
};

template <typename K,typename V> class TIMultiMapIterConst{
    TIMultiNode<K,V>* current;
    protected:
    friend TIMultiMap<K,V>;
    friend TIMultiNode<K,V>;
    TIMultiMapIterConst(){
        this->current=nullptr;
    }
    TIMultiMapIterConst(TIMultiNode<K,V>* current){
        this->current = current;
    }
    public:
    TIMultiMapIterConst<K,V>& operator++(){
        this->current = this->current->successor();
        return *this;
    }
    TIMultiMapIterConst<K,V>& operator++(int){
        this->current = this->current->successor();
        return *this;
    }
    TIMultiMapIterConst<K,V>& operator--(){
        this->current = this->current->predecessor();
        return *this;
    }
    TIMultiMapIterConst<K,V>& operator--(int){
        this->current = this->current->predecessor();
        return *this;
    }
    std::pair<K,V> operator*(){
        return std::pair<K,V>(this->current->getKey(),this->current->getValue());
    }
    bool operator==(const TIMultiMapIterConst<K,V>& iter)const{
        return this->current == iter.current;
    }
    bool operator!=(const TIMultiMapIterConst<K,V>& iter)const{
        return this->current != iter.current;
    }
    TIMultiMapIterConst<K,V>& operator=(const TIMultiMapIterConst<K,V>& iter){
        this->current = iter.current;
        return *this;
    }
    TIMultiMapIterConst<K,V>& operator=(TIMultiMapIterConst<K,V>&& iter){
        this->current = iter.current;
        iter.current = nullptr;
        return *this;
    }
};

template <typename K,typename V> class TIMultiMapIterReverse{
    TIMultiNode<K,V>* current;
    protected:
    friend TIMultiMap<K,V>;
    friend TIMultiNode<K,V>;
    TIMultiMapIterReverse(){
        this->current=nullptr;
    }
    TIMultiMapIterReverse(TIMultiNode<K,V>* current){
        this->current = current;
    }
    public:
    TIMultiMapIterReverse<K,V>& operator++(){
        this->current = this->current->predecessor();
        return *this;
    }
    TIMultiMapIterReverse<K,V>& operator++(int){
        this->current = this->current->predecessor();
        return *this;
    }
    TIMultiMapIterReverse<K,V>& operator--(){
        this->current = this->current->successor();
        return *this;
    }
    TIMultiMapIterReverse<K,V>& operator--(int){
        this->current = this->current->successor();
        return *this;
    }
    std::pair<K,V&> operator*(){
        return std::pair<K,V&>(this->current->getKey(),this->current->getValueReference());
    }
    bool operator==(const TIMultiMapIterReverse<K,V>& iter)const{
        return this->current == iter.current;
    }
    bool operator!=(const TIMultiMapIterReverse<K,V>& iter)const{
        return this->current != iter.current;
    }
    TIMultiMapIterReverse<K,V>& operator=(const TIMultiMapIterReverse<K,V>& iter){
        this->current = iter.current;
        return *this;
    }
    TIMultiMapIterReverse<K,V>& operator=(TIMultiMapIterReverse<K,V>&& iter){
        this->current = iter.current;
        iter.current = nullptr;
        return *this;
    }
};

template <typename K,typename V> class TIMultiMapIterConstReverse{
    TIMultiNode<K,V>* current;
    protected:
    friend TIMultiMap<K,V>;
    friend TIMultiNode<K,V>;
    TIMultiMapIterConstReverse(){
        this->current=nullptr;
    }
    TIMultiMapIterConstReverse(TIMultiNode<K,V>* current){
        this->current = current;
    }
    public:
    TIMultiMapIterConstReverse<K,V>& operator++(){
        this->current = this->current->predecessor();
        return *this;
    }
    TIMultiMapIterConstReverse<K,V>& operator++(int){
        this->current = this->current->predecessor();
        return *this;
    }
    TIMultiMapIterConstReverse<K,V>& operator--(){
        this->current = this->current->successor();
        return *this;
    }
    TIMultiMapIterConstReverse<K,V>& operator--(int){
        this->current = this->current->successor();
        return *this;
    }
    std::pair<K,V> operator*(){
        return std::pair<K,V>(this->current->getKey(),this->current->getValue());
    }
    bool operator==(const TIMultiMapIterConstReverse<K,V>& iter)const{
        return this->current == iter.current;
    }
    bool operator!=(const TIMultiMapIterConstReverse<K,V>& iter)const{
        return this->current != iter.current;
    }
    TIMultiMapIterConstReverse<K,V>& operator=(const TIMultiMapIterConstReverse<K,V>& iter){
        this->current = iter.current;
        return *this;
    }
    TIMultiMapIterConstReverse<K,V>& operator=(TIMultiMapIterConstReverse<K,V>&& iter){
        this->current = iter.current;
        iter.current = nullptr;
        return *this;
    }
};

template <typename K,typename V> std::ostream& operator<<(std::ostream& os,const TIMultiMap<K,V>& tree);
template <typename K,typename V> std::ostream& operator<<(std::ostream& os,const TIMultiNode<K,V>& tree);

template <typename K,typename V> class TIMultiNode{
    private:
    TIColor color;
    TIMultiNode<K,V>* left;
    TIMultiNode<K,V>* right;
    TIMultiNode<K,V>* parent;
    TIItem<K,V>* item;
    bool nil;

    TIMultiNode<K,V>* getNode(K key){
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

    std::pair<TIMultiNode<K,V>*,TIMultiNode<K,V>*> tree_remove(TIMultiNode<K,V>* node_to_remove,TIMultiNode<K,V>* root){
        if(node_to_remove==nullptr)
            throw ItemNotFoundException("remove");
        TIMultiNode<K,V>* y = node_to_remove;
        TIMultiNode<K,V>* x = node_to_remove;
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
        return std::pair<TIMultiNode<K,V>*,TIMultiNode<K,V>*>(root,y);
    }

    TIMultiNode<K,V>* removeFixup(TIMultiNode<K,V>* root){
        TIMultiNode<K,V>* x = this;
        while(x!=root && x->getColor()==INDIGO){
            if(x->isLeftChild()){
                TIMultiNode<K,V>* w = x->getSibling();
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
                TIMultiNode<K,V>* w = x->getSibling();
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
    TIMultiNode<K,V>* leftRotate(TIMultiNode<K,V>* root){
        if(!this->hasRight()){return root;}
        // temp is never nil
        TIMultiNode<K,V>* temp = this->getRight();
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
    TIMultiNode<K,V>* rightRotate(TIMultiNode<K,V>* root){
        if(!this->hasLeft()){return root;}
        // temp is never nil
        TIMultiNode<K,V>* temp = this->getLeft();
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
    TIMultiNode<K,V>* tree_insert(K key,V value){
        if(key >= this->getKey()){
            if(this->hasRight())
                return this->getRight()->tree_insert(key,value);
            delete this->getRight();
            auto new_node = new TIMultiNode<K,V>(key,value,TURQUIOISE,this);
            if(new_node==nullptr)
                throw MemoryException("insertion");
            this->setRight(new_node);
            return this->getRight();
        }
        if(this->hasLeft())
            return this->getLeft()->tree_insert(key,value);
        delete this->getLeft();
        auto new_node = new TIMultiNode<K,V>(key,value,TURQUIOISE,this);
            if(new_node==nullptr)
                throw MemoryException("insertion");
        this->setLeft(new_node);
        return this->getLeft();
    }

    void dotnames(std::string& s)const{
        if(this->isNil())
            return;
        s += this->dotname()+
            " [label=\"<L>"+
            to_string(this->getKey()) +
            " |<R>" +
            to_string(this->getValue()) +
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
        return "n_"+to_string(this);
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

    std::string dotedge(TIMultiNode<K,V>* dest)const{
        return this->dotname()+" -> "+dest->dotname();
    }

    protected:
    friend TIMultiMapIter<K,V>;
    friend TIMultiMapIterConst<K,V>;
    friend TIMultiMapIterReverse<K,V>;
    friend TIMultiMapIterConstReverse<K,V>;
    friend TIMultiMap<K,V>;
    TIMultiNode(){
        this->item = nullptr;
        this->color = INDIGO;
        this->left = nullptr;
        this->right = nullptr;
        this->parent = nullptr;
        this->nil = true;
    }
    TIMultiNode(TIMultiNode<K,V>* parent){
        this->item = nullptr;
        this->color = INDIGO;
        this->left = nullptr;
        this->right = nullptr;
        this->parent = parent;
        this->nil = true;
    }
    TIMultiNode(K key,V value){
        this->item = new TIItem<K,V>(key,value);
        this->color = TURQUIOISE;
        this->left = new TIMultiNode<K,V>(this);
        this->right = new TIMultiNode<K,V>(this);
        this->parent = nullptr;
        this->nil = false;
        if(this->item == nullptr || this->left == nullptr || this->right == nullptr)
            throw MemoryException("constructor");
    }
    TIMultiNode(K key,V value,TIColor node_color){
        this->item = new TIItem<K,V>(key,value);
        this->color = node_color;
        this->left = new TIMultiNode<K,V>(this);
        this->right = new TIMultiNode<K,V>(this);
        this->parent = nullptr;
        this->nil = false;
        if(this->item == nullptr || this->left == nullptr || this->right == nullptr)
            throw MemoryException("constructor");
    }
    TIMultiNode(K key,V value,TIMultiNode<K,V>* parent){
        this->item = new TIItem<K,V>(key,value);
        this->color = TURQUIOISE;
        this->left = new TIMultiNode<K,V>(this);
        this->right = new TIMultiNode<K,V>(this);
        this->parent = parent;
        this->nil = false;
        if(this->item == nullptr || this->left == nullptr || this->right == nullptr)
            throw MemoryException("constructor");
    }
    TIMultiNode(K key,V value,TIColor node_color,TIMultiNode<K,V>* parent){
        this->item = new TIItem<K,V>(key,value);
        this->color = node_color;
        this->left = new TIMultiNode<K,V>(this);
        this->right = new TIMultiNode<K,V>(this);
        this->parent = parent;
        this->nil = false;
        if(this->item == nullptr || this->left == nullptr || this->right == nullptr)
            throw MemoryException("constructor");
    }
    TIMultiNode(const TIMultiNode<K,V>& node){
        this->color = node.color;
        if(node.left==nullptr)
            this->left = node.left;
        else{
            this->left = new TIMultiNode<K,V>(*(node.left),this);
            if(this->left == nullptr)
                throw MemoryException("constructor");
        }
        if(node.right==nullptr)
            this->right = node.right;
        else{
            this->right = new TIMultiNode<K,V>(*(node.right),this);
            if(this->right == nullptr)
                throw MemoryException("constructor");
        }
        this->parent = nullptr;
        if(node.item==nullptr)
            this->item = node.item;
        else{
            this->item = new TIItem<K,V>(*(node.item));
            if(this->item == nullptr)
                throw MemoryException("constructor");
        }
        this->nil = node.nil;
    }
    TIMultiNode(const TIMultiNode<K,V>& node,TIMultiNode<K,V>* parent){
        this->color = node.color;
        if(node.left==nullptr)
            this->left = node.left;
        else{
            this->left = new TIMultiNode<K,V>(*(node.left),this);
            if(this->left == nullptr)
                throw MemoryException("constructor");
        }
        if(node.right==nullptr)
            this->right = node.right;
        else{
            this->right = new TIMultiNode<K,V>(*(node.right),this);
            if(this->right == nullptr)
                throw MemoryException("constructor");
        }
        this->parent = parent;
        if(node.item==nullptr)
            this->item = node.item;
        else{
            this->item = new TIItem<K,V>(*(node.item));
            if(this->item == nullptr)
                throw MemoryException("constructor");
        }
        this->nil = node.nil;
    }
    TIMultiNode(TIMultiNode<K,V>&& node){
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
    ~TIMultiNode(){
        if(this->left != nullptr)
            delete this->left;
        if(this->right != nullptr)
            delete this->right;
        if(this->item != nullptr)
            delete this->item;
    }
    TIMultiNode<K,V>& operator=(const TIMultiNode<K,V>& node){
        this->color = node.color;
        this->left = node.left;
        this->right = node.right;
        this->parent = nullptr;
        this->item = node.item;
        this->nil = node.nil;
        return *this;
    }
    TIMultiNode<K,V>& operator=(TIMultiNode<K,V>&& node){
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
    void setLeft(TIMultiNode<K,V>* node){this->left = node;}
    void setRight(TIMultiNode<K,V>* node){this->right = node;}
    void setParent(TIMultiNode<K,V>* node){this->parent = node;}
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
    TIMultiNode<K,V>* getLeft()const{return this->left;}
    TIMultiNode<K,V>* getRight()const{return this->right;}
    TIMultiNode<K,V>* getParent()const{return this->parent;}
    TIMultiNode<K,V>* getSibling()const{
        if(this->getParent()==nullptr)
            return nullptr;
        if(this->isLeftChild())
            return this->getParent()->getRight();
        return this->getParent()->getLeft();
    }
    TIMultiNode<K,V>* getGrandparent()const{
        if(this->getParent()==nullptr)
            return nullptr;
        return this->getParent()->getParent();
    }
    bool contains(K key){
        if(this->isNil())
            return false;
        if(key == this->getKey())
            return true;
        if(key > this->getKey())
            return this->getRight()->contains(key);
        return this->getLeft()->contains(key);
    }
    V getValue(K key)const{
        if(this->isNil())
            throw ItemNotFoundException("get value");
        if(key == this->getKey())
            return this->getValue();
        if(key > this->getKey())
            return this->getRight()->getValue(key);
        return this->getLeft()->getValue(key);
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
    TIMultiMapIter<K,V> find(K key){
        if(this->isNil())
            return this->end();
        if(key == this->item->getKey())
            return TIMultiMapIter<K,V>(this);
        if(key > this->item->getKey())
            return this->getRight()->find(key);
        return this->getLeft()->find(key);
    }
    bool hasLeft()const{return this->left != nullptr && ! this->left->isNil();}
    bool hasRight()const{return this->right != nullptr && ! this->right->isNil();}
    bool hasParent()const{return this->parent != nullptr;}
    unsigned int size()const{return this->isNil()?0:(this->getLeft()->size() + this->getRight()->size() + 1);}
    bool hasGrandparent()const{return this->hasParent()?this->parent->hasParent():false;}
    bool isLeftChild()const{return this->hasParent()?(this->parent->getLeft() == this):false;}
    bool isRightChild()const{return this->hasParent()?(this->parent->getRight() == this):false;}
    bool hasChildren()const{return this->hasLeft()||this->hasRight();}
    TIMultiNode<K,V>* insert(K key,V value,TIMultiNode<K,V>* root){
        TIMultiNode<K,V>* node = this->tree_insert(key,value);
        while(node!=root && node->getParent()->getColor()==TURQUIOISE){
            // father is never nullptr
            TIMultiNode<K,V>* father = node->getParent();
            TIMultiNode<K,V>* grandfather = father->getParent();
            TIMultiNode<K,V>* uncle = father->getSibling();
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
    TIMultiNode<K,V>* min()const{
        if(this->hasLeft())
            return this->getLeft()->min();
        return const_cast<TIMultiNode<K,V>*>(this);
    }
    TIMultiNode<K,V>* max()const{
        if(this->hasRight())
            return this->getRight()->max();
        return const_cast<TIMultiNode<K,V>*>(this);
    }
    TIMultiNode<K,V>* successor(){
        if(this->hasRight())
            return this->getRight()->min();
        if(this->isLeftChild())
            return this->getParent();
        if(this->isRightChild()){
            TIMultiNode<K,V>* parent = this->getParent();
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
    TIMultiNode<K,V>* predecessor(){
        if(this->hasLeft())
            return this->getLeft()->max();
        if(this->isRightChild())
            return this->getParent();
        if(this->isLeftChild()){
            TIMultiNode<K,V>* parent = this->getParent();
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

    std::pair<TIMultiNode<K,V>*,TIMultiNode<K,V>*> remove(K key,TIMultiNode<K,V>* root){
        TIMultiNode<K,V>* node_to_remove = this->getNode(key);
        return tree_remove(node_to_remove,root);
    }

    std::pair<TIMultiNode<K,V>*,TISet<TIMultiNode<K,V>*>> remove_all(K key,TIMultiNode<K,V>* root){
        TIMultiNode<K,V>* node_to_remove = root->getNode(key);
        TISet<TIMultiNode<K,V>*> result = TISet<TIMultiNode<K,V>*>(); 
        while(node_to_remove!=nullptr){
            std::pair<TIMultiNode<K,V>*,TIMultiNode<K,V>*> remove_result = root->tree_remove(node_to_remove,root);
            root = remove_result.first;
            result.insert(remove_result.second);
            node_to_remove = root->getNode(key);
        }
        return std::pair<TIMultiNode<K,V>*,TISet<TIMultiNode<K,V>*>>(root,result);
    }

    std::string dot()const{
        std::string res ="digraph G{\n";
        this->dotnames(res);
        this->dotedges(res);
        return res+"}";
    }

    TIMultiMapIter<K,V> begin(){return TIMultiMapIter<K,V>(this->min());}
    TIMultiMapIter<K,V> end(){return TIMultiMapIter<K,V>();}
    TIMultiMapIterConst<K,V> cbegin()const{return TIMultiMapIterConst<K,V>(this->min());}
    TIMultiMapIterConst<K,V> cend()const{return TIMultiMapIterConst<K,V>();}
    TIMultiMapIterReverse<K,V> rbegin(){return TIMultiMapIterReverse<K,V>(this->max());}
    TIMultiMapIterReverse<K,V> rend(){return TIMultiMapIterReverse<K,V>();}
    TIMultiMapIterConstReverse<K,V> crbegin()const{return TIMultiMapIterConstReverse<K,V>(this->max());}
    TIMultiMapIterConstReverse<K,V> crend()const{return TIMultiMapIterConstReverse<K,V>();}
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
    TIMultiMap<K,V> map(V (*func)(V))const{
        TIMultiMap<K,V> res(*this);
        res.apply(func);
        return res;
    }
    TIMultiNode<K,V>* filter(bool (*func)(K), TIMultiNode<K,V>* root){
        TIMultiSet<K> keys = this->keys();
        keys.antifilter(func);
        for(auto it=keys.cbegin();it!=keys.cend();it++){
            root = (root->remove_all(*it,root)).first;
        }
        return root;
    }
    TIMultiSet<K> keys()const{
        TIMultiSet<K> res = TIMultiSet<K>();
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
    friend std::ostream& operator<< <>(std::ostream& os,const TIMultiNode<K,V>& node);
};

template <typename K,typename V> class TIMultiMap{
    private:
    TIMultiNode<K,V>* root;

    public:
    TIMultiMap(){
        this->root = new TIMultiNode<K,V>();
        if(this->root == nullptr)
            throw MemoryException("constructor");
    }

    TIMultiMap(const TIMultiMap<K,V>& tree){
        if(!tree.isEmpty())
            this->root = new TIMultiNode<K,V>(*(tree.root));
        else
            this->root = new TIMultiNode<K,V>();
        if(this->root == nullptr)
            throw MemoryException("constructor");
    }

    TIMultiMap(TIMultiMap<K,V>&& tree){
        this->root = tree.root;
        tree.root = nullptr;
    }

    ~TIMultiMap(){
        if(this->root != nullptr)
            delete this->root;
    }

    TIMultiMap<K,V>& operator=(const TIMultiMap<K,V>& tree){
        if(!tree->isEmpty())
            this->root = new TIMultiNode<K,V>(*(tree->root));
        else
            this->root = new TIMultiNode<K,V>();
        if(this->root == nullptr)
            throw MemoryException("operator =");
        return *this;
    }

    TIMultiMap<K,V>& operator=(TIMultiMap<K,V>&& tree){
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
            this->root = new TIMultiNode<K,V>(key,value);
            this->root->setColor(INDIGO);
        }else
            this->root = this->root->insert(key,value,this->root);
    }

    V remove(K key){
        if(this->isEmpty()){
            throw ItemNotFoundException("remove");
        }else{
            std::pair<TIMultiNode<K,V>*,TIMultiNode<K,V>*> answer = this->root->remove(key,this->root);
            this->root = answer.first;
            V result = (answer.second)->getValue();
            delete answer.second;
            return result;
        }
    }

    TISet<V> remove_all(K key){
        if(this->isEmpty()){
            throw ItemNotFoundException("remove all");
        }else{
            std::pair<TIMultiNode<K,V>*,TISet<TIMultiNode<K,V>*>> answer = this->root->remove_all(key,this->root);
            this->root = answer.first;
            TISet<TIMultiNode<K,V>*>  answer_set = answer.second;
            if(answer_set.isEmpty())
                throw ItemNotFoundException("remove all");
            TISet<V> results = TISet<V>(); 
            for(auto it=answer_set.cbegin();it!=answer_set.cend();it++){
                results.safeInsert((*it)->getValue());
                delete (*it);
            }
            return results;
        }
    }

    TISet<V> safeRemoveAll(K key){
        if(this->isEmpty() || (!(this->containsKey(key))))
            return TISet<V>();
        return this->remove_all(key);
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

    TIMultiMapIter<K,V> find(K key){
        if(this->isEmpty())
            return this->end();
        return this->root->find(key);
    }

    void update(K key,V value){
        if(this->isEmpty){
            if(this->root != nullptr)
                delete this->root;
            this->root = new TIMultiNode<K,V>(key,value);
            if(this->root == nullptr)
                throw MemoryException("update");
        }else{
            if(this->containsKey(key))
                this->root->setValue(key,value);
            else
                this->root->insert(key,value,this->root);
        }
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

    TIMultiMapIter<K,V> begin(){
        if(this->isEmpty())
            return TIMultiMapIter<K,V>();
        return this->root->begin();
    }

    TIMultiMapIter<K,V> end(){
        if(this->isEmpty())
            return TIMultiMapIterConst<K,V>();
        return this->root->end();
    }

    TIMultiMapIterConst<K,V> cbegin()const{
        if(this->isEmpty())
            return TIMultiMapIterConst<K,V>();
        return this->root->cbegin();
    }

    TIMultiMapIterConst<K,V> cend()const{
        if(this->isEmpty())
            return TIMultiMapIterConst<K,V>();
        return this->root->cend();
    }

    TIMultiMapIterReverse<K,V> rbegin(){
        if(this->isEmpty())
            return TIMultiMapIterReverse<K,V>();
        return this->root->rbegin();
    }

    TIMultiMapIterReverse<K,V> rend(){
        if(this->isEmpty())
            return TIMultiMapIterReverse<K,V>();
        return this->root->rend();
    }

    TIMultiMapIterConstReverse<K,V> crbegin()const{
        if(this->isEmpty())
            return TIMultiMapIterConstReverse<K,V>();
        return this->root->crbegin();
    }

    TIMultiMapIterConstReverse<K,V> crend()const{
        if(this->isEmpty())
            return TIMultiMapIterConstReverse<K,V>();
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
    TIMultiMap<K,V> map(V (*func)(V))const{
        if(this->isEmpty()){
            return TIMultiMap<K,V>();
        }
        return this->root->map(func);
    }
    void filter(bool (*func)(K)){
        if(this->isEmpty()){
            return;
        }
        this->root = this->root->filter(func,this->root);
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

    friend std::ostream& operator<< <>(std::ostream& os,const TIMultiMap<K,V>& node);
};

template <typename K,typename V> std::ostream& operator<<(std::ostream& os,const TIMultiMap<K,V>& tree){
    if(tree.isEmpty())
        return os<<"Empty tree\n";
    os<<*(tree.root)<<"\n";
    return os;
}
template <typename K,typename V> std::ostream& print_with_depth(std::ostream& os,const TIMultiNode<K,V>& node, unsigned int depth){
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
template <typename K,typename V> std::ostream& operator<<(std::ostream& os,const TIMultiNode<K,V>& node){
    if(node.isNil())
        return os<<"Nil\n";
    return print_with_depth<K,V>(os,node,0);
}

#endif
#ifndef _TURQUOISE_INDIGO_MULTI_SET_H__
#define _TURQUOISE_INDIGO_MULTI_SET_H__

#include <string>
#include <exception>
#include <iostream>
#include <sstream>
#include <fstream>
#include <utility>
#include "tiset.h"
#include "tiexceptions.h"
#include "tiutil.h"


template <typename T> class TIMultiSetNode;
template <typename T> class TIMultiSet;

template <typename T> class TIMultiSetIterConst{
    TIMultiSetNode<T>* current;
    protected:
    friend TIMultiSetNode<T>;
    friend TIMultiSet<T>;
    TIMultiSetIterConst(){
        this->current=nullptr;
    }
    TIMultiSetIterConst(TIMultiSetNode<T>* current){
        this->current = current;
    }
    public:
    TIMultiSetIterConst<T>& operator++(){
        this->current = this->current->successor();
        return *this;
    }
    TIMultiSetIterConst<T>& operator++(int){
        this->current = this->current->successor();
        return *this;
    }
    TIMultiSetIterConst<T>& operator--(){
        this->current = this->current->predecessor();
        return *this;
    }
    TIMultiSetIterConst<T>& operator--(int){
        this->current = this->current->predecessor();
        return *this;
    }
    T operator*(){
        return this->current->getValue();
    }
    bool operator==(const TIMultiSetIterConst<T>& iter)const{
        return this->current == iter.current;
    }
    bool operator!=(const TIMultiSetIterConst<T>& iter)const{
        return this->current != iter.current;
    }
    TIMultiSetIterConst<T>& operator=(const TIMultiSetIterConst<T>& iter){
        this->current = iter.current;
        return *this;
    }
    TIMultiSetIterConst<T>& operator=(TIMultiSetIterConst<T>&& iter){
        this->current = iter.current;
        iter.current = nullptr;
        return *this;
    }
};

template <typename T> class TIMultiSetIterConstReverse{
    TIMultiSetNode<T>* current;
    protected:
    friend TIMultiSetNode<T>;
    friend TIMultiSet<T>;
    TIMultiSetIterConstReverse(){
        this->current=nullptr;
    }
    TIMultiSetIterConstReverse(TIMultiSetNode<T>* current){
        this->current = current;
    }
    public:
    TIMultiSetIterConstReverse<T>& operator++(){
        this->current = this->current->predecessor();
        return *this;
    }
    TIMultiSetIterConstReverse<T>& operator++(int){
        this->current = this->current->predecessor();
        return *this;
    }
    TIMultiSetIterConstReverse<T>& operator--(){
        this->current = this->current->successor();
        return *this;
    }
    TIMultiSetIterConstReverse<T>& operator--(int){
        this->current = this->current->successor();
        return *this;
    }
    T operator*(){
        return this->current->getValue();
    }
    bool operator==(const TIMultiSetIterConstReverse<T>& iter)const{
        return this->current == iter.current;
    }
    bool operator!=(const TIMultiSetIterConstReverse<T>& iter)const{
        return this->current != iter.current;
    }
    TIMultiSetIterConstReverse<T>& operator=(const TIMultiSetIterConstReverse<T>& iter){
        this->current = iter.current;
        return *this;
    }
    TIMultiSetIterConstReverse<T>& operator=(TIMultiSetIterConstReverse<T>&& iter){
        this->current = iter.current;
        iter.current = nullptr;
        return *this;
    }
};

template <typename T> std::ostream& operator<<(std::ostream& os,const TIMultiSet<T>& tree);
template <typename T> std::ostream& operator<<(std::ostream& os,const TIMultiSetNode<T>& tree);

template <typename T> class TIMultiSetNode{
    private:
    TIColor color;
    TIMultiSetNode<T>* left;
    TIMultiSetNode<T>* right;
    TIMultiSetNode<T>* parent;
    T value;
    bool nil;

    TIMultiSetNode<T>* getNode(T key){
        if(this->getValue() == key)
            return this;
        if(key > this->getValue()){
            if(this->hasRight())
                return this->getRight()->getNode(key);
            return nullptr;
        }
        if(this->hasLeft())
            return this->getLeft()->getNode(key);
        return nullptr;
    }

    std::pair<TIMultiSetNode<T>*,TIMultiSetNode<T>*> removeNode(TIMultiSetNode<T>* node_to_remove,TIMultiSetNode<T>* root){
        if(node_to_remove==nullptr)
            throw SetItemNotFoundException("remove");
        TIMultiSetNode<T>* y = node_to_remove;
        TIMultiSetNode<T>* x = node_to_remove;
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
            node_to_remove->setValue(y->getValue());
        }
        if(y->getColor()==INDIGO){
            root = x->removeFixup(root);
        }
        return std::pair<TIMultiSetNode<T>*,TIMultiSetNode<T>*>(root,y);
    }

    TIMultiSetNode<T>* removeFixup(TIMultiSetNode<T>* root){
        TIMultiSetNode<T>* x = this;
        while(x!=root && x->getColor()==INDIGO){
            if(x->isLeftChild()){
                TIMultiSetNode<T>* w = x->getSibling();
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
                TIMultiSetNode<T>* w = x->getSibling();
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
    TIMultiSetNode<T>* leftRotate(TIMultiSetNode<T>* root){
        if(!this->hasRight()){return root;}
        // temp is never nil
        TIMultiSetNode<T>* temp = this->getRight();
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
    TIMultiSetNode<T>* rightRotate(TIMultiSetNode<T>* root){
        if(!this->hasLeft()){return root;}
        // temp is never nil
        TIMultiSetNode<T>* temp = this->getLeft();
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
    TIMultiSetNode<T>* tree_insert(T value){
        if(value >= this->getValue()){
            if(this->hasRight())
                return this->getRight()->tree_insert(value);
            delete this->getRight();
            auto new_node = new TIMultiSetNode<T>(value,TURQUIOISE,this);
            if(new_node==nullptr)
                throw MemoryException("insertion");
            this->setRight(new_node);
            return this->getRight();
        }
        if(this->hasLeft())
            return this->getLeft()->tree_insert(value);
        delete this->getLeft();
        auto new_node = new TIMultiSetNode<T>(value,TURQUIOISE,this);
            if(new_node==nullptr)
                throw MemoryException("insertion");
        this->setLeft(new_node);
        return this->getLeft();
    }

    void dotnames(std::string& s)const{
        if(this->isNil())
            return;
        s += this->dotname()+
            " [label=\""+
            to_string(this->getValue())+
            "\", style=filled, fillcolor=";
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

    std::string dotedge(TIMultiSetNode<T>* dest)const{
        return this->dotname()+" -> "+dest->dotname();
    }

    protected:
    friend TIMultiSet<T>;
    friend TIMultiSetIterConst<T>;
    friend TIMultiSetIterConstReverse<T>;
    TIMultiSetNode(){
        this->value = T();
        this->color = INDIGO;
        this->left = nullptr;
        this->right = nullptr;
        this->parent = nullptr;
        this->nil = true;
    }
    TIMultiSetNode(TIMultiSetNode<T>* parent){
        this->value = T();
        this->color = INDIGO;
        this->left = nullptr;
        this->right = nullptr;
        this->parent = parent;
        this->nil = true;
    }
    TIMultiSetNode(T value){
        this->value = value;
        this->color = TURQUIOISE;
        this->left = new TIMultiSetNode<T>(this);
        this->right = new TIMultiSetNode<T>(this);
        this->parent = nullptr;
        this->nil = false;
        if(this->left == nullptr || this->right == nullptr)
            throw MemoryException("constructor");
    }
    TIMultiSetNode(T value,TIColor node_color){
        this->value = value;
        this->color = node_color;
        this->left = new TIMultiSetNode<T>(this);
        this->right = new TIMultiSetNode<T>(this);
        this->parent = nullptr;
        this->nil = false;
        if(this->left == nullptr || this->right == nullptr)
            throw MemoryException("constructor");
    }
    TIMultiSetNode(T value,TIMultiSetNode<T>* parent){
        this->value = value;
        this->color = TURQUIOISE;
        this->left = new TIMultiSetNode<T>(this);
        this->right = new TIMultiSetNode<T>(this);
        this->parent = parent;
        this->nil = false;
        if(this->left == nullptr || this->right == nullptr)
            throw MemoryException("constructor");
    }
    TIMultiSetNode(T value,TIColor node_color,TIMultiSetNode<T>* parent){
        this->value = value;
        this->color = node_color;
        this->left = new TIMultiSetNode<T>(this);
        this->right = new TIMultiSetNode<T>(this);
        this->parent = parent;
        this->nil = false;
        if(this->left == nullptr || this->right == nullptr)
            throw MemoryException("constructor");
    }
    TIMultiSetNode(const TIMultiSetNode<T>& node){
        this->color = node.color;
        if(node.left==nullptr)
            this->left = nullptr;
        else{
            this->left = new TIMultiSetNode<T>(*(node.left),this);
            if(this->left==nullptr)
                throw MemoryException("constructor");
        }
        if(node.right==nullptr)
            this->right = nullptr;
        else{
            this->right = new TIMultiSetNode<T>(*(node.right),this);
            if(this->right==nullptr)
                throw MemoryException("constructor");
        }
        this->parent = nullptr;
        this->value = node.value;
        this->nil = node.nil;
    }
    TIMultiSetNode(const TIMultiSetNode<T>& node,TIMultiSetNode<T>* parent){
        this->color = node.color;
        if(node.left==nullptr)
            this->left = nullptr;
        else{
            this->left = new TIMultiSetNode<T>(*(node.left),this);
            if(this->left==nullptr)
                throw MemoryException("constructor");
        }
        if(node.right==nullptr)
            this->right = nullptr;
        else{
            this->right = new TIMultiSetNode<T>(*(node.right),this);
            if(this->right==nullptr)
                throw MemoryException("constructor");
        }
        this->parent = parent;
        this->value = node.value;
        this->nil = node.nil;
    }
    TIMultiSetNode(TIMultiSetNode<T>&& node){
        this->color = node.color;
        this->left = node.left;
        this->right = node.right;
        this->parent = node.parent;
        this->value = node.value;
        this->nil = node.nil;
        node.left = nullptr;
        node.right = nullptr;
        node.parent = nullptr;
        node.value = T();
    }
    ~TIMultiSetNode(){
        if(this->left != nullptr)
            delete this->left;
        if(this->right != nullptr)
            delete this->right;
    }
    TIMultiSetNode<T>& operator=(const TIMultiSetNode<T>& node){
        this->color = node.color;
        this->left = node.left;
        this->right = node.right;
        this->parent = nullptr;
        this->value = node.value;
        this->nil = node.nil;
        return *this;
    }
    TIMultiSetNode<T>& operator=(TIMultiSetNode<T>&& node){
        this->color = node.color;
        this->left = node.left;
        this->right = node.right;
        this->parent = node.parent;
        this->item = node.item;
        this->nil = node.nil;
        node.left = nullptr;
        node.right = nullptr;
        node.parent = nullptr;
        node.value = T();
        return *this;
    }
    void setColor(TIColor color){if(!this->isNil())this->color = color;}
    void setLeft(TIMultiSetNode<T>* node){this->left = node;}
    void setRight(TIMultiSetNode<T>* node){this->right = node;}
    void setParent(TIMultiSetNode<T>* node){this->parent = node;}
    void setValue(T value){this->value = value;}
    bool isNil()const{return this->nil;}
    TIColor getColor()const{return this->color;}
    TIMultiSetNode<T>* getLeft()const{return this->left;}
    TIMultiSetNode<T>* getRight()const{return this->right;}
    TIMultiSetNode<T>* getParent()const{return this->parent;}
    TIMultiSetNode<T>* getSibling()const{
        if(this->getParent()==nullptr)
            return nullptr;
        if(this->isLeftChild())
            return this->getParent()->getRight();
        return this->getParent()->getLeft();
    }
    TIMultiSetNode<T>* getGrandparent()const{
        if(this->getParent()==nullptr)
            return nullptr;
        return this->getParent()->getParent();
    }
    bool contains(T key){
        if(this->isNil())
            return false;
        if(key == this->getValue())
            return true;
        if(key > this->getValue())
            return this->getRight()->contains(key);
        return this->getLeft()->contains(key);
    }
    TIMultiSetIterConst<T> find(T key){
        if(this->isNil())
            return this->cend();
        if(key == this->item->getKey())
            return TIMultiSetIterConst<T>(this);
        if(key > this->item->getKey())
            return this->getRight()->find(key);
        return this->getLeft()->find(key);
    }
    T getValue()const{return this->value;}
    bool hasLeft()const{return this->left != nullptr && ! this->left->isNil();}
    bool hasRight()const{return this->right != nullptr && ! this->right->isNil();}
    bool hasParent()const{return this->parent != nullptr;}
    unsigned int size()const{return this->isNil()?0:(this->getLeft()->size() + this->getRight()->size() + 1);}
    bool hasGrandparent()const{return this->hasParent()?this->parent->hasParent():false;}
    bool isLeftChild()const{return this->hasParent()?(this->parent->getLeft() == this):false;}
    bool isRightChild()const{return this->hasParent()?(this->parent->getRight() == this):false;}
    bool hasChildren()const{return this->hasLeft()||this->hasRight();}
    TIMultiSetNode<T>* insert(T value,TIMultiSetNode<T>* root){
        TIMultiSetNode<T>* node = this->tree_insert(value);
        while(node!=root && node->getParent()->getColor()==TURQUIOISE){
            // father is never nullptr
            TIMultiSetNode<T>* father = node->getParent();
            TIMultiSetNode<T>* grandfather = father->getParent();
            TIMultiSetNode<T>* uncle = father->getSibling();
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
    TIMultiSetNode<T>* min()const{
        if(this->hasLeft())
            return this->getLeft()->min();
        return const_cast<TIMultiSetNode<T>*>(this);
    }
    TIMultiSetNode<T>* max()const{
        if(this->hasRight())
            return this->getRight()->max();
        return const_cast<TIMultiSetNode<T>*>(this);
    }
    TIMultiSetNode<T>* successor(){
        if(this->hasRight())
            return this->getRight()->min();
        if(this->isLeftChild())
            return this->getParent();
        if(this->isRightChild()){
            TIMultiSetNode<T>* parent = this->getParent();
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
    TIMultiSetNode<T>* predecessor(){
        if(this->hasLeft())
            return this->getLeft()->max();
        if(this->isRightChild())
            return this->getParent();
        if(this->isLeftChild()){
            TIMultiSetNode<T>* parent = this->getParent();
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

    std::pair<TIMultiSetNode<T>*,TIMultiSetNode<T>*> remove(T value,TIMultiSetNode<T>* root){
        TIMultiSetNode<T>* node_to_remove = this->getNode(value);
        return this->removeNode(node_to_remove,root);
    }

    std::pair<TIMultiSetNode<T>*,TISet<TIMultiSetNode<T>*>> remove_all(T value,TIMultiSetNode<T>* root){
        TIMultiSetNode<T>* node_to_remove = root->getNode(value);
        TISet<TIMultiSetNode<T>*> result = TISet<TIMultiSetNode<T>*>();
        while(node_to_remove!=nullptr){
            std::pair<TIMultiSetNode<T>*,TIMultiSetNode<T>*> current = root->removeNode(node_to_remove,root);
            root = current.first;
            result.insert(current.second);
            node_to_remove = root->getNode(value);
        }
        return std::pair<TIMultiSetNode<T>*,TISet<TIMultiSetNode<T>*>>(root,result);
    }

    std::string dot()const{
        std::string res ="digraph G{\n";
        this->dotnames(res);
        this->dotedges(res);
        return res+"}";
    }

    TIMultiSetIterConst<T> cbegin()const{return TIMultiSetIterConst<T>(this->min());}
    TIMultiSetIterConst<T> cend()const{return TIMultiSetIterConst<T>();}
    TIMultiSetIterConstReverse<T> crbegin()const{return TIMultiSetIterConstReverse<T>(this->max());}
    TIMultiSetIterConstReverse<T> crend()const{return TIMultiSetIterConstReverse<T>();}
    T accumulate(T (*func)(const T&,const T&), T init_value)const{
        for(auto iter=this->cbegin(); iter != this->cend(); iter++){
            init_value = func(init_value,*iter);
        } 
        return init_value;
    }
    TIMultiSet<T> map(T (*func)(T))const{
        TIMultiSet<T> res(*this);
        for(auto iter=this->cbegin(); iter != this->cend(); iter++){
            res.insert(func((*iter)));
        } 
        return res;
    }
    TIMultiSetNode<T>* filter(bool (*func)(T), TIMultiSetNode<T>* root){
        TISet<T> removed = TISet<T>();
        for(auto it=this->cbegin();it!=this->cend();it++){
            if(func(*it)){
                removed.safeInsert(*it);
            }
        }
        for(auto it=removed.cbegin();it!=removed.cend();it++){
            root = (root->remove_all(*it,root)).first;
        }
        return root;
    }
    TIMultiSetNode<T>* antifilter(bool (*func)(T), TIMultiSetNode<T>* root){
        TISet<T> removed = TISet<T>();
        for(auto it=this->cbegin();it!=this->cend();it++){
            if(!func(*it)){
                removed.safeInsert(*it);
            }
        }
        for(auto it=removed.cbegin();it!=removed.cend();it++){
            root = (root->remove_all(*it,root)).first;
        }
        return root;
    }
    friend std::ostream& operator<< <>(std::ostream& os,const TIMultiSetNode<T>& node);
};

template <typename T> class TIMultiSet{
    private:
    TIMultiSetNode<T>* root;

    public:
    TIMultiSet(){
        this->root = new TIMultiSetNode<T>();
        if(this->root == nullptr)
            throw MemoryException("constructor");
    }

    TIMultiSet(const TIMultiSet<T>& tree){
        if(!tree.isEmpty())
            this->root = new TIMultiSetNode<T>(*(tree.root));
        else
            this->root = new TIMultiSetNode<T>();
        if(this->root == nullptr)
            throw MemoryException("constructor");
    }

    TIMultiSet(TIMultiSet<T>&& tree){
        this->root = tree.root;
        tree.root = nullptr;
    }

    ~TIMultiSet(){
        if(this->root != nullptr)
            delete this->root;
    }

    TIMultiSet<T>& operator=(const TIMultiSet<T>& tree){
        if(!(tree.isEmpty()))
            this->root = new TIMultiSetNode<T>(*(tree->root));
        else
            this->root = new TIMultiSetNode<T>();
        if(this->root == nullptr)
            throw MemoryException("operator =");
        return *this;
    }

    TIMultiSet<T>& operator=(TIMultiSet<T>&& tree){
        this->root = tree.root;
        tree.root = nullptr;
        return *this;
    }
    bool isEmpty()const{return this->root == nullptr || this->root->isNil();}
    unsigned int size()const{return this->isEmpty()?0:this->root->size();}
    bool contains(T value)const{return !this->isEmpty() && this->root->contains(value);}
    
    void insert(T value){
        if(this->isEmpty()){
            if(this->root!=nullptr)
                delete this->root;
            this->root = new TIMultiSetNode<T>(value);
            if(this->root == nullptr)
                throw MemoryException("insert");
            this->root->setColor(INDIGO);
        }else
            this->root = this->root->insert(value,this->root);
    }

    T remove(T value){
        if(this->isEmpty()){
            throw SetItemNotFoundException("remove");
        }else{
            std::pair<TIMultiSetNode<T>*,TIMultiSetNode<T>*> answer = this->root->remove(value,this->root);
            this->root = answer.first;
            auto result = answer.second->getValue();
            delete answer.second;
            return result;
        }
    }

    TISet<T> remove_all(T value){
        if(this->isEmpty()){
            throw SetItemNotFoundException("remove all");
        }else{
            std::pair<TIMultiSetNode<T>*,TISet<TIMultiSetNode<T>*>> answer = this->root->remove(value,this->root);
            this->root = answer.first;
            TISet<TIMultiSetNode<T>*> item_set = answer.second;
            if(item_set.isEmpty())
                throw SetItemNotFoundException("remove all");
            TISet<T> result = TISet<T>();
            for(auto it=item_set.cbegin();it!=item_set.cend();it++){
                TIMultiSetNode<T>* node = *it;
                result.insert(node->getValue());
                delete node;
            }
            return result;
        }
    }

    std::pair<bool,T> safeRemove(T value){
        if(this->contains(value))
            return std::pair<bool,T>(true,this->remove(value));
        return std::pair<bool,T>(false,T());
    }

    std::pair<bool,TISet<T>> safeRemoveAll(T value){
        if(this->contains(value))
            return std::pair<bool,TISet<T>>(true,this->remove_all(value));
        return std::pair<bool,TISet<T>>(false,TISet<T>());
    }

    T get(T key)const{
        if(this->isEmpty())
            throw SetItemNotFoundException("get");
        return this->root->getValue(key);
    }

    TIMultiSetIterConst<T> find(T key){
        if(this->isEmpty())
            return this->end();
        return this->root->find(key);
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

    TIMultiSetIterConst<T> cbegin()const{
        if(this->isEmpty())
            return TIMultiSetIterConst<T>();
        return this->root->cbegin();
    }

    TIMultiSetIterConst<T> cend()const{
        if(this->isEmpty())
            return TIMultiSetIterConst<T>();
        return this->root->cend();
    }

    TIMultiSetIterConstReverse<T> crbegin()const{
        if(this->isEmpty())
            return TIMultiSetIterConstReverse<T>();
        return this->root->crbegin();
    }

    TIMultiSetIterConstReverse<T> crend()const{
        if(this->isEmpty())
            return TIMultiSetIterConstReverse<T>();
        return this->root->crend();
    }

    T accumulate(T (*func)(const T&,const T&), T init_value)const{
        if(this->isEmpty())
            return init_value;
        return this->root->accumulate(func,init_value);
    }
    T accumulate(T (*func)(const T&,const T&))const{
        return this->accumulate(func,T());
    }
    TIMultiSet<T> map(T (*func)(T))const{
        if(this->isEmpty())
            return TIMultiSet<T>();
        return this->root->map(func);
    }
    void filter(bool (*func)(T)){
        if(this->isEmpty()){
            return;
        }
        this->root = this->root->filter(func,root);
    }
    void antifilter(bool (*func)(T)){
        if(this->isEmpty()){
            return;
        }
        this->root = this->root->antifilter(func,root);
    }

    friend std::ostream& operator<< <>(std::ostream& os,const TIMultiSet<T>& node);
};

template <typename T> std::ostream& operator<<(std::ostream& os,const TIMultiSet<T>& tree){
    if(tree.isEmpty())
        return os<<"Empty set\n";
    os<<*(tree.root)<<"\n";
    return os;
}
template <typename T> std::ostream& print_with_depth(std::ostream& os,const TIMultiSetNode<T>& node, unsigned int depth){
    if(node.isNil()){
        for(int i=0;i<depth;i++)
            os<<"\t";
        return os<<"Nil\n";
    }
    print_with_depth(os,*node.getLeft(),depth+1);
    for(int i=0;i<depth;i++)
        os<<"\t";
    os<<"V: "<<node.getValue();
    if(node.getColor()==TURQUIOISE)
        os<<" TURQUOISE\n";
    else
        os<<" INDIGO\n";
    print_with_depth(os,*node.getRight(),depth+1);
    return os;
}
template <typename T> std::ostream& operator<<(std::ostream& os,const TIMultiSetNode<T>& node){
    if(node.isNil())
        return os<<"Nil\n";
    return print_with_depth<T>(os,node,0);
}

#endif
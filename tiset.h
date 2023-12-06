#ifndef _TURQUOISE_INDIGO_SET_H__
#define _TURQUOISE_INDIGO_SET_H__

#include <string>
#include <exception>
#include <iostream>
#include <sstream>
#include <fstream>
#include <utility>
#include "tiexceptions.h"
#include "tiutil.h"


template <typename T> class TISetNode;
template <typename T> class TISet;

template <typename T> class TISetIterConst{
    TISetNode<T>* current;
    protected:
    friend TISet<T>;
    friend TISetNode<T>;
    TISetIterConst(){
        this->current=nullptr;
    }
    TISetIterConst(TISetNode<T>* current){
        this->current = current;
    }
    public:
    TISetIterConst<T>& operator++(){
        this->current = this->current->successor();
        return *this;
    }
    TISetIterConst<T>& operator++(int){
        this->current = this->current->successor();
        return *this;
    }
    TISetIterConst<T>& operator--(){
        this->current = this->current->predecessor();
        return *this;
    }
    TISetIterConst<T>& operator--(int){
        this->current = this->current->predecessor();
        return *this;
    }
    T operator*(){
        return this->current->getValue();
    }
    bool operator==(const TISetIterConst<T>& iter)const{
        return this->current == iter.current;
    }
    bool operator!=(const TISetIterConst<T>& iter)const{
        return this->current != iter.current;
    }
    TISetIterConst<T>& operator=(const TISetIterConst<T>& iter){
        this->current = iter.current;
        return *this;
    }
    TISetIterConst<T>& operator=(TISetIterConst<T>&& iter){
        this->current = iter.current;
        iter.current = nullptr;
        return *this;
    }
};

template <typename T> class TISetIterConstReverse{
    TISetNode<T>* current;
    protected:
    friend TISet<T>;
    friend TISetNode<T>;
    TISetIterConstReverse(){
        this->current=nullptr;
    }
    TISetIterConstReverse(TISetNode<T>* current){
        this->current = current;
    }
    public:
    TISetIterConstReverse<T>& operator++(){
        this->current = this->current->predecessor();
        return *this;
    }
    TISetIterConstReverse<T>& operator++(int){
        this->current = this->current->predecessor();
        return *this;
    }
    TISetIterConstReverse<T>& operator--(){
        this->current = this->current->successor();
        return *this;
    }
    TISetIterConstReverse<T>& operator--(int){
        this->current = this->current->successor();
        return *this;
    }
    T operator*(){
        return this->current->getValue();
    }
    bool operator==(const TISetIterConstReverse<T>& iter)const{
        return this->current == iter.current;
    }
    bool operator!=(const TISetIterConstReverse<T>& iter)const{
        return this->current != iter.current;
    }
    TISetIterConstReverse<T>& operator=(const TISetIterConstReverse<T>& iter){
        this->current = iter.current;
        return *this;
    }
    TISetIterConstReverse<T>& operator=(TISetIterConstReverse<T>&& iter){
        this->current = iter.current;
        iter.current = nullptr;
        return *this;
    }
};

template <typename T> std::ostream& operator<<(std::ostream& os,const TISet<T>& tree);
template <typename T> std::ostream& operator<<(std::ostream& os,const TISetNode<T>& tree);

template <typename T> class TISetNode{
    private:
    TIColor color;
    TISetNode<T>* left;
    TISetNode<T>* right;
    TISetNode<T>* parent;
    T value;
    bool nil;

    TISetNode<T>* getNode(T key){
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

    TISetNode<T>* removeFixup(TISetNode<T>* root){
        TISetNode<T>* x = this;
        while(x!=root && x->getColor()==INDIGO){
            if(x->isLeftChild()){
                TISetNode<T>* w = x->getSibling();
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
                TISetNode<T>* w = x->getSibling();
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
    TISetNode<T>* leftRotate(TISetNode<T>* root){
        if(!this->hasRight()){return root;}
        // temp is never nil
        TISetNode<T>* temp = this->getRight();
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
    TISetNode<T>* rightRotate(TISetNode<T>* root){
        if(!this->hasLeft()){return root;}
        // temp is never nil
        TISetNode<T>* temp = this->getLeft();
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
    TISetNode<T>* tree_insert(T value){
        if(this->getValue() == value)
            throw ValueAlreadyPresentException("insertion");
        if(value > this->getValue()){
            if(this->hasRight())
                return this->getRight()->tree_insert(value);
            delete this->getRight();
            auto new_node = new TISetNode<T>(value,TURQUIOISE,this);
            if(new_node==nullptr)
                throw MemoryException("insertion");
            this->setRight(new_node);
            return this->getRight();
        }
        if(this->hasLeft())
            return this->getLeft()->tree_insert(value);
        delete this->getLeft();
        auto new_node = new TISetNode<T>(value,TURQUIOISE,this);
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

    std::string dotedge(TISetNode<T>* dest)const{
        return this->dotname()+" -> "+dest->dotname();
    }

    protected:
    friend TISet<T>;
    friend TISetIterConst<T>;
    friend TISetIterConstReverse<T>;
    TISetNode(){
        this->value = T();
        this->color = INDIGO;
        this->left = nullptr;
        this->right = nullptr;
        this->parent = nullptr;
        this->nil = true;
    }
    TISetNode(TISetNode<T>* parent){
        this->value = T();
        this->color = INDIGO;
        this->left = nullptr;
        this->right = nullptr;
        this->parent = parent;
        this->nil = true;
    }
    TISetNode(T value){
        this->value = value;
        this->color = TURQUIOISE;
        this->left = new TISetNode<T>(this);
        this->right = new TISetNode<T>(this);
        this->parent = nullptr;
        this->nil = false;
        if(this->left==nullptr || this->right == nullptr)
            throw MemoryException("constructor");
    }
    TISetNode(T value,TIColor node_color){
        this->value = value;
        this->color = node_color;
        this->left = new TISetNode<T>(this);
        this->right = new TISetNode<T>(this);
        this->parent = nullptr;
        this->nil = false;
        if(this->left==nullptr || this->right == nullptr)
            throw MemoryException("constructor");
    }
    TISetNode(T value,TISetNode<T>* parent){
        this->value = value;
        this->color = TURQUIOISE;
        this->left = new TISetNode<T>(this);
        this->right = new TISetNode<T>(this);
        this->parent = parent;
        this->nil = false;
        if(this->left==nullptr || this->right == nullptr)
            throw MemoryException("constructor");
    }
    TISetNode(T value,TIColor node_color,TISetNode<T>* parent){
        this->value = value;
        this->color = node_color;
        this->left = new TISetNode<T>(this);
        this->right = new TISetNode<T>(this);
        this->parent = parent;
        this->nil = false;
        if(this->left==nullptr || this->right == nullptr)
            throw MemoryException("constructor");
    }
    TISetNode(const TISetNode<T>& node){
        this->color = node.color;
        if(node.left == nullptr)
            this->left = nullptr;
        else{
            this->left = new TISetNode<T>(*(node.left),this);
            if(this->left == nullptr)
                throw MemoryException("constructor");
        }
        if(node.right == nullptr)
            this->right = nullptr;
        else{
            this->right = new TISetNode<T>(*(node.right),this);
            if(this->right == nullptr)
                throw MemoryException("constructor");
        }
        this->parent = nullptr;
        this->value = node.value;
        this->nil = node.nil;
    }
    TISetNode(const TISetNode<T>& node,TISetNode<T>* parent){
        this->color = node.color;
        if(node.left == nullptr)
            this->left = nullptr;
        else{
            this->left = new TISetNode<T>(*(node.left),this);
            if(this->left == nullptr)
                throw MemoryException("constructor");
        }
        if(node.right == nullptr)
            this->right = nullptr;
        else{
            this->right = new TISetNode<T>(*(node.right),this);
            if(this->right == nullptr)
                throw MemoryException("constructor");
        }
        this->parent = parent;
        this->value = node.value;
        this->nil = node.nil;
    }
    TISetNode(TISetNode<T>&& node){
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
    ~TISetNode(){
        if(this->left != nullptr)
            delete this->left;
        if(this->right != nullptr)
            delete this->right;
    }
    TISetNode<T>& operator=(const TISetNode<T>& node){
        this->color = node.color;
        this->left = node.left;
        this->right = node.right;
        this->parent = nullptr;
        this->value = node.value;
        this->nil = node.nil;
        return *this;
    }
    TISetNode<T>& operator=(TISetNode<T>&& node){
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
    void setLeft(TISetNode<T>* node){this->left = node;}
    void setRight(TISetNode<T>* node){this->right = node;}
    void setParent(TISetNode<T>* node){this->parent = node;}
    void setValue(T value){this->value = value;}
    bool isNil()const{return this->nil;}
    TIColor getColor()const{return this->color;}
    TISetNode<T>* getLeft()const{return this->left;}
    TISetNode<T>* getRight()const{return this->right;}
    TISetNode<T>* getParent()const{return this->parent;}
    TISetNode<T>* getSibling()const{
        if(this->getParent()==nullptr)
            return nullptr;
        if(this->isLeftChild())
            return this->getParent()->getRight();
        return this->getParent()->getLeft();
    }
    TISetNode<T>* getGrandparent()const{
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
    T getValue()const{return this->value;}
    TISetIterConst<T> find(T key){
        if(this->isNil())
            return this->cend();
        if(key == this->item->getKey())
            return TISetIterConst<T>(this);
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
    TISetNode<T>* insert(T value,TISetNode<T>* root){
        TISetNode<T>* node = this->tree_insert(value);
        while(node!=root && node->getParent()->getColor()==TURQUIOISE){
            // father is never nullptr
            TISetNode<T>* father = node->getParent();
            TISetNode<T>* grandfather = father->getParent();
            TISetNode<T>* uncle = father->getSibling();
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
    TISetNode<T>* min()const{
        if(this->hasLeft())
            return this->getLeft()->min();
        TISetNode<T>* res = const_cast<TISetNode<T>*>(this);
        return res;
    }
    TISetNode<T>* max()const{
        if(this->hasRight())
            return this->getRight()->max();
        TISetNode<T>* res = const_cast<TISetNode<T>*>(this);
        return res;
    }
    TISetNode<T>* successor(){
        if(this->hasRight())
            return this->getRight()->min();
        if(this->isLeftChild())
            return this->getParent();
        if(this->isRightChild()){
            TISetNode<T>* parent = this->getParent();
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
    TISetNode<T>* predecessor(){
        if(this->hasLeft())
            return this->getLeft()->max();
        if(this->isRightChild())
            return this->getParent();
        if(this->isLeftChild()){
            TISetNode<T>* parent = this->getParent();
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

    std::pair<TISetNode<T>*,TISetNode<T>*> remove(T value,TISetNode<T>* root){
        TISetNode<T>* node_to_remove = this->getNode(value);
        if(node_to_remove==nullptr)
            throw SetItemNotFoundException("remove");
        TISetNode<T>* y = node_to_remove;
        TISetNode<T>* x = node_to_remove;
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
        return std::pair<TISetNode<T>*,TISetNode<T>*>(root,y);
    }

    std::string dot()const{
        std::string res ="digraph G{\n";
        this->dotnames(res);
        this->dotedges(res);
        return res+"}";
    }

    TISetIterConst<T> cbegin()const{return TISetIterConst<T>(this->min());}
    TISetIterConst<T> cend()const{return TISetIterConst<T>();}
    TISetIterConstReverse<T> crbegin()const{return TISetIterConstReverse<T>(this->max());}
    TISetIterConstReverse<T> crend()const{return TISetIterConstReverse<T>();}
    T accumulate(T (*func)(const T&,const T&), T init_value)const{
        for(auto iter=this->cbegin(); iter != this->cend(); iter++){
            init_value = func(init_value,*iter);
        } 
        return init_value;
    }
    TISet<T> map(T (*func)(T))const{
        TISet<T> res(*this);
        for(auto iter=this->cbegin(); iter != this->cend(); iter++){
            res.insert(func((*iter)));
        } 
        return res;
    }
    TISetNode<T>* filter(bool (*func)(T), TISetNode<T>* root){
        TISet<T> removed = TISet<T>();
        for(auto it=this->cbegin();it!=this->cend();it++){
            if(func(*it)){
                removed.insert(*it);
            }
        }
        for(auto it=removed.cbegin();it!=removed.cend();it++){
            root = (root->remove(*it,root)).first;
        }
        return root;
    }

    TISetNode<T>* antifilter(bool (*func)(T), TISetNode<T>* root){
        TISet<T> removed = TISet<T>();
        for(auto it=this->cbegin();it!=this->cend();it++){
            if(!func(*it)){
                removed.insert(*it);
            }
        }
        for(auto it=removed.cbegin();it!=removed.cend();it++){
            root = (root->remove(*it,root)).first;
        }
        return root;
    }
    friend std::ostream& operator<< <>(std::ostream& os,const TISetNode<T>& node);
};

template <typename T> class TISet{
    private:
    TISetNode<T>* root;

    public:
    TISet(){
        this->root = new TISetNode<T>();
        if(this->root == nullptr)
            throw MemoryException("constructor");
    }

    TISet(const TISet<T>& tree){
        if(!tree.isEmpty())
            this->root = new TISetNode<T>(*(tree.root));
        else
            this->root = new TISetNode<T>();
        if(this->root == nullptr)
            throw MemoryException("constructor");
    }

    TISet(TISet<T>&& tree){
        this->root = tree.root;
        tree.root = nullptr;
    }

    ~TISet(){
        if(this->root != nullptr)
            delete this->root;
    }

    TISet<T>& operator=(const TISet<T>& tree){
        if(!(tree.isEmpty()))
            this->root = new TISetNode<T>(*(tree->root));
        else
            this->root = new TISetNode<T>();
        if(this->root == nullptr)
            throw MemoryException("operator =");
        return *this;
    }

    TISet<T>& operator=(TISet<T>&& tree){
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
            this->root = new TISetNode<T>(value);
            if(this->root == nullptr)
                throw MemoryException("insert");
            this->root->setColor(INDIGO);
        }else
            this->root = this->root->insert(value,this->root);
    }

    void safeInsert(T value){
        if(!this->contains(value))
            this->insert(value);
    }

    T remove(T value){
        if(this->isEmpty()){
            throw SetItemNotFoundException("remove");
        }else{
            std::pair<TISetNode<T>*,TISetNode<T>*> answer = this->root->remove(value,this->root);
            this->root = answer.first;
            auto result = answer.second->getValue();
            delete answer.second;
            return result;
        }
    }

    std::pair<bool,T> safeRemove(T value){
        if(this->contains(value))
            return std::pair<bool,T>(true,this->remove(value));
        return std::pair<bool,T>(false,T());
    }

    T get(T key)const{
        if(this->isEmpty())
            throw SetItemNotFoundException("get");
        return this->root->getValue(key);
    }

    TISetIterConst<T> find(T key){
        if(this->isEmpty())
            return this->cend();
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

    TISetIterConst<T> cbegin()const{
        if(this->isEmpty())
            return TISetIterConst<T>();
        return this->root->cbegin();
    }

    TISetIterConst<T> cend()const{
        if(this->isEmpty())
            return TISetIterConst<T>();
        return this->root->cend();
    }

    TISetIterConstReverse<T> crbegin()const{
        if(this->isEmpty())
            return TISetIterConstReverse<T>();
        return this->root->crbegin();
    }

    TISetIterConstReverse<T> crend()const{
        if(this->isEmpty())
            return TISetIterConstReverse<T>();
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
    TISet<T> map(T (*func)(T))const{
        if(this->isEmpty())
            return TISet<T>();
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

    friend std::ostream& operator<< <>(std::ostream& os,const TISet<T>& node);
};

template <typename T> std::ostream& operator<<(std::ostream& os,const TISet<T>& tree){
    if(tree.isEmpty())
        return os<<"Empty set\n";
    os<<*(tree.root)<<"\n";
    return os;
}
template <typename T> std::ostream& print_with_depth(std::ostream& os,const TISetNode<T>& node, unsigned int depth){
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
template <typename T> std::ostream& operator<<(std::ostream& os,const TISetNode<T>& node){
    if(node.isNil())
        return os<<"Nil\n";
    return print_with_depth<T>(os,node,0);
}

#endif
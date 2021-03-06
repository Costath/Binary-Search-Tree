//C�digo Livro "ED e Alg. em C++ - Adam Drozdek" - 
//comentado por Irineu

//************************  genBST.h  **************************
//                 generic binary search tree
#include <queue>
#include <stack>
#include <vector>
#include <iostream>
#include <locale.h>
using namespace std;

vector<int> vet;

#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE
/*Observe que ser�o definidas "fun��es template" (via template<class >) que poder�o usar tipos gen�ricos,
 ou seja, permitir�o aplicar m�todos para qualquer tipo de dado(s) passado(s) como par�metro(s)...
 Leia mais: http://www.cplusplus.com/doc/oldtutorial/templates/ 
*/
template<class T> //T - s�mbolo aqui associado a qq tipo gen�rico 
class Stack : public stack <T> {//Implementa a fun��o pop de uma pilha para o tipo gen�rico T
public:
    T pop() {
        T tmp = stack<T>::top();
        stack<T>::pop();
        return tmp;
    }
};

template<class T>
class Queue : public queue<T> {//Implementa a fun��o dequeue de uma fila para o tipo gen�rico T
public:
    T dequeue() {
        T tmp = queue<T>::front();
        queue<T>::pop();
        return tmp;
    }
    void enqueue(const T& el) {//Implementa a fun��o enqueue de uma fila para o tipo gen�rico T 
        push(el);
    }
};

template<class T> class BST;//Declara uma classe de manipula��o de �rvore bin�ria
							// para tipo gen�rico. Observe que ainda n�o possui atributos ou m�todos - a ser feito mais abaixo...

template<class T>
class BSTNode {//Classe gen�rica que define o n�-dado para a �rvore
public:
	//Construtor: caso sem passagem de par�metros
    BSTNode() { 
        left = right = 0; 
    }
    //Construtor: caso com passagem de par�metros
    BSTNode(const T& e, BSTNode<T> *l = 0, BSTNode<T> *r = 0) {
        el = e; //dado gen�rico a ser guardado no n�
		left = l; //ponteiro que encadeia filho � esquerda, podendo ser NULL caso n�o seja passado
		right = r;//ponteiro que encadeia filho � direita, podendo ser NULL caso n�o seja passado 
    }
    //Atributos p�blicos do n�-dado
    T el;
    BSTNode<T> *left, *right;
};

template<class T>
class BST { //Aqui temos a implementa��o de m�todos e atributos da classe que definir� a �rvore bin�ria
public:
    BST() { //construtor
        root = 0; //root � o atributo de controle da ED, ponteiro de in�cio, inicia em NULL
    }
    ~BST() { //destrutor
        clear();
    }
    void clear() {//chamada para desalocar tudo que tiver sendo apontado pelo root...
        clear(root);//sobrecarga de m�todo mais abaixo, que aceitar� par�metro (ponteiro) para ir desalocando todos os n�s... 
        root = 0; //ap�s anterior, atribui NULL ao controle root
    }
    bool isEmpty() const { //teste se �rvore � vazia?
        return root == 0; 
    }
/*    void preorder() { //varre �rvore em pr�-ordem
        preorder(root); //sobrecarga de m�todo mais abaixo   
    }*/
/*    int inorder_count(){
    	inorder_count(root, int);
	}*/
    void inorder() { //varre �rvore em in-ordem ("em ordem")
        inorder(root); //sobrecarga de m�todo mais abaixo 
    }
/*    void postorder() { //varre �rvore em p�s-ordem
        postorder(root); //sobrecarga de m�todo mais abaixo   
    }*/
    void insert(const T&);
    void recursiveInsert(const T& el) { 
        recursiveInsert(root,el);
    }
    T* recursiveSearch(const T& el) const {
        return recursiveSearch(root,el);
    }
    void deleteByCopying(BSTNode<T>*&);
    void findAndDeleteByCopying(const T&);
    void deleteByMerging(BSTNode<T>*&);
    void findAndDeleteByMerging(const T&);
    void balance(){
    	int tamanho = vet.size();
    	/*int *inseridos;
    	*inseridos = 0;*/
    	
    	if(tamanho>1){
    		balance(vet, vet.front(), vet.back()/*, inseridos*/);
		}else{
			insert(vet[0]);
		}
	}
    void balance(vector<int>,int,int/*, int**/);
    void displayTree();
    void showEl(){
    	for(int i=0;i<vet.size();i++)
    		cout<<vet[i]<<" ";
	}
protected:
    BSTNode<T>* root;
    void clear(BSTNode<T>*);
    void recursiveInsert(BSTNode<T>*&, const T&);
    T* search(BSTNode<T>*, const T&) const;
    T* recursiveSearch(BSTNode<T>*, const T&) const;
//    void preorder(BSTNode<T>*);
	int inorder_count(BSTNode<T>*, int*);
    void inorder(BSTNode<T>*);
//    void postorder(BSTNode<T>*);
    virtual void count(BSTNode<T>* p, int* qtd) {		//visita apenas para contar
		*qtd++;
    }
    virtual void visit(BSTNode<T>* p) {		//visita para copiar os valores da �rvore em um vetor
		vet.push_back(p->el);
    }
};

template<class T>
void BST<T>::clear(BSTNode<T> *p) {//Observer chamada recursiva para dele��o de n�s terminais (folhas) para raiz 
    if (p != 0) {
         clear(p->left); //recurs�o para n� � esquerda
         clear(p->right); //recurs�o para n� � direita
         delete p; //desaloca objeto n�-dado
     }
}

template<class T>
void BST<T>::insert(const T& el) {   
    BSTNode<T> *p = root, *prev = 0;
    while (p != 0) {  // find a place for inserting new node;
        prev = p;
        if (el < p->el)
             p = p->left;
        else p = p->right;
    }
    if (root == 0)    // tree is empty; //ou poderia ser testado "prev"
         root = new BSTNode<T>(el);
    else if (el < prev->el)
         prev->left  = new BSTNode<T>(el);
    else prev->right = new BSTNode<T>(el);
}

template<class T>
void BST<T>::recursiveInsert(BSTNode<T>*& p, const T& el) {//inser��o feita com recursividade
    if (p == 0)
         p = new BSTNode<T>(el);
    else if (el < p->el)
         recursiveInsert(p->left, el);
    else recursiveInsert(p->right,el);
}

template<class T>
T* BST<T>::recursiveSearch(BSTNode<T>* p, const T& el) const {//uso de recursividade
    if (p != 0)
         if (el == p->el)
              return &p->el;
         else if (el < p->el)
              return recursiveSearch(p->left,el);
         else return recursiveSearch(p->right,el);
    else return 0;
}

template<class T>
int BST<T>::inorder_count(BSTNode<T> *p, int *qtd) {
	 
     if (p != 0) {
         inorder_count(p->left, qtd);
         count(p, qtd);
         inorder_count(p->right, qtd);
     }
     
     return qtd;
}

template<class T>
void BST<T>::inorder(BSTNode<T> *p) {
	 
     if (p != 0) {
         inorder(p->left);
         visit(p);
         inorder(p->right);
     }
}

/*template<class T>
void BST<T>::preorder(BSTNode<T> *p) {
    if (p != 0) {
        visit(p);
        preorder(p->left);
        preorder(p->right);
    }
}

template<class T>
void BST<T>::postorder(BSTNode<T>* p) {
    if (p != 0) {
        postorder(p->left);
        postorder(p->right);
        visit(p);
    }
}*/

template<class T>
void BST<T>::deleteByCopying(BSTNode<T>*& node) {    
    BSTNode<T> *previous, *tmp = node;
     if (node->right == 0)                  // node has no right child;
          node = node->left;
     else if (node->left == 0)              // node has no left child;
          node = node->right; 
     else {
          tmp = node->left;                  // node has both children;
          previous = node;                  // 1.
          while (tmp->right != 0) {         // 2.
              previous = tmp;
              tmp = tmp->right;
          }
          node->el = tmp->el;               // 3.
          if (previous == node)
               previous->left  = tmp->left;
          else previous->right = tmp->left; // 4.
     }
     delete tmp;                            // 5.
}

// findAndDeleteByCopying() searches the tree to locate the node containing
// el. If the node is located, the function DeleteByCopying() is called.

template<class T>
void BST<T>::findAndDeleteByCopying(const T& el) {    
    BSTNode<T> *p = root, *prev = 0;
     while (p != 0 && !(p->el == el)) {
         prev = p;
         if (el < p->el)
              p = p->left;
         else p = p->right;
     }
     if (p != 0 && p->el == el)
          if (p == root)
               deleteByCopying(root);
          else if (prev->left == p)
               deleteByCopying(prev->left);
          else deleteByCopying(prev->right);
     else if (root != 0){
     		cout << "el " << el << " is not in the tree\n";
         	system("pause");
	 }else cout << "the tree is empty\n";
}

template<class T>
void BST<T>::deleteByMerging(BSTNode<T>*& node) {   
    BSTNode<T> *tmp = node;
    if (node != 0) {
        if (!node->right)           // node has no right child: its left
             node = node->left;     // child (if any) is attached to its parent;
        else if (node->left == 0)   // node has no left child: its right
             node = node->right;    // child is attached to its parent;
        else {                      // be ready for merging subtrees;
             tmp = node->left;      // 1. move left
             while (tmp->right != 0)// 2. and then right as far as possible;
                tmp = tmp->right;
             tmp->right =           // 3. establish the link between the
                node->right;        //    the rightmost node of the left
                                    //    subtree and the right subtree;
             tmp = node;            // 4.
             node = node->left;     // 5.
        }
        delete tmp;                 // 6.
     }
}

template<class T>
void BST<T>::findAndDeleteByMerging(const T& el) {    
    BSTNode<T> *node = root, *prev = 0;
    while (node != 0) {
        if (node->el == el)
             break;
        prev = node;
        if (el < node->el)
             node = node->left;
        else node = node->right;
    }
    if (node != 0 && node->el == el)
         if (node == root)
              deleteByMerging(root);
         else if (prev->left == node)
              deleteByMerging(prev->left);
         else deleteByMerging(prev->right);
    else if (root != 0){
    	 cout << "el " << el << " is not in the tree\n";
         system("pause");
	}else cout << "the tree is empty\n";
}

/*template<class T>
void BST<T>::balance(vector<int> vet, int first, int last, int* inseridos) {
	if (first <= last && *inseridos<vet.size()) {
		//for(int i=0; i<)
        int middle = (first+last)/2;
        if(first==last){
        	insert(vet[middle-1]);
        	++*inseridos;
        	balance(vet, vet[0], vet[middle-1]-1, inseridos);
		}else{
        	insert(vet[middle]);
        	++*inseridos;
			balance(vet, vet[0], vet[middle-1], inseridos);
        }
        balance(vet, vet[middle+1], vet[vet.size()-1], inseridos);
    }
    if(*inseridos==vet.size()){
    	vet.clear();
    	return;
	}
}
*/

template<class T>
void BST<T>::balance (vector<int> vet, int first, int last) {
    if (first <= last) {
        int middle = (first + last)/2;
        insert(vet[middle]);
        balance(vet,first,vet[middle-1]);
        balance(vet,vet[middle+1],last);
    }
}

template<class T>
void BST<T>::displayTree(){
    Stack<BSTNode<T>*> pilhaGlobal;
    pilhaGlobal.push(root);
    int nEspacos = 32;
    bool isLinhaVazia = false;
    cout << "......................................................\n";
    
    while(isLinhaVazia==false){
        Stack<BSTNode<T>*> pilhaLocal;
        isLinhaVazia = true;
        for (int i=0; i<nEspacos; i++)
            cout << " ";
        while(pilhaGlobal.empty()==false){
            BSTNode<T> *tmp = pilhaGlobal.pop();
            if(tmp!=0){
                cout << tmp->el;
                pilhaLocal.push(tmp->left);
                pilhaLocal.push(tmp->right);
                if (tmp->left != 0 || tmp->right != 0)
                    isLinhaVazia = false;
            } else {
                cout << "--";
                pilhaLocal.push(0); //coloca NULL na pilhaLocal
                pilhaLocal.push(0); //coloca NULL na pilhaLocal
            }
            for(int j=0; j<nEspacos*2-2; j++){
                cout << " ";
            }
        }
        cout << endl;
        nEspacos /= 2;
        while(pilhaLocal.empty()==false){
            pilhaGlobal.push(pilhaLocal.pop());
        }
    }
    cout << "......................................................\n\n";
}

#endif

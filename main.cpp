#include "lib.hpp"

int main() {
	setlocale(LC_ALL, "");
	BST <int> arv;
	int menu, elemento, qtd;
	
	vector<int> vet;
	
	while(true){	
		cout<<"===Binary Search Tree==="<<endl<<endl;
		cout<<"1 - Inserir elemento"<<endl;
		cout<<"2 - DeleteByCopying"<<endl;
		cout<<"3 - DeleteByMerging"<<endl;
		cout<<"4 - DisplayTree"<<endl;
		cout<<"5 - Balance"<<endl;
		cout<<"6 - Sair"<<endl<<endl;
		
		cin>>menu;
		
		switch(menu){
			case(1):
				cout<<"\nElemento a ser inserido na árvore:";
				cin>>elemento;
				arv.insert(elemento);
				
				system("cls");
			break;
			case(2):
				if(!arv.isEmpty()){
					cout<<"\nElemento a ser removido by copying:";
					cin>>elemento;
					arv.findAndDeleteByCopying(elemento);
				}else{
					cout<<"A árvore está vazia.\n\n";
					system("pause");
				}
				
				system("cls");
			break;
			case(3):
				if(!arv.isEmpty()){
					cout<<"\nElemento a ser removido by merging:";
					cin>>elemento;
					arv.findAndDeleteByMerging(elemento);
				}else{
					cout<<"A árvore está vazia.\n\n";
					system("pause");
				}
				
				system("cls");
			break;
			case(4):
				arv.displayTree();
				
				system("pause");
				system("cls");
			break;
			case(5):
				if(!arv.isEmpty()){
					arv.inorder();
					arv.~BST();
					arv.balance();
				}else{
					cout<<"A árvove está vazia.\n";
					system("pause");
				}
				system("cls");
			break;
			case(6):
				arv.clear();
				
				cout<<"\nObrigado!";
				
				return 0;
			break;
			default:
				cout<<"Opção inválida. Tente novamente.";
				system("pause");
				system("cls");
			break;
		}
	}
}

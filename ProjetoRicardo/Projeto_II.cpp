#include <iostream>

using namespace std;

struct conta {
	string nome;
	string email;
	string numero_inscricao;
	conta* ant;
	conta* prox;

};

struct desc {
	conta* ini;
	conta* fim;
	int tam;
};

struct atv {
	string titulo;
	string tipo;
	string date;
	atv* prox;
	atv* ant;
};


//Função auxiliar que reserva/preenche os espaços de memoria que serão usados para as informações de cada usuário. 
conta *criar_conta(string nome, string email, string insc) {
	conta* novo = new conta;
	novo->nome = nome;
	novo->email = email;
	novo->numero_inscricao = insc;
	novo->ant = NULL;
	novo->prox = NULL;

	return novo;
}

//Função auxiliar que reserva o espaço de memoria do descritor.
desc* criar_desc() {
	desc* novo = new desc;
	novo->ini = NULL;
	novo->fim = NULL;
	novo->tam = 0;
	return novo;

}

//Função auxiliar que adiciona um novo usuário no final da lista.
void *adicionar(desc*& lista, string nome, string email, string insc) {
	conta* novo = criar_conta(nome, email, insc);
	if (lista == NULL) {
		lista->ini = novo;
		lista->fim = novo;
	}
	else {
		lista->fim->prox = novo;
		novo->ant = lista->fim;
		lista->fim = novo;
	}
	lista->tam++;

}

//Função de coleta de dados que utiliza todas as outras funções auxiliares anteriores
void preencher_conta(desc*& lista) {
	string nome = " ";
	string email;
	string insc;
	while (nome != "x") {
		cout << "Insira seu nome: (Insira 'x' para finalizar)\n";
		cin >> nome;
		cout << "Insira seu email:\n";
		cin >> email;
		cout << "Insira seu numero de inscrição:\n";
		cin >> insc;
		if (nome != "x")
			adicionar(lista, nome, email, insc);

	}

}
//OBS: MESCLAR ESSAS DUAS FUNÇÕES POSTERIORMENTE!!!
void preencher_atv(desc*& lista) {
	string titulo = " ";
	string tipo;
	string data;
	while (titulo != "x") {
		cout << "Insira o nome da atividade: (Insira 'x' para finalizar)\n";
		cin >> titulo;
		cout << "Insira o tipo:\n";
		cin >> tipo;
		cout << "Insira a data (XX/XX/XX-XX:XX):\n";
		cin >> data;
		if (titulo != "x")
			adicionar(lista, titulo, tipo, data);

	}

}





int main() {



}
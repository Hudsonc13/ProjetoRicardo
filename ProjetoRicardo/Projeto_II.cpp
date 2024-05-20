#include <iostream>

using namespace std;

struct conta {
	string nome;
	string email;
	string numero_inscricao;
	int presenca;
	conta* ant;
	conta* prox;

};

struct atv {
	string titulo;
	string tipo;
	string date;
	atv* prox;
};

struct desc_conta {
	conta* ini;
	conta* fim;
	int tam;
};

struct desc_atv {
	atv* ini;
	int tam;
};




//Função auxiliar que reserva/preenche os espaços de memoria que serão usados para as informações de cada usuário. 
conta* criar_conta(string nome, string email, string insc) {
	conta* novo = new conta;
	novo->nome = nome;
	novo->email = email;
	novo->numero_inscricao = insc;
	novo->presenca = NULL;
	novo->ant = NULL;
	novo->prox = NULL;

	return novo;
};

atv* criar_atv(string nome, string email, string insc) {
	atv* novo = new atv;
	novo->titulo = nome;
	novo->tipo = email;
	novo->date = insc;
	novo->prox = NULL;

	return novo;
}

//Função auxiliar que reserva o espaço de memoria do descritor.
desc_conta* criar_desc_conta() {
	desc_conta* novo = new desc_conta;
	novo->ini = NULL;
	novo->fim = NULL;
	novo->tam = 0;
	return novo;

}

desc_atv* criar_desc_atv() {
	desc_atv* novo = new desc_atv;
	novo->ini = NULL;
	novo->tam = 0;
	return novo;
}


//Função auxiliar que adiciona um novo usuário no final da lista.
void adicionar_conta(desc_conta*& lista, string nome, string email, string insc) {
	conta* novo = criar_conta(nome, email, insc);
	if (lista->tam == 0) {
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

void adicionar_atv(desc_atv*& lista, string titulo, string tipo, string date) {
	atv* novo = criar_atv(titulo, tipo, date);
	if (lista->tam == 0) {
		lista->ini = novo;
	}
	else {
		lista->ini->prox = novo;
		lista->ini = novo;
	}
	lista->tam++;

}

//Função de coleta de dados que utiliza todas as outras funções auxiliares anteriores
void preencher_conta(desc_conta*& lista) {
	string nome = " ";
	string email;
	string insc;
	cout << "Informações do usuário" << endl;
	while (nome != "x") {
		cout << "Insira seu nome: (Insira 'x' para finalizar)\n";
		cin >> nome;
		if (nome != "x") {
			cout << "Insira seu email:\n";
			cin >> email;
			cout << "Insira seu numero de inscrição:\n";
			cin >> insc;
			adicionar_conta(lista, nome, email, insc);
		}
		system("cls");

	}

}
//OBS: MESCLAR ESSAS DUAS FUNÇÕES POSTERIORMENTE!!!
void preencher_atv(desc_atv*& lista) {
	string titulo = " ";
	string tipo;
	string data;
	cout << "Liste as atividades do evento" << endl;
	while (titulo != "x") {
		cout << "Insira o nome da atividade: (Insira 'x' para finalizar)\n";
		cin >> titulo;
		if (titulo != "x") {
			cout << "Insira o tipo:\n";
			cin >> tipo;
			cout << "Insira a data (XX/XX/XX-XX:XX):\n"; //Adicionar date format???
			cin >> data;
			adicionar_atv(lista, titulo, tipo, data);
		}
		system("cls");
	}

}

//Criação de uma matriz dinamica para fazer a contagem da presença dos usuarios nas atividades
bool** criar_mat(desc_conta*& usuarios, desc_atv*& atv) {
	bool **mat = new bool *[usuarios->tam];
	for (int i = 0; i < usuarios->tam; i++)
			mat[i] = new bool[atv->tam];
	return mat;
}


//Marca a presença dos usuarios
void presenca(bool** mat, desc_conta *&usuarios, desc_atv *&atividade) {
	int pres;
	conta* aux = usuarios->ini;
	for (int i = 0; i < usuarios->tam; i++){
		cout << "Usuario: " << usuarios->ini->nome;
		for (int j = 0; j < atividade->tam; j++) {
			cout << "Atividade: " << atividade->ini->titulo <<"\n";
			cout << "1: Presente\n0: Ausente\n";
			cin >> pres;
			if (pres == 0)
				mat[i][j] = false;
			if (pres == 1)
				mat[i][j] = true;
			else {
				cout << "Valor inserido não condiz com o solicitado!!\n Tente novamente";
				i--;
				j--;
			}
			system("cls");
		}

	}

}


//Calcula a presença de cada usuario e retorna a porcentagem
void cal_presenca(bool** mat, desc_conta*& usuario, desc_atv*& atv) {
	conta* aux = usuario->ini;
	for (int i = 0; i < usuario->tam; i++) {
		int cont = 0;
		for (int j = 0; j < atv->tam; j++) {
			if (mat[i][j] == true)
				cont++;
		}
		usuario->ini->presenca = cont/atv->tam;
		aux = usuario->ini->prox;
		
	}
	
}

void imprimir(desc_conta*& user) {
	if (user == NULL) {
		cout << "Nenhum usuário encontrado!";

	}
	else {
		conta* aux = user->ini;
		while (aux != NULL) {
			cout << "Nome: " << aux->nome;
			cout << "Email: " << aux->email;
			cout << "Numero de inscrição: " << aux->numero_inscricao;
			cout << "Nivel de presença: " << aux->presenca;
			aux = aux->prox;
		}
	}

}




int main() {

	bool** matriz;
	desc_conta* usuarios = criar_desc_conta();
	desc_atv* atv = criar_desc_atv(); 

	preencher_atv(atv);
	preencher_conta(usuarios);

	matriz = criar_mat(usuarios, atv);
	presenca(matriz, usuarios, atv);
	cal_presenca(matriz, usuarios, atv);

	imprimir(usuarios);

}
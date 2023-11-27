#include <iostream>

using namespace std;

class Aluno {
public:
    int matricula;
    string nome;

    Aluno(int matricula, const string& nome) : matricula(matricula), nome(nome) {}
};

class No {
public:
    Aluno aluno;
    No* esquerda;
    No* direita;

    No(Aluno aluno) : aluno(aluno), esquerda(NULL), direita(NULL) {}
};

class ArvoreBinariaBusca {
private:
    No* raiz;

    No* inserirRec(No* no, Aluno aluno);
    No* removerRec(No* no, int matricula);
    No* encontrarMenorNo(No* no);
    No* buscarRec(No* no, int matricula);
    void imprimirRec(No* no);
    bool ehBSTRec(No* no, int& anterior);
    bool saoIguaisRec(No* no1, No* no2);

public:
    ArvoreBinariaBusca() : raiz(NULL) {}

    void inserir(Aluno aluno);
    void remover(int matricula);
    void buscar(int matricula);
    void imprimir();
    bool ehBST();

    bool saoIguais(ArvoreBinariaBusca outra);

    bool temMesmoConjunto(ArvoreBinariaBusca outra);
};

No* ArvoreBinariaBusca::inserirRec(No* no, Aluno aluno) {
    if (no == NULL) {
        return new No(aluno);
    }

    if (aluno.matricula < no->aluno.matricula) {
        no->esquerda = inserirRec(no->esquerda, aluno);
    } else if (aluno.matricula > no->aluno.matricula) {
        no->direita = inserirRec(no->direita, aluno);
    }

    return no;
}

void ArvoreBinariaBusca::inserir(Aluno aluno) {
    raiz = inserirRec(raiz, aluno);
}

No* ArvoreBinariaBusca::removerRec(No* no, int matricula) {
    if (no == NULL) {
        return no;
    }

    if (matricula < no->aluno.matricula) {
        no->esquerda = removerRec(no->esquerda, matricula);
    } else if (matricula > no->aluno.matricula) {
        no->direita = removerRec(no->direita, matricula);
    } else {
        if (no->esquerda == NULL) {
            No* temp = no->direita;
            delete no;
            return temp;
        } else if (no->direita == NULL) {
            No* temp = no->esquerda;
            delete no;
            return temp;
        }

        No* temp = encontrarMenorNo(no->direita);
        no->aluno = temp->aluno;
        no->direita = removerRec(no->direita, temp->aluno.matricula);
    }

    return no;
}

void ArvoreBinariaBusca::remover(int matricula) {
    raiz = removerRec(raiz, matricula);
}

No* ArvoreBinariaBusca::encontrarMenorNo(No* no) {
    No* atual = no;
    while (atual->esquerda != NULL) {
        atual = atual->esquerda;
    }
    return atual;
}

No* ArvoreBinariaBusca::buscarRec(No* no, int matricula) {
    if (no == NULL || no->aluno.matricula == matricula) {
        return no;
    }

    if (matricula < no->aluno.matricula) {
        return buscarRec(no->esquerda, matricula);
    }

    return buscarRec(no->direita, matricula);
}

void ArvoreBinariaBusca::buscar(int matricula) {
    No* resultado = buscarRec(raiz, matricula);
    if (resultado != NULL) {
        cout << "Aluno encontrado - Matrícula: " << resultado->aluno.matricula << ", Nome: " << resultado->aluno.nome << endl;
    } else {
        cout << "Aluno não encontrado." << endl;
    }
}

void ArvoreBinariaBusca::imprimirRec(No* no) {
    if (no != NULL) {
        imprimirRec(no->esquerda);
        cout << "Matrícula: " << no->aluno.matricula << ", Nome: " << no->aluno.nome << endl;
        imprimirRec(no->direita);
    }
}

void ArvoreBinariaBusca::imprimir() {
    imprimirRec(raiz);
}

bool ArvoreBinariaBusca::ehBSTRec(No* no, int& anterior) {
    if (no != NULL) {

        if (!ehBSTRec(no->esquerda, anterior)) {
            return false;
        }

        if (no->aluno.matricula <= anterior) {
            return false;
        }

        anterior = no->aluno.matricula;

        return ehBSTRec(no->direita, anterior);
    }

    return true;  
}

bool ArvoreBinariaBusca::ehBST() {
    int anterior = INT_MIN;  
    return ehBSTRec(raiz, anterior);
}

bool ArvoreBinariaBusca::saoIguaisRec(No* no1, No* no2) {

    if (no1 == NULL && no2 == NULL) {
        return true;
    }

    if (no1 == NULL || no2 == NULL) {
        return false;
    }

    if (no1->aluno.matricula != no2->aluno.matricula) {
        return false;
    }

    return saoIguaisRec(no1->esquerda, no2->esquerda) && saoIguaisRec(no1->direita, no2->direita);
}

bool ArvoreBinariaBusca::saoIguais(ArvoreBinariaBusca outra) {

    return saoIguaisRec(raiz, outra.raiz);
}

bool ArvoreBinariaBusca::temMesmoConjunto(ArvoreBinariaBusca outra) {

    return saoIguais(outra);
}

int main() {

    ArvoreBinariaBusca arvore1, arvore2;

    arvore1.inserir(Aluno(1, "Arione"));
    arvore1.inserir(Aluno(2, "Rivinha"));
    arvore1.inserir(Aluno(3, "Faeu"));
    arvore1.inserir(Aluno(4, "Marciano"));
    arvore1.inserir(Aluno(5, "Gustavo"));

    arvore2.inserir(Aluno(1, "Arione"));
    arvore2.inserir(Aluno(2, "Rivinha"));
    arvore2.inserir(Aluno(3, "Faeu"));
    arvore2.inserir(Aluno(4, "Marciano"));
    arvore2.inserir(Aluno(5, "Gustavo"));

    cout << "Arvore 1:" << endl;
    arvore1.imprimir();
    cout << endl;

    cout << "Arvore 2:" << endl;
    arvore2.imprimir();
    cout << endl;

    if (arvore1.temMesmoConjunto(arvore2)) {
        cout << "As arvores têm o mesmo conjunto de elementos." << endl;
    } else {
        cout << "As arvores não têm o mesmo conjunto de elementos." << endl;
    }
    
    cout << "Arvore Binária de Busca (in-order):" << endl;
    arvore1.imprimir();
    cout << endl;

    arvore1.buscar(2);
    arvore1.buscar(10);

    
    if (arvore1.ehBST()) {
        cout << "A arvore e uma BST." << endl;
    } else {
        cout << "A arvore não e uma BST." << endl;
    }

    
    arvore1.remover(2);
    cout << "Arvore apos a remocao (in-order):" << endl;
    
	cout << "Arvore 1:" << endl;
    arvore1.imprimir();
    cout << endl;
    
	cout << "Arvore 2:" << endl;
    arvore2.imprimir();
    cout << endl;
    
    if (arvore1.temMesmoConjunto(arvore2)) {
        cout << "As arvores têm o mesmo conjunto de elementos." << endl;
    } else {
        cout << "As arvores não têm o mesmo conjunto de elementos." << endl;
    }

    return 0;
}

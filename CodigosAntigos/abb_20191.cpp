#include <iostream>
using namespace std;
typedef int Dado;

class Noh {
friend class ABB;
public:
    Noh(Dado dado);
private:
    int ContarFolhas();
    Noh* esquerda;
    Noh* direita;
    Noh* pai;
    Dado valor;
};

Noh::Noh(Dado dado) {
    valor = dado;
    direita = NULL;
    esquerda = NULL;
    pai == NULL;
}

int Noh::ContarFolhas() {
    if (esquerda == NULL and direita == NULL) {
        return 1;
    }
    else {
        if (esquerda == NULL) {
            return direita->ContarFolhas();
        }
        else if (direita == NULL) {
            return esquerda->ContarFolhas();
        }
        else {
            return esquerda->ContarFolhas() + direita->ContarFolhas();
        }
    }
}

class ABB {
public:
    ABB();
    void Inserir(Dado _dado);
    void CalcularAltura();
    bool Buscar(Dado _dado);
    void Remover(Dado _dado);
    void ContarNohs();
    Noh* BuscarNoh(Dado _dado);
    void ImprimeEmOrdem();
    int ContarNohsFolhas();
private:
    void ContarNohsFolhasAux(Noh *_noh);
    void ContarNohsAux(Noh *_noh);
    void ImprimeEmOrdemAux(Noh *_noh);
    int CalcularAlturaAux(Noh *_noh);
    Noh* GetSucessor(Noh* _noh);
    void Transplanta(Noh* antigo, Noh* novo);
    Noh* sucessor;
    Noh* raiz;
    int altura;
    int nohs;
    int nohsFolhas;
};

ABB::ABB() {
    raiz = NULL;
    altura = 0;
    nohs = 0;
    nohsFolhas = 0;
}

void ABB::Inserir(Dado _dado) {
    Noh* novoNoh = new Noh(_dado);

    if (raiz == NULL) {
        raiz = novoNoh;
    } else {
        Noh* percorredor = raiz;
        bool inserido = false;

        while (!inserido) {
            if (_dado < percorredor->valor) {
                if (percorredor->esquerda == NULL) {
                    percorredor->esquerda = novoNoh;
                    novoNoh->pai = percorredor;
                    inserido = true;
                } 
                else {
                    percorredor = percorredor->esquerda;
                }
            }
            else {
                if (percorredor->direita == NULL) {
                    percorredor->direita = novoNoh;
                    novoNoh->pai = percorredor;
                    inserido = true;
                }
                else {
                    percorredor = percorredor->direita;
                }
            }
            
        }
    }

    CalcularAltura();
}

void ABB::CalcularAltura() {
    altura = CalcularAlturaAux(raiz);
}

int ABB::CalcularAlturaAux(Noh *_noh) {
    if (_noh == NULL) {
        return 0;
    }
    int esquerda = CalcularAlturaAux(_noh->esquerda);
    int direita = CalcularAlturaAux(_noh->direita);

    if (esquerda > direita) {
        return 1 + esquerda;
    } else {
        return 1 + direita;
    }
}

Noh* ABB::GetSucessor(Noh* _noh) {
    if (_noh->direita == NULL) {
        return NULL;
    } else {
        Noh* percorredor = _noh->direita;

        while (percorredor->esquerda != NULL) {
            percorredor = percorredor->esquerda;
        }
        return percorredor;
    }
}

bool ABB::Buscar(Dado _dado) {
    if (raiz == NULL) {
        return false;
    } else {
        Noh* percorredor = raiz;

        while (percorredor != NULL) {
            if (percorredor->valor == _dado) {
                return true;
            }
            else if (percorredor->valor < _dado) {
                percorredor = percorredor->esquerda;
            }
            else {
                percorredor = percorredor->direita;
            }
        }
        return false;
    }
}

Noh* ABB::BuscarNoh(Dado _dado) {
    Noh* iterador = raiz;
    while(iterador != NULL) { 
        if(iterador->valor == _dado) {
            return iterador;
        }
        else if(_dado > iterador->valor) { 
            iterador = iterador->direita;
        }
        else { 
            iterador = iterador->esquerda;
        }
    }
    return iterador; 
}

int ABB::ContarNohsFolhas() {
    if (raiz == NULL) {
        return 0;
    } else {
        return raiz->ContarFolhas();
    }
    
}

void ABB::ImprimeEmOrdem() {
    ImprimeEmOrdemAux(raiz);
    cout << endl << "A altura eh " << altura << endl;
    cout << "A quantidade de nohs folha eh " << ContarNohsFolhas() << endl;
}

void ABB::ImprimeEmOrdemAux(Noh* _noh) {
    if (_noh != NULL) {
        ImprimeEmOrdemAux(_noh->esquerda);
        cout << _noh->valor << " ";
        ImprimeEmOrdemAux(_noh->direita);
    }
}

int main () {
    ABB arvore;

    arvore.Inserir(50);
    arvore.Inserir(25);
    arvore.Inserir(75);
    arvore.Inserir(15);
    arvore.Inserir(35);
    arvore.Inserir(90);

    arvore.ImprimeEmOrdem();

    return 0;
}
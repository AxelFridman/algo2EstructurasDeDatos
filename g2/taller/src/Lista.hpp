#include "Lista.h"
#include <vector>

Lista::Lista() {
    longi = 0;
    punteroInicial = nullptr;
    punteroFinal = nullptr;
    // Completar
}

Lista::Lista(const Lista& l) : Lista() {
    //Inicializa una lista vacía y luego utiliza operator= para no duplicar el código de la copia de una lista.
    *this = l;
}

Lista::~Lista() {
    // Completar
    if(longitud()==0){
        //delete punteroInicial;
        //delete punteroFinal;
    }
    else{
            Nodo* ultimoNodo = punteroFinal;
            Nodo* anteriorAlUltimo = punteroFinal->punteroAtras;
            while(anteriorAlUltimo != nullptr){
                delete ultimoNodo;
                ultimoNodo = anteriorAlUltimo;
                anteriorAlUltimo = ultimoNodo->punteroAtras;
            }
            delete punteroInicial;
    }
}




Lista& Lista::operator=(const Lista& aCopiar) {
    // Completar
    int longit = longitud();
    for(int i = 0; i < longit; i++){
        this->eliminar(0);
    }
    for(int i = 0; i < aCopiar.longitud(); i++){
        this->agregarAtras(aCopiar.iesimo(i));
    }
    return *this;
}

void Lista::agregarAdelante(const int& elem) {
    // Completar
    Nodo* nuevo = new Nodo;
    nuevo->dato=elem;
    nuevo->punteroAdelante= punteroInicial;
    if(longi>0){
        punteroInicial->punteroAtras = nuevo;
    }
    else{
        punteroFinal = nuevo;
    }
    longi++;
    punteroInicial = nuevo;
}

void Lista::agregarAtras(const int& elem) {
    Nodo* nuevo = new Nodo;
    nuevo->dato=elem;
    nuevo->punteroAtras= punteroFinal;
    if(longi>0){
        punteroFinal->punteroAdelante = nuevo;
    }
    else{
        punteroInicial = nuevo;
    }
    longi++;
    punteroFinal = nuevo;
}

void Lista::eliminar(Nat i) {
    // Completar
    int j = i;
    Nodo* actual = punteroInicial;
    if(j == 0){
        if(longitud() != 1){
            Nodo* Segundo = punteroInicial->punteroAdelante;
            Segundo->punteroAtras = nullptr;
            delete punteroInicial;
            punteroInicial = Segundo;
        }
        else{
            delete punteroInicial;
        }


    } else {
        if (j == longitud()-1) {
            Nodo *anteUltimo = punteroFinal->punteroAtras;
            anteUltimo->punteroAdelante = nullptr;
            delete punteroFinal;
            punteroFinal = anteUltimo;
        } else {
            while(j>=0) {
                if (j == 0) {
                    Nodo* siguiente = actual->punteroAdelante;
                    Nodo* previo = actual->punteroAtras;
                    siguiente->punteroAtras = previo;
                    previo->punteroAdelante = siguiente;
                    delete actual;
                }
                else {
                    actual = actual->punteroAdelante;
                }
                j--;
            }
        }
    }
    longi= longi - 1;
}

int Lista::longitud() const {
    // Completar
    return longi;
}

const int& Lista::iesimo(Nat i) const {
    // Completar
    int cont = 0;
    Nodo* actual = punteroInicial;
    while(cont<i) {
        actual = actual->punteroAdelante;
        cont++;
    }
    return actual->dato;
}

int& Lista::iesimo(Nat i) {
    int cont = 0;
    Nodo* actual = punteroInicial;
    while(cont<i) {
        actual = actual->punteroAdelante;
        cont++;
    }
    return actual->dato;
}

void Lista::mostrar(ostream& o) {
    // Completar
}

/*
 * Lista nueva;
    nueva.longi = aCopiar.longi;
    if(aCopiar.longitud()==0){
        nueva.punteroInicial = nullptr;
        nueva.punteroFinal = nullptr;
    }
    if(aCopiar.longitud()>=1){
        nueva.longi = aCopiar.longi;
        int totalIteraciones = aCopiar.longi-1;
        Nodo* actualAcopiar = aCopiar.punteroInicial->punteroAdelante;
        Nodo* actualNodoNueva = new Nodo;
        nueva.punteroInicial =actualNodoNueva;

        nueva.punteroInicial->dato = aCopiar.punteroInicial->dato;
        while(totalIteraciones>0){
            Nodo* nuevoNodoNueva = new Nodo;
            actualNodoNueva->punteroAdelante=nuevoNodoNueva;
            nuevoNodoNueva->punteroAtras=actualNodoNueva;
            nuevoNodoNueva->dato= actualAcopiar->dato;
            actualAcopiar = actualAcopiar->punteroAdelante;
            actualNodoNueva = nuevoNodoNueva;

            nueva.longi = aCopiar.longi;
            nueva.punteroFinal =actualNodoNueva;
            totalIteraciones--;
        }
    }
    if(longi>0) {
        nueva.punteroFinal->punteroAdelante = nullptr;
        nueva.punteroInicial->punteroAtras = nullptr;
    }
    int asd = nueva.longi;
    return nueva;
 */
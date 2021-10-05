
template <class T>
Conjunto<T>::Conjunto() {
    _raiz = nullptr;
    cantidadNodos = 0;
}
template <class T>
void Conjunto<T>::eliminarAuxiliarRecursion( Conjunto<T>:: Nodo* original) {
    if(original!= nullptr) {
        if(original->der!= nullptr){
            eliminarAuxiliarRecursion(original->der);
        }
        if(original->izq!= nullptr){
            eliminarAuxiliarRecursion(original->izq);
        }
        delete original;
    }

}
template <class T>
Conjunto<T>::~Conjunto() { 
    eliminarAuxiliarRecursion(_raiz);
    //delete this;
}



template <class T>
bool Conjunto<T>::pertenece(const T& clave) const {
    if(_raiz == nullptr){
        return false;
    }
    else {
        Nodo *base = _raiz;
        if ((*base).valor == clave) {
            return true;
        }
        while (base != nullptr) {
            if ((*base).valor == clave) {
                return true;
            }
            else {
                if ((*base).valor < clave) {
                    base = base->der;
                } else {
                    base = base->izq;
                }
            }

        }

        return false;
    }
}



template <class T>
void Conjunto<T>::insertar(const T& clave) {

    if(cardinal()==0 and _raiz == nullptr){
        Nodo* t = new Nodo(clave);
        t->der = nullptr;
        t->izq = nullptr;
        _raiz = t;
        cantidadNodos ++;
        return;
    }
    else{
        Nodo* base = _raiz;
        while(base != nullptr){
            if((*base).valor == clave){
                return;
            }
            if((*base).valor<clave and base->der == nullptr){
                Nodo* t = new Nodo(clave);
                t->der = nullptr;
                t->izq = nullptr;
                (*base).der = t ;
                cantidadNodos ++;
                return;
            }
            if((*base).valor>clave and base->izq == nullptr){
                Nodo* t = new Nodo(clave);
                t->der = nullptr;
                t->izq = nullptr;
                (*base).izq = t ;
                cantidadNodos ++;
                return;
            }
            if((*base).valor<clave){
                base = base->der;
            }
            else {
                if((*base).valor>clave){
                    base = base->izq;
                }
            }
        }
    }

}
template <class T>
void Conjunto<T>::removerAuxiliarRecursion( Conjunto<T>:: Nodo* original) {
    if(original->der!= nullptr){
        removerAuxiliarRecursion(original->der);
    }
    if(original->izq!= nullptr){
        removerAuxiliarRecursion(original->izq);
    }
    insertar(original->valor);
    delete original;
    cantidadNodos--;

}

template <class T>
void Conjunto<T>::remover(const T& clave) {
    if(not pertenece(clave)){
        return;
    }
    cantidadNodos--;
    Nodo* padre = _raiz;
    Nodo* hijo = _raiz;
    if(clave>hijo->valor and hijo->der!= nullptr){
        hijo = hijo->der;
    }
    else{
        if(hijo->izq!= nullptr and clave < hijo->valor) {
            hijo = hijo->izq;
        }
    }
    //int c = clave;
    while((*hijo).valor != clave){
        //int h = (*hijo).valor;
        if(clave>hijo->valor){
            padre = hijo;
            hijo = hijo->der;
        }
        else{
            padre = hijo;
            hijo = hijo->izq;
        }
    }
    if(padre==hijo) { //Si hay que borrar la raiz:
        if (hijo->der != nullptr) {
            _raiz = hijo->der;
            if (hijo->izq != nullptr) {
                insertar((*(hijo->izq)).valor);


                removerAuxiliarRecursion(hijo->izq);
            }
            delete hijo;
        } else if (hijo->izq != nullptr) {
            _raiz = hijo->izq;
            if (hijo->der != nullptr) {
                insertar((*(hijo->der)).valor);

                removerAuxiliarRecursion(hijo->der);
            }
            delete hijo;
        }
        else{
            _raiz = nullptr;
            delete hijo;
        }
        return;
    }
    //si hay que borrar una hoja
    if(hijo->der== nullptr and hijo->izq== nullptr){
        if(padre->valor > hijo->valor){
            delete hijo;
            padre->izq= nullptr;
        }
        else{
            delete hijo;
            padre->der= nullptr;
        }
        return;
    }
    //si hay que borrar algo del medio
    if(padre->valor > hijo->valor){
        Nodo* mayores = (hijo->der);
        Nodo* menores = (hijo->izq);
        padre->izq= nullptr;
        delete hijo;
        if(mayores!= nullptr){
            insertar(mayores->valor);

            removerAuxiliarRecursion(mayores);
        }
        if(menores!= nullptr){
            insertar(menores->valor);

            removerAuxiliarRecursion(menores);
        }

        return;
    }
    if(padre->valor < hijo->valor){
        Nodo* mayores = (hijo->der);
        Nodo* menores = (hijo->izq);
        padre->der= nullptr;
        delete hijo;
        if(mayores!= nullptr){
            insertar(mayores->valor);
            removerAuxiliarRecursion(mayores);

        }
        if(menores!= nullptr){
            insertar(menores->valor);
            removerAuxiliarRecursion(menores);

        }
        return;
    }
    //assert(false);
}

template <class T>
const T& Conjunto<T>::siguiente(const T& clave) {
    Nodo* padre = _raiz;
    Nodo* hijo = _raiz;
    if(clave>hijo->valor and hijo->der!= nullptr){
        hijo = hijo->der;
    }
    else{
        if(hijo->izq!= nullptr) {
            hijo = hijo->izq;
        }
    }
    //Primero llego al nodo deseado
    while((*hijo).valor != clave){
        if(clave>hijo->valor){
            padre = hijo;
            hijo = hijo->der;
        }
        else{
            padre = hijo;
            hijo = hijo->izq;
        }
    }
    // ahora voy al siguiente, y despues al minimo del siguiente
    if(hijo->der== nullptr){
        return padre->valor;
    }
    else{
        hijo = hijo->der;
        while (hijo->izq != nullptr){
            hijo = hijo->izq;
        }
        return (*hijo).valor;
    }

}

template <class T>
const T& Conjunto<T>::minimo() const {
    Nodo* base = _raiz;
    while (base->izq != nullptr){
        base = base->izq;
    }
    return (*base).valor;
}

template <class T>
const T& Conjunto<T>::maximo() const {
    Nodo* base = _raiz;
    while (base->der != nullptr){
        base = base->der;
    }
    return (*base).valor;
}

template <class T>
unsigned int Conjunto<T>::cardinal() const {
    return cantidadNodos;
}

template <class T>
void Conjunto<T>::mostrar(std::ostream&) const {
    assert(false);
}



#ifndef LISTA_H_
#define LISTA_H_

#include "Nodo.h"


/*
 * Una Lista es una colección dinámica de elementos dispuestos en una secuencia.
 *
 * Define operaciones para agregar, remover, acceder y cambiar elementos
 * en cualquier posición.
 *
 * Tiene un cursor que permite recorrer todos los elementos secuencialmente.
 *
 */

template<class T>
class Lista {

    private:

        Nodo<T>* primero;
        unsigned int tamanio;
        Nodo<T>* cursor;

    public:

        /*
         * POST: Construye una lista vacía.
         */
        Lista();


        /*
         *
         * POST: Crea una Lista que tiene los mismos elementos que otraLista.
         *       La instancia resulta en una copia de otraLista.
         */
        Lista(Lista<T>& otraLista);


        /*
         * POST: Devuelve un valor de verdad que indica si la Lista no tiene
         * 		 ningun elemento.
         */
        bool estaVacia();


        /*
         * POST: Devuelve la cantidad de elementos que tiene la Lista.
         */
        unsigned int contarElementos();


        /*
         * POST: Invierte los elementos de la Lista.
         */
        void invertir();


        /*
         * PRE: Elemento es de un tipo de dato valido.
         * POST: Agrega el elemento al final de la Lista, en la posición:
         *       contarElementos() + 1.
         */
        void agregar(T elemento);


        /*
         * PRE: posición pertenece al intervalo: [1, contarElementos() + 1]
         * POST: Agrega el elemento en la posición indicada.
         *
         */
        void agregar(T elemento, unsigned int posicion);


        /*
         * POST: Agrega todos los elementos de otraLista a partir de la posición
         * 		 contarElementos() + 1.
         */
        void agregar(Lista<T> &otraLista);


        /*
         * PRE:  posicion pertenece al intervalo: [1, contarElementos()]
         * POST: Devuelve el elemento en la posición indicada.
         */
        T obtener(unsigned int posicion);


        /*
         * PRE:  posicion pertenece al intervalo: [1, contarElementos()]
         * POST: Cambia el elemento en la posición indicada por el
         *       elemento dado.
         */
        void asignar(T elemento, unsigned int posicion);


        /*
         * PRE:  posicion pertenece al intervalo: [1, contarElementos()]
         * POST: Remueve de la Lista el elemento en la posición indicada.
         */
        void remover(unsigned int posicion);


        /*
         * POST: Deja el cursor de la Lista apuntando a NULL para comenzar
         * 		 un nuevo recorrido de la misma.
         */
        void iniciarCursor();


        /*
         * PRE:  Se ha iniciado un recorrido (invocando el método
         *       iniciarCursor()) y desde entonces no se han agregado o
         *       removido elementos de la Lista.
         * POST: Mueve el cursor y lo posiciona en el siguiente elemento
         *       del recorrido.
         *       El valor de retorno indica si el cursor quedó posicionado
         *       sobre un elemento o no (en caso de que la Lista esté vacía o
         *       no existan más elementos por recorrer.)
         */
        bool avanzarCursor();


        /*
         * PRE:  El cursor está posicionado sobre un elemento de la Lista
         *       (fue invocado el método avanzarCursor() y devolvió true)
         * POST: Devuelve el elemento en la posición del cursor.
         */
        T obtenerCursor();


        /*
         * POST: Libera los recursos asociados a la Lista.
         */
        ~Lista();

    private:

        /*
         * PRE:  posicion pertenece al intervalo: [1, contarElementos()]
         * POST: Devuelve el Nodo en la posición indicada.
         */
        Nodo<T>* obtenerNodo(unsigned int posicion); // NOTA: primitiva PRIVADA
};


/*
 * Excepción que representa el intento de acceder a un elemento
 * que no existe dentro de la Lista.
 */

class ExcepcionElementoInexistente {

    private:
        unsigned int posicion;

    public:

        /*
         * POST: Excepción creada a partir de la posición inválida a la
         *       que se intentó acceder.
         */
        ExcepcionElementoInexistente(unsigned int posicion) {

            this->posicion = posicion;
        }

        /*
         * POST: devuelve la posición inválida a la que se intentó acceder.
         */
        unsigned int obtenerPosicionInvalida() {

            return this->posicion;
        }
};


template<class T>
Lista<T>::Lista() {

    this->primero = NULL;
    this->tamanio = 0;
    this->cursor = NULL;
}


template<class T>
Lista<T>::Lista(Lista<T>& otraLista) {

    this->primero = NULL;
    this->tamanio = 0;
    this->cursor = NULL;

    this->agregar(otraLista);
}


template<class T>
bool Lista<T>::estaVacia() {

	return (this->tamanio == 0);
}


template<class T>
unsigned int Lista<T>::contarElementos() {

    return this->tamanio;
}


template<class T>
void Lista<T>::invertir() {

	Nodo<T> *aux1, *aux2;

	if(this->contarElementos()>1){

		aux1 = this->primero;
		this->primero = aux1->obtenerSiguiente();
		aux1->cambiarSiguiente(NULL);

		do {
			aux2 = this->primero->obtenerSiguiente();
			this->primero->cambiarSiguiente(aux1);
			aux1 = this->primero;
			this->primero = aux2;

		} while(aux2 != NULL);

		this->primero = aux1;
	}
}


template<class T>
void Lista<T>::agregar(T elemento) {

    this->agregar(elemento, this->contarElementos() + 1);
}


template<class T>
void Lista<T>::agregar(T elemento, unsigned int posicion) {

    if ((posicion > 0) && (posicion <= this->contarElementos() + 1)) {

        Nodo<T>* nuevo = new Nodo<T>(elemento);

        if (posicion == 1) {

            nuevo->cambiarSiguiente(this->primero);
            this->primero = nuevo;

        } else {

            Nodo<T>* anterior = this->obtenerNodo(posicion - 1);
            nuevo->cambiarSiguiente(anterior->obtenerSiguiente());
            anterior->cambiarSiguiente(nuevo);
        }

        this->tamanio++;

        /* cualquier recorrido actual queda invalidado */
        this->iniciarCursor();

    } else {

        throw ExcepcionElementoInexistente(posicion);
    }
}


template<class T>
void Lista<T>::agregar(Lista<T> &otraLista) {

    otraLista.iniciarCursor();

    while (otraLista.avanzarCursor()) {

        this->agregar(otraLista.obtenerCursor());
    }
}


template<class T>
T Lista<T>::obtener(unsigned int posicion) {

    T elemento;

    if ((posicion > 0) && (posicion <= this->contarElementos())) {

        elemento = this->obtenerNodo(posicion)->obtenerDato();

    } else {

        throw ExcepcionElementoInexistente(posicion);
    }

    return elemento;
}


template<class T>
void Lista<T>::asignar(T elemento, unsigned int posicion) {

    if ((posicion > 0) && (posicion <= this->contarElementos())) {

        this->obtenerNodo(posicion)->cambiarDato(elemento);

    } else {

        throw ExcepcionElementoInexistente(posicion);
    }
}


template<class T>
void Lista<T>::remover(unsigned int posicion) {

    if ((posicion > 0) && (posicion <= this->contarElementos())) {

        Nodo<T>* removido;

        if (posicion == 1) {

            removido = this->primero;
            this->primero = removido->obtenerSiguiente();

        } else {

            Nodo<T>* anterior = this->obtenerNodo(posicion - 1);
            removido = anterior->obtenerSiguiente();
            anterior->cambiarSiguiente(removido->obtenerSiguiente());
        }

        delete removido;
        this->tamanio--;

        /* cualquier recorrido actual queda invalidado */
        this->iniciarCursor();

    } else {

        throw ExcepcionElementoInexistente(posicion);
    }
}


template<class T>
void Lista<T>::iniciarCursor() {

    this->cursor = NULL;
}


template<class T>
bool Lista<T>::avanzarCursor() {

    if (this->cursor == NULL) {

        this->cursor = this->primero;

    } else {

        this->cursor = this->cursor->obtenerSiguiente();
    }

    /* pudo avanzar si el cursor ahora apunta a un nodo */
    return (this->cursor != NULL);
}


template<class T>
T Lista<T>::obtenerCursor() {

    T elemento;

    if (this->cursor != NULL) {

        elemento = this->cursor->obtenerDato();

    } else {

        throw ExcepcionElementoInexistente(0);
    }

    return elemento;
}


template<class T>
Lista<T>::~Lista() {

    while (this->primero != NULL) {

        Nodo<T>* aBorrar = this->primero;
        this->primero = this->primero->obtenerSiguiente();

        delete aBorrar;
    }
}


template<class T>
Nodo<T>* Lista<T>::obtenerNodo(unsigned int posicion) {

    Nodo<T>* actual = this->primero;
    for (unsigned int i = 1; i < posicion; i++) {

        actual = actual->obtenerSiguiente();
    }

    return actual;
}


#endif /* LISTA_H_ */


#ifndef NODO_H_
#define NODO_H_

#ifndef NULL
#define NULL 0
#endif


template<class T>
class Nodo {

	private:

        T dato;
        Nodo<T>* siguiente;

    public:

        /*
         * POST: El Nodo resulta inicializado con el dato dado
         *       y un puntero a NULL.
         */
        Nodo(T dato);


        /*
         * POST: Devuelve el dato que contiene el nodo.
         */
        T obtenerDato();


        /*
         * PRE:  nuevoDato debe ser de un tipo válido.
         * POST: cambia el valor del dato.
         */
        void cambiarDato(T nuevoDato);


        /*
         * POST: Devuelve el puntero al siguiente Nodo.
         */
        Nodo<T>* obtenerSiguiente();


        /*
         * POST: Cambia el siguiente Nodo por nuevoSiguiente.
         */
        void cambiarSiguiente(Nodo<T>* nuevoSiguiente);


        /*
         * POST: Libera los recursos solicitados.
         */
        ~Nodo();

};


template <class T>
Nodo<T>::Nodo(T dato) {

	this->dato = dato;
	this->siguiente = NULL;
}


template <class T>
T Nodo<T>::obtenerDato() {

	return this->dato;
}


template <class T>
void Nodo<T>::cambiarDato(T nuevoDato) {

	this->dato = nuevoDato;
}


template <class T>
Nodo<T>* Nodo<T>::obtenerSiguiente() {

	return this->siguiente;
}


template <class T>
void Nodo<T>::cambiarSiguiente(Nodo<T>* nuevoSiguiente) {

    this->siguiente = nuevoSiguiente;
}


template <class T>
Nodo<T>::~Nodo(){

}


#endif /* NODO_H_ */

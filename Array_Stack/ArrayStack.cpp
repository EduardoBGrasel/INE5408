#ifndef STRUCTURES_ARRAY_STACK_H
#define STRUCTURES_ARRAY_STACK_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions

namespace structures {

template<typename T>
//! CLASSE PILHA
class ArrayStack {
 public:
    //! construtor simples
    ArrayStack();
    //! construtor com parametro tamanho
    explicit ArrayStack(std::size_t max);
    //! destrutor
    ~ArrayStack();
    //! metodo empilha
    void push(const T& data);
    //! metodo desempilha
    T pop();
    //! metodo retorna o topo
    T& top();
    //! metodo limpa pilha
    void clear();
    //! metodo retorna tamanho
    std::size_t size();
    //! metodo retorna capacidade maxima
    std::size_t max_size();
    //! verifica se esta vazia
    bool empty();
    //! verifica se esta cheia
    bool full();

 private:
    T* contents;
    int top_;
    std::size_t max_size_;

    static const auto DEFAULT_SIZE = 10u;
};

}  // namespace structures

#endif



/* seta o valor do array com o valor
padrão definido na classe */
template<typename T>
structures::ArrayStack<T>::ArrayStack() {
    max_size_ = DEFAULT_SIZE;
    contents = new T[max_size_];
    top_ = -1;
}


/* seta o valor do array com
o valor informado pelo usuario */
template<typename T>
structures::ArrayStack<T>::ArrayStack(std::size_t max) {
    max_size_ = max;
    contents = new T[max_size_];
    top_ = -1;
}

template<typename T>
structures::ArrayStack<T>::~ArrayStack() {
    /* destructor da classe, deleta
    o vetor de conteudos */
    delete [] contents;
}

// adicionar itens na pilha
template<typename T>
void structures::ArrayStack<T>::push(const T& data) {
    if (full()) {
        // se a pilha estiver cheia lançar um erro
        throw std::out_of_range("pilha cheia");
    } else {  // senão move o topo para o novo item adicionado
        top_++;
        contents[top_] = data;
    }
}

template<typename T>
T structures::ArrayStack<T>::pop() {  // excluir item da pilha
    if (empty())
        // se a pilha estiver vazia lança um erro
        throw std::out_of_range("pilha vazia");
    T aux;
    // senão recupera o valor do item a ser excluido e em seguida o remove
    aux = contents[top_];
    top_--;
    return aux;
}

// retorna a valor que está no topo da pilha
template<typename T>
T& structures::ArrayStack<T>::top() {
    if (empty())
        // caso a pilha esteja vazia lança um erro
        throw std::out_of_range("pilha vazia");
    return contents[top_];
}


// limpa toda a pilha, movendo o top para o indice -1
template<typename T>
void structures::ArrayStack<T>::clear() {
    top_ = -1;
}

// recupera o tamanho da pilha (o 1 é adicionado pois a pilha inicia do 0)
template<typename T>
std::size_t structures::ArrayStack<T>::size() {
    return top_ + 1;
}


// recupera o tamanho maximo da pilha definido na classe
template<typename T>
std::size_t structures::ArrayStack<T>::max_size() {
    return max_size_;
}

// caso a pilha esteja vazia retorna True
template<typename T>
bool structures::ArrayStack<T>::empty() {
    return (top_ == -1);
}

// caso a lista esteja cheira retorna True
template<typename T>
bool structures::ArrayStack<T>::full() {
    return size() == max_size();
}

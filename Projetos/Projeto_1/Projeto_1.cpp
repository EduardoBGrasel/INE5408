#include <iostream>
#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions
#include <string>
#include <fstream>
#include <vector>

//implementacao da pilha e fila feitas em aula:

template<typename T>
//! CLASSE PILHA
class ArrayStack {
 public:
    //! construtor simples
    ArrayStack() {
        max_size_ = DEFAULT_SIZE;
        contents = new T[max_size_];
        top_ = -1;
    }
    //! construtor com parametro tamanho
    explicit ArrayStack(std::size_t max) {
        max_size_ = max;
        contents = new T[max_size_];
        top_ = -1;
    }
    //! destrutor
    ~ArrayStack() {
        delete [] contents;
    }
    //! metodo empilha
    void push(const T& data) {
        if (full()) {
            throw std::out_of_range("pilha cheia");
        } else {
            top_++;
            contents[top_] = data;
        }
    }
    //! metodo desempilha
    T pop() {
        if (empty())
            throw std::out_of_range("pilha vazia");
        T aux;
        aux = contents[top_];
        top_--;
        return aux;
    }
    //! metodo retorna o topo
    T& top() {
        if (empty())
            throw std::out_of_range("pilha vazia");
        return contents[top_];
    }
    //! metodo limpa pilha
    void clear() {
        top_ = -1;
    }
    //! metodo retorna tamanho
    std::size_t size() {
        return (top_ + 1);
    }
    //! metodo retorna capacidade maxima
    std::size_t max_size() {
        return(max_size_);
    }
    //! verifica se esta vazia
    bool empty() {
        return (top_ == -1);
    }
    //! verifica se esta cheia
    bool full() {
        return (static_cast<size_t>(top_) == max_size()-1);
    }

 private:
    T* contents;
    int top_;
    std::size_t max_size_;

    static const auto DEFAULT_SIZE = 10u;
};

template<typename T>
//! classe ArrayQueue
class ArrayQueue {
 public:
    //! construtor padrao
    ArrayQueue() {
        max_size_ = DEFAULT_SIZE;
        contents = new T[max_size_];
        size_ = 0;
        begin_ = 0;
        end_ = -1;
    }
    //! construtor com parametro
    explicit ArrayQueue(std::size_t max) {
        max_size_ = max;
        contents = new T[max_size_];
        size_ = 0;
        begin_ = 0;
        end_ = -1;
    }
    //! destrutor padrao
    ~ArrayQueue() {
        delete [] contents;
    }
    //! metodo enfileirar
    void enqueue(const T& data) {
        if (full()) {
            throw std::out_of_range("Fila cheia");
        } else {
            end_ = (end_ + 1) % max_size();
            size_++;
            contents[end_] = data;
        }
    }

    //! metodo desenfileirar
    T dequeue() {
        if (empty()) {
            throw std::out_of_range("Fila vazia");
        } else {
            T aux;
            aux = contents[begin_];
            begin_ = (begin_ + 1) % max_size();
            size_--;
            return (aux);
        }
    }
    //! metodo retorna o ultimo
    T& back() {
        if (empty()) {
            throw std::out_of_range("Fila vazia");
        } else {
            return (contents[end_]);
        }
    }
    //! metodo limpa a fila
    void clear() {
        begin_ = 0;
        end_ = -1;
        size_ = 0;
    }
    //! metodo retorna tamanho atual
    std::size_t size() {
        return (size_);
    }
    //! metodo retorna tamanho maximo
    std::size_t max_size() {
        return(max_size_);
    }
    //! metodo verifica se vazio
    bool empty() {
        return (size_ == 0);
    }
    //! metodo verifica se esta cheio
    bool full() {
        return (static_cast<size_t>(size_) == max_size());
    }

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;
    int begin_;  // indice do inicio (para fila circular)
    int end_;  // indice do fim (para fila circular)
    static const auto DEFAULT_SIZE = 1000u;
};

// PARTE 2 - FATIANDO O XML
ArrayQueue<std::string> get_xml_sliced(const std::string& xml_data) {
    ArrayQueue<std::string> tags;
    // UTILITARIO
    std::string sliced_string;  // return
    std::string Tag_start = "<cenario>";  // inicio da substring
    std::string tag_end = "</cenario>";  //  fim da substring
    // CONTROLE
    int pos = 0; 
    int opening = 0;
    int closing = 0;
    // algoritimo para fatiar a string
    while ((opening = xml_data.find(Tag_start, pos)) != std::string::npos) {
        opening = opening + Tag_start.length();
        closing = xml_data.find(tag_end, opening);
        sliced_string = xml_data.substr(opening, closing - opening);
        pos = closing + tag_end.length();
        tags.enqueue(sliced_string);
    }
    return tags;
}
// PARTE 3 - RECUPARANDO DADOS ENTRE TAGS
std::string get_data_name(const std::string& xml, std::string tag_open, std::string tag_close) {
    int pos = 0;
    int opening = 0;
    int closing = 0;
    std::string data;  // return
    while ((opening = xml.find(tag_open, pos)) != std::string::npos) {
        opening += tag_open.length();
        closing = xml.find(tag_close, opening);
        data = xml.substr(opening, closing - opening);
        pos = closing + tag_close.length();
    }
    return data;  // nome
}

int get_data(const std::string& xml, const std::string& tag_start, const std::string& tag_end) {
    int pos = 0;
    int opening = 0;
    int closing = 0;
    int data;
   
    while ((opening = xml.find(tag_start, pos)) != std::string::npos) {
        opening += tag_start.length();
        closing = xml.find(tag_end, opening);
        data = stoi(xml.substr(opening, closing - opening));
        pos = closing + tag_end.length();
    }
    return data;
}
// PARTE 1 CHECK_XML
bool check_xml(const std::string& xml) {
    ArrayStack<std::string> stack;  // verificação
    std::size_t pos = 0;  // posição
    while (pos < xml.size()) { 
        if (xml[pos] == '<') {  // indentifica a inicio da tag 
            std::size_t closing = xml.find('>', pos);  // encontra o fim da tag
            if (closing == std::string::npos) {
                return false;
            }
            std::string id = xml.substr(pos + 1, closing - pos - 1);
            if (id[0] == '/') {  // tag de fechamento
                if (stack.empty() || stack.top() != id.substr(1)) { // verificação
                    return false;
                }
                stack.pop();
            } else {
                stack.push(id);
            }
            pos = closing + 1;
        } else {
            pos++;
        }
    }
    if (!stack.empty()) {
        return false;
    }
    return true;
}
// PARTE 4  - FUNÇÃO NÚCLEO DA EXECUSÃO 
std::string worker_function_master(const std::string& cenario) {
    std::string answer;
    // pagando os dados do cenário
    int x = get_data(cenario, "<x>", "</x>");
    int y = get_data(cenario, "<y>", "</y>");
    int width = get_data(cenario, "<altura>", "</altura>");
    int height = get_data(cenario, "<largura>", "</largura>");
    std::string nome = get_data_name(cenario, "<nome>", "</nome>");
    // criação de matrizes
    std::vector<std::vector<int>> matriz_zero(width, std::vector<int>(height, 0));
    std::vector<std::vector<int>> matriz_cenario(width, std::vector<int>(height, 0));
    //  preenchendo a matriz com zeros
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++){
            matriz_zero[i][j] = 0;
        }
    }
    
    // Preenche matriz 
    std::string matriz = get_data_name(cenario, "<matriz>", "</matriz>");
    int cont = 0;
    std::string aux;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++){
            aux = matriz[cont];
            matriz_cenario[i][j] = stoi(aux);
            cont++;
        }
    }
    
    // INICIALIZAÇÃO DO ROBO
    int area;
    if(matriz_cenario[x][y] == 0) {
        area = 0;
    } else {
        ArrayQueue<std::pair<int, int>> queue;
        queue.enqueue({x, y});
        matriz_zero[x][y] = 1;
        while (!queue.empty()) {
            std::pair<int, int> temp = queue.dequeue();
            int currentX = temp.first;
            int currentY = temp.second;
    
            int dx[] = {-1, 1, 0, 0};
            int dy[] = {0, 0, -1, 1};
    
            for (int i = 0; i < 4; i++) {
                int nx = currentX + dx[i];
                int ny = currentY + dy[i];
    
                if (nx >= 0 && nx < width && ny >= 0 && ny < height && matriz_cenario[nx][ny] == 1 && matriz_zero[nx][ny] == 0) {
                    queue.enqueue({nx, ny});
                    matriz_zero[nx][ny] = 1;
                }
            }
        }
        area = 0;
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                if (matriz_zero[i][j] == 1) {
                    area++;
                }
            }
        }
    }
    answer = nome + " " + std::to_string(area);
    return answer;
}

int main() {
    char xmlfilename[100];
    std::cin >> xmlfilename;  
    // Arquivo aberto em modo de leitura
    std::ifstream arquivo(xmlfilename);
    std::string row;
    std::string xml;
    //  PARTE 1 - LENDO O ARQUIVO
    while (std::getline(arquivo, row)) {
        xml += row; //  concatenando as linhas
    }
    // valida as tags
    if(check_xml(xml)) {
        // PARTE 2
        ArrayQueue<std::string> xml_sliced = get_xml_sliced(xml);
        int size = xml_sliced.size();
        std::string answer;
        std::string target;
        // PARTE 4
        for (int i = 0; i < size; i++) {
            target = xml_sliced.dequeue();
            answer = worker_function_master(target);
            std::cout << answer << std::endl;
        }   
    } else {
        std::cout << "erro" << std::endl;
        return 1;
    };
    return 0;
}


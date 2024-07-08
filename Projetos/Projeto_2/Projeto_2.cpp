#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int AVALIABLE_CHARS = 26;

struct NoTrie {
    int position;
    int length;
    int words; 
    bool word;
    NoTrie *child[AVALIABLE_CHARS]; // define o número total de filhos possíveis
};

// cria um novo nó e inicializa os valores
NoTrie *makeNo() {
    NoTrie *No = new NoTrie;
    No->position = 0;
    No->length = 0;
    No->words = 0;
    No->word = false;
    for (int i = 0; i < AVALIABLE_CHARS; i++) {
        No->child[i] = nullptr;
    }
    return No;
}

// inserir palavra na trie
void insert(NoTrie *root, const string &word, int position, int length) {
    NoTrie* current = root;
    for (char c : word) { // percorre a palavra
        int i = c - 'a';
        // se o ponteiro for null, cria um novo No
        if (current->child[i] == nullptr) {
            current->child[i] = makeNo();
        }
        // aumentamos o total de palavras
        current = current->child[i];
        current->words++; 
    }
    // marcar como palavra completa e atualizar posição e comprimento
    current->length = length;
    current->position = position;
    current->word = true;
}

NoTrie *findPrefix(NoTrie *root, const string &prefix) {
    NoTrie* current = root;
    for (char c : prefix) {  // percorre o prefixo
        int i = c - 'a';
        // verifica se o nó existe na trie, se não existir retorna nullptr
        if (current->child[i] == nullptr) {
            return nullptr;
        }
        // senão atualizamos o current
        current = current->child[i];
    }
    // retornamos o current
    return current;
}

void showPrefix(NoTrie* root, const string& prefix) {
    NoTrie* NoPrefix = findPrefix(root, prefix); // busca o prefixo
    if (NoPrefix != nullptr) { // se o nó existir
        cout << prefix << " is prefix of " << NoPrefix->words << " words" << endl;
        if (NoPrefix->word) { // se for uma palavra
            cout << prefix << " is at (" << NoPrefix->position << "," << NoPrefix->length << ")" << endl;
        }
    } else { // senão não é um prefixo
        cout << prefix << " is not prefix" << endl;
    }
}

void Dict(const string& filename, NoTrie* root) {
    int location = 0;
    string row; 
    ifstream dict(filename);  // ler um arquivo
    while (getline(dict, row)) { //  ler as linhas do arquivo
        // buscar a abertura e fechamento das tags
        int opening = row.find('[');
        int closing = row.find(']');
        // verificamos se a posição é válida
        if (opening != string::npos && closing != string::npos && closing > opening + 1) {
            // inserimos a palavra na trie
            string word = row.substr(opening + 1, closing - opening - 1);
            insert(root, word, location, row.length());
        }
        // atualizamos a localização
        location += row.length() + 1; 
    }
    dict.close();
}

int main() {
    string dictionaryFile;
    cin >> dictionaryFile;
    // criando a root
    NoTrie* root = makeNo();
    // lendo o dicionario e adicionando os valores
    Dict(dictionaryFile, root);

    string word;
    cin >> word;
    // ler as palavras de entrada
    while (word != "0") {
        showPrefix(root, word);
        cin >> word;
    }

    return 0;
}
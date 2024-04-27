#include "./array_stack.h"

bool verificaChaves(std::string trecho_programa) {
    bool resposta = true;
    int  tamanho  = trecho_programa.length();
    structures::ArrayStack<char> pilha(500);
    for (int i = 0; i < tamanho; i++) {
        // condições de parada dor 'for' podem ser adicionadas...
        /*
            COLOCAR SEU CÓDIGO AQUI...
        */
        if (pilha.empty() && trecho_programa[i] == '}') {
            resposta = false;
            return resposta;
        }
        if (trecho_programa[i] == '{') {
            pilha.push(trecho_programa[i]);
        } else if (trecho_programa[i] == '}' && pilha.top() == '{') {
            pilha.pop();
        }

    }

    return resposta;
}

// Questão 1

(a)

void insereNoInicio(T dado) {
    NoLista* novo_no = new NoLista(dado);  // instancia um novo né

    if (quantidade > 0) {  // se a lista não estiver vazia
        NoLista* antigo_primeiro_no = movel->prim();  // guarda o primeiro elemento da lista

        NoLista* atual = antigo_primeiro_no;  // variável que vai ser usada para percorrer a lista

        for (int i = 0; i < quantidade; i++) {  // loop para atualizar o atributo prim de todos os
                                                // nós para apontar para o novo nó que foi criado
            atual->prim(novo_no);
            atual = atual->prox();
        }

        novo_no->prox(antigo_primeiro_no); // o novo nó passa a apontar para o antigo primeiro nó
        }
    else {  // se caso a lista estiver vazia
        novo_no->prim(novo_no);  // novo_no vai apontar para si mesmo
        novo_no->prox(nullptr);  // não existirá próximo nó
        pos_movel = 1;  // posição do móvel será igual a 1, ou seja, a posição do nó que acaba de ser inserido
        movel = novo_no;  // movel aponta para novo_no
        }
    quantidade = quantidade + 1;  // incrementa a quantidade de elementos
    pos_movel = pos_movel + 1;  // incrementa o pos_movel
}


(b)

Acredito que um ponto que pode ser ressaltado e considerado uma vantagem na
utilização do ponteiro "móvel" na estrutura de dados Lista, proposta na
questão, seja que podemos acessar elementos mais ao final da lista sem precisar,
necessariamente, atravessar a lista inteira. Por exemplo, se quisermos acessar
apenas a segunda metade de uma lista e sabemos que o número de elementos
presentes nessa lista é n, podemos setar o atributo pos_móvel da seguinte forma
pos_móvel = n/2, de modo que móvel passará a apontar para o meio da lista.
Poderemos então, iterar de móvel até o último elemento da lista e recolher os
dados que desejamos (os da segunda metade) evitando percorrer a primeira metade
desnecessáriamente, nesse caso.

// Questão 2

void concatena(Lista *L1, Lista *L2) {
    if (L1->tamanho() > 0 && L2->tamanho() == 0) {  // verifica se a segunda lista é igual a zero, se for
                                                    // considerei que não há nada a ser feito, pois seria
                                                    // impossível fazer separa apontar para o primeiro elemento
                                                    // de L2 já que L2 não possui elementos. Levantei uma exceção
        throw std::out_of_range("Impossível concatenar uma lista vazia ao final de outra lista!");
    }
    else if (L1->tamanho() == 0 && L2->tamanho() > 0) {  // Caso L1 tenha tamanho 0 e L2 não
        int tamanho_lista_concatenada = L2->tamanho();  // tamanho da nova lista será o próprio tamanho de L2
        L1->tamanho(tamanho_lista_concatenada);  // define o tamanho de L1 como sendo o tamanho_lista_concatenada
        L1->inicio(L2->inicio());  // inicio vai ser o nó do início de L2
        L1->pos_sep(1);  // pos_sep será setado para 1 (assumi que existe um setter na estrutura para este atributo)
        L1->separa(L1->inicio());  // separa será o primeiro nó da segunda lista, que agora se encontra também em L1->inicio()
        delete L2;  // nesta parte fiquei em dúvida, se deveria utilizar o o delete, já que ele chama o destrutor que por sua vez
                    // deleta todos os nós presentes na lista, o que seria indesejado, porém, para fins de simplificação assumirei que
                    // o destrutor da lista não deleta todos os nós da lista, apenas seta o tamanho da lista para 0, ou tome alguma outra
                    // medida mais apropriada nesta situação que nunca me havia ocorrido.
        return;  // retorna
    }
    NoLista* inicio_lista_concatenada = L1->inicio();  // o inicio da lista concatenada será o próprio início da lista L1
    NoLista* inicio_L2 = L2->inicio();  // guarda o inicio de L2
    NoLista* fim_lista_concatenada = inicio_L2->prev();  // o final da lista será o último elemento de L2

    int pos_sep_lista_concatenada = L1->tamanho();  // pos_sep da lista concatenada será o tamanho de L1, que será o index do primeiro nó de L2
    int tamanho_lista_concatenada = L1->tamanho() + L2->tamanho();  // tamanho total da lista concatenada

    inicio_lista_concatenada->prev(fim_lista_concatenada);  // prev() da lista concatenada será o último elemento da lista concatenada
    fim_lista_concatenada->prox(inicio_lista_concatenada);  // o prox() do fim da lisca concatenada será o inicio da lista concatenada
    L1->pos_sep = pos_sep_lista_concatenada;  // pos_sep de da lista concatenada (que é o próprio L1) será o index do primeiro elemento de L2
    L1->separa(L2->inicio());  // separa apontará para o início de L2
    L1->tamanho(tamanho_lista_concatenada);  // seta o tamanho para o novo tamanho, que é a soma dos dois tamanhos
    delete L2;  // deleta L2, como pedido no enunciado (aqui tive a mesma dúvida do delete acima e aderi o mesmo pensamento)
}


// Questão 3

// Decidi usar a Lista do tipo Circular Duplamente Encadeada
void reposicioneSubListaNoInicio(int p, int k) {
    if (k >= tamanho() || p < 0 || p >= tamanho() || p + k - 1 > tamanho() - 1) {  // verifico se os limites requisitados são válidos
        throw std::out_of_range("Limites inválidos!");
    }

    Lista lista_auxiliar = Lista();  // crio uma lista auxiliar para guardar os elementos que vão ser selecionados

    for (int i = 0; i < tamanho(); i++) {  // itero sobre a lista inteira guardando os dados requisitados na lista_auxiliar
        if (i >= p && i < k + p) {
           lista_auxiliar.push_back(at(i));
        }
    }

    for (int = 0; i < tamanho(); i++) {  // itero novamente sobre a lista inteira, desta vez, removendo todos os elementos
                                         // que serão realocados para o início da lista
        if (i >= p && i < k + p) {
           pop(i);
        }
    }

    NoLista* novo_inicio = lista_auxiliar.inicio();  // variável para guardar o novo início da lista gerada
    NoLista* fim_lista_auxiliar = novo_inicio.prev();  // variável que guarda o fim da lista auxiliar
    NoLista* primeiro_elemento = sentinela->prox();  // primeiro elemento da lista atual, sem ser o sentinela
    NoLista* fim_lista = sentinela->prev();  // elemento que se encontra no fim da lista atual (não da auxiliar)
    fim_lista_auxiliar.prox(primeiro_elemento);  // define o próximo elemento do fim da lista auxiliar como sendo
    primeiro_elemento.prev(fim_lista_auxiliar);  // prev do primeiro elemento da lista passa a apontar para o fim da lista_auxiliar
                                                 // ou seja, estamos começando a interligar as duas listas
    fim_lista->prox(novo_inicio);  // fim da lista atual passa a apontar para o inicio (sentinela) da lista_auxiliar
    novo_inicio->prev(fim_lista);  // prev do novo_inicio passa a apontar para o fim da lista, já que a lista é circular
    delete sentinela;  // deleta o sentinela da lista atual
    sentinela = novo_inicio;  // define o sentinela da lista atual como sendo o novo_inicio
    delete lista_auxiliar;  // deleta a lista auxiliar, já que agora ela já foi ligada com a lista atual
}

// Questão 4
//
// (b)

while (L.size() >= 46) {
    L.back();
    L.pop_front();
}

// L.size() = 200
// size() - 1
// ou seja, pop() vai ser executado 200 - 46 = 154 vezes
// 154 - 200 = 46
// ((a1 + an) * n)/2
// ((199 + 46) * 154)/2

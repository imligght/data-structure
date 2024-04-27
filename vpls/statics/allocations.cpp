#include <string>


class Aluno {
 public:
    Aluno() {}  // construtor
    ~Aluno() {}  // destrutor
    std::string devolveNome() {
        return nome;
    }
    int devolveMatricula() {
        return matricula;
    }
    void escreveNome(std::string nome_) {
        nome = nome_;
    }
    void escreveMatricula(int matricula_) {
        matricula = matricula_;
    }
 private:
    std::string nome;
    int matricula;
};


/*
(1) cria um vetor de 'Alunos' a partir de nomes e matriculas; exemplo:
vetor de nomes: ['Fulano', 'Beltrano', 'Ciclano']
vetor de matriculas: [1010, 2020, 3030]
vetor t alocado de saida: [{'Fulano',1010}, {'Beltrano',2020}, {'Ciclano':3030}]
*/

Aluno *turma(std::string nomes[], int matriculas[], int N) {
    Aluno *t = new Aluno[N];

    // ... COLOQUE SEU CÓDIGO AQUI ...
    for (int i = 0; i < N; i++) {
        t[i].escreveNome(nomes[i]);
        t[i].escreveMatricula(matriculas[i]);
    }

    return t;
}

/*
(2) cria um novo vetor contendo outros dois vetores de alunos (acrescenta vetor 2 apos o vetor 1); exemplo:
t1 de estrada: [{'Fulano',1010}, {'Beltrano',2020}];  N1 = 2
t2 de entrada: [{'Fulana',7070}, {'Beltrana',8080}, {'Cicrana',9090}];  N2 = 3
tu de saída: [{'Fulano',1010}, {'Beltrano',2020}, {'Fulana',7070}, {'Beltrana',8080}, {'Cicrana':9090}]
*/
Aluno *turmas_uniao(Aluno t1[], Aluno t2[], int N1, int N2) {
    Aluno *tu = new Aluno[N1 + N2];

    for (int i = 0; i < N1; i++) {
        tu[i] = t1[i];
    }

    for (int j = 0; j < N2; j++) {
        tu[N1 + j] = t2[j];
    }

    // ... COLOQUE SEU CÓDIGO AQUI ...

    return tu;
}

/*
(3) divide uma turma t existente em duas outras (os conteúdos dos ponteiros pt1 e pt2 serão as duas saídas; inicialmente são iguais a 'nullptr'), a primeira com k elementos e a segunda com o restante (N-k elementos); exemplo:
t de entrada: [{'Fulano',1010}, {'Beltrano',2020}, {'Fulana',7070}, {'Beltrana',8080}, {'Cicrana':9090}]
k = 2
conteudo de pt1: [{'Fulano',1010}, {'Beltrano',2020}]
conteudo de pt2: [{'Fulana',7070}, {'Beltrana',8080}, {'Cicrana',9090}]
*/
void turmas_divisao(Aluno t[], int k, int N, Aluno **pt1, Aluno **pt2) {
    Aluno *t1 = new Aluno[k];
    Aluno *t2 = new Aluno[N-k];

    // ... COLOQUE SEU CÓDIGO AQUI ...
    for (int i = 0; i != k; i++) {
        t1[i] = t[i];
    }

    for (int j = 0; j != N - k; j++) {
        t2[j] = t[k + j];
    }

    *pt1 = t1;
    *pt2 = t2;
}

// (4)
Aluno *turma_filtra(Aluno t[], int N, int menor_matr) {
    Aluno *tf;
    tf = nullptr;  // retirar e alocar (com new)
    int k = 0;

    for (int i = 0; i < N; i++) {
        if (t[i].devolveMatricula() >= menor_matr) {
            k += 1;
        }
    }

    tf = new Aluno[k];

    for (int i = 0, j = 0; i < N; i++) {
        if (t[i].devolveMatricula() >= menor_matr) {
            tf[j++] = t[i];
        }
    }

    return tf;
}

// (5)
int *turma_conta(Aluno t[], int N) {
    int *c;
    c = new int[26]();  // retirar e alocar (com new)
    for (int i = 0; i < N; i++) {
        c[toupper(t[i].devolveNome()[0]) - 'A'] += 1;
    }
    return c;
}

// (6)
Aluno **grupos_por_iniciais(Aluno t[], int N) {
    Aluno **g;
    g = new Aluno*[26];  // vetor de ponteiros;
                         // cada posição aponta para um vetor de alunos;
                         // tg[i] deve ser alocado com o seguinte:
                         //   tg[0] é um ponteiro para alunos com letra 'A'
                         //   tg[1] é um ponteiro para alunos com letra 'B'
                         //   ...
                         //   tg[25] é um ponteiro para alunos com letra 'Z'

    // DICA: utilize a função 'turma_conta' (implementada no execício 5) para
    //       definir o tamanho de cada um dos 26 vetores
    // int *c = turma_conta(t, N);

    // COLOQUE SEU CÓDIGO AQUI ...
    int* qtd_alunos_por_inicial = turma_conta(t, N);

    for (int i = 0; i < 26; i++) {
        g[i] = new Aluno[qtd_alunos_por_inicial[i]];
    }

    int* indice_por_inicial = new int[26]();

    for (int i = 0; i < N; i++) {
        char inicial = t[i].devolveNome()[0];
        int indice_da_inicial = inicial - 'A';
        g[indice_da_inicial][indice_por_inicial[indice_da_inicial]++] = t[i];
    }

    delete [] qtd_alunos_por_inicial;
    delete [] indice_por_inicial;

    return g;
}

int main() {
    ;
}


/*
    *** Importante ***

    A função 'main()' não deve ser escrita aqui, pois é parte do código dos testes e já está implementada

*/

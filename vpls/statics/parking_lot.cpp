/*
    *** Importante ***

    O código de fila em vetor está disponível internamente (não precisa de implementação aqui)

*/



void retira_veiculo(structures::ArrayQueue<int> *f, int k) {
    // ... COLOQUE SEU CÓDIGO AQUI ...
    for (int i = 0; i < k - 1; i++) {
        int dequeued_element = f->dequeue();
        f->enqueue(dequeued_element);
    }
    f->dequeue();
}


void mantenha_veiculo(structures::ArrayQueue<int> *f, int k) {
    // ... COLOQUE SEU CÓDIGO AQUI ...
    for (int i = 0; i < k - 1; i++) {
        int dequeued_element = f->dequeue();
        f->enqueue(dequeued_element);
    }
    int permanent_element = f->dequeue();
    f->clear();
    f->enqueue(permanent_element);
}



/*
    *** Importante ***

    A função 'main()' não deve ser escrita aqui, pois é parte do código dos testes e já está implementada

*/

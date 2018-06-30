#include "ArvoreB.hpp"

NodeArvoreB::NodeArvoreB(int aux_min_ordem, bool aux_folha){
    Min_ordem = aux_min_ordem;
    folha = aux_folha;
 
    Chaves = new char*[2*Min_ordem-1];
    for (int i = 0; i < (2*Min_ordem-1); ++i){
        Chaves[i] = new char[9];
    }
    Filhos = new NodeArvoreB *[2*Min_ordem];
 
    Numero_chaves = 0;
}

int NodeArvoreB::Encontra_Chave(char* chave){
    int indice=0;
    while (indice < Numero_chaves && (strcmp(chave,Chaves[indice]) > 0))
        ++indice;
    return indice;
}

void NodeArvoreB::Remove(char *chave){
    int indice = Encontra_Chave(chave);
    if (indice < Numero_chaves && (strcmp(chave,Chaves[indice]) == 0)){
        if (folha)
            Remove_Folha(indice);
        else
            Remove_Nao_Folha(indice);
    }
    else{

        if (folha){
            cout << "The key "<< chave <<" is does not exist in the tree\n";
            return;
        }

        bool flag = ( (indice==Numero_chaves)? true : false );
        if (Filhos[indice]->Numero_chaves < Min_ordem)
            Preenche_Node_Filho(indice);

        if (flag && indice > Numero_chaves)
            Filhos[indice-1]->Remove(chave);
        else
            Filhos[indice]->Remove(chave);
    }
    return;
}

void NodeArvoreB::Remove_Folha (int indice){

    for (int i=indice+1; i<Numero_chaves; ++i)
        Chaves[i-1] = Chaves[i];

    Numero_chaves--;
 
    return;
}

void NodeArvoreB::Remove_Nao_Folha(int indice){
 
    char* chave = Chaves[indice];
    if (Filhos[indice]->Numero_chaves >= Min_ordem){
        char* predecessor = Encontra_Predecessor(indice);
        Chaves[indice] = predecessor;
        Filhos[indice]->Remove(predecessor);
    }
    else if  (Filhos[indice+1]->Numero_chaves >= Min_ordem){
        char* sucessor = Encontra_Sucessor(indice);
        Chaves[indice] = sucessor;
        Filhos[indice+1]->Remove(sucessor);
    }

    else{
        merge(indice);
        Filhos[indice]->Remove(chave);
    }
    return;
}

char* NodeArvoreB::Encontra_Predecessor(int indice){
    NodeArvoreB *atual=Filhos[indice];
    while (!atual->folha)
        atual = atual->Filhos[atual->Numero_chaves];
    
    return atual->Chaves[atual->Numero_chaves-1];
}

char* NodeArvoreB::Encontra_Sucessor(int indice){
 
    NodeArvoreB *atual = Filhos[indice+1];
    while (!atual->folha)
        atual = atual->Filhos[0];

    return atual->Chaves[0];
}

void NodeArvoreB::Preenche_Node_Filho(int indice){
 
    if (indice!=0 && Filhos[indice-1]->Numero_chaves>=Min_ordem)
        Pega_Chave_Node_Anterior(indice);

    else if (indice!=Numero_chaves && Filhos[indice+1]->Numero_chaves>=Min_ordem)
        Pega_Chave_Node_Seguinte(indice);

    else{
        if (indice != Numero_chaves)
            merge(indice);
        else
            merge(indice-1);
    }
    return;
}

void NodeArvoreB::Pega_Chave_Node_Anterior(int indice){
 
    NodeArvoreB *filho=Filhos[indice];
    NodeArvoreB *irmao=Filhos[indice-1];

    for (int i=filho->Numero_chaves-1; i>=0; --i)
        filho->Chaves[i+1] = filho->Chaves[i];
 
    if (!filho->folha){
        for(int i=filho->Numero_chaves; i>=0; --i)
            filho->Filhos[i+1] = filho->Filhos[i];
    }

    filho->Chaves[0] = Chaves[indice-1];
 
    if(!filho->folha)
        filho->Filhos[0] = irmao->Filhos[irmao->Numero_chaves];
 
    Chaves[indice-1] = irmao->Chaves[irmao->Numero_chaves-1];
 
    filho->Numero_chaves += 1;
    irmao->Numero_chaves -= 1;
 
    return;
}

void NodeArvoreB::Pega_Chave_Node_Seguinte(int indice){
 
    NodeArvoreB *filho=Filhos[indice];
    NodeArvoreB *irmao=Filhos[indice+1];

    filho->Chaves[(filho->Numero_chaves)] = Chaves[indice];

    if (!(filho->folha))
        filho->Filhos[(filho->Numero_chaves)+1] = irmao->Filhos[0];
 

    Chaves[indice] = irmao->Chaves[0];
 

    for (int i=1; i<irmao->Numero_chaves; ++i)
        irmao->Chaves[i-1] = irmao->Chaves[i];
 
    
    if (!irmao->folha){
        for(int i=1; i<=irmao->Numero_chaves; ++i)
            irmao->Filhos[i-1] = irmao->Filhos[i];
    }

    filho->Numero_chaves += 1;
    irmao->Numero_chaves -= 1;
 
    return;
}
void NodeArvoreB::merge(int indice){
    NodeArvoreB *filho = Filhos[indice];
    NodeArvoreB *irmao = Filhos[indice+1];

    filho->Chaves[Min_ordem-1] = Chaves[indice];
 

    for (int i=0; i<irmao->Numero_chaves; ++i)
        filho->Chaves[i+Min_ordem] = irmao->Chaves[i];
 
    
    if (!filho->folha){
        for(int i=0; i<=irmao->Numero_chaves; ++i)
            filho->Filhos[i+Min_ordem] = irmao->Filhos[i];
    }
 
    for (int i=indice+1; i<Numero_chaves; ++i)
        Chaves[i-1] = Chaves[i];
 
    for (int i=indice+2; i<=Numero_chaves; ++i)
        Filhos[i-1] = Filhos[i];

    filho->Numero_chaves += irmao->Numero_chaves+1;
    Numero_chaves--;

    delete(irmao);
    return;
}

void NodeArvoreB::Percorre_ArvoreB(){
    int i;
    for (i = 0; i < Numero_chaves; i++){
        if (folha == false)
            Filhos[i]->Percorre_ArvoreB();
        cout << " " << Chaves[i];
    }

    if (folha == false)
        Filhos[i]->Percorre_ArvoreB();
}
 

NodeArvoreB *NodeArvoreB::Pesquisa_ArvoreB(char* chave){
    int i = 0;
    while (i < Numero_chaves && (strcmp(chave, Chaves[i]) > 0))
        i++;

    if (strcmp(chave, Chaves[i]) == 0)
        return this;

    if (folha == true)
        return NULL;

    return Filhos[i]->Pesquisa_ArvoreB(chave);
}

void ArvoreB::Insere_ArvoreB(char* chave){
    if (Raiz == NULL){
        Raiz = new NodeArvoreB(Min_ordem, true);
        Raiz->Chaves[0] = chave;  
        Raiz->Numero_chaves = 1;
    }
    else{
        if (Raiz->Numero_chaves == 2*Min_ordem-1){
            NodeArvoreB *Nova_raiz = new NodeArvoreB(Min_ordem, false);
            Nova_raiz->Filhos[0] = Raiz;
 
            Nova_raiz->Divide_Filho(0, Raiz);

            int i = 0;
            if ((strcmp(chave, Nova_raiz->Chaves[0]) > 0)){
                i++;
            }
            Nova_raiz->Filhos[i]->Insere_Nao_Cheio(chave);

            Raiz = Nova_raiz;
        }
        else
            Raiz->Insere_Nao_Cheio(chave);
    }
}

void NodeArvoreB::Insere_Nao_Cheio(char* chave){
    int i = Numero_chaves-1;

    if (folha == true){
        while (i >= 0 && (strcmp(chave,Chaves[i]) < 0)){
            Chaves[i+1] = Chaves[i];
            i--;
        }
 
        Chaves[i+1] = chave;
        Numero_chaves = Numero_chaves+1;
    }
    else{
        while (i >= 0 && (strcmp(chave,Chaves[i]) < 0))
            i--;

        if (Filhos[i+1]->Numero_chaves == 2*Min_ordem-1){
            Divide_Filho(i+1, Filhos[i+1]);

            if ((strcmp(chave,Chaves[i+1]) > 0))
                i++;
        }
        Filhos[i+1]->Insere_Nao_Cheio(chave);
    }
}

void NodeArvoreB::Divide_Filho(int i, NodeArvoreB *y){
    NodeArvoreB *z = new NodeArvoreB(y->Min_ordem, y->folha);
    z->Numero_chaves = Min_ordem - 1;
 
    for (int j = 0; j < Min_ordem-1; j++)
        z->Chaves[j] = y->Chaves[j+Min_ordem];

    if (y->folha == false){
        for (int j = 0; j < Min_ordem; j++)
            z->Filhos[j] = y->Filhos[j+Min_ordem];
    }

    y->Numero_chaves = Min_ordem - 1;

    for (int j = Numero_chaves; j >= i+1; j--)
        Filhos[j+1] = Filhos[j];

    Filhos[i+1] = z;

    for (int j = Numero_chaves-1; j >= i; j--)
        Chaves[j+1] = Chaves[j];
 
    Chaves[i] = y->Chaves[Min_ordem-1];

    Numero_chaves = Numero_chaves + 1;
}

void ArvoreB::Remove(char* chave){
    if (!Raiz){
        cout << "The tree is empty\n";
        return;
    }

    Raiz->Remove(chave);
    if (Raiz->Numero_chaves==0){
        NodeArvoreB *tmp = Raiz;
        if (Raiz->folha)
            Raiz = NULL;
        else
            Raiz = Raiz->Filhos[0];

        delete tmp;
    }
    return;
}
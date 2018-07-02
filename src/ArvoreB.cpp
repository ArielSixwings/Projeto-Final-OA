#include <string.h>
#include "In_OutPuts.hpp"
#include "ArvoreB.hpp"

NodeArvoreB::NodeArvoreB(int aux_min_ordem, bool aux_folha){
    Min_ordem = aux_min_ordem;
    folha = aux_folha;
 
    Chaves = new char*[2*Min_ordem-1];
    for (int i = 0; i < (2*Min_ordem-1); ++i){
        Chaves[i] = new char[9];
    }
    Filhos = new NodeArvoreB *[2*Min_ordem];
    for (int i = 0; i < (2*Min_ordem); ++i){
        Filhos[i] = nullptr;
    }
    PRR = new int[2*Min_ordem-1];
    Posicao_filhos = new int[2*Min_ordem];
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

    for (int i=indice+1; i<Numero_chaves; ++i){
        Chaves[i-1] = Chaves[i];
        PRR[i-1] = PRR[i];
    }
    Numero_chaves--;
 
    return;
}

void NodeArvoreB::Remove_Nao_Folha(int indice){
 
    char* chave = Chaves[indice];
    if (Filhos[indice]->Numero_chaves >= Min_ordem){
        int aux_prr_predecessor;
        char* predecessor = Encontra_Predecessor(indice,&aux_prr_predecessor);
        Chaves[indice] = predecessor;
        PRR[indice] = aux_prr_predecessor;
        Filhos[indice]->Remove(predecessor);
    }
    else if  (Filhos[indice+1]->Numero_chaves >= Min_ordem){
        int aux_prr_sucessor;
        char* sucessor = Encontra_Sucessor(indice,&aux_prr_sucessor);
        Chaves[indice] = sucessor;
        PRR[indice] = aux_prr_sucessor;
        Filhos[indice+1]->Remove(sucessor);
    }

    else{
        merge(indice);
        Filhos[indice]->Remove(chave);
    }
    return;
}

char* NodeArvoreB::Encontra_Predecessor(int indice,int *aux_prr_predecessor){
    NodeArvoreB *atual=Filhos[indice];
    while (!atual->folha)
        atual = atual->Filhos[atual->Numero_chaves];
    *(aux_prr_predecessor) = atual->PRR[atual->Numero_chaves-1];
    return atual->Chaves[atual->Numero_chaves-1];
}

char* NodeArvoreB::Encontra_Sucessor(int indice,int *aux_prr_sucessor){
 
    NodeArvoreB *atual = Filhos[indice+1];
    while (!atual->folha)
        atual = atual->Filhos[0];
    *(aux_prr_sucessor) = atual->PRR[0];
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

    for (int i=filho->Numero_chaves-1; i>=0; --i){ 
        filho->Chaves[i+1] = filho->Chaves[i];
        filho->PRR[i+1] = filho->PRR[i];
    }
    if (!filho->folha){
        for(int i=filho->Numero_chaves; i>=0; --i)
            filho->Filhos[i+1] = filho->Filhos[i];
    }

    filho->Chaves[0] = Chaves[indice-1];
    filho->PRR[0] = PRR[indice-1];
 
    if(!filho->folha)
        filho->Filhos[0] = irmao->Filhos[irmao->Numero_chaves];
 
    Chaves[indice-1] = irmao->Chaves[irmao->Numero_chaves-1];
    PRR[indice-1] = irmao->PRR[irmao->Numero_chaves-1];

    filho->Numero_chaves += 1;
    irmao->Numero_chaves -= 1;
 
    return;
}

void NodeArvoreB::Pega_Chave_Node_Seguinte(int indice){
 
    NodeArvoreB *filho=Filhos[indice];
    NodeArvoreB *irmao=Filhos[indice+1];

    filho->Chaves[(filho->Numero_chaves)] = Chaves[indice];
    filho->PRR[(filho->Numero_chaves)] = PRR[indice];

    if (!(filho->folha))
        filho->Filhos[(filho->Numero_chaves)+1] = irmao->Filhos[0];
 

    Chaves[indice] = irmao->Chaves[0];
    PRR[indice] = irmao->PRR[0];
 

    for (int i=1; i<irmao->Numero_chaves; ++i){ 
        irmao->Chaves[i-1] = irmao->Chaves[i];
        irmao->PRR[i-1] = irmao->PRR[i];
    }
    
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
    filho->PRR[Min_ordem-1] = PRR[indice];
 

    for (int i=0; i<irmao->Numero_chaves; ++i){ 
        filho->Chaves[i+Min_ordem] = irmao->Chaves[i];
        filho->PRR[i+Min_ordem] = irmao->PRR[i];
    }
    
    if (!filho->folha){
        for(int i=0; i<=irmao->Numero_chaves; ++i)
            filho->Filhos[i+Min_ordem] = irmao->Filhos[i];
    }
 
    for (int i=indice+1; i<Numero_chaves; ++i){ 
        Chaves[i-1] = Chaves[i];
        PRR[i-1] = PRR[i];
    }
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
        cout<<Chaves[i]<<"  "<<PRR[i]<<endl;
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

void ArvoreB::Insere_ArvoreB(char* chave,int prr){
    if (Raiz == NULL){
        Raiz = new NodeArvoreB(Min_ordem, true);
        Raiz->Chaves[0] = chave;
        Raiz->PRR[0] = prr;
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
            Nova_raiz->Filhos[i]->Insere_Nao_Cheio(chave,prr);

            Raiz = Nova_raiz;
        }
        else
            Raiz->Insere_Nao_Cheio(chave,prr);
    }
}

void NodeArvoreB::Insere_Nao_Cheio(char* chave,int prr){
    int i = Numero_chaves-1;

    if (folha == true){
        while (i >= 0 && (strcmp(chave,Chaves[i]) < 0)){
            PRR[i+1] = PRR[i];
            Chaves[i+1] = Chaves[i];
            //cout<<"na troca"<<PRR[i+1]<<endl;
            i--;
        }
        
        Chaves[i+1] = chave;
        PRR[i+1] = prr;
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
        Filhos[i+1]->Insere_Nao_Cheio(chave,prr);
    }
}

void NodeArvoreB::Divide_Filho(int i, NodeArvoreB *y){
    NodeArvoreB *z = new NodeArvoreB(y->Min_ordem, y->folha);
    z->Numero_chaves = Min_ordem - 1;
    
    int j;
    for ( j = 0; j < Min_ordem-1; j++){
        z->Chaves[j] = y->Chaves[j+Min_ordem];
        z->PRR[j] = y->PRR[j+Min_ordem];
    }
    if (y->folha == false){
        for (int j = 0; j < Min_ordem; j++)
            z->Filhos[j] = y->Filhos[j+Min_ordem];
    }

    y->Numero_chaves = Min_ordem - 1;

    for ( j = Numero_chaves; j >= i+1; j--)
        Filhos[j+1] = Filhos[j];

    Filhos[i+1] = z;

    for ( j = Numero_chaves-1; j >= i; j--){
        Chaves[j+1] = Chaves[j];
        PRR[j+1] = PRR[j];
    }
 
    Chaves[i] = y->Chaves[Min_ordem-1];
    PRR[i] = y->PRR[Min_ordem-1];

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

void ArvoreB::Escreve_Arquivo(int ordem, char* nomearquivo){
    FILE * arquivo_Arvore;
    char* nometodo = (char*) malloc(sizeof(char) + 9);
    sprintf(nometodo, "indice%s.bt", nomearquivo);
    arquivo_Arvore = fopen(nometodo, "w+");
    Raiz->Escreve_Interno(arquivo_Arvore, ordem);
    free(nometodo);
    fclose(arquivo_Arvore);
}

int NodeArvoreB::Escreve_Interno(FILE * arquivo_Arvore, int ordem){
    if(this == nullptr){
        return -1;
    }
    else{
        int i, k = 0;
        Filhos[Numero_chaves+1] = nullptr;  
        while(Filhos[k] != nullptr){// && (k < (ordem))){
            k++;
        }
        for(i = 0; i < k; i++){
            Posicao_filhos[i] =  Filhos[i]->Escreve_Interno(arquivo_Arvore, ordem);
        }
        for (; i < 2*Min_ordem; ++i){
            Posicao_filhos[i] = -1;
        }
        int tamanho_linha = (((ordem-1)*12) + 1 + (3*ordem));  
        int tamanho = ftell(arquivo_Arvore);
        tamanho /= tamanho_linha;
        for(i = 0; i < (ordem - 1); i++){
            if(i < Numero_chaves){
                fprintf(arquivo_Arvore,"%s %.2d ", this->Chaves[i], this->PRR[i]);
            }else{
                fprintf(arquivo_Arvore,"*********** ");
            }
        }
        for(i = 0; i < ordem; i++){
            if (this->Posicao_filhos[i] == -1){
                fprintf(arquivo_Arvore, " %d", this->Posicao_filhos[i]);
            }else{
                fprintf(arquivo_Arvore, " %.2d", this->Posicao_filhos[i]);
            }
        }
        fprintf(arquivo_Arvore, "\n");
        return tamanho;
    }
}

int NodeArvoreB::Busca_Interno(FILE * arquivo_Arvore,
                                char* chave,
                                int ordem,
                                int& numero_seeks,
                                int tamanho_linha){
    int i = 0;
    while (i < Numero_chaves && (strcmp(chave, Chaves[i]) > 0)){
        i++;
    }
    if (strcmp(chave, Chaves[i]) == 0){
        numero_seeks++;
        return PRR[i];
    }

    //se for folha
    if (Posicao_filhos[0] == -1){
        //registro não encontrado
        cout<<"Registro não esta presente na arvore"<<endl;
        return -1;
    }
    //carrega filho i 
    //faz pesquisa no filho i
    fseek(arquivo_Arvore, (Posicao_filhos[i]*tamanho_linha), SEEK_SET);
    numero_seeks++;
    this->Leitura_Pagina(arquivo_Arvore,ordem);
    return this->Busca_Interno(arquivo_Arvore,chave,ordem,numero_seeks,tamanho_linha);
}

void NodeArvoreB::Leitura_Pagina(FILE *arquivo_Arvore, int ordem){
    int prr, prr_filhos;
    char *aux_chave = new char[8];
    char *aux_prr = new char[3];
    char *aux_posicao_filhos = new char[4];

    for (int i = 0; i < ordem-1; ++i){
        fread(aux_chave, sizeof(char), 9, arquivo_Arvore);
        fread(aux_prr, sizeof(char), 3, arquivo_Arvore);
        if (aux_chave[0] != '*'){
            aux_prr[2] = '\0';
            prr = atoi(aux_prr);
            for (int j = 0; j < 8; ++j){
                Chaves[i][j] = aux_chave[j];
            }
            Chaves[i][8] ='\0';
            PRR[i] = prr;
            Numero_chaves++;
        }
    }
    for (int i = 0; i < ordem; ++i){
        fread(aux_posicao_filhos, sizeof(char), 3, arquivo_Arvore);
        aux_posicao_filhos[3] = '\0';
        prr_filhos = atoi(aux_posicao_filhos);
        Posicao_filhos[i] = prr_filhos;
    }
    delete[] aux_chave;
    delete[] aux_prr;
    delete[] aux_posicao_filhos;
}

int ArvoreB::Busca_Registro(char* chave, int ordem, char* nomearquivo, int whichcase){
    int tamanho_linha = (((ordem-1)*12) + 1 + (3*ordem));
    int numero_seeks = 0;
    //aloca espaço para o nó que será usado para pesquisa
    Raiz = new NodeArvoreB(Min_ordem, false);
    
    FILE * arquivo_Arvore;
    char* nometodo = (char*) malloc(sizeof(char) + 9);
    sprintf(nometodo, "indice%s.bt", nomearquivo);
    arquivo_Arvore = fopen(nometodo, "r");

    //Faz leitura da raiz no arquivo de arvore
    fseek(arquivo_Arvore, -tamanho_linha, SEEK_END);
    numero_seeks++;
    Raiz->Leitura_Pagina(arquivo_Arvore,2*Min_ordem);

    //busca da chave na arvore b
    int prr_chave = Raiz->Busca_Interno(arquivo_Arvore,chave,ordem,numero_seeks,tamanho_linha);
    if (prr_chave != -1){
        if(!whichcase){
            return prr_chave;
        }
        FindInTheRegister(nomearquivo, prr_chave);
    }
    fclose(arquivo_Arvore);
    free(nometodo);
    return numero_seeks;
}
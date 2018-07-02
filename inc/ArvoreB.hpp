#ifndef ARVOREB_H
#define ARVOREB_H

#include <iostream>
#include <string.h>
#include <cstddef>
using namespace std;
 
typedef struct 
{
    char* chave;
    int PRR;
}IndicePrimario;

// No arvore B
class NodeArvoreB
{
public:
    char **Chaves;  // para armazenar chaves do tipo char*
    int *PRR;
    int *Posicao_filhos; 
    int Min_ordem;      // para determinar quantidade minima de chaves/ponteiro
    NodeArvoreB **Filhos; // array para os filhos do nó
    int Numero_chaves;     // numero de chaves atualmente presenter no nó
    bool folha; // indica de o nó é folha ou não
public:
    NodeArvoreB(int _Min_chaves, bool _folha);   // Construtor da classe NodeArvoreB
 
    void Percorre_ArvoreB();
    /*Insere em um nó que não estiver cheio*/
    NodeArvoreB *Pesquisa_ArvoreB(char* chave);   // returns NULL if chave is not present.
    
    int Encontra_Chave(char* chave);
    
    void Insere_Nao_Cheio(char* chave,int PRR);
    
    /*Faz split em um determinado nó*/
    void Divide_Filho(int i, NodeArvoreB *y);

    void Remove(char *chave);
    
    void Remove_Folha (int indice);

    void Remove_Nao_Folha(int indice);

    char* Encontra_Predecessor(int indice,int *aux_prr_predecessor);
    
    char* Encontra_Sucessor(int indice,int *aux_prr_sucessor);

    void Preenche_Node_Filho(int indice);

    void Pega_Chave_Node_Anterior(int indice);

    void Pega_Chave_Node_Seguinte(int indice);
 
    void merge(int indice);

    int Escreve_Interno(FILE * arquivo_Arvore, int ordem);

    void Leitura_Pagina(FILE *arquivo_Arvore, int ordem);

    int Busca_Interno(FILE * arquivo_Arvore,
                                char* chave,
                                int ordem,
                                int& numero_seeks,
                                int tamanho_linha);

// Make ArvoreB friend of this so that we can access private members of this
// class in ArvoreB functions
    friend class ArvoreB;
};
 
// A ArvoreB
class ArvoreB
{
public:
    NodeArvoreB *Raiz;
    int Min_ordem;   
public:
    // Constructor (Initializes tree as empty)
    ArvoreB(int _Min_ordem)
    {  Raiz = NULL;  Min_ordem = _Min_ordem; }
 
    // function to PercorreArvoreB the tree
    void Percorre_ArvoreB()
    {  if (Raiz != NULL) Raiz->Percorre_ArvoreB(); }
 
    // function to PesquisaArvoreB a key in this tree
    NodeArvoreB* Pesquisa_ArvoreB(char* chave)
    {  return (Raiz == NULL)? NULL : Raiz->Pesquisa_ArvoreB(chave); }
 
    // The main function that inserts a new key in this B-Tree
    void Insere_ArvoreB(char* chave,int PRR);

    void Remove(char* chave);

    void Escreve_Arquivo(int ordem);

    int Busca_Registro(char* chave,int ordem);
    //friend class NodeArvoreB;
};

#endif
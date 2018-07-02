#include "ArvoreB.hpp"
#include "In_OutPuts.hpp"
#include "EscreveArvoreB.hpp"


int main(){
    int ordem;
    int size;
    FILE * exist1;
    FILE * exist2;
    unsigned int option;
    char choice[50];
    char name1[50];
    char name2[50];
    char fullname1[50];
    char fullname2[50];
    char buf[32];
    printf("------------------------------------\n");
    printf("----         Trabalho 2         ----\n");
    printf("-        [1] - Ver Arquivo         -\n");
    printf("-   [2] - Fazer Índice(Árvore B)   -\n");
    printf("- [3] - Adicionar Aluno no Arquivo -\n");
    printf("-  [4] - Remover Aluno do Arquivo  -\n");
    printf("-      [5] - Buscar Aluno(Chave)   -\n");
    printf("----         [6] - Exit         ----\n");
    printf("------------------------------------\n");
    printf("Choose one: ");
    scanf(" %[^\n]", choice);
    option = atoi(choice);
    system("clear");
    switch(option){
        case 1:
            printf("\n");
            printf("Qual o tipo do arquivo que deseja-se vizualizar? \n");
            printf("-------- [0] - .bt --------\n");
            printf("-------- [1] - .txt --------\n");
            printf("Choose one: ");
            scanf(" %[^\n]", choice);
            option = atoi(choice);
            system("clear");
            if(option == 0){
                printf("Arquivos Disponíveis:\n");
                printf("--------------------\n");
                printf("\n\n");
                system("ls *.bt");
                printf("\n\n");
                printf("--------------------\n");
                printf("\n");
                printf("Escolha algum dos arquivos acima (escreva o nome sem a terminação .bt)\n");
                printf("Choose one: ");
                scanf(" %[^\n]", name1);
                sprintf(fullname1, "%s.bt", name1);
                exist1 = fopen(fullname1, "r");
                if(exist1 == NULL){
                    printf("Arquivo selecionado não foi encontrado!\n");
                    break;
                }else{
                    sprintf(buf, "cat %s.bt", name1);
                    printf("\n\n");
                    system("clear");
                    printf("Preview do Arquivo %s:\n\n", fullname1);
                    system(buf);
                    printf("\n\n");
                    main();
                    break;
                }
            }else if(option == 1){
                printf("Arquivos Disponíveis:\n");
                printf("--------------------\n");
                printf("\n\n");
                system("ls *.txt");
                printf("\n\n");
                printf("--------------------\n");
                printf("\n");
                printf("Escolha algum dos arquivos acima (escreva o nome sem a terminação .txt)\n");
                printf("Choose one: ");
                scanf(" %[^\n]", name1);
                sprintf(fullname1, "%s.txt", name1);
                exist1 = fopen(fullname1, "r");
                if(exist1 == NULL){
                    printf("Arquivo selecionado não foi encontrado!\n");
                    break;
                }else{
                    sprintf(buf, "cat %s.txt", name1);
                    printf("\n\n");
                    system("clear");
                    printf("Preview do Arquivo %s:\n\n", fullname1);
                    system(buf);
                    printf("\n\n");
                    main();
                    break;
                }
            }else{
                printf("Infelizmente o vizualizador apenas funciona com os tipos apresentados!\n");
                break;
            }
        case 2:
            printf("\n");
            printf("Arquivos Disponíveis:\n");
            printf("--------------------\n");
            printf("\n\n");
            system("ls *.txt");
            printf("\n\n");
            printf("--------------------\n");
            printf("\n");
            printf("Escolha algum dos arquivos acima (escreva o nome sem a terminação .txt)\n");
            printf("Choose one: ");
            scanf(" %[^\n]", name1);
            sprintf(fullname1, "%s.txt", name1);
            exist1 = fopen(fullname1, "r");
            if(exist1 == NULL){
                printf("Arquivo selecionado não foi encontrado!\n");
                break;
            }else{
                fclose(exist1);
                printf("\n");
                printf("Escolha a ordem da árvore B: ");
                scanf(" %[^\n]", name2);
                ordem = atoi(name2);
                if(ordem %2 == 0){
                    ArvoreB teste((ordem / 2));
                    int size = HowManyLines(fullname1);
                    ChavePrimaria* Chaves = BuildPrimaryKey(name1, size);
                    for(int i = 0; i < size; i++){
                        if (Chaves[i].chave[0] != '*'){
                            teste.Insere_ArvoreB(Chaves[i].chave,Chaves[i].prr);
                        }
                    }
                    teste.Escreve_Arquivo(ordem, name1);
                    sprintf(buf, "cat indice%s.bt", name1);
                    system("clear");
                    printf("Preview do Arquivo %s:\n\n", buf);
                    system(buf);
                    printf("\n\n");
                    main();
                    break;
                }else{
                    ArvoreB teste((ordem / 2) + 1);
                    int size = HowManyLines(fullname1);
                    ChavePrimaria* Chaves = BuildPrimaryKey(name1, size);
                    for(int i = 0; i < size; i++){
                        if (Chaves[i].chave[0] != '*'){
                            teste.Insere_ArvoreB(Chaves[i].chave,Chaves[i].prr);
                        }
                    }
                    teste.Escreve_Arquivo(ordem, name1);
                    sprintf(buf, "cat indice%s.bt", name1);
                    system("clear");
                    printf("Preview do Arquivo %s:\n\n", buf);
                    system(buf);
                    printf("\n\n");
                    main();
                    break;
                }
            }
        case 3:
            printf("\n");
            printf("Arquivos Disponíveis:\n");
            printf("--------------------\n");
            printf("\n\n");
            system("ls *.txt");
            printf("\n\n");
            printf("--------------------\n");
            printf("\n");
            printf("Escolha algum dos arquivos acima (escreva o nome sem a terminação .txt)\n");
            printf("Choose one: ");
            scanf(" %[^\n]", name1);
            sprintf(fullname1, "%s.txt", name1);
            exist1 = fopen(fullname1, "r");
            if(exist1 == NULL){
                printf("Arquivo selecionado não foi encontrado!\n");
                break;
            }else{
                fclose(exist1);
                size = HowManyLines(fullname1);
                AddStudent(name1, size);
                printf("\n");
                printf("Escolha a ordem da árvore B: ");
                scanf(" %[^\n]", name2);
                ordem = atoi(name2);
                if(ordem %2 == 0){
                    ArvoreB teste((ordem / 2));
                    int size = HowManyLines(fullname1);
                    ChavePrimaria* Chaves = BuildPrimaryKey(name1, size);
                    for(int i = 0; i < size; i++){
                        if (Chaves[i].chave[0] != '*'){
                            teste.Insere_ArvoreB(Chaves[i].chave,Chaves[i].prr);
                        }
                    }
                    teste.Escreve_Arquivo(ordem, name1);
                    printf("\n\n");
                    main();
                    break;
                }else{
                    ArvoreB teste((ordem / 2) + 1);
                    int size = HowManyLines(fullname1);
                    ChavePrimaria* Chaves = BuildPrimaryKey(name1, size);
                    for(int i = 0; i < size; i++){
                        if (Chaves[i].chave[0] != '*'){
                            teste.Insere_ArvoreB(Chaves[i].chave,Chaves[i].prr);
                        }
                    }
                    teste.Escreve_Arquivo(ordem, name1);
                    printf("\n\n");
                    main();
                    break;
                }
            }
        case 4:
            printf("\n");
            printf("Arquivos Disponíveis:\n");
            printf("--------------------\n");
            printf("\n\n");
            system("ls *.txt");
            printf("\n\n");
            printf("--------------------\n");
            printf("\n");
            printf("Escolha algum dos arquivos acima (escreva o nome sem a terminação .txt)\n");
            printf("Choose one: ");
            scanf(" %[^\n]", name1);
            sprintf(fullname1, "%s.txt", name1);
            sprintf(fullname2, "indice%s.bt", name1);
            exist1 = fopen(fullname1, "r");
            exist2 = fopen(fullname2, "r");
            if(exist1 == NULL){
                printf("Arquivo selecionado não foi encontrado!\n");
                break;
            }else{
                fclose(exist1);
                if(exist2 == NULL){
                    printf("Arquivo referente a árvore binária do arquivo não foi encontrado!\n");
                }else{
                    fclose(exist2);
                    printf("Insira a chave primária do arquivo que se deseja a remoção: \n");
                    scanf(" %[^\n]", name2);
                    printf("Informe qual a ordem da árvore binária que contém a chave primária: \n");
                    scanf(" %[^\n]", choice);
                    ordem = atoi(choice);
                    if(ordem %2 == 0){
                        ArvoreB Arvore_Atual((ordem / 2));
                        int prr = Arvore_Atual.Busca_Registro(name2, ordem, name1, 0);
                        RemoveRegisterFromFile(name1, prr);
                        int size = HowManyLines(fullname1);
                        ChavePrimaria* Chaves = BuildPrimaryKey(name1, size);
                        for(int i = 0; i < size; i++){
                            if (Chaves[i].chave[0] != '*'){
                                Arvore_Atual.Insere_ArvoreB(Chaves[i].chave,Chaves[i].prr);
                            }
                        }
                        Arvore_Atual.Escreve_Arquivo(ordem, name1);
                        main();
                        break;
                    }else{
                        ArvoreB Arvore_Atual((ordem / 2) + 1);
                        int prr = Arvore_Atual.Busca_Registro(name2, ordem, name1, 0);
                        RemoveRegisterFromFile(name1, prr);
                        int size = HowManyLines(fullname1);
                        ChavePrimaria* Chaves = BuildPrimaryKey(name1, size);
                        for(int i = 0; i < size; i++){
                            if (Chaves[i].chave[0] != '*'){
                                Arvore_Atual.Insere_ArvoreB(Chaves[i].chave,Chaves[i].prr);
                            }
                        }
                        Arvore_Atual.Escreve_Arquivo(ordem, name1);
                        main();
                        break;
                    }
                }
            }
        case 5:
            ArvoreB Arvore_Atual((4 / 2));
            //Arvore_Atual.Insere_ArvoreB("jorge",0);
            int numero_seeks = Arvore_Atual.Busca_Registro("AND71929",4, "lista1", 1);
            cout<<"Numero de seeks para encontrar registro: "<<numero_seeks<<endl;
            // BTreePrinter print_arvore;
            // print_arvore.print(Arvore_Atual);
            main();
            break;
        // case 6:
        //     return 1;
        // default:
        //     return 1;
    }
    return 0;
}
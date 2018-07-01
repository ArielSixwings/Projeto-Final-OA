// Driver program to test above functions
#include "ArvoreB.hpp"
#include "In_OutPuts.hpp"
#include "EscreveArvoreB.hpp"
int main(){
    int ordem;
    int size;
    FILE * exist1;
    unsigned int option;
    char choice[50];
    char name1[50];
    char name2[50];
    // char student[30];
    char fullname1[50];
    // char fullname2[50];
    char buf[32];
    printf("------------------------------------\n");
    printf("----         Trabalho 2         ----\n");
    printf("-        [1] - Ver Arquivo         -\n");
    printf("-   [2] - Fazer Índice(Árvore B)   -\n");
    printf("- [3] - Atualizar Aluno no Arquivo -\n");
    printf("- [4] - Adicionar Aluno no Arquivo -\n");
    printf("-  [5] - Remover Aluno do Arquivo  -\n");
    printf("-      [6] - Buscar Aluno(Chave)   -\n");
    printf("----         [7] - Exit         ----\n");
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
                    //----------------------------
                    BTreePrinter printer;
                    printer.print(teste);
                    teste.EscreveArvoreB(ordem);
                    //system("clear");
                    //printf("Preview do Arquivo indicelista.bt:\n\n" );
                    //system("cat indicelista.bt");
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
                    BTreePrinter printer;
                    printer.print(teste);
                    // system("clear");
                    // printf("Preview do Arquivo indicelista.bt:\n\n");
                    // system("cat indicelista.bt");
                    printf("\n\n");
                    main();
                    break;
                }
            }
        case 3:
            return 1;
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
            exist1 = fopen(fullname1, "r");
            if(exist1 == NULL){
                printf("Arquivo selecionado não foi encontrado!\n");
                break;
            }else{
                size = HowManyLines(fullname1);
                AddStudent(name1, size);
            }
        case 5:
            RemoveRegisterFromFile("lista1", 1);
            return 1;
        case 6:
            return 1;     
        case 7:
            return 1;
    }
    

    // cout<<"Inicialmente\n\n\n"<<endl; //é o print do C++
    // teste.Percorre_ArvoreB();

    // teste.Remove("CAR62364");
    // cout<<"\n\n";
    // teste.Percorre_ArvoreB();
    return 0;
}
#include<stdio.h>
#include<string.h>
#include<locale.h>//biblioteca para compreender simbolos (ç, ^, ´), comando "setlocale(LC_ALL,"Portuguese");
#include<ctype.h> //biblioteca de manipulação de caracteres

int i=0; //Variável do índice para troca de posição na função Registro
struct{ //Estrutura de cadastro
    char nome[30];
    char email[50];
    char senha[100];
    float nota1, nota2;
}dados_cadastro[100];//O vetor da Struct cadastro que define o numero de linhas "i".

int logado; //Coordenada para localizar a posição do vetor da Struct cadastro[100]

void registro(){ //Função global de registro de usuário

    int arroba = 0, ponto = 0, antesPonto = 0, depois_ponto = 0, x, a=0;
    char c;

        printf("\n-Informe o nome do usuário: ");
        fflush(stdin);
        scanf("%[^\n]", dados_cadastro[i].nome);

            for(int l=0; l < strlen(dados_cadastro[i].nome); l++) //L vai ser o contador para verificar cada letra em nome
            {
                if(isalpha(dados_cadastro[i].nome[l]) == 0) //isalpha verifica se cada letra é alfabética, 0 = False
                    {
                    printf("Nome Inválido!"); //se falso imprime nome inválido
                    sleep(1);
                    system("cls");
                    main(); //volta ao login
                    }
            }
        printf("-Informe o e-mail: ");
        fflush(stdin);
        gets(dados_cadastro[i].email);
        int tam=strlen(dados_cadastro[i].email); //Utilizamos o comando "strlen" para atribuir o tamanho da string

            for (x = 0; x < tam; x++)//Laço de repetição que vai verificar o indice até o tamanho da string
            {
                if(dados_cadastro[i].email[x] == '@') //Se ele identificar na string um '@' fará os testes a seguir:
                    {
                      if (arroba) //Faz um teste booleano para verificar a váriavel "arroba".
                        break; //Para este "if" se na repetição "@" for == true.
                        arroba = 1; //Se identificar um '@', torna a variável "arroba" == true
                      if (x < 3)
                        break; // Se o "@" vier antes de pelo menos 3 caracteres, para a execução.
                    }
                else if (arroba) // Se na repetição ele já encontrou o '@'.
                {
                    if (ponto) // Se na repetição já encontrou . depois de @
                        depois_ponto++;
                    else if(dados_cadastro[i].email[x] == '.') //Senão verifica se na posião após o "@" existe algum "."
                    {
                        ponto = 1;
                        if (antesPonto < 3)
                        break; // Se o "." depois de "@" vier antes de pelo menos 3 caracteres,para a execução.
                    }
                    else
                        antesPonto++;
                }
            } // Fim do laço de repetição "for".
        for(int y=0; y<i; y++) //laço de repetição para verificar se um email já foi cadastrado
        {
            if(strcmp(dados_cadastro[y].email, dados_cadastro[i].email)==0) //verifica se já existe um email dentro de cadastro
              {
                    printf("\t->Este email já foi cadastrado!<-"); //caso seja verdadeiro, imprime uma mensagem na tela e retorna ao menu
                    sleep(2);
                    system("cls");
                    main();
              }
        }

        if (x == tam && depois_ponto > 1) //Se o indice alcançar o tamanho da string e a variável depois_ponto, valida o e-mail e segue o registro
        {
            printf("-Digite sua senha: ");
            fflush(stdin);
            gets(dados_cadastro[i].senha);
        }
        else //Senão, mostra que o e-mail é inválido.
        {
            printf("E-mail Inválido\n");
            sleep(1);
            system("cls");
            registro(); //Retorna para o inicio do registro caso o e-mail seja invalidado.
        }
} //Fim da função de registros do usuário


void main(){ //Função principal do código

  int op_menu, log_efetuado, a=0;
  char login[100], senha[50], c;

  setlocale(LC_ALL,"Portuguese"); //Função que converte o texto impresso na tela para o Português.
  printf("\t--------CADASTRO---------");
  printf("\n 1-> Para se cadastrar\n 2-> Para logar com uma conta existente\n  R:");
  scanf("%d", &op_menu);
  system("cls");
        if(op_menu==1 || op_menu==2)
        { //Teste para verificar se a entrada é uma das opções válidas.
            switch(op_menu)
            { //Estrutura de decisão para opções do menu

                case 1: //Opção que realiza a chamada da função "resgistro", para cadasto do usuário.
                    registro();

                    printf("\n\t>Usuário cadastrado<\n\n");
                    sleep(1); //Comando com temporizador do tempo de exibição
                    i++;
                    system("cls"); //Comando para limpar a tela
                    main();

                case 2: //Opção para efetuar o login do usuário
                    printf("\n-Digite seu email: ");
                    fflush(stdin);
                    gets(login); //entrada do e-mail para login


                    printf("-Digite sua senha: ");
                    fflush(stdin);

                    while(c!=13) //valor de enter na tabela ASCII
                    {
                            c=getch(); //Variável "c" recebe a letra digitada
                            if(isprint(c)) //verifica se é um valor a qual pode ser imprimido
                            {
                               senha[a]=c; //senha na posição do vetor recebe a letra da variavel C
                               a++; //contador de C
                               printf("*"); //Imprime o "*"
                            }
                            else if(c==8&&a) //Valor do "BACKSPACE" na tabela ASCII
                            {
                               a--; //Contador para apagar a letra
                               senha[a]='\0'; //Retorna o valor da posição do vetor em NULL
                               printf("\b \b"); //Apaga o "*"
                            }
                    }

                    for(int j=0; j<100; j++) //Laço de repetição para testar se as informações são iguais as inseridas em cadastro.
                    {
                            //Uso da função "strcmp" para comparar os valores
                            if(strcmp(dados_cadastro[j].email,login) == 0 && strcmp(dados_cadastro[j].senha,senha) == 0)
                            {
                                printf("\n\t>Login efetuado<  \n\n");
                                logado=j;
                                sleep(1); //Comando com temporizador do tempo de exibição
                                system("cls"); //Comando para limpar a tela
                                menu();
                                break;
                            }
                    }
                    default: //Caso não seja a opção de cadastro/login.
                        system("cls");
                        printf("\n>Email ou senha incorreto<");
                        sleep(2);
                        system("cls");
                        main();
            } //fim do switch
        } //fim do if
        else //Senão for uma entrada válida, limpa o buffer do teclado e retorna para a função Main.
            fflush(stdin);
            main();
} //Fim do bloco Main()

void menu(){ //Menu de opções para o usuário após o login.

  setlocale(LC_ALL,"Portuguese"); //Função que converte o texto impresso na tela para o Português.
  int op_menu, op_sair;
     //Enunciado do menu após o login, com o nome de usuário logado.
     printf("\t---------MENU---------\n\t   > Bem Vindo %s <  \n\n  1->Questionários\n  2->Notas\n  3->Média\n  4->Sair\n  R:",   dados_cadastro[logado].nome);
     scanf("%d", &op_menu);
     if(op_menu>=1 && op_menu<=4)
     {
        switch(op_menu)
        { //Estrutura de decisão para opções do menu

          case 1: //Caso 1, realiza a chamada da função "questionário"
            system("cls");
            questionario();

          case 2: //Caso 2, informa as notas do usuário.
            system("cls");
            printf("\n  Aluno: %s \n\tNota do questionário 1: %f\n\tNota do questionário 2: %f\n", dados_cadastro[logado].nome, dados_cadastro[logado].nota1, dados_cadastro[logado].nota2); //Função que mostra as notas do usuário na tela.
                if(dados_cadastro[logado].nota1>7 && dados_cadastro[logado].nota2<7) //Teste para comparar se a primeira nota está acima da média.
                    printf("\n\n> Podemos melhorar a nota do Questionário 2! <\n->Refaça o teste para obter uma melhor nota.");
                    else if(dados_cadastro[logado].nota1<7 && dados_cadastro[logado].nota2>7) //Teste para comparar se a segunda nota está acima da média.
                         printf("\n\n> Podemos melhorar a nota do Questionário 1! <\n->Refaça o teste para obter uma melhor nota.");
                        else if(dados_cadastro[logado].nota1<7 && dados_cadastro[logado].nota2<7) //Teste para comparar se as duas notas estão abaixo da média.
                            printf("\n\n> Todas as notas estão abaixo da Média! <\n->Refaça o testes para obter melhores notas.");
                            else //Senão for nenhuma das opções anteriores, as duas notas estão acima da média.
                                printf("\n\n> Parabéns! <\n  Suas notas estão acima da Média!!!");
            sleep(4); //Comando com temporizador do tempo de exibição
            system("cls");
            menu();

          case 3: //Caso 3, informa a média do usuário.
            system("cls");
            printf("\n  ALuno: %s \n\tMédia Geral: %f", dados_cadastro[logado].nome, (dados_cadastro[logado].nota1+dados_cadastro[logado].nota2)/2);
                if((dados_cadastro[logado].nota1+dados_cadastro[logado].nota2)/2>7) //Teste para verificar se a média é maior que 7.
                    printf("\n\n > PARABÉNS <\n ->Você foi APROVADO!!!");
                    else //Senão for maior que 7, informa o usuário.
                        printf("\n\n > NÃO FOI DESTA VEZ <\n ->Você foi REPROVADO!!!\n ->Repita os Testes e Tente Novamente");
            sleep(3);
            system("cls");
            menu();

          case 4: //Caso 4, retorna ao menu anterior.
            system("cls");
            printf("\nDeseja sair?\n    1->Sim\n    2->Não\n    R:");
            scanf("%d", &op_sair);
            system("cls");

              if(op_sair==1) //Se pressionar um, retorna ao menu.
              main();

              else //Senão, mantém no menu de notas/média.
              menu();

          default:
            system("cls");
            menu();
        } //fim do switch
    } //fim do if
    else
      fflush(stdin);
      system("cls");
      menu();
}

void questionario(){ // Inicio do bloco de questionário
    int quest;
    char q1[4], q2[4];

        setlocale(LC_ALL,"Portuguese"); //Função que converte o texto impresso na tela para o Português.
        printf("\t--------Questionários---------");
        printf("\n->Selecione o questionário que deseja responder:\n   1->Sistemas Financeiros\n   2->Instituições\n   3->Retornar ao menu anterior\n   R:");
        scanf("%d", &quest);
        system("cls");
        if(quest>=1 && quest<=3)
        { //Válidação para a entrada inserida (neste caso precisa ser numérica).
            switch(quest)
            { //Estrutura de decisão para selecionar o Questionário e receber as respostas direcionadas
                case 1: //Caso 1, apresenta as questões relacionadas ao Questionário 1
                    printf("Questionario 1!");
                    printf("\n  1. Uma facilidade decorrente da função de prestação de serviços de gerenciamento de recursos desempenhada pelo Sistema Financeiro Nacional é a:\n   (A)Intermediação financeira entre agentes.\n   (B)Disponibilização de um serviço de guarda limitado a bens de luxo.\n   (C)Disponibilização de seguros para as mais diferentes finalidades.\n   (D)Possibilidade de emissão de papel-moeda por bancos privados.\n    R:");
                    fflush(stdin);
                    scanf("%c", &q1[0]);
                        if(q1[0]=='a')
                      //Caso a resposta esteja correta, armazena a pontuação no vetor nota1, da Struct de Cadastro
                        dados_cadastro[logado].nota1=dados_cadastro[logado].nota1+2.5;

                    printf("\n  2. O Conselho Monetário Nacional (CMN) é o órgão\n   (A)Subordinado hierarquicamente ao Banco Central do Brasil.\n   (B)Composto pelos diretores do Banco Central do Brasil.\n   (C)Deliberativo máximo do Sistema Financeiro Nacional.\n   (D)Subordinado ao Ministro da Economia.\n    R:");
                    fflush(stdin);
                    scanf("%c", &q1[1]);
                        if(q1[1]=='b')
                        dados_cadastro[logado].nota1=dados_cadastro[logado].nota1+2.5;

                    printf("\n  3. É uma atribuição do Banco Central do Brasil (BACEN)\n    (A)Definir as condições e os limites de emissão de papel-moeda.\n    (B)Autorizar o funcionamento de instituições financeiras e promover a fiscalização delas.\n    (C)Eleger os administradores de todas as instituições financeiras privadas.\n    (D)Fiscalizar o funcionamento de sociedades seguradoras.\n     R:");
                    fflush(stdin);
                    scanf("%c", &q1[2]);
                        if(q1[2]=='a')
                        dados_cadastro[logado].nota1=dados_cadastro[logado].nota1+2.5;

                    printf("\n  4. O órgão responsável pela proteção da captação de poupança popular em investimentos realizados em planos de previdência complementar aberta é:\n    (A)O Banco Central do Brasil (BACEN)\n    (B)A Comissão de Valores Mobiliários (CVM)\n    (C)O Conselho Monetário Nacional (CMN)\n    (D)A Superintendência de Seguros Privados (Susep)\n     R:");
                    fflush(stdin);
                    scanf("%c", &q1[3]);
                        if(q1[3]=='b')
                        dados_cadastro[logado].nota1=dados_cadastro[logado].nota1+2.5;

                    system("cls"); //Comando para limpar a tela
                    break;

                case 2: //Caso 2, apresenta as questões relacionadas ao Questionário 2
                    printf("Questionario 2!");
                    printf("\n  1. É uma atribuição do Banco Central do Brasil (BACEN)\n    (A)Definir as condições e os limites de emissão de papel-moeda.\n    (B)Autorizar o funcionamento de instituições financeiras e promover a fiscalização delas.\n    (C)Eleger os administradores de todas as instituições financeiras privadas.\n    (D)Fiscalizar o funcionamento de sociedades seguradoras.\n     R:");
                    fflush(stdin);
                    scanf("%c", &q2[0]);
                        if(q2[0]=='a')
                      //Caso a resposta esteja correta, armazena a pontuação no vetor nota2, da Struct de Cadastro
                        dados_cadastro[logado].nota2=dados_cadastro[logado].nota2+2.5;

                    printf("\n   2. O órgão responsável pela proteção da captação de poupança popular em investimentos realizados em planos de previdência complementar aberta é:\n    (A)O Banco Central do Brasil (BACEN)\n    (B)A Comissão de Valores Mobiliários (CVM)\n    (C)O Conselho Monetário Nacional (CMN)\n    (D)A Superintendência de Seguros Privados (Susep)\n     R:");
                    fflush(stdin);
                    scanf("%c", &q2[1]);
                        if(q2[1]=='b')
                        dados_cadastro[logado].nota2=dados_cadastro[logado].nota2+2.5;

                    printf("\n  3. O cadastro dos dados dos clientes das instituições financeiras:\n    (A)Deve reunir o maior número de informações, independentemente da atualização desse cadastro, para a prevenção de lavagem de dinheiro.\n    (B)Deve estar completo e atualizado para auxiliar na verificação da capacidade financeira desses clientes com o objetivo de prevenir o crime de lavagem de dinheiro.\n    (C)Pode ser atualizado pelos canais de atendimento telefônico, sem a necessidade da comprovação desses dados.\n    (D)Pode ser atualizado, a qualquer momento, a critério dessas instituições\n     R:");
                    fflush(stdin);
                    scanf("%c", &q2[2]);
                        if(q2[2]=='a')
                        dados_cadastro[logado].nota2=dados_cadastro[logado].nota2+2.5;

                    printf("\n  4. Quanto ao registro das operações dos clientes, as instituições financeiras reguladas pelo BACEN são obrigadas a mantê-lo integralmente:\n    (A)Sem identificar esses clientes, pelo prazo mínimo de cinco anos.\n    (B)Sem identificar esses clientes, pelo prazo mínimo de dez anos.\n    (C)Identificando esses clientes, pelo prazo mínimo de cinco anos.\n    (D)Identificando esses clientes, pelo prazo mínimo de dez anos.\n     R:");
                    fflush(stdin);
                    scanf("%c", &q2[3]);
                        if(q2[3]=='b')
                        dados_cadastro[logado].nota2=dados_cadastro[logado].nota2+2.5;

                    system("cls"); //Comando para limpar a tela
                    break;

                case 3:
                    return menu(); //Comando para chamar a função menu e retornar ao Menu de usuário
            } //Fim do switch
        } //Fim do primeiro if
      else
         fflush(stdin);
         questionario(); //Retorno para o menu de seleção de questionário
}

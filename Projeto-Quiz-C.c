#include<stdio.h>
#include<string.h>
#include<locale.h>//biblioteca para compreender simbolos (�, ^, �), comando "setlocale(LC_ALL,"Portuguese");
#include<ctype.h> //biblioteca de manipula��o de caracteres

int i=0; //Vari�vel do �ndice para troca de posi��o na fun��o Registro
struct{ //Estrutura de cadastro
    char nome[30];
    char email[50];
    char senha[100];
    float nota1, nota2;
}dados_cadastro[100];//O vetor da Struct cadastro que define o numero de linhas "i".

int logado; //Coordenada para localizar a posi��o do vetor da Struct cadastro[100]

void registro(){ //Fun��o global de registro de usu�rio

    int arroba = 0, ponto = 0, antesPonto = 0, depois_ponto = 0, x, a=0;
    char c;

        printf("\n-Informe o nome do usu�rio: ");
        fflush(stdin);
        scanf("%[^\n]", dados_cadastro[i].nome);

            for(int l=0; l < strlen(dados_cadastro[i].nome); l++) //L vai ser o contador para verificar cada letra em nome
            {
                if(isalpha(dados_cadastro[i].nome[l]) == 0) //isalpha verifica se cada letra � alfab�tica, 0 = False
                    {
                    printf("Nome Inv�lido!"); //se falso imprime nome inv�lido
                    sleep(1);
                    system("cls");
                    main(); //volta ao login
                    }
            }
        printf("-Informe o e-mail: ");
        fflush(stdin);
        gets(dados_cadastro[i].email);
        int tam=strlen(dados_cadastro[i].email); //Utilizamos o comando "strlen" para atribuir o tamanho da string

            for (x = 0; x < tam; x++)//La�o de repeti��o que vai verificar o indice at� o tamanho da string
            {
                if(dados_cadastro[i].email[x] == '@') //Se ele identificar na string um '@' far� os testes a seguir:
                    {
                      if (arroba) //Faz um teste booleano para verificar a v�riavel "arroba".
                        break; //Para este "if" se na repeti��o "@" for == true.
                        arroba = 1; //Se identificar um '@', torna a vari�vel "arroba" == true
                      if (x < 3)
                        break; // Se o "@" vier antes de pelo menos 3 caracteres, para a execu��o.
                    }
                else if (arroba) // Se na repeti��o ele j� encontrou o '@'.
                {
                    if (ponto) // Se na repeti��o j� encontrou . depois de @
                        depois_ponto++;
                    else if(dados_cadastro[i].email[x] == '.') //Sen�o verifica se na posi�o ap�s o "@" existe algum "."
                    {
                        ponto = 1;
                        if (antesPonto < 3)
                        break; // Se o "." depois de "@" vier antes de pelo menos 3 caracteres,para a execu��o.
                    }
                    else
                        antesPonto++;
                }
            } // Fim do la�o de repeti��o "for".
        for(int y=0; y<i; y++) //la�o de repeti��o para verificar se um email j� foi cadastrado
        {
            if(strcmp(dados_cadastro[y].email, dados_cadastro[i].email)==0) //verifica se j� existe um email dentro de cadastro
              {
                    printf("\t->Este email j� foi cadastrado!<-"); //caso seja verdadeiro, imprime uma mensagem na tela e retorna ao menu
                    sleep(2);
                    system("cls");
                    main();
              }
        }

        if (x == tam && depois_ponto > 1) //Se o indice alcan�ar o tamanho da string e a vari�vel depois_ponto, valida o e-mail e segue o registro
        {
            printf("-Digite sua senha: ");
            fflush(stdin);
            gets(dados_cadastro[i].senha);
        }
        else //Sen�o, mostra que o e-mail � inv�lido.
        {
            printf("E-mail Inv�lido\n");
            sleep(1);
            system("cls");
            registro(); //Retorna para o inicio do registro caso o e-mail seja invalidado.
        }
} //Fim da fun��o de registros do usu�rio


void main(){ //Fun��o principal do c�digo

  int op_menu, log_efetuado, a=0;
  char login[100], senha[50], c;

  setlocale(LC_ALL,"Portuguese"); //Fun��o que converte o texto impresso na tela para o Portugu�s.
  printf("\t--------CADASTRO---------");
  printf("\n 1-> Para se cadastrar\n 2-> Para logar com uma conta existente\n  R:");
  scanf("%d", &op_menu);
  system("cls");
        if(op_menu==1 || op_menu==2)
        { //Teste para verificar se a entrada � uma das op��es v�lidas.
            switch(op_menu)
            { //Estrutura de decis�o para op��es do menu

                case 1: //Op��o que realiza a chamada da fun��o "resgistro", para cadasto do usu�rio.
                    registro();

                    printf("\n\t>Usu�rio cadastrado<\n\n");
                    sleep(1); //Comando com temporizador do tempo de exibi��o
                    i++;
                    system("cls"); //Comando para limpar a tela
                    main();

                case 2: //Op��o para efetuar o login do usu�rio
                    printf("\n-Digite seu email: ");
                    fflush(stdin);
                    gets(login); //entrada do e-mail para login


                    printf("-Digite sua senha: ");
                    fflush(stdin);

                    while(c!=13) //valor de enter na tabela ASCII
                    {
                            c=getch(); //Vari�vel "c" recebe a letra digitada
                            if(isprint(c)) //verifica se � um valor a qual pode ser imprimido
                            {
                               senha[a]=c; //senha na posi��o do vetor recebe a letra da variavel C
                               a++; //contador de C
                               printf("*"); //Imprime o "*"
                            }
                            else if(c==8&&a) //Valor do "BACKSPACE" na tabela ASCII
                            {
                               a--; //Contador para apagar a letra
                               senha[a]='\0'; //Retorna o valor da posi��o do vetor em NULL
                               printf("\b \b"); //Apaga o "*"
                            }
                    }

                    for(int j=0; j<100; j++) //La�o de repeti��o para testar se as informa��es s�o iguais as inseridas em cadastro.
                    {
                            //Uso da fun��o "strcmp" para comparar os valores
                            if(strcmp(dados_cadastro[j].email,login) == 0 && strcmp(dados_cadastro[j].senha,senha) == 0)
                            {
                                printf("\n\t>Login efetuado<  \n\n");
                                logado=j;
                                sleep(1); //Comando com temporizador do tempo de exibi��o
                                system("cls"); //Comando para limpar a tela
                                menu();
                                break;
                            }
                    }
                    default: //Caso n�o seja a op��o de cadastro/login.
                        system("cls");
                        printf("\n>Email ou senha incorreto<");
                        sleep(2);
                        system("cls");
                        main();
            } //fim do switch
        } //fim do if
        else //Sen�o for uma entrada v�lida, limpa o buffer do teclado e retorna para a fun��o Main.
            fflush(stdin);
            main();
} //Fim do bloco Main()

void menu(){ //Menu de op��es para o usu�rio ap�s o login.

  setlocale(LC_ALL,"Portuguese"); //Fun��o que converte o texto impresso na tela para o Portugu�s.
  int op_menu, op_sair;
     //Enunciado do menu ap�s o login, com o nome de usu�rio logado.
     printf("\t---------MENU---------\n\t   > Bem Vindo %s <  \n\n  1->Question�rios\n  2->Notas\n  3->M�dia\n  4->Sair\n  R:",   dados_cadastro[logado].nome);
     scanf("%d", &op_menu);
     if(op_menu>=1 && op_menu<=4)
     {
        switch(op_menu)
        { //Estrutura de decis�o para op��es do menu

          case 1: //Caso 1, realiza a chamada da fun��o "question�rio"
            system("cls");
            questionario();

          case 2: //Caso 2, informa as notas do usu�rio.
            system("cls");
            printf("\n  Aluno: %s \n\tNota do question�rio 1: %f\n\tNota do question�rio 2: %f\n", dados_cadastro[logado].nome, dados_cadastro[logado].nota1, dados_cadastro[logado].nota2); //Fun��o que mostra as notas do usu�rio na tela.
                if(dados_cadastro[logado].nota1>7 && dados_cadastro[logado].nota2<7) //Teste para comparar se a primeira nota est� acima da m�dia.
                    printf("\n\n> Podemos melhorar a nota do Question�rio 2! <\n->Refa�a o teste para obter uma melhor nota.");
                    else if(dados_cadastro[logado].nota1<7 && dados_cadastro[logado].nota2>7) //Teste para comparar se a segunda nota est� acima da m�dia.
                         printf("\n\n> Podemos melhorar a nota do Question�rio 1! <\n->Refa�a o teste para obter uma melhor nota.");
                        else if(dados_cadastro[logado].nota1<7 && dados_cadastro[logado].nota2<7) //Teste para comparar se as duas notas est�o abaixo da m�dia.
                            printf("\n\n> Todas as notas est�o abaixo da M�dia! <\n->Refa�a o testes para obter melhores notas.");
                            else //Sen�o for nenhuma das op��es anteriores, as duas notas est�o acima da m�dia.
                                printf("\n\n> Parab�ns! <\n  Suas notas est�o acima da M�dia!!!");
            sleep(4); //Comando com temporizador do tempo de exibi��o
            system("cls");
            menu();

          case 3: //Caso 3, informa a m�dia do usu�rio.
            system("cls");
            printf("\n  ALuno: %s \n\tM�dia Geral: %f", dados_cadastro[logado].nome, (dados_cadastro[logado].nota1+dados_cadastro[logado].nota2)/2);
                if((dados_cadastro[logado].nota1+dados_cadastro[logado].nota2)/2>7) //Teste para verificar se a m�dia � maior que 7.
                    printf("\n\n > PARAB�NS <\n ->Voc� foi APROVADO!!!");
                    else //Sen�o for maior que 7, informa o usu�rio.
                        printf("\n\n > N�O FOI DESTA VEZ <\n ->Voc� foi REPROVADO!!!\n ->Repita os Testes e Tente Novamente");
            sleep(3);
            system("cls");
            menu();

          case 4: //Caso 4, retorna ao menu anterior.
            system("cls");
            printf("\nDeseja sair?\n    1->Sim\n    2->N�o\n    R:");
            scanf("%d", &op_sair);
            system("cls");

              if(op_sair==1) //Se pressionar um, retorna ao menu.
              main();

              else //Sen�o, mant�m no menu de notas/m�dia.
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

void questionario(){ // Inicio do bloco de question�rio
    int quest;
    char q1[4], q2[4];

        setlocale(LC_ALL,"Portuguese"); //Fun��o que converte o texto impresso na tela para o Portugu�s.
        printf("\t--------Question�rios---------");
        printf("\n->Selecione o question�rio que deseja responder:\n   1->Sistemas Financeiros\n   2->Institui��es\n   3->Retornar ao menu anterior\n   R:");
        scanf("%d", &quest);
        system("cls");
        if(quest>=1 && quest<=3)
        { //V�lida��o para a entrada inserida (neste caso precisa ser num�rica).
            switch(quest)
            { //Estrutura de decis�o para selecionar o Question�rio e receber as respostas direcionadas
                case 1: //Caso 1, apresenta as quest�es relacionadas ao Question�rio 1
                    printf("Questionario 1!");
                    printf("\n  1. Uma facilidade decorrente da fun��o de presta��o de servi�os de gerenciamento de recursos desempenhada pelo Sistema Financeiro Nacional � a:\n   (A)Intermedia��o financeira entre agentes.\n   (B)Disponibiliza��o de um servi�o de guarda limitado a bens de luxo.\n   (C)Disponibiliza��o de seguros para as mais diferentes finalidades.\n   (D)Possibilidade de emiss�o de papel-moeda por bancos privados.\n    R:");
                    fflush(stdin);
                    scanf("%c", &q1[0]);
                        if(q1[0]=='a')
                      //Caso a resposta esteja correta, armazena a pontua��o no vetor nota1, da Struct de Cadastro
                        dados_cadastro[logado].nota1=dados_cadastro[logado].nota1+2.5;

                    printf("\n  2. O Conselho Monet�rio Nacional (CMN) � o �rg�o\n   (A)Subordinado hierarquicamente ao Banco Central do Brasil.\n   (B)Composto pelos diretores do Banco Central do Brasil.\n   (C)Deliberativo m�ximo do Sistema Financeiro Nacional.\n   (D)Subordinado ao Ministro da Economia.\n    R:");
                    fflush(stdin);
                    scanf("%c", &q1[1]);
                        if(q1[1]=='b')
                        dados_cadastro[logado].nota1=dados_cadastro[logado].nota1+2.5;

                    printf("\n  3. � uma atribui��o do Banco Central do Brasil (BACEN)\n    (A)Definir as condi��es e os limites de emiss�o de papel-moeda.\n    (B)Autorizar o funcionamento de institui��es financeiras e promover a fiscaliza��o delas.\n    (C)Eleger os administradores de todas as institui��es financeiras privadas.\n    (D)Fiscalizar o funcionamento de sociedades seguradoras.\n     R:");
                    fflush(stdin);
                    scanf("%c", &q1[2]);
                        if(q1[2]=='a')
                        dados_cadastro[logado].nota1=dados_cadastro[logado].nota1+2.5;

                    printf("\n  4. O �rg�o respons�vel pela prote��o da capta��o de poupan�a popular em investimentos realizados em planos de previd�ncia complementar aberta �:\n    (A)O Banco Central do Brasil (BACEN)\n    (B)A Comiss�o de Valores Mobili�rios (CVM)\n    (C)O Conselho Monet�rio Nacional (CMN)\n    (D)A Superintend�ncia de Seguros Privados (Susep)\n     R:");
                    fflush(stdin);
                    scanf("%c", &q1[3]);
                        if(q1[3]=='b')
                        dados_cadastro[logado].nota1=dados_cadastro[logado].nota1+2.5;

                    system("cls"); //Comando para limpar a tela
                    break;

                case 2: //Caso 2, apresenta as quest�es relacionadas ao Question�rio 2
                    printf("Questionario 2!");
                    printf("\n  1. � uma atribui��o do Banco Central do Brasil (BACEN)\n    (A)Definir as condi��es e os limites de emiss�o de papel-moeda.\n    (B)Autorizar o funcionamento de institui��es financeiras e promover a fiscaliza��o delas.\n    (C)Eleger os administradores de todas as institui��es financeiras privadas.\n    (D)Fiscalizar o funcionamento de sociedades seguradoras.\n     R:");
                    fflush(stdin);
                    scanf("%c", &q2[0]);
                        if(q2[0]=='a')
                      //Caso a resposta esteja correta, armazena a pontua��o no vetor nota2, da Struct de Cadastro
                        dados_cadastro[logado].nota2=dados_cadastro[logado].nota2+2.5;

                    printf("\n   2. O �rg�o respons�vel pela prote��o da capta��o de poupan�a popular em investimentos realizados em planos de previd�ncia complementar aberta �:\n    (A)O Banco Central do Brasil (BACEN)\n    (B)A Comiss�o de Valores Mobili�rios (CVM)\n    (C)O Conselho Monet�rio Nacional (CMN)\n    (D)A Superintend�ncia de Seguros Privados (Susep)\n     R:");
                    fflush(stdin);
                    scanf("%c", &q2[1]);
                        if(q2[1]=='b')
                        dados_cadastro[logado].nota2=dados_cadastro[logado].nota2+2.5;

                    printf("\n  3. O cadastro dos dados dos clientes das institui��es financeiras:\n    (A)Deve reunir o maior n�mero de informa��es, independentemente da atualiza��o desse cadastro, para a preven��o de lavagem de dinheiro.\n    (B)Deve estar completo e atualizado para auxiliar na verifica��o da capacidade financeira desses clientes com o objetivo de prevenir o crime de lavagem de dinheiro.\n    (C)Pode ser atualizado pelos canais de atendimento telef�nico, sem a necessidade da comprova��o desses dados.\n    (D)Pode ser atualizado, a qualquer momento, a crit�rio dessas institui��es\n     R:");
                    fflush(stdin);
                    scanf("%c", &q2[2]);
                        if(q2[2]=='a')
                        dados_cadastro[logado].nota2=dados_cadastro[logado].nota2+2.5;

                    printf("\n  4. Quanto ao registro das opera��es dos clientes, as institui��es financeiras reguladas pelo BACEN s�o obrigadas a mant�-lo integralmente:\n    (A)Sem identificar esses clientes, pelo prazo m�nimo de cinco anos.\n    (B)Sem identificar esses clientes, pelo prazo m�nimo de dez anos.\n    (C)Identificando esses clientes, pelo prazo m�nimo de cinco anos.\n    (D)Identificando esses clientes, pelo prazo m�nimo de dez anos.\n     R:");
                    fflush(stdin);
                    scanf("%c", &q2[3]);
                        if(q2[3]=='b')
                        dados_cadastro[logado].nota2=dados_cadastro[logado].nota2+2.5;

                    system("cls"); //Comando para limpar a tela
                    break;

                case 3:
                    return menu(); //Comando para chamar a fun��o menu e retornar ao Menu de usu�rio
            } //Fim do switch
        } //Fim do primeiro if
      else
         fflush(stdin);
         questionario(); //Retorno para o menu de sele��o de question�rio
}

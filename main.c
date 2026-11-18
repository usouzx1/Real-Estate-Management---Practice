#include <stdio.h>
#include <unistd.h>
#include <string.h>

//-------------------------definiçoes

#define APARTAMENTO 1 // {
#define CASA 2
#define TERRENO 3 // } TIPO

#define VENDA 1   // {
#define LOCACAO 2 // } NEGOCIACAO

#define DISPONIVEL 1 // {
#define NEGOCIANDO 2
#define INDISPONIVEL 3 // } SITUACAO

#define ADMIN 1   // {
#define CLIENTE 0 
#define ERRO -1 // } USUARIO

typedef struct FichaImovel ficha_imovel;

//-------------------------protótipos auxiliares

void demorar(int segundos);
void limparBuffer();
void garantirArquivo();

//-------------------------protótipos main

void menuCliente();
void mesaControle();
void menuImovel();
//-------------------------protótipos CRUD
int logar();
int cadastrar();

//-------------------------funções auxiliares

void demorar(int segundos)
{
    printf("...");
    sleep(segundos);
}

void limparBuffer()
{
    int c;
    while (
        ((c = getchar()) != '\n' && c != EOF));
}

int logar()
{
    char linha[300];
    char usuario_digitado[20], senha_digitada[20];
    char usuario_arquivo[20], senha_arquivo[20];

    do {
    printf("\n>> Digite seu usuário : ");
    scanf("%19s", usuario_digitado);
    limparBuffer();
    printf("\n>> Digite sua senha : ");
    scanf("%19s", senha_digitada);
    limparBuffer();

    FILE *arq = fopen("usuarios.csv", "r");
    if (arq == NULL)
    {
        printf("\nErro ao abrir arquivo.");
        return 0;
    }
    while (fgets(linha, sizeof(linha), arq) != NULL)
    {
        if (sscanf(linha, "%19[^;];%19s", usuario_arquivo, senha_arquivo) == 2)
        {
            if (strcmp(usuario_digitado, usuario_arquivo) == 0 && strcmp(senha_digitada, senha_arquivo) == 0)
            {
                
                printf("\n>> Login bem-sucedido!");
                fclose(arq);
                return CLIENTE;
            }
            else if (strcmp(usuario_digitado, usuario_arquivo) != 0 || strcmp(senha_digitada, senha_arquivo) != 0)
                printf("\n>> Usuário ou senha incorretos.");
                return ERRO;
            }
            else if (strcmp(usuario_digitado, "admin") == 0 && strcmp(senha_digitada, "admin") == 0)
            {
                printf("\n>> Login ADMIN bem-sucedido!");
                fclose(arq);
                return ADMIN;
            }
            else if (strcmp(usuario_digitado, "admin") == 0 && strcmp(senha_digitada, "admin") != 0)
            {
                
                printf("\n>> Senha ADMIN incorreta.");
                return ERRO;
            }
        } while ( ERRO );
    }
    fclose(arq);
    


int cadastrar()
{
    char linha[300];
    char usuario_arquivo[20], senha_arquivo[20];
    char usuario_digitado[20], senha_digitada[20];

    do {
    printf("\n>> Digite seu usuário : ");
    scanf("%19s", usuario_digitado);
    limparBuffer();
    printf("\n>> Digite sua senha : ");
    scanf("%19s", senha_digitada);
    limparBuffer();

    FILE *arq = fopen("usuarios.csv", "r");
    if (arq == NULL)
    {
        printf("\nErro ao abrir arquivo.");
        return;
    }
    while (fgets(linha, sizeof(linha), arq) != NULL)
    {
        if (sscanf(linha, "%19[^;];%19s", usuario_arquivo, senha_arquivo) == 2)
        {
            if (strcmp(usuario_arquivo, "admin") == 0 && (strcmp(senha_digitada, "admin" == 0)))
            {
                printf("\n>> Usuário ADMIN não pode ser cadastrado.");
                fclose(arq);
                return;
            }
        }
    }
    arq = fopen("usuarios.csv", "a");
    if (arq == NULL)
    {
        printf("\nErro ao abrir arquivo.");
        return;
    }
    fprintf(arq, "%s;%s\n", usuario_digitado, senha_digitada);
    fclose(arq);
    printf("\n>> Cadastro realizado com sucesso!");
}

void garantirArquivo(const char *nomeArquivo)
{
    FILE *arq = fopen(nomeArquivo, "a");
    if (arq != NULL)
    {
        fclose(arq);
    }
}

//-------------------------funções crud

struct FichaImovel
{
    int id;
    char tipo[15];
    char negociacao[10];
    char situacao[15];
    char endereco[60];
    float area;
    long valor_int;
};

//-------------------------create
void novoImovel()
{
    ficha_imovel f;
    int op;
    int ok = 0;
    FILE *arq = fopen("imovel.csv", "a");
    if (arq == NULL)
    {
        printf("\nErro ao abrir arquivo.");
        return;
        fclose(arq);
    }
    printf("\n>> ID : ");
    scanf("%d", &f.id);
    limparBuffer();
    do
    {
        printf("\n>> Tipo ( APARTAMENTO - 1 / CASA - 2 / TERRENO - 3 ) ");
        scanf("%d", &op);
        limparBuffer();
        switch (op)
        {
        case APARTAMENTO:
            ok = 1;
            printf("\nTipo de Imóvel definido para APARTAMENTO.");
            strcpy(f.tipo, "APARTAMENTO");
            break;

        case CASA:
            ok = 1;
            printf("\nTipo de Imóvel definido para CASA.");
            strcpy(f.tipo, "CASA");
            break;

        case TERRENO:
            ok = 1;
            printf("\nTipo de Imóvel definido para TERRENO.");
            strcpy(f.tipo, "TERRENO");
            break;

        default:
            ok = 0;
            printf("\nOpção INVÁLIDA.");
        }
    } while (ok == 0);

    do
    {
        printf(">> Negociação ( VENDA - 1 / LOCAÇÃO - 2 )");
        scanf("%d", &op);
        limparBuffer();
        switch (op)
        {
        case VENDA:
            ok = 1;
            printf("\nNegociação de Imóvel definida para VENDA.");
            strcpy(f.negociacao, "VENDA");
            break;

        case LOCACAO:
            ok = 1;
            printf("\nNegociação de Imóvel definida para LOCAÇÃO.");
            strcpy(f.negociacao, "LOCACAO");
            break;

        default:
            ok = 0;
            printf("\nOpção INVÁLIDA.");
        }
    } while (ok == 0);

    do
    {
        printf(">> Situação ( DISPONIVEL - 1 / NEGOCIANDO - 2 / INDISPONÍVEL - 3 ) ");
        scanf("%d", &op);
        limparBuffer();

        switch (op)
        {
        case DISPONIVEL:
            ok = 1;
            printf("\nNegociação de Imóvel definida para DISPONÍVEL.");
            strcpy(f.situacao, "DISPONIVEL");
            break;

        case NEGOCIANDO:
            ok = 1;
            printf("\nNegociação de Imóvel definida para NEGOCIANDO.");
            strcpy(f.situacao, "NEGOCIANDO");
            break;

        case INDISPONIVEL:
            ok = 1;
            printf("\nNegociação de Imóvel definida para INDISPONIVEL");
            strcpy(f.situacao, "INDISPONIVEL");
            break;

        default:
            ok = 0;
            printf("\nOpção INVÁLIDA.");
        }
    } while (ok == 0);

    printf("\n>> Endereço\n");
    fgets(f.endereco, sizeof(f.endereco), stdin);

    printf("\n>> Área ( em m²)");
    scanf("%f", &f.area);
    limparBuffer();

    printf("\n>> Valor ( R$ )");
    scanf("%ld", &f.valor_int);
    limparBuffer();

    fprintf(arq, "%d;%s;%s;%s;%s;%f;%ld", f.id, f.tipo, f.negociacao, f.situacao, f.endereco, f.area, f.valor_int);
    fclose(arq);
}
//-------------------------read
void listarImoveis()
{
    ficha_imovel f;
    char linha[300];
    FILE *arq = fopen("imovel.csv", "r");
    if (arq == NULL)
    {
        printf("Erro ao abrir arquivo.");
        return;
    }
    while (fgets(linha, sizeof(linha), arq) != NULL)
    {
        if (
            sscanf(linha, "%d;%[^;];%[^;];%[^;];%[^;];%.f;%ld", &f.id, &f.tipo, &f.negociacao, &f.situacao, &f.endereco, &f.area, &f.valor_int) == 7)
        {
            printf("\n%d;%s;%s;%s;%s;%f;%ld", f.id, f.tipo, f.negociacao, f.situacao, f.endereco, f.area, f.valor_int);
        }
    }
    fclose(arq);
}

//------------------------submenus
//------------------------ <<Tabela Admin
void mesaControle()
{
    printf("\n1. GERENCIAR USUÁRIOS\n");
    printf("2. GERENCIAR IMÓVEIS\n");
    printf("3. \n");
    printf("4. \n");
}

//------------------------ << Imóveis
void menuImovel()
{
    int opcao;
    ficha_imovel f;
    printf("Você selecionou a opção GERENCIAR IMÓVEIS.\n");
    printf("\n1. Novo Imóvel\n");
    printf("2. Listar Imóveis\n");
    printf("3. Editar Imóvel\n");
    printf("4. Excluir Imóvel\n");
    printf("0. Voltar\n");
    printf("\nSelecione a opção desejada : ");
    scanf("%d", &opcao);
    limparBuffer();
    demorar(1);

    switch (opcao)
    {

    case 1:
        printf("\nVocê selecionou a opção 'NOVO IMÓVEL'.");
        novoImovel();
        break;

    case 2:
        printf("\nVocê selecionou a opção 'LISTAR IMÓVEIS'.");
        listarImoveis();
        break;

    case 3:
        printf("\nVocê selecionou a opção 'EDITAR IMÓVEL'.");
        // editarImovel;
        break;

    case 4:
        printf("\nVocê selecionou a opção 'EXCLUIR IMÓVEL'.");
        // excluirImovel;
        break;

    case 0:
        printf("\nVocê selecionou a opção VOLTAR.");
        break;

    default:
        printf("\nA opção selecionada é inválida. Tente novamente.\n");
        demorar(1);
    }
}

// ------------------------<<Tabela Cliente
void menuCliente()
{
    int opcao;
    printf("\n1. Listar Imóveis\n");
    printf("2. Pesquisar Imóveis\n");
    printf("3. Demonstrar Interesse / Solicitar Visita\n");
    printf("0. Voltar\n");
    printf("\nSelecione a opção desejada :");
    scanf("%d", &opcao);
    limparBuffer();
    demorar(1);
}

int main()
{
    int escolha = 0;
    garantirArquivo("imovel.csv");
    garantirArquivo("usuarios.csv");
    // garantirArquivo("interesse.csv");
    // garantirArquivo("visita.csv");
    // garantirArquivo("negociacao.csv");
    // garantirArquivo("historico.csv");

    printf("========================================================\n");
    printf("------------ GERENCIAMENTO DE IMOBILIÁRIA--------------\n");
    printf("========================================================\n");

    printf("Carregando o sistema, aguarde");
    demorar(1);

    printf("Para acessar o sistema, informe se você é um ADMINISTRADOR ou CLIENTE.\n");
    do
    {
        printf(">> Digite 1 para LOGAR e 2 para CADASTRAR : ");
        scanf("%d", &escolha);
        limparBuffer();

        switch (escolha)
        {
        case 1:
            printf("\nVocê selecionou a opção LOGAR.");
            logar();
            break;

        case 2:
            printf("\nVocê selecionou a opção CADASTRAR.");
            cadastrar();
            break;

        default:
            printf("\nA opção selecionada é inválida. Tente novamente.\n");
            demorar(1);
        }
    } 
    while (escolha != 1 && escolha != 2);

        if (1)
        {
            printf("\n>> ");
            mesaControle();
        }

        else if (0)
        {
            printf("\n>> ");
            menuCliente();
        }

        return 0;
    }
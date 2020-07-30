//ProdutoPim.cpp : Este arquivo contém a função 'main'. A execucao do programa começa e termina ali.
//	O arquivo esta sendo salvo na pasta original criada pelo programa ao criar novo projeto 

										   /*                 APRESENTACAO PREVISTA PARA O DIA 04/12 AS 20:30
										   *                 PARTICIPANTES DO GRUPO 3 DO PIM SEGUNDO SEMESTRE
										   *                      
										   *          BRENO SILVA DE OLIVEIRA             RA: F013GFQ - TURMA: DS2Q22 
										   *          JESSICA JULIANA SILVA JARA BOTARO   RA: D995006 - TURMA: DS2P22
										   *          JOICE NATALICE ALVES DE ABREU       RA: D859927 - TURMA: DS2P22
										   *          LUCAS DOS SANTOS PEREIRA            RA: F023893 - TURMA: DS2Q22
										   *          LUCIANO ERIC DAMASCENO SILVA        RA: N463GB0 - TURMA: DS2P22
										   *          MARCIA GONCALVES DE ABREU           RA: D961209 - TURMA: DS2Q22
										   */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
const float TX = 5.00; //Taxa de entrega fixo.
void limpabuffer()
{
	char c;
	while ((c = getchar()) != '\n' && c != EOF);
}

//-----------------------------------------------------------OS ARQUIVOS  DO SISTEMA
FILE* arquivo = NULL;    //Ponteiro para arquivo produto
FILE* arq = NULL;        //Ponteiro para arquivo cliente
FILE* relatorio = NULL; //Ponteiro para arquivo relatorio
FILE* ptr_elogio = NULL;//Ponteiro para arquivo elogio
FILE* ptr_reclam = NULL;//Ponteiro para arquivo reclamacao
FILE* func = NULL; // Ponteiro para arquivo funcionario
//--------------------------------------------------------------------STRUCTS-------------
struct Login //declara a struct login
{
	char login[15];
	int senha;
	char nome[20];
	int unidade;
}m_login[15];

typedef struct //declara a struct do sac
{
	int dia;
	int mes;
	int ano;
	int id_elo;
	int id_rec;
	char nome[51];
	int telefone;
	char c_mani[301];
}cadastro;
cadastro mCadastro[200][200]; //Linha = Elogio - Coluna //Reclamacao

struct produto //declarando a struct de produto
{
	int codigo;
	char descricao[50];
	float preco;
	float custo;
	int quantidade;
	int vendas;
} mproduto[100];


struct fichaf //declarando a struct de funcionario
{
	int pos;
	char nome[50];
	char cpf[15];
	char cargo[15];
}m_funcionarios[40];

struct pedido //declarando a struct de pedido

{
	int posicao;
	int dia;
	int mes;
	int ano;
	int telefone_Cliente;
	int codigo_produto;
	char descricao_produto[50];
	int quantidade;
	int unidade_Login;
	int ativo;
	float lucro;
	float totalgeral;
	int qtdd;
}mpedido[200];
struct tm* data_hora; // vetor para hora/data

struct Clientes //declarando a struct de  cliente

{
	int telefone;
	char nome[50];
	char endereco[100];
	int ativo; // na hora de excluir vou dizer se esta ativo sim ou nao
}m_clientes[200];
//==================================PROTOTIPOS ===================================================================
void login();
void menugeral(); //Tela menu principal
void tela010(); //Tela pedido
void tela020(); //Tela produto
void tela040(); //Tela relatorios
void tela050(); //Tela sac
void tela060(); //Tela funcionarios
void tela011(); //Cadastro de pedido
void tela012(); //Exibir conteudo do arquivo
void tela013(); //Cancelar pedido
int localiza_Clientes(int telefone); //Localiza cliente
int localiza_pedido(int telefone); //Localiza pedido
int tela021(); //Tela cadastro do produto
void tela022(); //Tela busca produto
void tela023(); //Tela altera produto
void tela024(); //Tela de estoque
void inicializa_arquivo_prod(); //Inicializa arquivo de produto
void inicializa_arq_clientes(); //Inicializa arquivo de cliene
void inicializa_arquivo_pedido(); //Inicializa arquivo de pedido
void inicializa_arquivo_funcionario(); //Inicializa arquivo de funcionario
void inicializa_arquivos_sac();    //Inicializa arquivo sac
void cabecalho();
void cadastrar_funcionario(); //Cadastrar funcionario
void listar(); //Listar funcionarios
void cadastro_v(); //Tela de cadastro
void buscar_sac(); //Tela de busca
void lista_dado(); //Tela gerencia de dados

int main()
{
	inicializa_arquivo_pedido(); //Inicializacao do pedido
	inicializa_arquivo_prod(); //Inicializacao do produto
	inicializa_arq_clientes(); //Inicializacao de clientes
	inicializa_arquivo_funcionario(); //Inicializa arquivo de funcionario    
	inicializa_arquivos_sac();    //Inicializa arquivo sac
	//  login();
	menugeral(); // LEMBRAR DE APAGAR

	system("pause");
	return 0;
}
void menugeral() //Menu principal
{
	char opcao;
	do
	{
		system("cls");
		cabecalho();
		printf("\n\n 1-Pedido");
		printf("\n 2-Produtos ");
		printf("\n 3-Relatorios");
		printf("\n 4-SAC");
		printf("\n 5-Funcionarios");
		printf("\n 0-sair\n");
		printf("\n Escolha uma opcao: ");
		fflush(stdin);
		scanf("%s", &opcao);

		if (opcao == '1')
			tela010();
		if (opcao == '2')
			tela020();
		if (opcao == '3')
			tela040();
		if (opcao == '4')
			tela050();
		if (opcao == '5')
			tela060();
		if (opcao == '0')
		{
			printf("Saindo do programa !\n\n");
			system("pause");
			exit(0);
		}
	} while (opcao != '0'); //Sair quando digitar 0
	system("pause");
}

void cabecalho()
{
	time_t t;
	t = time(NULL);
	data_hora = localtime(&t);
	printf("\n===========================================================\n");
	printf("\n=                     PIZZARIA 6 AMIGOS                   =\n");
	printf("\n===========================================================\n");
	printf(" %d/%d/%d %d:%d\n", data_hora->tm_mday, data_hora->tm_mon + 1, data_hora->tm_year + 1900, data_hora->tm_hour, data_hora->tm_min);
}
void login() //Login de cada unidade para ter acesso ao sistema
{
	int pass, opcao; char usuario[15]; int i = 0;
	strcpy(m_login[0].login, "pizzaria-10");
	strcpy(m_login[0].nome, "Pizzaria 1");
	m_login[0].senha = 1010;
	m_login[0].unidade = 1;
	//Inclui dados login  2
	strcpy(m_login[1].login, "pizzaria-20");
	strcpy(m_login[1].nome, "Pizzaria 2");
	m_login[1].senha = 1020;
	m_login[1].unidade = 2;
	//Inclui dados login 3
	strcpy(m_login[2].login, "pizzaria-30");
	strcpy(m_login[2].nome, "Pizzaria 3");
	m_login[2].senha = 1030;
	m_login[2].unidade = 3;
	//Inclui dados login 7
	strcpy(m_login[3].login, "6AMIGOS");
	strcpy(m_login[3].nome, "Administrador");
	m_login[3].senha = 1020;
	m_login[3].unidade = 123;

	system("cls");
	cabecalho();
	printf("\nDigite o LOGIN: ");
	scanf("%s", usuario);
	fflush(stdin);
	printf("\nDigite a SENHA: ");
	scanf("%d", &pass);
	fflush(stdin);

	while (i < 40)
	{
		if (strcmp(usuario, m_login[i].login) == 0 && pass == m_login[i].senha) //Corfirma se login e senha estao corretos para ter acesso ao sistema
		{
			printf("\nLogado com sucesso!\n\n-------------Bem-vindo(a): %s\n-----------------------\nUNIDADE: %d\n ", m_login[i].nome, m_login[i].unidade);
			menugeral();
		}
		i++;
	}
	if (i >= 40)
	{
		limpabuffer();
		printf("\n Erro: Login ou senha incorreta \n");
		printf("\n1-Tentar de novo\n0-Sair ");
		scanf("%d", &opcao);
		switch (opcao)
		{
		case 1: login(); break; // Volta a janela de entrada de login e senha
		case 0: exit(0); break; //Sair quando digitar 0
		default: printf("Opcao invalida!\n\n");
		}
	}
}
void inicializa_arq_clientes()
{
	//inicializacao da matriz produto
	int i = 0;
	for (i = 0; i < sizeof(m_clientes) / sizeof(struct Clientes); i++)
	{
		if (i == 0)
			m_clientes[i].telefone = 1;

		else
		{
			m_clientes[i].telefone = -1;
			strcpy(m_clientes[i].nome, "");
			strcpy(m_clientes[i].endereco, "");
		}
	}
	arq = fopen("arqclientes.bin", "a+b"); //A crescenta dados ou cria um arquivo(cliente) binário para leitura e escrita
	fclose(arq); //fecha arquivo(cliente)
	arq = fopen("arqclientes.bin", "r+b"); //Abre arquivo(cliente)para leitura
	i = 0;
	while (!feof(arq) && i < 200) //Leitura do arquivo para a memoria
	{
		fread(&m_clientes[i], sizeof(struct Clientes), 1, arq);
		i++;
	}
	fclose(arq);
}
void inicializa_arquivo_prod() //inicializacao da matriz produto
{

	int i = 0;
	for (i = 0; i < sizeof(mproduto) / sizeof(struct produto); i++) //Deixara todo os codigos nao cadastrados em -1
	{
		mproduto[i].codigo = -1;
		mproduto[i].quantidade = 0;
		mproduto[i].custo = 0;
		mproduto[i].preco = 0;
		mproduto[i].vendas = 0;
		strcpy(mproduto[i].descricao, "");
	}

	arquivo = fopen("produto.bin", "a+b"); //A crescenta dados ou cria um arquivo(produto) binário para leitura e escrita
	fclose(arquivo); //fecha arquivo(produto)
	arquivo = fopen("Produto.bin", "r+b"); //Abre arquivo(produto) para leitura
	i = 0;
	while (i < 100 && !feof(arquivo)) //Leitura do arquivo para a memoria
	{
		fread(&mproduto[i], sizeof(struct produto), 1, arquivo);
		i++;
	}
	fclose(arquivo);
}

void inicializa_arquivo_pedido()//inicializacao da matriz pedido

{
	int i = 0;
	for (i = 0; i < sizeof(mpedido) / sizeof(pedido); i++)//Deixara todo os codigos nao cadastrados em -1
	{
		mpedido[i].telefone_Cliente = -1;
		mpedido[i].posicao = 0;
		mpedido[i].unidade_Login = 0;
		mpedido[i].totalgeral = 0;
		mpedido[i].lucro = 0;
	}

	relatorio = fopen("relatorio.bin", "a+b"); //A crescenta dados ou cria um arquivo(relatorio) binário para leitura e escrita
	fclose(relatorio); //fechar arquivo(relatorio) 
	relatorio = fopen("relatorio.bin", "r+b"); //Abre arquivo(relatorio) para leitura
	i = 0;

	while (i < 200 && !feof(relatorio)) //Leitura do arquivo para a memoria
	{
		fread(&mpedido[i], sizeof(struct pedido), 1, relatorio);
		i++;
	}
	fclose(relatorio);

}


void inicializa_arquivo_funcionario() //inicializacao da matriz funcionarios
{
	int i = 0;

	func = fopen("arqficha.bin", "a+b"); //A crescenta dados ou cria um arquivo(ficha de funcionarios) binário para leitura e escrita
	fclose(func); //fechar arquivo(ficha de funcionarios) 
	func = fopen("arqficha.bin", "r+b"); //Abre arquivo(ficha de funcionarios) para leitura
	for (i = 0; i < sizeof(m_funcionarios) / sizeof(struct fichaf); i++) //Deixara todo os codigos nao cadastrados em -1
	{
		m_funcionarios[i].pos = -1;
		strcpy(m_funcionarios[i].cpf, "");
		strcpy(m_funcionarios[i].cargo, "");
		strcpy(m_funcionarios[i].nome, "");
	}
	i = 0;
	while (i < 40 && !feof(func)) //Leitura do arquivo para a memoria
	{
		fread(&m_funcionarios[i], sizeof(m_funcionarios), 1, func);
		i++;
	}
	fclose(func);
}

void inicializa_arquivos_sac() //Carrega os dados do arquivo para o vetor de Struct SAC
{
	int i = 0;

	for (i = 0; i < 200; i++)
	{
		mCadastro[i][0].id_elo = 0; //ID elogios ELOGIOS
		mCadastro[i][1].id_rec = 0; //ID reclamacoes
		strcpy(mCadastro[i][0].nome, ""); //Nome de quem fez elogio
		strcpy(mCadastro[i][1].nome, ""); //Nome de quem fez reclamacao
		mCadastro[i][0].telefone = -1; //Telefone de quem fez o elogio
		mCadastro[i][1].telefone = -1; //Telefone de quem fez a reclamacao
		strcpy(mCadastro[i][0].c_mani, ""); //Manifesto elogio
		strcpy(mCadastro[i][1].c_mani, ""); //Manifesto reclamacao
	}

	i = 0;
	ptr_elogio = fopen("elogio.bin", "a+b"); //A crescenta dados ou cria um arquivo(elogio) binário para leitura e escrita
	fclose(ptr_elogio);//fechar arquivo(elogio) 
	ptr_elogio = fopen("elogio.bin", "r+b"); //Abre arquivo(elogio) para leitura

	while (i < 200 && !feof(ptr_elogio))
	{
		fread(&mCadastro[i][0], sizeof(cadastro), 1, ptr_elogio); //Leitura do arquivo para a memoria
		i++;
	}

	i = 0;
	ptr_reclam = fopen("reclamacao.bin", "a+b");//A crescenta dados ou cria um arquivo(reclamacao) binário para leitura e escrita
	fclose(ptr_reclam);//fechar arquivo(elogio) 
	ptr_reclam = fopen("reclamacao.bin", "r+b");//Abre arquivo(elogio) para leitura

	while (i < 200 && !feof(ptr_reclam))
	{
		fread(&mCadastro[i][1], sizeof(cadastro), 1, ptr_reclam); //Leitura do arquivo para a memoria
		i++;
	}
	fclose(ptr_elogio);
	fclose(ptr_reclam);

}

int localiza_Clientes(int telefone) //Localizar cliente por passagem de valor 
{
	int i = 0;
	while (i < sizeof(m_clientes) / sizeof(struct Clientes) && m_clientes[i].telefone != -1)
	{
		if (m_clientes[i].telefone == telefone)
			return i;
		i++;
	}
	if (m_clientes[i].telefone == -1)
		return -i;

	return -32000; //Significa que a matriz localizou o cliente

}
int localiza_pedido(int telefone) //Localizar pedido por passagem de valor
{

	int i = 0;
	while (i < sizeof(mpedido) / sizeof(struct pedido) && mpedido[i].telefone_Cliente != -1)
	{
		if (mpedido[i].telefone_Cliente == telefone)
			return i;
		i++;
	}

	return -32000; //Significa que a matriz de produtos esta cheia e nao localizou o produto pesquisado
}


int localiza_produto(int codigo) //Localizar produto por passagem de valor
{
	int i = 0;
	while (i < sizeof(mproduto) / sizeof(struct produto) && mproduto[i].codigo != -1)
	{
		if (mproduto[i].codigo == codigo)
			return i;
		i++;
	}

	return -32000; //Significa que a matriz de produtos esta cheia e nao localizou o produto pesquisado
}
void tela010() //Menu pedido
{
	char opcao;

	do
	{
		system("cls");
		cabecalho();
		printf("\n                        PEDIDO\n\n");
		printf("\n\n 1-Cadastrar Pedido");
		printf("\n 2-Consultar Pedido");
		printf("\n 3-Cancelar Pedido");
		printf("\n 0-Voltar\n");
		printf("\n Escolha uma opcao: ");
		scanf("%s", &opcao);

		if (opcao == '1')
			tela011();
		if (opcao == '2')
			tela012();
		if (opcao == '3')
			tela013();
		if (opcao == '0')
			menugeral();
		else
			tela010();

	} while (opcao != '0');

}
void tela011() //Pedido
{
	//FILE* arquivo = NULL; //Cria ponteiro de tipo FILE iniciado em NULL
	time_t t; // Cria variavel do tipo time
	t = time(NULL); // cria varial que aponta para t de time iniciado em NULL
	data_hora = localtime(&t); // variavel data_hora recebe hora e data atual do computador

	int telefone, posicao_Clientes, opcao, codigo, posicao_produto, confir, qtdd, j = 0, i = 0;
	float lucro = 0, total = 0;
	char desc;
	while (mpedido[j].telefone_Cliente != -1) // procura posicao para gravar os dados (quando posicao tiver valor -1)
	{
		j++;
	}
	arq = fopen("relatorio.bin", "a+b");
	do
	{
		system("cls");
		cabecalho();
		arq = fopen("arqclientes.bin", "r+b");
		printf("\nDigite o telefone a ser procurado: \n");
		scanf("%d", &telefone);
		getchar();
		posicao_Clientes = localiza_Clientes(telefone); //

		if (posicao_Clientes >= 0) //Localiza o cliete pelo telefone. Se achr, mostra os dados 
		{
			printf("\n Bem-vindo");
			printf("\n\n Nome: %s", m_clientes[posicao_Clientes].nome);
			printf(" Telefone: %d", m_clientes[posicao_Clientes].telefone);
			printf("\n Endereco: %s", m_clientes[posicao_Clientes].endereco);
			getchar();
		}

		else  // Caso nao ache o cadastro, pergunta se o deseja fazer 
		{
			fflush(stdin);
			char cadastro;
			printf("\nCliente nao encontrado. Deseja cadastrar? (s/n): ");
			scanf("%c", &cadastro);
			if (cadastro == 's')//Caso positivo, entrar com os dados do cliente para cadastro
			{
				arq = fopen("arqclientes.bin", "a+b");
				printf("\nTelefone: %d", telefone);
				m_clientes[-posicao_Clientes].telefone = telefone;
				fflush(stdin);
				printf("\nDigite o Nome: ");
				getchar();
				fgets(m_clientes[-posicao_Clientes].nome, 50, stdin);
				fflush(stdin);
				printf("Digite o endereco: ");
				fgets(m_clientes[-posicao_Clientes].endereco, 100, stdin);
				fwrite(&m_clientes[-posicao_Clientes], sizeof(struct Clientes), 1, arq);
				fclose(arq);
			}
			else if (cadastro == 'n') //Se optar por nao cadastrar, volta para o menu principal
			{
				menugeral();
			}
		}

		do //Inserir produtos no pedido
		{
			printf("\n\nDigite o codigo do produto: ");
			scanf("%d", &codigo);
			posicao_produto = localiza_produto(codigo);

			if (posicao_produto >= 0)
			{
				printf("\nDescricao: %s", mproduto[posicao_produto].descricao);
				printf("\nPreco: R$ %.2f", mproduto[posicao_produto].preco);
				printf("\nQuantidade: %d", mproduto[posicao_produto].quantidade);

				limpabuffer();
				printf("\nQuantidade do produto: "); //Quantidade que o cliente quer do produto
				scanf("%d", &qtdd);
				mproduto[posicao_produto].quantidade = mproduto[posicao_produto].quantidade - qtdd; //Subtrair quantidade do produto do estoque
				mproduto[posicao_produto].vendas += qtdd;
				total += mproduto[posicao_produto].preco * qtdd;  //Total do produto = preco x quantidade
				mpedido[j].posicao = j; // Atribui a posicao do pedido para coloca-lo em ordem 
				mpedido[j].telefone_Cliente = m_clientes[-posicao_Clientes].telefone; // Atribui o telefone do cliente ao pedido
				strcpy(mpedido[j].descricao_produto, mproduto[posicao_produto].descricao); //Atribui a descricao do produto
				mpedido[j].codigo_produto = posicao_produto; //Atribui o codigo do produto
				mpedido[j].lucro += ((mproduto[posicao_produto].preco * qtdd) - (mproduto[posicao_produto].custo * qtdd)); //Calcula o lucro da venda
				mpedido[j].totalgeral = total; //Soma do pedido
				printf("\nTotal do produto: R$ %.2f", total);

				mpedido[j].ativo = 1; // Coloca o pedido como "ativo". Quando = 0, o produto esta inativo
				mpedido[j].dia = data_hora->tm_mday; // Recebe dia do momento do cadastro
				mpedido[j].mes = data_hora->tm_mon + 1; // Recebe data-mes do momento do cadastro
				mpedido[j].ano = data_hora->tm_year + 1900; // Recebe ano do momento do cadastro
			}
			else
			{
				printf("\nProduto não localizado!\n\n\n");
				system("pause");
				tela010();
			}

			fflush(stdin);
			printf("\n 1-Adicionar mais produto\n 0-Continuar "); //Pergunta se quer adicionar mais produtos
			scanf("%d", &opcao);

		} while (opcao != 0); //Caso 1 ira, adicionar mais um produto(s)
		fflush(stdin);
		printf(" Cupom de desconto(s/n): "); //PROMOCAO: informou o cupom, 15% de desconto 
		getchar();
		scanf("%c", &desc);
		if (desc == 's') //Caso tenha o cupom, calcula o desconto
		{
			printf("Desconto de 15%");
			mpedido[j].totalgeral *= 0.85; // Calcula o desconto
		}
		else if (desc != 's')
			printf(" Sem desconto\n"); //Cao nao haja cupom, nao calcula desconto

		printf("\n\nTotal do pedido: R$ %.2f", mpedido[j].totalgeral + TX); //Total do pedido completo (com ou sem desconto) + taxa de entrega
		printf("\n1-Novo Pedido\n 0-Sair "); //Opcao para efetuar novo pedido
		scanf("%d", &opcao);
		if (opcao == 1)
		{
			j++; //Pula para oroxima posicao disponivel na matriz
		}
	} while (opcao != 0);
	fwrite(&mpedido[j], sizeof(struct pedido), 1, relatorio); //Gravar pedido no relatorio
	fclose(relatorio);
	fclose(arq);
	system("pause");
}

void tela012()//exebir relatorio completo
{
	system("cls");
	getchar();
	int i = 0;
	relatorio = fopen("relatorio.bin", "r+b");
	system("cls");
	cabecalho();
	printf("\n\n");

	if (relatorio == NULL)  //Verfica arquivo
	{
		printf("Ainda nao ha pedido cadastrado\n"); //Se arquivo estiver vazio, informa que nao ha cadastro
		getchar();
		menugeral(); // Volta ao menu principal
	}
	// Se pular a verificacao, quer dizer que ha arquivo e faz o bloco de codigo abaixo
	while (mpedido[i].telefone_Cliente != -1) //Busca e imprimir na tela os pedidos cadastrados
	{

		printf(" Cadastro %d", i+1);
		printf("\n Unidade: %d", mpedido[i].unidade_Login);
		printf("\n Telefone: %d", mpedido[i].telefone_Cliente);
		printf("\n Produto: %s \n\n\n", mpedido[i].descricao_produto);
		printf("\n_____________\n");
		i++;
	}
	fclose(relatorio);
	printf("\n\n\n");
	system("pause");
}
void tela013()//cancelar o pedido
{
	int flag = 0, cont = 0, w, telefone, posicao_pedido, op;
	system("cls");
	do {
		system("cls");
		limpabuffer();
		relatorio = fopen("relatorio.bin", "w+b");
		fclose(relatorio);
		relatorio = fopen("relatorio.bin", "a+b");
		printf("Digite o telefone do pedido que deseja cancelar:  ");
		scanf("%d", &telefone);
		posicao_pedido = localiza_pedido(telefone);

		if (posicao_pedido >= 0) //Localizar o pedido por telefone 
		{

			for (w = posicao_pedido; w < sizeof(mpedido); w++)
			{
				mpedido[w] = mpedido[w + 1];//pega conteudo da posicao da frente e coloca em cima dessa posicao 
			}
			printf("\nPedido do telefone %d cancelado com sucesso!\n", telefone);
			flag = 1;
			cont--; //decrementa uma unidade pois teve um cadastro a menos  
			int i = 0;

			while (i < sizeof(mpedido))
			{
				fwrite(&mpedido[i], sizeof(mpedido), 1, relatorio);
				i++;
			}
			fclose(relatorio);
		}
		if (!flag) //Checa se ha pedido com telefone digitado
		{
			printf("Cadastro nao encontrado !\n"); //Caso nao haja, informa que nao foi encontrado
		}
		printf("\n 1-Continuar\n 0-Sair\n\n");
		scanf("%d", &op);
	} while (op != 0);
	system("pause");
}

void tela020() //Tela menu produto
{
	char opcao;
	do
	{
		system("cls");
		cabecalho();
		printf("\n                        PRODUTO\n\n");

		printf("\n\n 1-Cadastrar");
		printf("\n 2-Consultar");
		printf("\n 3-Alterar");
		printf("\n 4-Estoque");
		printf("\n 0-Voltar\n");
		printf("\n Escolha uma opcao: ");
		scanf("%s", &opcao);

		if (opcao == '1')
			tela021();
		if (opcao == '2')
			tela022();
		if (opcao == '3')
			tela023();
		if (opcao == '4')
			tela024();
		if (opcao == '0')
			menugeral();

	} while (opcao != '0');
	menugeral();

}

int tela021()//Cadastro produto
{
	limpabuffer();
	system("cls");
	int i=0, codigo, posicao_produto;
	char opcao;
	FILE* arquivo = NULL;

	arquivo = fopen("produto.bin", "a+b");               //Abre o arquivo binario para gravacao
	if (!arquivo)                                        //Verifica se o arquivo foi aberto com sucesso
	{
		printf("\n Arquivo inexistente\n\n");
		system("pause");
		return 0;                                        //forcar o encerramento da aplicacao
	}
		system("cls");
		cabecalho();
		fflush(stdin);
		printf("Codigo do produto: ");         //solicita o codigo a ser gravado para o usuario
		scanf("%d", &codigo);
		posicao_produto = localiza_produto(codigo);

		if (posicao_produto >= 0)
			printf("\nCodigo ja cadastrado\n\n"); //Se ja existir codigo de cadastro, informa o usuario 

		else //Caso nao haja cadastro, cadastra produto
		{
			system("cls");
			cabecalho();
			printf("Codigo %d disponivel", codigo);
			mproduto[posicao_produto].codigo = codigo;
			getchar();
			printf("\n\nDescricao do produto: ");
			fgets(mproduto[posicao_produto].descricao, sizeof(mproduto[posicao_produto].descricao), stdin);
			printf("\n\nPreco do produto: ");
			scanf("%f", &mproduto[posicao_produto].preco);
			printf("\n\nCusto do produto: ");
			scanf("%f", &mproduto[posicao_produto].custo);
			printf("\n\nQuantidade do produto: ");
			scanf("%d", &mproduto[posicao_produto].quantidade);
			printf("\n\nCadastro efetuado com sucesso!\n\n");
			printf("\n_____________\n");
			fwrite(&mproduto[posicao_produto], sizeof(struct produto), 1, arquivo);
			fclose(arquivo);
		}
		inicializa_arquivo_prod();
		printf("\n 1-Continuar\n 0-Sair\n Escolha uma opcao: ");
		scanf("%s", &opcao);
		if (opcao == '1')
		{
			tela021();
		}
		if (opcao == '0')
		{
			tela020();
			fclose(arquivo);
		}
		else
		{
			tela021();
			fclose(arquivo);
		}
	system("pause");
	return 0;
}

void tela022()//Busca de produto
{
	limpabuffer();
	int posicao_produto, codigo;
	char opcao;
	do
	{
		system("cls");
		cabecalho();
		printf("\nCodigo do produto: ");
		scanf("%d", &codigo);
		fflush(stdin);
		posicao_produto = localiza_produto(codigo);

		if (posicao_produto >= 0) //Localiza o produto com o codigo
		{
			printf("\nCodigo     : %d", mproduto[posicao_produto].codigo);
			printf("\nDescricao  : %s", mproduto[posicao_produto].descricao);
			printf("\nPreco      : %.2f", mproduto[posicao_produto].preco);
			printf("\nCusto      : %.2f", mproduto[posicao_produto].custo);
			printf("\nQuantidade : %d", mproduto[posicao_produto].quantidade);
		}

		getchar();
		printf("\n\n 1-Nova busca\n 0-Sair\n Escolha uma opcao: ");
		fflush(stdin);
		scanf("%s", &opcao);
		if (opcao == '1')
		{
			tela022();
		}
		if (opcao == '0')
		{
			tela020();
		}
		else
		{
			tela022();
		}
	} while (opcao != '0');
	tela020();
}

void tela023()//tela de alteracao
{
	limpabuffer();
	int codigo, posicao_produto, i = 0;
	char opcao;
	FILE* arquivo = NULL;
	arquivo = fopen("Produto.bin", "wb"); //Abre arquivo (produto) binario em branco
	fclose(arquivo); //Fecha arquivo (produto)
	arquivo = fopen("Produto.bin", "ab"); //Abrir arquivo (produto) para fazer a gravacao uma embaixo da outra

	do
	{
		system("cls");
		cabecalho();
		printf("\nCodigo do produto para alteracao: ");
		scanf("%s", &codigo);
		fflush(stdin);

		posicao_produto = localiza_produto(codigo);

		if (posicao_produto >= 0) //Localiza o produto
		{
			printf("\n Codgigo    : %d", mproduto[posicao_produto].codigo);
			printf("\n Descricao  : %s", mproduto[posicao_produto].descricao);
			printf(" Preco      : %.2f", mproduto[posicao_produto].preco);
			printf("\n Custo      : %.2f", mproduto[posicao_produto].custo);
			printf("\n Quantidade : %d", mproduto[posicao_produto].quantidade);

			//Solicita os novos dados do produto a serem gravados pelo o usuario
			printf("\n\n Codigo do produto: %d", mproduto[posicao_produto].codigo);
			getchar();
			printf("\n Nova descricao do produto: ");
			fgets(mproduto[posicao_produto].descricao, sizeof(mproduto[posicao_produto].descricao), stdin);
			printf("\n Novo preco do produto: ");
			scanf("%f", &mproduto[posicao_produto].preco);
			printf("\n Novo custo do produto: ");
			scanf("%f", &mproduto[posicao_produto].custo);
			printf("\n Nova quantidade do produto: ");
			scanf("%d", &mproduto[posicao_produto].quantidade);

			while (mproduto[i].codigo != -1) //Grava todos os produtos no arquivo
			{
				fwrite(&mproduto[i], sizeof(struct produto), 1, arquivo);
				i++;
			}
		}
		else
		{
			printf("\n\n   Produto nao cadastrado\n");
		}
		printf("\n\n 1-Nova alteracao\n 0-Sair\n Escolha uma opcao: ");
		scanf("%s", &opcao);
		if (opcao == '1')
		{
			tela023();
		}
		if (opcao == '0')
		{
			tela020();
			fclose(arquivo);
		}
	} while (opcao != '0');
	tela020();
	fclose(arquivo);
	system("pause");
}
void tela024()//Tela lista estoque
{
	int i = 0;
	system("cls");
	cabecalho();
	while (mproduto[i].codigo != -1) //Listar todos os produtos de codigo enquanto diferente de -1
	{
		printf("\n Codgigo    : %d", mproduto[i].codigo);
		printf("\n Descricao  : %s", mproduto[i].descricao);
		printf(" Quantidade : %d\n", mproduto[i].quantidade);
		printf("\n__________\n");
		i++;
	}
	printf("\n\n\n");
	system("pause");
}
void tela040() // relatorios
{
	char opcao;
	system("cls");
	cabecalho();
	printf("\n                        RELATORIO\n\n");
	do
	{
		printf("\n 1-Busca por periodo"); //Baseado na data digitada
		printf("\n 2-Relatorio do dia"); //Todos os registros
		printf("\n 0-Voltar");
		printf("\n\n Escolha uma opcao: ");
		scanf("%s", &opcao);
		getchar();

		if (opcao == '1') //Busca por periodo
		{
			int i = 0, dia, mes, dia_de, dia_ate, mes_de, mes_ate;
			float total = 0, liquido = 0;

			printf("\n (Dia: DD(01...31)\n De: ");
			scanf("%d", &dia_de);
			fflush(stdin);
			printf("\n (Mes: MM(01...12)\n De: ");
			scanf("%d", &mes_de);
			fflush(stdin);
			printf("\n (Dia: DD(01...31)\n Ate: ");
			scanf("%d", &dia_ate);
			fflush(stdin);
			printf("\n (Mes: MM(01...12)\n Ate: ");
			scanf("%d", &mes_ate);
			fflush(stdin);
			system("cls");
			while (i < sizeof(mpedido))
			{
				if (dia_de >= mpedido[i].dia && dia_ate <= mpedido[i].dia && mes_de >= mpedido[i].mes && mes_ate <= mpedido[i].mes) // Imprime relatorio do periodo selecionado
				{
					printf("\n %d/%d/%d", mpedido[i].dia, mpedido[i].mes, mpedido[i].ano);
					printf(" Venda: R$ %.2f", mpedido[i].totalgeral);
					printf("\n Lucro: R$ %.2f", mpedido[i].lucro);
					printf("\n__________________\n");
					total += mpedido[i].totalgeral;
					liquido += mpedido[i].lucro;
				}
				i++;
			}
			printf("\n\n[Total bruto: R$ %.2f             Total liquido: R$ %.2f]\n\n", total, liquido); //Mostra o total liquido e bruto do  periodo escolhido
			system("pause");
		}
		if (opcao == '2') // Mostra todos os registros do dia atual(dia corrente da consulta do relatorio)
		{
			int i = 0, dia, mes, dia_atual, mes_atual;
			float total = 0, liquido = 0;
			dia_atual = data_hora->tm_yday;
			mes_atual = data_hora->tm_mon;

			system("cls");
			cabecalho();

			while (mpedido[i].telefone_Cliente != -1) //Mostra ate chegar na posicao com valor -1
			{
				if (dia_atual == mpedido[i].dia && mes_atual == mpedido[i].mes)
				{
					printf("\n %d/%d/2019", mpedido[i].dia, mpedido[i].mes);
					printf("\n Venda: R$%.2f", mpedido[i].totalgeral);
					printf("\n Lucro: R$%.2f", mpedido[i].lucro);
					printf("\n__________________\n");
					total += mpedido[i].totalgeral;
					liquido += mpedido[i].lucro;
				}
				i++;
			}
			printf("\n\n[Total bruto: R$ %.2f             Total liquido: R$ %.2f]\n\n", total, liquido);
			system("pause");
		}
		if (opcao == '0')
		{
			menugeral();
		}
		else
		{
			tela040();
		}
		tela040();
	} while (opcao != '0');
}

void tela050() //Menu SAC
{
	char opcao;
	do
	{
		system("cls");
		cabecalho();
		printf("\n                        SAC\n");

		printf("\n\n 1-Cadastrar SAC\n 2-Buscar SAC\n 3-Listar\n 0-Voltar\n\n Escolha uma opcao: ");        scanf("%s", &opcao);

		if (opcao == '1')
			cadastro_v();
		if (opcao == '2')
			buscar_sac();
		if (opcao == '3')
			lista_dado();
	} while (opcao != '0');
	menugeral();
}

void cadastro_v() //Menu cadastro SAC
{
	char opcao;
	system("cls");
	cabecalho();
	printf("\n\n 1-SAC de elogio\n 2-SAC de reclamacao\n 0-Voltar\n\n Escolha a opcao: ");
	scanf("%s", &opcao);
	if (opcao == '1') //Cadastrar elogio
	{
		int i = 0;
		limpabuffer();
		while (mCadastro[i][0].telefone != -1) //Procura posicao livre para gravar dados
		{
			i++;
		}
		ptr_elogio = fopen("elogio.bin", "a+b"); //Abre arquivo(elogio) para gravacao de dado
		if (ptr_elogio == NULL)
		{
			printf(" Problema na abertura do arquivo!\n\n");
		}
		else
		{
			system("cls");
			cabecalho();
			mCadastro[i][0].id_elo = i + 1;
			mCadastro[i][0].dia = data_hora->tm_mday; // Recebe dia do momento do cadastro
			mCadastro[i][0].mes = data_hora->tm_mon + 1; // Recebe data-mes do momento do cadastro
			mCadastro[i][0].ano = data_hora->tm_year + 1900; // Recebe ano do momento do cadastro
			printf("\n\n ID: %d\n", mCadastro[i][0].id_elo);
			fflush(stdin);
			printf(" Nome: ");
			fgets(mCadastro[i][0].nome, sizeof(mCadastro[i][0].nome), stdin);
			fflush(stdin);
			printf(" Telefone: ");
			scanf("%d", &mCadastro[i][0].telefone);
			fflush(stdin);
			printf("\n Manifesto: ");
			getchar();
			fgets(mCadastro[i][0].c_mani, sizeof(mCadastro[i][0].c_mani), stdin);
			fflush(stdin);
		}
		fwrite(&mCadastro[i][0], sizeof(cadastro), 1, ptr_elogio);
		printf("\nCadastro efetuado!\n\n\n");
		system("pause");
		printf("\n\n\n");
		fclose(ptr_elogio);
		tela050();
	}
	if (opcao == '2')// Cadastrar reclamacao
	{
		int i = 0;
		while (mCadastro[i][1].telefone != -1)
		{
			i++;
		}
		ptr_reclam = fopen("reclamacao.bin", "a+b");
		if (ptr_reclam == NULL)
		{
			printf("Problema na abertura do arquivo!\n\n");
		}
		else
		{
			system("cls");
			cabecalho();
			mCadastro[i][1].id_elo = i + 1;
			mCadastro[i][1].dia = data_hora->tm_mday; // Recebe dia do momento do cadastro
			mCadastro[i][1].mes = data_hora->tm_mon + 1; // Recebe data-mes do momento do cadastro
			mCadastro[i][1].ano = data_hora->tm_year + 1900; // Recebe ano do momento do cadastro
			fflush(stdin);
			mCadastro[i][1].id_rec = i;
			printf(" ID: %d\n", mCadastro[i][1].id_rec);
			fflush(stdin);
			printf(" Nome: ");
			fgets(mCadastro[i][1].nome, sizeof(mCadastro[i][1].nome), stdin);
			fflush(stdin);
			printf(" Telefone: ");
			scanf("%d", &mCadastro[i][1].telefone);
			fflush(stdin);
			printf("\n Manifesto: ");
			getchar();
			fgets(mCadastro[i][1].c_mani, sizeof(mCadastro[i][1].c_mani), stdin);
			fflush(stdin);;
		}
		fwrite(&mCadastro[i][1], sizeof(cadastro), 1, ptr_reclam);
		printf("\nCadastro efetuado!\n\n\n");
		system("pause");
		printf("\n\n\n");
		fclose(ptr_reclam);
		tela050();
	}
	if (opcao == '0')
	{
		tela050();
	}
	else
	{
		cadastro_v();
	}
}

void buscar_sac() //Menu busca SAC
{
	char opcao;
	system("cls");
	cabecalho();
	fflush(stdin);
	printf("\n 1-Busca elogio\n 2-Busca reclamacao\n 0-Voltar\n\n Escolha uma opcao: ");
	scanf("%s", &opcao);
	do
	{
		if (opcao == '1')  //Busca elogio pelo numero de telefone
		{
			int i = 0, tell;
			system("cls");
			cabecalho();
			fflush(stdin);
			printf("\n Digite o telefone para busca: ");
			scanf("%d", &tell);
			while (mCadastro[i][0].telefone != -1 && i < 201)
			{
				if (tell == mCadastro[i][0].telefone)
				{
					printf("\n\n Cadastro localizado!\n\n");
					printf("\n %d/%d/%d", mCadastro[i][0].dia, mCadastro[i][0].mes, mCadastro[i][0].ano);
					printf("\n ID: %d", mCadastro[i][0].id_elo);
					printf("\n Nome: %s", mCadastro[i][0].nome);
					printf(" Telefone: %d\n", mCadastro[i][0].telefone);
					printf(" Manifesto: %s", mCadastro[i][0].c_mani);
					printf("________________________\n");
					system("pause");
					tela050();
				}
				i++;
			}
			if (mCadastro[i][0].telefone == -1 || tell != mCadastro[i][0].telefone)
			{
				printf("\n\nCadastro nao localizado!\n\n_______________\n\n");
				system("pause\n\n");
			}
		}
		if (opcao == '2')  //Busca reclamacao pelo numero de telefone
		{
			int i = 0, tell;
			system("cls");
			cabecalho();
			fflush(stdin);
			printf("\n Digite o telefone para busca: ");
			scanf("%d", &tell);
			while (mCadastro[i][1].telefone != -1 && i < 201)
			{
				if (tell == mCadastro[i][1].telefone)
				{
					printf("\n\n Cadastro localizado!\n\n");
					printf("\n %d/%d/%d", mCadastro[i][1].dia, mCadastro[i][1].mes, mCadastro[i][1].ano);
					printf("\n ID: %d", mCadastro[i][1].id_elo);
					printf("\n Nome: %s", mCadastro[i][1].nome);
					printf(" Telefone: %d\n", mCadastro[i][1].telefone);
					printf(" Manifesto: %s\n\n", mCadastro[i][1].c_mani);
					printf("________________________\n\n");
					system("pause");
					tela050();
				}
			}
			if (mCadastro[i][1].telefone == -1 || tell != mCadastro[i][1].telefone)
			{
				printf("\n\nCadastro nao localizado!\n\n_______________\n");
				system("pause\n\n");
			}
		}
		if (opcao == '0')
		{
			tela050();
		}
		else
		{
			buscar_sac();
		}
	} while (opcao != '0');
	tela050();
}

void lista_dado() //Mostra os dados de SAC
{
	char opcao;
	system("cls");
	cabecalho();
	printf("\n 1-Elogio\n 2-Reclamacao\n 0-Voltar\n\n Escolha uma opcao: ");
	fflush(stdin);
	scanf("%s", &opcao);
	do
	{
		if (opcao == '1')// Mostra dados de elogio
		{
			int j = 0, cont = 0;
			system("cls");
			cabecalho();
			ptr_elogio = fopen("elogio.bin", "r+b");
			if (ptr_elogio == NULL)
			{
				printf("\n Problema na abertura do arquivo!\n\n");
			}
			else
			{
				while (j < 200)
				{
					if (mCadastro[j][0].telefone != -1)
					{
						cont++;
					}
					j++;
				}

				for (int i = 0; i < cont; i++)
				{
					printf("\n %d/%d/%d", mCadastro[i][0].dia, mCadastro[i][0].mes, mCadastro[i][0].ano);
					printf("\n ID: %d", mCadastro[i][0].id_elo);
					printf("\n Nome: %s", mCadastro[i][0].nome);
					printf(" Telefone: %d", mCadastro[i][0].telefone);
					printf("\n Manifesto: %s", mCadastro[i][0].c_mani);
					printf("\n__________________");
				}
			}
			fclose(ptr_elogio);
			printf("\n\nElogios totais: %d\n\n", cont);
			system("pause\n\n");
			lista_dado();
		};
		if (opcao == '2') // Mostra dados reclamacao
		{
			int j = 0, cont = 0;
			system("cls");
			cabecalho();
			ptr_reclam = fopen("reclamacao.bin", "r+b");
			if (ptr_reclam == NULL)
			{
				printf("\n Problema na abertura do arquivo!\n\n");
			}
			else
			{
				while (j < 200)
				{
					if (mCadastro[j][1].telefone != -1)
					{
						cont++;
					}
					j++;
				}
				for (int i = 0; i < cont; i++)
				{
					printf("\n%d/%d/%d", mCadastro[i][1].dia, mCadastro[i][1].mes, mCadastro[i][1].ano);
					printf("\n ID: %d", mCadastro[i][1].id_elo);
					printf("\n Nome: %s", mCadastro[i][1].nome);
					printf(" Telefone: %d", mCadastro[i][1].telefone);
					printf("\n Manifesto: %s", mCadastro[i][1].c_mani);
					printf("\n__________________");
				}
			}
			fclose(ptr_reclam);
			printf("\n\n Reclamacoes totais: %d\n\n", cont);
			system("pause\n\n");
			lista_dado();
		}
		if (opcao == '0')
		{
			tela050();
		}
	} while (opcao != '0');
	lista_dado();
}
void tela060() //Menu funcionario
{
	char opcao;
	do
	{
		system("cls");
		cabecalho();
		printf("\n                        Funcionario\n");
		printf("\n 1-Cadastrar Funcionarios\n 2-Listar Funcionarios\n 0-sair\n\n Escolha uma opcao: ");
		scanf("%s", &opcao);
		if (opcao == '1') // Faz cadastro dos funcionarios
		{
			cadastrar_funcionario();
		}
		if (opcao == '2') // Mostra os funcionarios e seus dados
		{
			listar();
		}
	} while (opcao != '0'); // Caso 0, encerra o loop e volta ao menu geral
	menugeral();
}

void cadastrar_funcionario() //cadastrar funcionario
{
	FILE* func = NULL;
	char op;
	int i = 0;

	while (m_funcionarios[i].pos != -1) // Busca por uma posicao disponivel 
	{
		i++;
	}
	func = fopen("arqficha.bin", "a+b");//Abrir o  arquivo para gravacao em binario

	system("cls");
	printf("\n                     FUNCIONARIOS\n\n ");
	getchar();
	printf("\nEntre com o nome: "); //Dados para o cadastro do funcionario
	fgets(m_funcionarios[i].nome, 50, stdin);
	fflush(stdin);
	printf("\nEntre com o cpf: ");
	fgets(m_funcionarios[i].cpf, 15, stdin);
	fflush(stdin);
	printf("\nEntre com o cargo: ");
	fgets(m_funcionarios[i].cargo, 15, stdin);
	fflush(stdin);

	fwrite(&m_funcionarios[i], sizeof(struct fichaf), 1, func); //Faz a gravacao no arquivo
	{
		i++;
	}

	fclose(func);
	printf("Cadastro efetuado com sucesso!\n\n");
	printf("\n____________________\n");
	printf("\n 1-Continuar\n 0-Sair\n"); //Caso queira cadastrar outro funcionario, apertar a tecla 1
	scanf("%s", &op);
	fflush(stdin);
	if (op == '1')
	{
		cadastrar_funcionario();
	}
	if (op == '0')
	{
		tela060();
	}
	if (op == '0')
	{
		tela060();
	}
	menugeral();
}

void listar() //listar o conteudo do arquivo
{
	int i = 0;
	FILE* func = NULL;
	func = fopen("arqficha.bin", "r+b");
	system("cls");
	cabecalho();
	printf("\n\n");
	while (fread(&m_funcionarios, sizeof(fichaf), 1, func) == 1)
	{
		fflush(stdin);
		printf("\n_______________________\n");
		printf(" Cadastro %d", i + 1);
		printf("\n Nome: %s", m_funcionarios[i].nome);
		printf(" Cpf: %s", m_funcionarios[i].cpf);
		printf(" Cargo: %s", m_funcionarios[i].cargo);
		i++;
	}
	fclose(func);
	printf("\n\n");
	system("pause");
}

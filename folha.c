/*Aluno: Matheus G. M. de Oliveira
RA: 183959-2024
Obj: Este exercício tem como objetivo aplicar os conceitos de estruturas de dados em C,
especificamente listas simplesmente encadeadas, para criar um programa de cadastro de
funcionários. */

// bibliotecas necessárias
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <locale.h>

// função para posicionar o cursor
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = (short)x;
	coord.Y = (short)y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// construção da tela
void tela()
{
	int lin;
	int col;

	// se a biblioteca correta não for declarada o system cls não ira funcionar "stdlib. h". Sua função é limpar a tela de saída
	system("cls");
	// para definir a cor da tela
	system("color 5F");

	// usando o gotoxy para posicionar corretamente os caracteres e formar uma tela mais xuxuzinha
	for (lin = 1; lin < 25; lin++)
	{
		gotoxy(1, lin);
		printf("|");
		gotoxy(79, lin);
		printf("|");
	}

	for (col = 1; col < 80; col++)
	{
		gotoxy(col, 1);
		printf("-");
		gotoxy(col, 4);
		printf("-");
		gotoxy(col, 22);
		printf("-");
		gotoxy(col, 24);
		printf("-");
	}

	gotoxy(1, 1);
	printf("+");
	gotoxy(79, 1);
	printf("+");

	gotoxy(1, 4);
	printf("+");
	gotoxy(79, 4);
	printf("+");

	gotoxy(1, 22);
	printf("+");
	gotoxy(79, 22);
	printf("+");

	gotoxy(3, 2);
	printf("UNICV");
	gotoxy(60, 2);
	printf("ESTRUTURA DE DADOS | ");
	gotoxy(3, 3);
	printf("CADASTRO DE FUNCIONARIOS");
	gotoxy(62, 3);
	printf("Matheus Moreira  | ");
	gotoxy(2, 23);
	printf("MSG: ");
	gotoxy(30, 03);
	printf(" - Menu principal -");
}

// estrutura de dados
typedef struct
{
	int codigo;
	float salario;
	char nome[50];
	char endereco[50];
	char cargo[50];
	char telefone[15];
	char dt_admissao[11];
} reg_funcionarios;

// é um ponteiro
typedef struct tipoItem *TipoApontador;

typedef struct tipoItem
{
	reg_funcionarios conteudo;
	TipoApontador proximo;
} TipoItem;

// uma estrutura com dois campos
typedef struct
{
	TipoApontador primeiro;
	TipoApontador ultimo;

} Tipolista;

// criando a tela responsável por fazer as "perguntas " para o cadastro do usuario
void tela_funcionario()
{
	gotoxy(32, 8);
	printf("Codigo..........:");
	gotoxy(32, 10);
	printf("1-Nome..........:");
	gotoxy(32, 12);
	printf("2-Telefone......:");
	gotoxy(32, 14);
	printf("3-Cargo.........:");
	gotoxy(32, 16);
	printf("4-Salario.......:");
	gotoxy(32, 18);
	printf("5-Endereco......:");
	gotoxy(32, 20);
	printf("6-Data Admissao.:");
}

// TIPO APONTADOR PRA "PESQUISA"
TipoApontador pesquisa(Tipolista *l, int cod)
{
	TipoApontador opc2 = l->primeiro;
	while (opc2 != NULL)
	{
		if (opc2->conteudo.codigo == cod)
		{
			return opc2;
		}
		opc2 = opc2->proximo;
	}
	return NULL;
}

// func que vai ser responsável por contar a quant de elementos na lista,
// ele vai percorrer a lista, necessário para quando perguntar qual posicao quero cadastrar
int contador(Tipolista *l)
{
	TipoApontador opc2;
	int cont = 0;
	opc2 = l->primeiro;
	while (opc2 != NULL)
	{
		opc2 = opc2->proximo;
		cont++;
	}
	return cont;
}

// para cadastrar o funcionario no final
void cadastra_funcionarios(Tipolista *l, int opcao)
{
	reg_funcionarios reg_func;
	TipoApontador P;
	TipoApontador opc2;
	int resposta;
	int posicao;
	int quantidade;
	int x;

	do
	{
		do
		{
			tela();
			tela_funcionario();
			gotoxy(28, 03);
			printf("- Cadastrando Funcionario - ");
			if (opcao == 1)
			{
				gotoxy(30, 05);
				printf("- Inserir no final");
			}
			else if (opcao == 2)
			{
				gotoxy(30, 05);
				printf("- Inserir no inicio");
			}
			else if (opcao == 3)
			{
				gotoxy(30, 05);
				printf("- Inserir na posicao");
			}

			opc2 = pesquisa(l, reg_func.codigo);
			if (opc2 != NULL)
			{
				gotoxy(06, 23);
				printf("Funcionario cadastrado");
				getch();
			}

		} while (opc2 != NULL);

		gotoxy(49, 8);
		scanf("%d", &reg_func.codigo);

		gotoxy(49, 10);
		fflush(stdin);
		fgets(reg_func.nome, 50, stdin);

		gotoxy(49, 12);
		fflush(stdin);
		fgets(reg_func.telefone, 11, stdin);

		gotoxy(49, 14);
		fflush(stdin);
		fgets(reg_func.cargo, 50, stdin);

		gotoxy(49, 16);
		fflush(stdin);
		scanf("%f", &reg_func.salario);

		gotoxy(49, 18);
		fflush(stdin);
		fgets(reg_func.endereco, 50, stdin);

		gotoxy(49, 20);
		fflush(stdin);
		fgets(reg_func.dt_admissao, 50, stdin);

		// pergunta se quer cadastrar esses dados ou não
		gotoxy(06, 23);
		printf("Deseja gravar esses dados? 1 - Sim | 2 - Nao: ");
		scanf("%d", &resposta);
		gotoxy(06, 23);
		printf("                                                      ");
		// Se a lista está vazia, o primeiro e último funcionário são o mesmo
		if (resposta == 1)
		{
			// tenho que fazer isso pra criar o objeto
			P = (TipoApontador)malloc(sizeof(TipoItem));
			P->proximo = NULL;

			P->conteudo = reg_func;
			if (opcao == 1)
			{
				if (l->primeiro == NULL)
				{
					l->primeiro = P;
					l->ultimo = P;
				}
				else
				{
					l->ultimo->proximo = P;
					l->ultimo = P;
				}
			}
			// parte responsável por cadastrar o func no final
			else if (opcao == 2)
			{
				if (l->primeiro == NULL)
				{
					l->primeiro = P;
					l->ultimo = P;
				}
				else
				{
					P->proximo = l->primeiro;
					l->primeiro = P;
				}
			}
			else if (opcao == 3)
			{
				do
				{
					gotoxy(06, 23);
					printf("                                              ");
					gotoxy(06, 23);
					printf("Digite qual a posicao?: ");
					scanf("%d", &posicao);
					quantidade = contador(l);
					if (posicao > quantidade)
					{
						gotoxy(06, 23);
						printf("                                                ");
						gotoxy(06, 23);
						printf("Posicao invalida");
						getch();
					}
				} while (posicao > quantidade);
				opc2 = l->primeiro;
				for (x = 1; x <= posicao - 2; x++)
				{
					opc2 = opc2->proximo;
				}

				P->proximo = opc2->proximo;
				opc2->proximo = P;
			}

			gotoxy(06, 23);
			printf("                                                      ");
			gotoxy(06, 23);
			printf("Funcionario cadastrado com sucesso!");
			getch();
		}

		gotoxy(06, 23);
		printf("                                                             ");
		gotoxy(06, 23);
		printf("1 - Cadastrar outro funcionario | 2 - Voltar ao menu ");
		scanf("%d", &resposta);

	} while (resposta == 1);
}
// Listando os funcionários | mostra os dados do usuário

void listar_funcionarios(Tipolista *l)
{
	TipoApontador P = l->primeiro;
	while (P != NULL)
	{
		tela();
		gotoxy(27, 3);
		printf(" - Lista a ficha dos funcionarios -");

		gotoxy(27, 7);
		printf("Codigo...........: %d", P->conteudo.codigo);
		gotoxy(27, 9);
		printf("1-Nome...........: %s", P->conteudo.nome);
		gotoxy(27, 11);
		printf("2-Telefone.......: %s", P->conteudo.telefone);
		gotoxy(27, 13);
		printf("3-Cargo..........: %s", P->conteudo.cargo);
		gotoxy(27, 15);
		printf("4-Salario........: %.2f", P->conteudo.salario);
		gotoxy(27, 17);
		printf("5-Endereco.......: %s", P->conteudo.endereco);
		gotoxy(27, 19);
		printf("6-Data Admissao..: %s", P->conteudo.dt_admissao);

		// Move para o próximo funcionário
		P = P->proximo;

		// Mensagem de espera
		gotoxy(06, 23);
		printf("Pressione qualquer tecla para continuar...");
		getch();
	}
}

// função para alterar os funcionários
void alterar_funcionarios(Tipolista *l)
{
	reg_funcionarios reg_func;
	TipoApontador opc2;
	int resposta;
	int campo;

	do
	{
		do
		{

			tela();
			tela_funcionario();
			gotoxy(28, 03);
			printf("- Alteracao de funcionario -");
			gotoxy(50, 8);
			scanf("%d", &reg_func.codigo);
			opc2 = pesquisa(l, reg_func.codigo);
			if (opc2 == NULL)
			{
				gotoxy(07, 23);
				printf("Funcionario nao cadastrado.");
				getch();
			}
		} while (opc2 == NULL);
		reg_func = opc2->conteudo;
		// mostrar o registro do funcionario
		gotoxy(50, 10);
		printf("%s", opc2->conteudo.nome);
		gotoxy(50, 12);
		printf("%s", opc2->conteudo.telefone);
		gotoxy(50, 14);
		printf("%s", opc2->conteudo.cargo);
		gotoxy(50, 16);
		printf("%.2f", opc2->conteudo.salario);
		gotoxy(50, 18);
		printf("%s", opc2->conteudo.endereco);
		gotoxy(50, 20);
		printf("%s", opc2->conteudo.dt_admissao);
		do
		{
			do
			{
				gotoxy(07, 23);
				printf("                                                                                                    ");
				gotoxy(07, 23);
				printf("Digite o Campo a Ser Alterado 0 = Sair: ");
				scanf("%d", &campo);
				gotoxy(07, 23);
				printf("                                                       ");
				if (campo < 0 || campo > 6)
				{
					gotoxy(07, 23);
					printf("                                                                                                    ");
					gotoxy(07, 23);
					printf("Campo Invalido");
					getch();
				}
			} while (campo < 0 || campo > 6);

			switch (campo)
			{
			case 1:
				gotoxy(45, 9);
				printf("                                                       ");
				gotoxy(45, 9);
				fflush(stdin);
				fgets(reg_func.nome, 50, stdin);
				break;
			case 2:
				gotoxy(45, 11);
				printf("                                                                                        ");
				gotoxy(45, 11);
				fflush(stdin);
				fgets(reg_func.telefone, 15, stdin);
				break;
			case 3:
				gotoxy(45, 13);
				printf("                                                                                        ");
				gotoxy(45, 13);
				fflush(stdin);
				fgets(reg_func.cargo, 50, stdin);
				break;
			case 4:
				gotoxy(45, 15);
				printf("                                                                                        ");
				gotoxy(45, 15);
				fflush(stdin);
				scanf("%f", &reg_func.salario);
				break;
			case 5:
				gotoxy(45, 17);
				printf("                                                                                        ");
				gotoxy(45, 17);
				fflush(stdin);
				fgets(reg_func.endereco, 50, stdin);
				break;
			case 6:
				gotoxy(45, 19);
				printf("                                                                                        ");
				gotoxy(45, 19);
				fgets(reg_func.dt_admissao, 11, stdin);
				break;
			}
		} while (campo != 0);
		// confirmando a alteraçao
		gotoxy(07, 23);
		printf("Confirma a Alteracao 1 = Sim | 2 = Nao");
		scanf("%d", &resposta);
		gotoxy(07, 23);
		printf("                                                       ");
		if (resposta == 1)
		{
			opc2->conteudo = reg_func;
		}

		gotoxy(07, 23);
		printf("Deseja alterar outro 1 = Sim | 2 = Nao?");
		scanf("%d", &resposta);
		gotoxy(07, 23);
		printf("                                                       ");
	} while (resposta == 1);
}

// para remover o funcionario no final
void Remover_funcionarioFinal(Tipolista *L)
{
	system("cls");
	tela();

	// Verifica se a lista está vazia
	if (L->primeiro == NULL)
	{
		gotoxy(7, 23);
		printf("Nenhum funcionario cadastrado!");
		getch();
		return;
	}

	// Se só houver um funcionário, a lista vai ficar vazia após a remoção
	if (L->primeiro == L->ultimo)
	{
		free(L->primeiro);
		L->primeiro = NULL;
		L->ultimo = NULL;

		gotoxy(7, 23);
		printf("Funcionario removido com sucesso!");
		getch();
		return;
	}

	// Caso contrário, percorre a lista até encontrar o penúltimo funcionário
	TipoApontador P = L->primeiro;
	while (P->proximo != L->ultimo)
	{
		P = P->proximo;
	}

	// Remove o último funcionário
	free(L->ultimo);
	L->ultimo = P;
	L->ultimo->proximo = NULL;

	gotoxy(7, 23);
	printf("Funcionario removido com sucesso!");
	getch();
}

// para remover o funcionario no inicio
void Remover_funcionarioInicio(Tipolista *L)
{
	system("cls");
	tela();

	// Verifica se a lista está vazia
	if (L->primeiro == NULL)
	{
		gotoxy(7, 23);
		printf("Nenhum funcionario cadastrado!");
		getch();
		return;
	}

	// Se só houver um funcionário, a lista ficará vazia após a remoção
	if (L->primeiro == L->ultimo)
	{
		free(L->primeiro);
		L->primeiro = NULL;
		L->ultimo = NULL;
	}
	else
	{
		// Remove o primeiro funcionário
		TipoApontador temp = L->primeiro;
		L->primeiro = L->primeiro->proximo;
		free(temp);
	}

	gotoxy(7, 23);
	printf("Funcionario removido com sucesso!");
	getch();
}

void Remover_funcionarioPosicao(Tipolista *L)
{
	system("cls");
	tela();

	// Verifica se a lista está vazia
	if (L->primeiro == NULL)
	{
		gotoxy(7, 23);
		printf("Nenhum funcionario cadastrado!");
		getch();
		return;
	}

	int posicao, i;
	TipoApontador P, anterior;

	gotoxy(7, 7);
	printf("Digite a posicao do Funcionario: ");
	scanf("%d", &posicao);

	// Verifica se a posição é válida
	if (posicao < 1 || posicao > contador(L))
	{
		gotoxy(7, 23);
		printf("Posicao invalida!");
		getch();
		return;
	}

	P = L->primeiro;

	// Se for remover o primeiro funcionário
	if (posicao == 1)
	{
		L->primeiro = P->proximo;
		if (L->primeiro == NULL) // Se só houver um elemento
		{
			L->ultimo = NULL;
		}
		free(P);
	}
	else
	{
		// Percorrer até o elemento da posição desejada
		for (i = 1; i < posicao; i++)
		{
			anterior = P;
			P = P->proximo;
		}

		// Remove o funcionário na posição
		anterior->proximo = P->proximo;
		if (P == L->ultimo) // Se for o último elemento
		{
			L->ultimo = anterior;
		}
		free(P);
	}

	gotoxy(7, 23);
	printf("Funcionario removido com sucesso!");
	getch();
}

int main()
{
	tela();
	int opcao;
	// CRIADO PARA NÃO APONTAR PARA NADA
	Tipolista l;
	// inicializar a lista = atribuir null para os ponteiros primeiro e ultimo
	l.primeiro = NULL;
	l.ultimo = NULL;
	TipoApontador P;

	do
	{

		tela();
		gotoxy(24, 5);
		printf("1 - Cadastrar funcionario no final ");
		gotoxy(24, 7);
		printf("2 - Cadastrar funcionario no inicio ");
		gotoxy(24, 9);
		printf("3 - Cadastrar funcionario na posicao ");
		gotoxy(24, 11);
		printf("4 - Remover funcionario no final ");
		gotoxy(24, 13);
		printf("5 - Remover funcionario no inicio ");
		gotoxy(24, 15);
		printf("6 - Remover funcionario na posicao ");
		gotoxy(24, 17);
		printf("7 - Alteracao do funcionario  ");
		gotoxy(24, 19);
		printf("8 - Listar funcionarios ");
		gotoxy(24, 21);
		printf("9 - Sair ");
		gotoxy(06, 23);
		printf("Digite a opcao: ");
		scanf("%d", &opcao);

		switch (opcao)
		{
		case 1:
			// opc 1 cadastrar func no final
			cadastra_funcionarios(&l, opcao); // Chama a função para cadastrar um funcionário
			break;
		case 2:
			// opc 2 cadastrar no começo
			cadastra_funcionarios(&l, opcao);
			break;
		case 3:
			// cadastrar na posi
			cadastra_funcionarios(&l, opcao);
			break;
		case 4:
			Remover_funcionarioFinal(&l);
			break;
		case 5:
			Remover_funcionarioInicio(&l);
			break;
		case 6:
			Remover_funcionarioPosicao(&l);
			break;
		case 7:
			// alterar func
			alterar_funcionarios(&l);
			break;
		case 8:
			// listar func
			listar_funcionarios(&l);
			break;
		// função responsável por sair do programa
		case 9:
			gotoxy(06, 23);
			printf("Saindo do programa...");
			getch();
			break;
			// se caso o usuário digitar algo diferente de 9
		default:
			gotoxy(06, 23);
			printf("Opcao Invalida. Tente Novamente.");
			getch();
			break;
		}

	} while (opcao != 9);

	// liberar memoria
	while (l.primeiro != NULL)
	{
		P = l.primeiro;
		l.primeiro = l.primeiro->proximo;
		free(P);
	}
	l.primeiro = NULL;
	l.ultimo = NULL;
	return 0;
}
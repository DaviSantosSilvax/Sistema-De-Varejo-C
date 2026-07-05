#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* --- CONSTANTES --- */
// Restrição obrigatória: A loja realiza 50 vendas por dia
#define MAX_VENDAS_DIA 50
#define NUM_MESES 12

/* --- ESTRUTURAS (STRUCTS) --- */

// Struct para o registro do cliente
typedef struct {
  int id;
  char nome[50];
} Cliente;

// Struct para o registro do produto
typedef struct {
  int id;
  char descricao[50];
  float preco;
} Produto;

// Struct para o registro do pedido completo
typedef struct {
  int idPedido;
  int mes; // 1 a 12 (para facilitar o relatorio anual)
  Cliente cliente;
  Produto produto;
  int quantidade;
  int numDevolucoes; // Usado para a regra de negocio da transportadora
  float valorTotal;
} Pedido;

// Struct auxiliar para ajudar na ordenacao do Relatorio Anual
typedef struct {
  int mes;
  float faturamento;
} FaturamentoMes;

/* --- PROTOTIPOS DAS FUNCOES --- */
void registrarVenda(Pedido vendas[], int *qtdVendas, float totaisMensais[]);
void registrarDevolucao(Pedido vendas[], int qtdVendas, float totaisMensais[]);
void relatorioDiario(Pedido vendas[], int qtdVendas);
void relatorioMensal(float totaisMensais[]);
void relatorioAnual(float totaisMensais[]);
void ordenarMeses(FaturamentoMes array[], int tamanho);

/* --- FUNCAO PRINCIPAL (MAIN) --- */
int main() {
  // Array para armazenar as vendas do dia (cumprindo a restricao de 50 vendas)
  Pedido vendasDoDia[MAX_VENDAS_DIA];

  // Array para armazenar o consolidado de cada mes (indices 0 a 11)
  float faturamentoMensal[NUM_MESES] = {0.0};

  int qtdVendasDia = 0;
  int opcao;

  do {
    // Menu de interacao
    printf("\n=== SISTEMA DE GESTAO DE VAREJO ===\n");
    printf("1. Registrar Venda (Restante: %d)\n",
           MAX_VENDAS_DIA - qtdVendasDia);
    printf("2. Registrar Devolucao de Item\n");
    printf("3. Relatorio Diario\n");
    printf("4. Relatorio Mensal\n");
    printf("5. Relatorio Anual\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);

    switch (opcao) {
    case 1:
      registrarVenda(vendasDoDia, &qtdVendasDia, faturamentoMensal);
      break;
    case 2:
      registrarDevolucao(vendasDoDia, qtdVendasDia, faturamentoMensal);
      break;
    case 3:
      relatorioDiario(vendasDoDia, qtdVendasDia);
      break;
    case 4:
      relatorioMensal(faturamentoMensal);
      break;
    case 5:
      relatorioAnual(faturamentoMensal);
      break;
    case 0:
      printf("Encerrando o sistema e salvando dados...\n");
      break;
    default:
      printf("Opcao invalida! Tente novamente.\n");
    }
  } while (opcao != 0);

  return 0;
}

/* --- IMPLEMENTACAO DAS FUNCOES --- */

// Funcao para registrar uma nova venda
void registrarVenda(Pedido vendas[], int *qtdVendas, float totaisMensais[]) {
  // Valida a restricao obrigatoria de 50 vendas diarias
  if (*qtdVendas >= MAX_VENDAS_DIA) {
    printf("\n[ERRO] A quantidade maxima de %d vendas diarias foi atingida!\n",
           MAX_VENDAS_DIA);
    return;
  }

  Pedido novoPedido;
  novoPedido.idPedido = *qtdVendas + 1;

  printf("\n--- Registro de Cliente ---\n");
  printf("Nome do Cliente: ");
  getchar(); // Limpar o buffer do teclado
  fgets(novoPedido.cliente.nome, 50, stdin);
  novoPedido.cliente.nome[strcspn(novoPedido.cliente.nome, "\n")] =
      0; // Remove o '\n' do final

  printf("\n--- Registro de Produto ---\n");
  printf("Descricao do Produto: ");
  fgets(novoPedido.produto.descricao, 50, stdin);
  novoPedido.produto.descricao[strcspn(novoPedido.produto.descricao, "\n")] = 0;

  printf("Valor (preco) do Produto: R$ ");
  scanf("%f", &novoPedido.produto.preco);

  printf("Quantidade adquirida: ");
  scanf("%d", &novoPedido.quantidade);

  printf("Mes da Venda (1-12): ");
  scanf("%d", &novoPedido.mes);

  // Inicializa contador de devolucoes em zero
  novoPedido.numDevolucoes = 0;

  // Calculo do valor total de cada item do pedido
  novoPedido.valorTotal = novoPedido.produto.preco * novoPedido.quantidade;

  // Salva o pedido no Array
  vendas[*qtdVendas] = novoPedido;

  // Adiciona o valor ao faturamento consolidado do mes (indice = mes - 1)
  if (novoPedido.mes >= 1 && novoPedido.mes <= 12) {
    totaisMensais[novoPedido.mes - 1] += novoPedido.valorTotal;
  }

  (*qtdVendas)++; // Incrementa o total de vendas do dia
  printf("\n[SUCESSO] Venda #%d registrada com sucesso! Valor Total: R$ %.2f\n",
         novoPedido.idPedido, novoPedido.valorTotal);
}

// Funcao para aplicar a Regra de Negocio da Transportadora (Taxa de Devolucao)
void registrarDevolucao(Pedido vendas[], int qtdVendas, float totaisMensais[]) {
  int idBusca;
  printf("\nInforme o ID do Pedido devolvido: ");
  scanf("%d", &idBusca);

  // Valida se o ID existe
  if (idBusca <= 0 || idBusca > qtdVendas) {
    printf("\n[ERRO] Pedido nao encontrado!\n");
    return;
  }

  int index = idBusca - 1; // O indice no array e o ID - 1
  vendas[index].numDevolucoes++;

  printf(
      "\n[INFO] Devolucao registrada. Total de devolucoes do Pedido #%d: %d\n",
      idBusca, vendas[index].numDevolucoes);

  // Regra de negocio: Se devolvido pela segunda vez, cobra taxa fixa de R$
  // 20,00
  if (vendas[index].numDevolucoes == 2) {
    printf("[ATENCAO] Regra de Negocio Aplicada: Cobranca de taxa fixa de R$ "
           "20.00 referente as despesas da transportadora.\n");
    vendas[index].valorTotal += 20.00;

    // Atualiza tambem o array consolidado do relatorio mensal
    if (vendas[index].mes >= 1 && vendas[index].mes <= 12) {
      totaisMensais[vendas[index].mes - 1] += 20.00;
    }
  }
}

// 1) Relatorio Diario
void relatorioDiario(Pedido vendas[], int qtdVendas) {
  float totalDia = 0.0;
  printf("\n=== 1) RELATORIO DIARIO ===\n");

  if (qtdVendas == 0) {
    printf("Nenhum pedido realizado hoje.\n");
    return;
  }

  // Listagem dos pedidos do dia e seus respectivos valores
  for (int i = 0; i < qtdVendas; i++) {
    printf(
        "Pedido #%d | Cliente: %s | Produto: %s | Qtd: %d | Total: R$ %.2f\n",
        vendas[i].idPedido, vendas[i].cliente.nome, vendas[i].produto.descricao,
        vendas[i].quantidade, vendas[i].valorTotal);
    totalDia += vendas[i].valorTotal;
  }
  printf("----------------------------------------------------\n");
  // Valor total das vendas diarias
  printf("Faturamento Total do Dia: R$ %.2f\n", totalDia);
}

// 2) Relatorio Mensal
void relatorioMensal(float totaisMensais[]) {
  float totalConsolidado = 0.0;
  printf("\n=== 2) RELATORIO MENSAL ===\n");

  // Listagem do total vendido em cada mes
  for (int i = 0; i < NUM_MESES; i++) {
    if (totaisMensais[i] > 0) {
      printf("Mes %02d: R$ %.2f\n", i + 1, totaisMensais[i]);
    }
    totalConsolidado += totaisMensais[i];
  }
  printf("----------------------------------------------------\n");
  // Valor total consolidado das vendas mensais
  printf("Valor Total Consolidado (Todos os Meses): R$ %.2f\n",
         totalConsolidado);
}

// Algoritmo de Ordenacao (Bubble Sort) utilizado no Relatorio Anual
void ordenarMeses(FaturamentoMes array[], int tamanho) {
  FaturamentoMes temp;
  for (int i = 0; i < tamanho - 1; i++) {
    for (int j = 0; j < tamanho - i - 1; j++) {
      // Ordena em ordem decrescente (maior faturamento para o menor)
      if (array[j].faturamento < array[j + 1].faturamento) {
        temp = array[j];
        array[j] = array[j + 1];
        array[j + 1] = temp;
      }
    }
  }
}

// 3) Relatorio Anual
void relatorioAnual(float totaisMensais[]) {
  FaturamentoMes arrayOrdenacao[NUM_MESES];
  float totalAno = 0.0;

  // Preenche a struct auxiliar para a ordenacao e calcula o total do ano
  for (int i = 0; i < NUM_MESES; i++) {
    arrayOrdenacao[i].mes = i + 1;
    arrayOrdenacao[i].faturamento = totaisMensais[i];
    totalAno += totaisMensais[i]; // Total das vendas realizadas ao longo do ano
  }

  // Chama o Algoritmo de Ordenacao
  ordenarMeses(arrayOrdenacao, NUM_MESES);

  printf("\n=== 3) RELATORIO ANUAL (ORDEM DECRESCENTE) ===\n");

  // Apresentar os meses em ordem decrescente de faturamento
  for (int i = 0; i < NUM_MESES; i++) {
    if (arrayOrdenacao[i].faturamento > 0) {
      printf("%do Maior Faturamento -> Mes %02d: R$ %.2f\n", i + 1,
             arrayOrdenacao[i].mes, arrayOrdenacao[i].faturamento);
    }
  }
  printf("----------------------------------------------------\n");
  printf("Faturamento Total do Ano: R$ %.2f\n", totalAno);
}
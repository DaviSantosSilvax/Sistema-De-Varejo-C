# Sistema de Gestão e Otimização de Processos para o Setor de Varejo 🛒🖥️

Projeto de Extensão desenvolvido para a disciplina de **Algoritmos e Laboratório de Programação** do curso de Ciência da Computação da Universidade Veiga de Almeida (UVA). 

O sistema foi construído inteiramente em **Linguagem C** e tem como objetivo digitalizar e otimizar o registro de vendas diárias de pequenos e médios comércios varejistas, substituindo métodos manuais (como cadernos e planilhas simples) por uma solução estruturada e eficiente.

## 🎯 Objetivos de Desenvolvimento Sustentável (ODS)
Este projeto está alinhado com a **Agenda 2030 da ONU**, atuando diretamente nos seguintes objetivos:
* **ODS 8 (Trabalho Decente e Crescimento Econômico):** Apoia a modernização tecnológica e a eficiência de micro e pequenas empresas.
* **ODS 9 (Indústria, Inovação e Infraestrutura):** Insere negócios locais na era digital através da automação de cálculos operacionais.

## ✨ Funcionalidades
O sistema atende a restrições operacionais específicas (limite de 50 vendas/dia) e implementa as seguintes funções:
- **Registro de Vendas:** Cadastro de produtos (ID, descrição, preço), clientes e quantidade adquirida.
- **Gestão de Devoluções (Regra de Negócio):** Controle de itens devolvidos. A partir da segunda devolução de um mesmo pedido, o sistema aplica automaticamente uma taxa fixa de R$ 20,00 referente a despesas logísticas.
- **Relatório Diário:** Listagem detalhada dos pedidos do dia e cálculo do faturamento total.
- **Relatório Mensal:** Consolidação do total vendido em cada mês.
- **Relatório Anual:** Exibição dos meses organizados em ordem **decrescente** de faturamento, utilizando o algoritmo de ordenação *Bubble Sort*.

## 🛠️ Tecnologias e Estruturas Utilizadas
- **Linguagem C**
- `structs` (Estruturas de dados para Produtos, Clientes e Pedidos)
- `arrays` (Vetores para armazenamento em memória das vendas e faturamentos)
- Algoritmos de Ordenação (*Bubble Sort*)
- Modularização (Funções para separação lógica do código)

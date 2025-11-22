# 🗺️ Desafio WAR Estruturado – Nível Mestre: Missões Estratégicas

## 🏆 Status do Projeto: Nível Mestre Concluído

Este repositório contém a solução para o **Desafio WAR Estruturado**, uma série de exercícios focados na evolução de habilidades de programação em C. O projeto foi concluído no **Nível Mestre**, implementando o sistema de missões estratégicas, modularização total, alocação dinâmica e gerenciamento de memória.

---

## 🎯 Requisitos Funcionais Implementados (Nível Mestre)

A implementação no Nível Mestre adiciona uma nova camada estratégica, exigindo organização modular e o uso de ponteiros avançados.

| Funcionalidade | Implementação no Código |
| :--- | :--- |
| **Criação do Vetor de Missões** | Vetor `MISSOES` com 5 descrições estratégicas (`Destruir Verde`, `Conquistar 3 territórios`, etc.). |
| **Sorteio da Missão** | Função `void atribuirMissao(char* destino, ...)` que sorteia a missão e a copia usando `strcpy`. |
| **Armazenamento Dinâmico** | A missão do jogador é alocada dinamicamente com `malloc` e liberada com `free`. |
| **Verificação da Missão** | Função `int verificarMissao(...)` avalia se os objetivos (contagem de territórios ou destruição de exércitos) foram cumpridos. |
| **Encerramento Condicional** | O loop principal do jogo (`main`) encerra **imediatamente** após a missão ser cumprida, declarando a vitória. |

---

## ⚙️ Requisitos Técnicos e Boas Práticas (C)

Todos os requisitos técnicos avançados e de boas práticas foram aplicados no projeto:

* **Modularização Total:** O código é dividido em funções claras (`atribuirMissao`, `verificarMissao`, `atacar`, `exibirMapa`, etc.).
* **Uso de Ponteiros:** Manipulação de dados (`mapa` e `missaoJogador`) através de ponteiros.
* **Const Correctness:** Uso de `const` (ex: `exibirMapa(const Territorio *mapa)`) para garantir que dados de leitura não sejam modificados.
* **Alocação e Liberação:** Uso de `calloc` para o mapa e `malloc` para a missão, e `liberarMemoria()` e `free()` ao final para evitar vazamentos.
* **Lógica de Combate:** A função `atacar()` implementa a regra de **transferir a cor e metade das tropas** em caso de conquista.
* **Validação:** Validação implementada para garantir que o jogador só possa atacar com o seu exército (`g_corJogador`) e somente territórios inimigos.

---

## 💻 Estrutura do Jogo e Execução

O jogo segue uma estrutura limpa e orientada a funções:

1.  **Setup Inicial:** Alocação de memória, inicialização de 5 territórios com cores fixas e únicas, e a escolha do exército pelo jogador.
2.  **Atribuição da Missão:** A missão secreta é sorteada e atribuída dinamicamente.
3.  **Game Loop (`do-while`):**
    * Exibe o mapa e a missão.
    * O jogador escolhe entre **Atacar** ou **Verificar Missão**.
    * A cada ataque, a vitória é checada silenciosamente.
4.  **Encerramento:** O loop termina quando o jogador cumpre a missão (`venceu = 1`) ou escolhe sair (`opcao = 0`).

---

### 📚 Progressão de Habilidades

Este projeto representa a evolução pelos três níveis:

| Nível | Habilidades Chave |
| :--- | :--- |
| **Nível Novato** | `struct`, vetor estático, entrada/saída. |
| **Nível Aventureiro** | `calloc`/`free`, ponteiros, `rand()`, laço interativo. |
| **Nível Mestre** | Modularização, Ponteiros Avançados, `const` correctness, Sistema de Missões. |
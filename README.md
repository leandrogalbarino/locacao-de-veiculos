# Sistema de Gestão de Locação de Veículos

Este programa simula a gestão de locação de veículos, permitindo o cadastro de veículos, clientes e locações. O objetivo é facilitar o gerenciamento das locações ativas, realizar relatórios e oferecer uma visão geral dos veículos disponíveis.

## Funcionalidades

O sistema oferece as seguintes funcionalidades principais:

1. **Incluir Veículos**: Adiciona novos veículos ao sistema.
2. **Listar Veículos**: Exibe a lista de veículos cadastrados.
3. **Incluir Clientes**: Cadastra novos clientes.
4. **Listar Clientes**: Mostra a lista de clientes cadastrados.
5. **Realizar Locação**: Permite realizar a locação de um veículo por um cliente.
6. **Devolver Veículo**: Registra a devolução de um veículo locado.
7. **Listar Locações**: Exibe todas as locações realizadas.
8. **Gerar Relatórios**: Permite visualizar relatórios sobre locações e veículos disponíveis.
9. **Sair**: Encerra o programa.

## Relatórios Disponíveis

Os relatórios disponíveis incluem:

1. Listar todas locações ativas.
2. Listar todas locações realizadas por um cliente.
3. Listar faturamento das locações por mês.
4. Listar a placa dos 3 veículos mais rodados.
5. Listar a placa e o modelo de todos os veículos disponíveis.

## Estruturas de Dados Utilizadas

O programa utiliza três principais estruturas de dados:

- **Veículos (`Veiculos`)**: Representa os veículos disponíveis para locação.
- **Clientes (`Clientes`)**: Gerencia os clientes cadastrados no sistema.
- **Locação (`Locacao`)**: Controla as locações realizadas, incluindo informações sobre o veículo, cliente e status da locação.

## Menu Principal

No menu principal, o usuário pode escolher entre as seguintes opções:

1. Incluir veículos
2. Listar veículos
3. Incluir clientes
4. Listar clientes
5. Realizar locação
6. Devolver veículo
7. Listar locações
8. Gerar relatórios
9. Sair

### Submenu de Relatórios

O submenu de relatórios permite ao usuário visualizar detalhes sobre o estado atual do sistema, com as seguintes opções:

1. Listar todas locações ativas.
2. Listar todas locações realizadas por um cliente.
3. Listar faturamento das locações por mês.
4. Listar a placa dos 3 veículos mais rodados.
5. Listar a placa e o modelo de todos os veículos disponíveis.

## Fluxo do Programa

1. **Inicialização**: As listas de veículos, clientes e locações são inicializadas.
2. **Menu Principal**: O usuário escolhe uma das opções disponíveis para gerenciar locações.
3. **Operações**: Dependendo da escolha, o sistema executa uma operação, como adicionar um veículo, cadastrar um cliente ou gerar relatórios.
4. **Relatórios**: Se escolhido, o programa exibe relatórios sobre o estado atual das locações e veículos disponíveis.
5. **Sair**: O programa encerra quando o usuário escolhe a opção "Sair".

## Como Executar

1. Compile o programa utilizando um compilador C. Exemplo: `gcc -o locadora main.c veiculos.c clientes.c locacao.c -I.`
2. Execute o programa gerado: `./locadora`

## Dependências

- `clientes.h` e `clientes.c`: Gerenciamento dos clientes cadastrados.
- `veiculos.h` e `veiculos.c`: Manipulação dos veículos disponíveis para locação.
- `locacao.h` e `locacao.c`: Controle das locações realizadas.

## Nota

Este código é uma simulação simples para fins educacionais e demonstra o uso de diferentes estruturas de dados e suas operações em C.


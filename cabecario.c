

//  Deve ser possível cadastrar veículos: incluir veículos e listar todos os veículos. o Sobre cada veículo, guardar: placa, marca, modelo, ano de fabricação, quilometragem atual, valor da diária, e uma flag “disponibilidade” que informa se o veículo está disponível para locação (um veículo está disponível para locação se ele não está locado no dia atual).

//  Deve ser possível cadastrar clientes: incluir clientes e listar todos os clientes. o Sobre cada cliente, guardar: CNH, nome e telefone.

// Deve ser possível realizar a locação de veículos por clientes: locar veículo (retirar), devolver veículo e listar todas as locações. o Sobre cada locação, guardar: cliente, veículo, dia da retirada, dia da devolução e valor total pago.

// Restrições:
// 1) Um veículo só pode ser locado se estiver disponível na data solicitada.
// 2) A quilometragem atual do veículo deve ser solicitada pelo programa e atualizada pelo usuário sempre que o veículo for devolvido.
// 3) A flag “disponibilidade” deve ser atualizada automaticamente pelo programa sempre que o veículo for locado (indisponível) e devolvido (disponível).

// 4) O valor total pago deve ser calculado automaticamente pelo programa, com base no valor da diária e nos dias locados.
// 5) Uma locação só pode ser feita por um cliente já cadastrado e um veículo já cadastrado;
// 6) Não pode haver duplicidade de informações sobre clientes e veículos. Por exemplo, uma locação não armazena/replica os dados de clientes e veículos, mas guarda apenas ponteiros que apontam para os respectivos cliente e veículo já previamente cadastrados.

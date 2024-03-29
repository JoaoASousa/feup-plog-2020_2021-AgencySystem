Projeto 2 - Turma 4, Grupo 9

O programa possui todas as funcionalidades / características que foram pedidas, apresentando comentários ao longo do código
de modo a facilitar a interpretação/análise do mesmo.

O programa lê e guarda os conteúdos dos ficheiros de agência, clientes e pacotes, recorrendo-se, por exemplo, a classes.

Possui um sistema de menus e submenus, onde se pode proceder à escolha da operação a realizar,
existindo sempre a possibilidade de voltar ao menu anterior ou de terminar o programa
('0' ou "control + z", respetivamente), encontrando-se esta observação explícita logo no começo do programa,
aquando da inserção do nome do ficheiro da agência.

Ao terminar uma operação (por exemplo, a visualização da informação de um dos clientes),
é apresentada ao utilizador a possibilidade de voltar ao menu inicial ou de terminar o programa,
atualizando-se a informação dos ficheiros de texto no caso da segunda opção.

Em relação ao controlo de entradas inválidas, o ficheiro fornecido pelo utilizador no momento inicial
(input do nome do ficheiro da agência) é alvo de verificação relativamente ao número de dados que possui, inclusive testando
se as duas últimas linhas correspondem efetivamente a ficheiros que possam ser abertos.

Como se explicou anteriormente, o input '0' é considerado "inválido" em todos os locais de input,
com exceção do número de pacotes vendidos (tanto na criação como na alteração de pacote), onde se assume que 0 é um input válido.

Todos os locais de input dispõem de controlo de entradas inválidas que está de forma geral associado ao tipo de variável
que vai receber o valor, não sendo possível verificar, por exemplo, se a rua fornecida no input da morada existe realmente.

Existem inclusive casos mais particulares como, por exemplo, as datas (Ano / Mês / Dia) que são controladas com base na data em que
se está a correr o programa; as moradas que são alvo de controlo ao nível do número de elementos (têm de possuir obrigatoriamente
Rua, Número da porta, Andar (ou '-' se não for aplicável), Código postal e Localidade); o Número de Identificação Fiscal (NIF)
que tem de possuir 9 algarismos; e o número de pacotes vendidos sendo que, em qualquer tentativa de compra, se a mesma igualar
o valor máximo permitido, atualiza o pacote em questão para indisponível, não aceitando a intenção de compra se o número de pacotes
adicionais vendidos vier a superar o valor máximo disponível.


No projeto assumiu-se as seguintes situações:
1 - não é permitido ao cliente comprar mais do que uma vez cada um dos pacotes turísticos;
2 - quando um cliente procede à compra de um pacote, isso significa que está a comprar para todos os elementos da sua família;
3 - não é permitido criar um pacote turístico com data inicial / final que seja anterior à data corrente;
4 - os ficheiros de texto com a informação dos clientes e pacotes encontram-se inicialmente válidos
(isto é, com a informação corretamente escrita).
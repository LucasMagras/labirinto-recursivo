# Labirinto recursivo

<p align="justify">
	O algoritmo tem como objetivo caminhar de forma randômica por N matrizes NxN ou seja, quadráticas, na qual se encontra diversos obstaculos, como se fosse um labirinto. As matrizes sao constituidas por numeros inteiros de 0 a 9, por paredes representadas pelo caracter # e por perigos representados pelo caracter *. O caminhho realizado é de forma randômica, a cada iteração a posição será alterada para alguma posição válida aleatória, ou seja uma posição ao redor da posiçaõ atual. Durante a trajetória, as posciçoes que contém numeros devem ser subtraidas em 1 a cada passagem, além disso ao passar por um perrigo a vida é consumida.
</p>

	Em relação as paredes, não a muito o que fazer a não ser desviar e continuar a rota. Já os perigos como foi dito, sempre consomem a vida ao se passar por eles, nesse caso é subtraido 1 de um total de 10 vidas. Assim ao ficar sem pontos de vida o algoritmo deve parar e indicar o fim do jogo.

	Ao decorrer da trajetória, a cada passo sob uma posição que contém um numero, é coletado um item e é subtraido 1 da posição atual como ja foi dito. Ao coletar 4 itens a vida aumenta em 1 se não estiver cheia, ou seja, se for diferente de 0. Contudo pode haver posiçãoes da matriz cujo o valor é 0, nesse caso não é coletado item e tambem não é decrementado 1 da posição.

	O labirinto é lido de um arquivo input.data, o qual apresentará N matrizes NxN. O objetivo do trabalho é percorrer as matrizes até que todo caminho percorrido se torne 0 ou quando a vida chegar a 0. No final é mostrado quantas casas não foram visitas, a soma de itens consumidos pelo caminho, quanto foram pegos no total, a quantidade de vida se ela for diferente de 0 e quantos perigos foram enfrentados ao longo do trajéto.
	
	Ao iniciar o algoritmo, a primeira coisa a ser feita é a leitura do arquivo input.data. O algoritmo lê todas as matrizes que estão no arquivo e cria um arquivo de saída separado para cada matriz, dessa forma quando for preciso mudar de matriz o codigo lê o arquvio correspondente e carrega a matriz de novo. Para entender como é feito a mudança de matriz é preciso entender como é realizado o caminho. Como ja foi dito, o caminho é feito de forma randômica, neste caso quando se inicia o algoritmo é gerado uma coordenada que contem um valor de linha e um valor de coluna aleatorios da matriz, feito isso durante a trajetoria dependendo da posição atual são gerado numeros entre -1 e 1 para uma variavel linha e uma variavel coluna. Esses valores gerados são incrementados a posição atual e realizando o caminho, por exemplo posição atual for linha = 2 e coluna = 1, e for gerado 0 e 1 nas variaveis linha e coluna, a posição nova será linha = 2 e coluna = 2, ou seja ele caminhou para direita. 


# Compilação e Execução

O código possui um arquivo Makefile que realiza todo o procedimento de compilação e execução. Para tanto, temos as seguintes diretrizes de execução:


| Comando                |  Função                                                                                           |                     
| -----------------------| ------------------------------------------------------------------------------------------------- |
|  `make clean`          | Apaga a última compilação realizada contida na pasta build                                        |
|  `make`                | Executa a compilação do programa utilizando o gcc, e o resultado vai para a pasta build           |
|  `make run`            | Executa o programa da pasta build após a realização da compilação                                 |

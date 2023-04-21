# Labirinto recursivo

<p align="justify">
	O algoritmo tem como objetivo caminhar de forma randômica por N matrizes NxN ou seja, quadráticas, na qual se encontra diversos obstaculos, como se fosse um labirinto. As matrizes são constituidas por numeros inteiros de 0 a 9, por paredes representadas pelo caracter # e por perigos representados pelo caracter *. O caminhho realizado é de forma randômica, a cada iteração a posição será alterada para alguma posição válida aleatória, ou seja uma posição ao redor da posiçaõ atual. Durante a trajetória, as poscições que contém numeros devem ser subtraidas em 1 a cada passagem, além disso ao passar por um perrigo a vida é consumida.
</p>

<p align="justify">
	Em relação as paredes, não a muito o que fazer a não ser desviar e continuar a rota. Já os perigos como foi dito, sempre consomem a vida ao se passar por eles, nesse caso é subtraido 1 de um total de 9 vidas. Assim, ao ficar sem pontos de vida o algoritmo deve parar e indicar o fim do jogo.
</p>

<p align="justify">
	Ao decorrer da trajetória, a cada passo sob uma posição que contém um numero, é coletado um item e é subtraido 1 da posição atual como ja foi dito. Ao coletar 4 itens, a vida aumenta em 1 se não estiver cheia, ou seja, se for diferente de 9. Contudo pode haver posiçãoes da matriz cujo o valor é 0, nesse caso não é coletado item e tambem não é decrementado 1 da posição.
</p>

<p align="justify">
	As matrizes são lidas de um arquivo input.data. O objetivo do trabalho é percorrer as matrizes até que todo caminho percorrido se torne 0 ou quando a vida chegar a 0. No final é mostrado quantas casas não foram visitas, a soma de itens consumidos pelo caminho, quantos itens foram pegos no total, a quantidade de vida se ela for diferente de 0 o que significa vitoria e quantos perigos foram enfrentados ao longo do trajéto.
</p>

<p align="justify">
	Ao iniciar o algoritmo, a primeira coisa a ser feita é a leitura do arquivo input.data na função LerMatriz(). O algoritmo lê todas as matrizes que estão no arquivo e cria um arquivo de saída separado para cada matriz, dessa forma quando for preciso mudar de matriz o codigo lê o arquvio correspondente e carrega a matriz de novo. Para entender como é feito a mudança de matriz é preciso entender como funciona a função Caminho(). Como ja foi dito, o caminho é feito de forma randômica, neste caso quando se inicia o algoritmo é gerado uma coordenada que contem um valor de linha e um valor de coluna aleatórios armazenados nas variaveis posição_linha e posição_coluna respectivamente, feito isso durante a trajetoria dependendo da posição atual são gerado numeros entre -1 e 1 para as variaveis. Esses valores gerados são incrementados a posição atual e realizando o caminho, por exemplo, se a posição atual for linha = 2 e coluna = 1, e for gerado 0 e 1 nas variaveis posição_linha e posição_coluna, a posição nova será linha = 2 e coluna = 2, ou seja ele caminhou para direita. Sabendo disso, a mudança de matriz é feita quando a posição atual for qualquer uma da última coluna da matriz e for gerado 1 na variável posição_coluna, nesse caso será incrementado +1 na coluna e mudará de matriz, já que não existe mais colunas na matriz atual. Ao chegar na última matriz, se ocorrer uma troca de matrizes, o algoritmo irá voltar para a primeira matriz e continuará rodando da mesma forma.
</p>

<p align="justify">
	A função caminho gera esses números aleatórios de -1 a 1 na maioria dos casos. Existem casos em que não se pode gerar números nesse intervalo, por exemplo se a posição atual for na primeira linha, não pode gerar -1 na variável posição_linha, já que não existe uma linha a cima da primeira. Isso vale para toda a borda da matriz fora a última coluna, onde é realizado a troca de matrizes. A função Caminho() é responsavel tambem pela incrementação dos itens e o decremento da vida e das posiçãoes da matriz. A vida é uma variavel do tipo int que decrementa toda vez que a posição atual for um perigo e incrementa toda vez que é pego 4 itens. Os itens tambem são uma variavel que incrementa toda vez ao passar por uma posição que contem um numero diferente de 0. Além disso, foi criada outra variavel que conta os itens totais coletados, pois a primeira zera quando são pegos 4 itens. Para o decremento das posições, como a matriz é do tipo char, foi necessário converter o caracter da posição em inteiro, decrementar e depois converter esse int em char denovo para inserir na matriz. 
</p>

<p align="justify">
	Para realizar a troca de matrizes, foram usadas 2 funções distintas. Primeiro é usada a função Checkpoint() que lê a matriz atual e reescreve ela com as modificações feitas durante o trajeto no arquivo correspondente à essa matriz, dessa forma quando precisar carregar essa matriz novamente não será perdida as mudanças feitas anteriormente. Depois é usada a função SetMat() que apenas lê o arquivo da proxima matriz e carrega ela no codigo. Por exemplo, se a matriz atual for a 1, quando for realizar a troca de matrizes a próxima será a matriz 2, nesse caso será chamada a função Checkpoint() para salvar as mudanças da matriz 1 no arquivo referetnte a ela e depois a função SetMat() que irá ler a matriz 2 do arquivo e carregar ela no codigo. 
</p>

<p align="center">
<img src="img/mat1.0.png"/>
</p>


# Compilação e Execução

O código possui um arquivo Makefile que realiza todo o procedimento de compilação e execução. Para tanto, temos as seguintes diretrizes de execução:


| Comando                |  Função                                                                                           |                     
| -----------------------| ------------------------------------------------------------------------------------------------- |
|  `make clean`          | Apaga a última compilação realizada contida na pasta build                                        |
|  `make`                | Executa a compilação do programa utilizando o gcc, e o resultado vai para a pasta build           |
|  `make run`            | Executa o programa da pasta build após a realização da compilação                                 |

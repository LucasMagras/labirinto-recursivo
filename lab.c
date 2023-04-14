#include "lab.h"

void LerMatriz()
{
  struct stat sb;
  stat("dataset/input.data", &sb);

  FILE *fp;
  int  i=0, j=0, tam=0, cont=0, quantidade_matriz=0;
  char *linha = malloc(sb.st_size);
  char *tok;

  char filename[100];
  int num_matrices = 1;
  int rows, cols;
  char **mat;


    if ((fp = fopen("dataset/input.data", "r")) == NULL){
        printf("File could not be opened");
        exit(-1);
    }

    while (fscanf(fp, "%[^\n] ", linha) != EOF) {
		if(cont==0){
			tok = strtok(linha, "\n");
			while (tok != NULL){
				tam=atoi(tok);
				tok = strtok (NULL," ");
    		}

			mat = malloc(tam*sizeof(char*));

			for(int k=0;k<tam;k++)
				mat[k]=malloc(sizeof(char)*tam);
			
			cont++;

		}
		
    	else{
			tok = strtok(linha, " ");

			while (tok != NULL)
   			{
				mat[i][j] = (char) *tok;
				j++;
				tok = strtok (NULL," ");
    		}
			
			j=0;
			i++;

			if(i==tam)
			{
				// Cria um arquivo de saída para a matriz atual
				sprintf(filename, "matriz%d.txt", num_matrices);
				FILE *out_fp = fopen(filename, "w");

				// Escreve a matriz no arquivo de saída
				for (int i = 0; i < tam; i++) {
					for (int j = 0; j < tam; j++) {
						fprintf(out_fp, "%c ", mat[i][j]);
					}
				fprintf(out_fp, "\n");
				}

				// Fecha o arquivo de saída e incrementa o contador de matrizes
				fclose(out_fp);
				num_matrices++;
				i=0;
				quantidade_matriz++;
				printf("\n================================================================================\n");
				//voltando o i para 0 para ele pegar as outras matrizes
			}
		}
  }

	fclose(fp);
	SetMat0(mat,tam);
	Caminho(mat,tam,quantidade_matriz);
}

void Caminho(char **mat, int tam, int quantidade_matriz)
{
    int posicao_linha, posicao_coluna; 
	int itens=0, itens_totais=0, vida=10; 
	int decremento_posi=0; 
	int path_linha, path_coluna;
	int escolha;
	char pos_decremento;
	int numero_matriz=1;
	srand(time(NULL));


	// randomizando a posicao inicial ate ela ser diferente de parede
	do{
    	posicao_linha=(rand()% tam);
		posicao_coluna=(rand()% tam);

	}while(mat[posicao_linha][posicao_coluna] == '#');

	printf("\n\nPOSICAO INICIAL  %d x %d = [%c] \n\n" , posicao_linha, posicao_coluna, mat[posicao_linha][posicao_coluna]);

	// caso a posicao inicial for uma armadilha
	if(mat[posicao_linha][posicao_coluna] == '*'){
		printf("\nSUA POSICAO INICIAL EH UMA ARMADILHA !!! VOCE PERDEU UMA VIDA\n");
		vida--;
		printf("VIDA ATUAL [%d]\n", vida);
	}

	printf("==============================================\n");
	printf("\nMAPA DO LABIRINTO  \n\n");
		for(int i=0; i<tam; i++){
			for(int j=0; j<tam; j++){
				printf("%c ", mat[i][j]);
			}
			printf("\n");
		}
	printf("\n");
    
	do
	{
		do{
			// casos especiais
			// se a posicao for alguma da primeira linha 
			if(posicao_linha==0){
				// se a posicao for a posicao 0x0 da matriz
				if(posicao_linha==0 && posicao_coluna==0){
					path_linha=rand()% 2;
					path_coluna=rand()% 2;
				}
				// se a posicao for na primeira linha/ultima coluna
				else if(posicao_linha==0 && posicao_coluna==tam-1){
					path_linha=rand()% 2;
					path_coluna=(rand()% 2) -1;
				}
				// se a posicao for alguma da ultima linha fora as posicoes acima
				else{
					path_linha=rand()% 2;
					path_coluna=(rand()% 3)-1;
				}
			}

			// se a posicao for alguma da ultima linha
			else if(posicao_linha==tam-1){
				// se a posicao for na ultima linha/primeira coluna
				if(posicao_linha==tam-1 && posicao_coluna==0){
					path_linha=(rand()% 2) -1;
					path_coluna=(rand()% 2);
				}
				
				// se a posicao for a NxN matriz 
				else if(posicao_linha==tam-1 && posicao_coluna==tam-1){
					path_linha=(rand()% 2) -1;
					path_coluna=(rand()% 2) -1;
				}

				// se a posicao for alguma da ultima linha fora as posicoes acima
				else{
					path_linha=(rand()% 2) -1;
					path_coluna=(rand()% 3) -1;
				}

			}

			// se a posicao for alguma da primeira coluna
			else if(posicao_coluna==0){
				// se a posicao for a 0x0 da matriz
				if(posicao_linha==0 && posicao_coluna==0){
					path_linha=rand()% 2;
					path_coluna=rand()% 2;
				}
				
				// se a posicao for na ultima linha/primeira coluna
				if(posicao_linha==tam-1 && posicao_coluna==0){
					path_linha=(rand()% 2) -1;
					path_coluna=(rand()% 2);
				}
				// se a posicao for alguma da primeira coluna fora as posicoes acima
				else{
					path_linha=(rand()% 3) -1;
					path_coluna=rand()% 2;
				}
			}

			// se a posicao for alguma da ultima coluna
			else if(posicao_coluna==tam-1){
				// se a posicao for na primeira linha/ultima coluna
				do{
					if(posicao_linha==0 && posicao_coluna==tam-1){
						path_linha=rand()% 2;
						path_coluna=(rand()% 3) -1;
					}

					// se a posicao for a NxN matriz 
					else if(posicao_linha==tam-1 && posicao_coluna==tam-1){
						path_linha=(rand()% 2) -1;
						path_coluna=(rand()% 3) -1;
					}

					// se for alguma posicao na ultima coluna fora as posicoes acima
					else{
						path_linha=(rand()% 3) -1;
						path_coluna=(rand()% 3) -1;
					}

					//verificando se precisa trocar de matriz
					if(path_coluna==1)
					{
						if(numero_matriz != quantidade_matriz){
							Checkpoint(mat,tam,numero_matriz);
							numero_matriz++;
							SetMat(mat,tam,numero_matriz);
						}
						else{
							Checkpoint(mat,tam,numero_matriz);
							numero_matriz=1;
							SetMat(mat,tam,numero_matriz);
						}
						posicao_coluna=0;
						path_coluna=0;
						break;
					}
				}while((mat[posicao_linha+path_linha][0] == '#'));
			}

			// se a posicao for qualquer uma que nao seja na borda da matriz
			else{
				path_linha=(rand()% 3) -1;
				path_coluna=(rand()% 3) -1;
			}
		}while((mat[posicao_linha+path_linha][posicao_coluna+path_coluna] == '#') || (path_linha==0 && path_coluna==0) );
		
		printf("ANDANDO PARA PARA POSICAO %d x %d = [%c]....\n", posicao_linha+path_linha, posicao_coluna+path_coluna, mat[posicao_linha+path_linha][posicao_coluna+path_coluna]);
		printf("\n==============================================\n");

		posicao_linha=posicao_linha+path_linha;
		posicao_coluna=posicao_coluna+path_coluna;

		// vendo se essa posicao eh diferente de armadilha
		if(mat[posicao_linha][posicao_coluna]!='*'){
			// vendo se essa posicao eh diferente de 0
			if(mat[posicao_linha][posicao_coluna] != '0'){
				decremento_posi=(mat[posicao_linha][posicao_coluna] - '0')-1;
				pos_decremento=decremento_posi + '0';
				mat[posicao_linha][posicao_coluna] = pos_decremento;
				printf("\n VOCE COLETOU UM ITEM!!!\n");
				itens++;
				itens_totais++;
				if(itens==4)
					printf(" \n PARABENS VOCE COLETOU 4 ITENS!!! SE CURE QUANDO PERDER UMA VIDA\n");
			}
			else{
				printf("\n POSICAO VAZIA!!! NAO HA ITENS PARA COLETAR\n");
			}
		}
		// caso a posicao na qual irei andar for uma armadilha
		else{
			printf("\n VOCE CAIU EM UMA ARMADILHA E PERDEU UMA VIDA!!!!\n");
			vida--;
		}

		printf("\n --------------------------------------");
		printf("\n|QUANTIDADE DE ITENS NO INVENTARIO [%d] |\n", itens);
		printf("|VIDA [%d]                              |\n", vida);
		printf(" --------------------------------------\n");
		printf("\n==============================================\n");

		printf("\nATUALIZANDO MAPA DO LABIRINTDO...\n\n");
			for(int i=0; i<tam; i++){
				for(int j=0; j<tam; j++){
					printf("%c ", mat[i][j]);
				}
				printf("\n");
			}
			printf("\n");
		
		printf("POSICAO ATUAL %d x %d = [%c]\n", posicao_linha, posicao_coluna, mat[posicao_linha][posicao_coluna]);

		if(itens==4){
			if(vida!=9){
				printf("\nVOCE POSSUI ITENS SUFICIENTE PARA SE CURAR\n\nSE CURANDO...");
				vida++;
				printf("VOCE GANHOU UMA VIDA!!!\n\nVIDA [%d]\n", vida);
				itens=0;
			}
			else{
				printf("\nVOCE POSSUIR ITENS SUFICIENTE PARA SE CURAR, NAO SE ESQUECA DE SE CURAR QUANDO PERDER UMA VIDA\n");
			}
		}

		if(itens>4){
			if(vida!=9){
				printf("\nVOCE POSSUI ITENS SUFICIENTE PARA SE CURAR\n\nSE CURANDO...");
				vida++;
				printf("VOCE GANHOU UMA VIDA!!!\n\nVIDA [%d]\n", vida);
				itens=itens-4;

			}
			else{
				printf("\nVOCE POSSUIR ITENS SUFICIENTE PARA SE CURAR, NAO SE ESQUECA DE SE CURAR QUANDO PERDER UMA VIDA\n");
			}
		}

		if(vida==0){
			printf("\nVOCE FOI DE COMIS\n");
			printf("\nQUANTIDADE DE ITENS NO INVENTARIO [%d]\n", itens);
			printf("\nQUANTIDADE TOTAL DE ITENS COLETADOS [%d]\n\n\n", itens_totais);
			break;
		}

		if(escolha!=1){
			printf("\n\nMOSTRAR A PROXIMA ITERACAO OU PULAR PARA O FINAL? (1-PULAR / 2-PROXIMA ITERACAO)\n\n");
			scanf("%d", &escolha);
		}
		printf("\n");

	}while(escolha==1 || escolha==2);
}


void SetMat0(char **mat, int tam)
{
	struct stat sb;

    FILE *f;
	int i=0, j=0, cont=0;
    char *linha = malloc(sb.st_size);
    char *tok;

    if ((f = fopen("matriz1.txt", "r")) == NULL){
        printf("file could not be opened");
        exit(-1);
    }

    while (fscanf(f, "%[^\n] ", linha) != EOF) {

      tok = strtok(linha, " ");

      while (tok != NULL)
      {
          mat[i][j]=*tok;
          j++;
          tok = strtok (NULL," ");
      }
      
      j=0;
      i++;
	}

  fclose(f);
}

void SetMat(char **mat, int tam, int numero_matriz)
{
	struct stat sb;
  	stat("dataset/input.data", &sb);

	FILE *f;
	int i=0, j=0, cont=0;
	char *linha = malloc(sb.st_size);
	char *tok;
	char filename[100];
	printf("NUMERO MATRIZ %d\n", numero_matriz);

	sprintf(filename, "matriz%d.txt", numero_matriz);

	if ((f = fopen(filename,"r")) == NULL){
		printf("file could not be opened");
		exit(-1);
	}

	while (fscanf(f, "%[^\n] ", linha) != EOF) {

		tok = strtok(linha, " ");

		while (tok != NULL)
		{
			mat[i][j]=*tok;
			j++;
			tok = strtok (NULL," ");
		}
		
		j=0;
		i++;
	}

	fclose(f);
}

void Checkpoint(char **mat, int tam, int numero_matriz)
{
	char filename[100];
	FILE *f;

	
	sprintf(filename, "matriz%d.txt", numero_matriz);
	f = fopen(filename, "w");
	

	// Escreve a matriz no arquivo de saída
	for (int i = 0; i < tam; i++) {
		for (int j = 0; j < tam; j++) {
			fprintf(f, "%c ", mat[i][j]);
		}
	fprintf(f, "\n");
	}

	fclose(f);
}
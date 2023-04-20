#include "lab.h"

void LerMatriz()
{
  struct stat sb;
  stat("dataset/input.data", &sb);

  FILE *fp;
  int  i=0, j=0, tam=0, cont=0, quantidade_matriz=0;
  char *linha = malloc(sb.st_size);
  char *tok;

  char filename[100], filename_path[100];
  int num_matrices = 1;
  char **mat;
  char **mat_path;


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
			mat_path = malloc(tam*sizeof(char*));

			for(int k=0;k<tam;k++){
				mat[k]=malloc(sizeof(char)*tam);
				mat_path[k]=malloc(sizeof(char)*tam);
			} 
			cont++;

		}
		
    	else{
			tok = strtok(linha, " ");

			while (tok != NULL)
   			{
				mat[i][j] = *tok;
				mat_path[i][j] = *tok;
				j++;
				tok = strtok (NULL," ");
    		}
			
			j=0;
			i++;

			if(i==tam)
			{
				// Cria um arquivo de saída para a matriz atual
				sprintf(filename, "matriz%d.txt", num_matrices);
				sprintf(filename_path, "path%d.txt", num_matrices);
				FILE *out_fp = fopen(filename, "w");
				FILE *out_f = fopen(filename_path, "w");

				// Escreve a matriz no arquivo de saída
				for (int i = 0; i < tam; i++) {
					for (int j = 0; j < tam; j++) {
						fprintf(out_fp, "%c ", mat[i][j]);
						
					}
				fprintf(out_fp, "\n");
				}
				
				for (int i = 0; i < tam; i++) {
					for (int j = 0; j < tam; j++) {
						if(mat[i][j] == '#'){
							fprintf(out_f, "%c ", mat[i][j]);	
						}
						else{
							fprintf(out_f, "%c ", '0');	
						}
						
					}
				fprintf(out_f, "\n");
				}

				// Fecha o arquivo de saída e incrementa o contador de matrizes
				fclose(out_fp);
				fclose(out_f);
				num_matrices++;
				i=0;
				quantidade_matriz++;
				printf("\n================================================================================\n");
				//voltando o i para 0 para ele pegar as outras matrizes
			}
		}
   	}
	fclose(fp);
	SetMat0(mat,mat_path);
	Caminho(mat,tam,quantidade_matriz,mat_path);
}

void Caminho(char **mat, int tam, int quantidade_matriz, char **mat_path)
{
    int posicao_linha, posicao_coluna, linha_inicial, coluna_inicial;
	int itens=0, itens_totais=0, vida=9, quantidade_perigo=0, contCasasNaoVisitadas=0;
	int decremento_posi=0; 
	int path_linha, path_coluna, passos=0, contador_vitoria=0, vitoria=0, passos_totais=0;
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

	// salvando a posicao inicial
	linha_inicial=posicao_linha;
	coluna_inicial=posicao_coluna;

	mat_path[linha_inicial][coluna_inicial]='1';

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

					//verificando se precisa trocar de matriz, se ele estiver na ultima coluna e gerar um path coluna +1
					if(path_coluna==1)
					{	
						if(numero_matriz != quantidade_matriz){
							Checkpoint(mat,tam,numero_matriz,mat_path);
							numero_matriz++;
							SetMat(mat,numero_matriz,mat_path);
						}
						else{
							Checkpoint(mat,tam,numero_matriz,mat_path);
							numero_matriz=1;
							SetMat(mat,numero_matriz,mat_path);
						}

						if(contador_vitoria==passos && contador_vitoria!=0){
							vitoria++;
						}
						posicao_coluna=0;
						path_coluna=0;
						contador_vitoria=0;
						passos=0;
						
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
		passos++;
		passos_totais++;

		posicao_linha=posicao_linha+path_linha;
		posicao_coluna=posicao_coluna+path_coluna;
			
		if(mat_path[posicao_linha][posicao_coluna] == '0'){
			mat_path[posicao_linha][posicao_coluna]='1';
		}


		// vendo se essa posicao eh diferente de armadilha
		if(mat[posicao_linha][posicao_coluna]!='*'){
			// vendo se essa posicao eh diferente de 0
			if(mat[posicao_linha][posicao_coluna] != '0'){
				decremento_posi=(mat[posicao_linha][posicao_coluna] - '0')-1;
				pos_decremento=decremento_posi + '0';
				mat[posicao_linha][posicao_coluna] = pos_decremento;
				printf("\n VOCE COLETOU UM ITEM!!!\n");
				vitoria=0;
				itens++;
				itens_totais++;
				if(itens==4)
					printf(" \n PARABENS VOCE COLETOU 4 ITENS!!! SE CURE QUANDO PERDER UMA VIDA\n");
			}
			//caso a posicao for 0
			else{
				printf("\n POSICAO VAZIA!!! NAO HA ITENS PARA COLETAR\n");
				contador_vitoria++;
			}
		}
		// caso a posicao for armadilha
		else{
			printf("\n VOCE CAIU EM UMA ARMADILHA E PERDEU UMA VIDA!!!!\n");
			vida--;
			quantidade_perigo++;
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
			Checkpoint(mat,tam,numero_matriz,mat_path);;
			printf("\n\nVOCE MORREU!!!\n\n");
			printf("QUANTIDADE DE ITENS NO INVENTARIO [%d]\n", itens);
			printf("QUANTIDADE TOTAL DE ITENS COLETADOS [%d]\n", itens_totais);
			printf("QUANTIDADE DE PERIGOS ENFRENTADOS [%d]\n", quantidade_perigo);
			printf("QUANTIDADE DE CASAS VISITADAS [%d]\n", passos_totais);
			CasasNaoVisitadas(mat_path,quantidade_matriz,tam,contCasasNaoVisitadas);
			Resultado(mat,tam,quantidade_matriz);
			break;
		}

		if((vitoria>=quantidade_matriz) && (posicao_linha==linha_inicial && posicao_coluna==coluna_inicial) && numero_matriz==1){
			Checkpoint(mat,tam,numero_matriz,mat_path);
			printf("\n\nVOCE VENCEU!!!\n");
			printf("QUANTIDADE DE ITENS NO INVENTARIO [%d]\n", itens);
			printf("QUANTIDADE TOTAL DE ITENS COLETADOS [%d]\n", itens_totais);
			printf("QUANTIDADE DE PERIGOS ENFRENTADOS [%d]\n", quantidade_perigo);
			printf("QUANTIDADE DE CASAS VISITADAS [%d]\n", passos_totais);
			CasasNaoVisitadas(mat_path,quantidade_matriz,tam,contCasasNaoVisitadas);
			Resultado(mat,tam,quantidade_matriz);
			break;
		}

		if(escolha!=1){
			printf("\n\nMOSTRAR A PROXIMA ITERACAO OU PULAR PARA O FINAL? (1-PULAR / 2-PROXIMA ITERACAO)\n\n");
			scanf("%d", &escolha);
		}
		printf("\n");

		

	}while(escolha==1 || escolha==2);
}


void SetMat0(char **mat,char **mat_path)
{
	struct stat sb;
	stat("dataset/input.data", &sb);
	FILE *f;
	FILE *fp;
	int i=0, j=0;
    char *linha = malloc(sb.st_size);
    char *tok;
	char *linha_path = malloc(sb.st_size);
    char *tok_path;

    if ((f = fopen("matriz1.txt", "r")) == NULL){
        printf("file could not be opened");
        exit(-1);
    }

	if ((fp = fopen("path1.txt", "r")) == NULL){
        printf("file could not be opened");
        exit(-1);
    }

    while (fscanf(f, "%[^\n] ", linha) != EOF) {
		tok = strtok(linha, " ");
		while (tok != NULL)
      	{
        	mat[i][j] = *tok;
          	j++;
          	tok = strtok (NULL," ");
      	}
      j=0;
      i++;
	}

	i=0;
	j=0;
	
	while (fscanf(fp, "%[^\n] ", linha_path) != EOF) {
		tok_path = strtok(linha_path, " ");
		while (tok_path != NULL)
      	{
        	mat_path[i][j] = *tok_path;
          	j++;
          	tok_path = strtok (NULL," ");
      	}
      j=0;
      i++;
	}

  fclose(f);
  fclose(fp);
}

void SetMat(char **mat, int numero_matriz, char **mat_path)
{
	struct stat sb;
	stat("dataset/input.data", &sb);

	FILE *f;
	FILE *fp;
	int i=0, j=0;
	char *linha = malloc(sb.st_size);
	char *tok;
	char filename[100], filename_path[100];
	char *linha_path = malloc(sb.st_size);
    char *tok_path;

	sprintf(filename, "matriz%d.txt", numero_matriz);
	sprintf(filename_path, "path%d.txt", numero_matriz);

	if ((f = fopen(filename, "r")) == NULL){
        printf("file could not be opened");
        exit(-1);
    }

	if ((fp = fopen(filename_path, "r")) == NULL){
        printf("file could not be opened");
        exit(-1);
    }

	while (fscanf(f, "%[^\n] ", linha) != EOF) {
		tok = strtok(linha, " ");
		while (tok != NULL)
		{
			mat[i][j] = *tok;
			j++;
			tok = strtok (NULL," ");
		}
		j=0;
		i++;
	}
		
	fclose(f);
	i=0;
	j=0;

	while (fscanf(fp, "%[^\n] ", linha_path) != EOF) {
		tok_path = strtok(linha_path, " ");
		while (tok_path != NULL)
      	{
          	mat_path[i][j] = *tok_path;
          	j++;
          	tok_path = strtok (NULL," ");
      	}
      	j=0;
      	i++;
	}

	fclose(fp);
}

void Checkpoint(char **mat, int tam, int numero_matriz, char **mat_path)
{
	char filename[100], filename_path[100];
	FILE *f;
	FILE *fp;	

	sprintf(filename, "matriz%d.txt", numero_matriz);
	sprintf(filename_path, "path%d.txt", numero_matriz);

	f = fopen(filename, "w");
	fp = fopen(filename_path, "w");
	

	// Escreve a matriz no arquivo de saída
	for (int i = 0; i < tam; i++) {
		for (int j = 0; j < tam; j++) {
			fprintf(f, "%c ", mat[i][j]);
		}
	fprintf(f, "\n");
	}

	for (int i = 0; i < tam; i++) {
		for (int j = 0; j < tam; j++) {
			fprintf(fp, "%c ", mat_path[i][j]);
		}
	fprintf(fp, "\n");
	}

	fclose(f);
	fclose(fp);
}

void CasasNaoVisitadas(char **mat_path, int quantidade_matriz, int tam, int contCasasNaoVisitadas)
{	
	struct stat sb;
	stat("dataset/input.data", &sb);

	int linha, coluna, numero_matriz=1;
	char filename_path[100];
	char *linha_path = malloc(sb.st_size);
    char *tok_path;

	FILE *fp;

	for(int i=0; i<quantidade_matriz; i++){
		linha=0;
		coluna=0;
		sprintf(filename_path, "path%d.txt", numero_matriz);
		fp = fopen(filename_path, "r");
		while (fscanf(fp, "%[^\n] ", linha_path) != EOF) {
			tok_path = strtok(linha_path, " ");
			while (tok_path != NULL)
      		{
          		mat_path[linha][coluna] = *tok_path;
          		coluna++;
          		tok_path = strtok (NULL," ");
      		}
      		coluna=0;
      		linha++;
		}
		fclose(fp);
		for(int j=0; j<tam; j++){
			for(int k=0; k<tam; k++){
				if(mat_path[j][k]=='0'){
					contCasasNaoVisitadas++;
				}
			}
		}
		numero_matriz++;
	}

	printf("QUANTIDADE DE CASAS NAO VISITAS [%d]\n\n\n", contCasasNaoVisitadas);
	
}

void Resultado(char **mat, int tam, int quantidade_matriz)
{
	struct stat sb;
	stat("dataset/input.data", &sb);

	int k, j, numero_matriz=1;
	char filename[100], filename_path[100];
	char *linha = malloc(sb.st_size);
    char *tok;

	FILE *f;
	FILE *out_f;

	out_f = fopen("output.txt", "w");
	fprintf(out_f, "RESULTADO DAS MATRIZES :\n\n");

	for(int i=0; i<quantidade_matriz; i++){
		k=0;
		j=0;
		sprintf(filename, "matriz%d.txt", numero_matriz);
		sprintf(filename_path, "path%d.txt", numero_matriz);
		f = fopen(filename, "r");
		while (fscanf(f, "%[^\n] ", linha) != EOF) {
			tok = strtok(linha, " ");
			while (tok != NULL)
      		{
          		mat[k][j] = *tok;
          		j++;
          		tok = strtok (NULL," ");
      		}
      		j=0;
      		k++;
		}
		fclose(f);
		remove(filename);
		remove(filename_path);
		fprintf(out_f, "MATRIZ %d\n", numero_matriz);
		for (int l = 0; l < tam; l++) {
				for (int m = 0; m < tam; m++) {
					fprintf(out_f, "%c ", mat[l][m]);
				}
			fprintf(out_f, "\n");
		}
		numero_matriz++;
		fprintf(out_f, "\n");
	}
	fclose(out_f);
	rename("output.txt", "dataset/output.txt");
}
//BufferPool
#include "buffend.h"

/* ----------------------------------------------------------------------------------------------
    Objetivo:   Utilizada para impressão de tabelas (select * from table;).
    Parametros: Nome da tabela (char).
    Retorno:    void.
   ---------------------------------------------------------------------------------------------*/

void imprime(rc_insert *s_insert, int cols) {

    int j,erro, x, p, cont=0, countCheck = 0, check = 0, counter = 0;
    struct fs_objects objeto;

    if(!verificaNomeTabela(s_insert->objName)){
        printf("\nERROR: relation \"%s\" was not found.\n\n\n", s_insert->objName);
        return;
    }

    objeto = leObjeto(s_insert->objName);

    tp_table *esquema = leSchema(objeto);

    if(esquema == ERRO_ABRIR_ESQUEMA){
        printf("ERROR: schema cannot be created.\n");
        free(esquema);
        return;
    }

    tp_buffer *bufferpoll = initbuffer();

    if(bufferpoll == ERRO_DE_ALOCACAO){
        free(bufferpoll);
        free(esquema);
        printf("ERROR: no memory available to allocate buffer.\n");
        return;
    }

    erro = SUCCESS;
    for(x = 0; erro == SUCCESS; x++)
        erro = colocaTuplaBuffer(bufferpoll, x, esquema, objeto);

    int ntuples = --x;
	p = 0;
	while(x){
	    column *pagina = getPage(bufferpoll, esquema, objeto, p);
	    if(pagina == ERRO_PARAMETRO){
		    printf("ERROR: could not open the table.\n");
		    free(bufferpoll);
		    free(esquema);
		    return;
	    }

	    if(!cont) {
	        for(j=0; j < objeto.qtdCampos; j++){


		    while (countCheck < cols) {


			if (strcmp(s_insert->columnName[countCheck], pagina[j].nomeCampo) == 0) {

			    check = 1;

			}

			countCheck++;

		    }
								
		    if (check == 1) {

			if(pagina[j].tipoCampo == 'S')
			        printf(" %-20s ", pagina[j].nomeCampo);
				else
			        printf(" %-10s ", pagina[j].nomeCampo);
			if(j<cols-1)
			    	printf("|");
		    }

		    check = 0;
		    countCheck = 0;

	        }
	        printf("\n");
	        for(j=0; j < objeto.qtdCampos; j++){

		    while (countCheck < cols) {

			if (strcmp(s_insert->columnName[countCheck], pagina[j].nomeCampo) == 0) {

			    check = 1;

			}

			countCheck++;

		    }
		    if (check == 1) {
			
			    printf("%s",(pagina[j].tipoCampo == 'S')? "----------------------": "------------");
			    if(j<objeto.qtdCampos-1)
			    	printf("+");

		    }

		    check = 0;
		    countCheck = 0;
		    
	        }
	        printf("\n");

	    	check = 0;
	    	countCheck = 0;

	    }
	    cont++; 

		for(j=0; j < objeto.qtdCampos*bufferpoll[p].nrec; j++){

			while (countCheck < cols) {


				if (strcmp(s_insert->columnName[countCheck], pagina[j].nomeCampo) == 0) {

				    check = 1;

				}

				countCheck++;

			}
								
		    if (check == 1) {
			
			if(pagina[j].tipoCampo == 'S')
		    		printf(" %-20s ", pagina[j].valorCampo);
			else if(pagina[j].tipoCampo == 'I'){
		    		int *n = (int *)&pagina[j].valorCampo[0];
		    		printf(" %-10d ", *n);
			} else if(pagina[j].tipoCampo == 'C'){
		    		printf(" %-10c ", pagina[j].valorCampo[0]);
			} else if(pagina[j].tipoCampo == 'D'){
		    		double *n = (double *)&pagina[j].valorCampo[0];
	    	        	printf(" %-10f ", *n);
			};

			
			if((counter>=1 || cols == 1) && ((counter+1)%cols)==0)
			    printf("\n");
			else

			    
			    printf("|");
			
			counter++;

		     };


		    

		    check = 0;
		    countCheck = 0;
		
    	}
    	x-=bufferpoll[p++].nrec;
    }
    printf("\n(%d %s)\n\n",ntuples,(1>=ntuples)?"row": "rows");

    free(bufferpoll);
    free(esquema);
}

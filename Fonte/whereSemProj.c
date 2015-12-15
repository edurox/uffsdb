#include "buffend.h"

/* Função que faz a PROJEÇÃO*/



// Se foram especificadas colunas no *s_insert, verifica se elas existem no esquema.
//int allColumnsExistsWhereSemProj(rc_where *r_where, table *tabela);

void whereSemProj(rc_insert *s_insert, rc_where *r_where, char nomeTabela[]) {

	

    int j,erro, x, p, cont=0, checker = 0, tester = 0;
    struct fs_objects objeto;

    if(!verificaNomeTabela(nomeTabela)){
        printf("\nERROR: relation \"%s\" was not found.\n\n\n", nomeTabela);
        return;
    }

    objeto = leObjeto(nomeTabela);

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
		    if(pagina[j].tipoCampo == 'S')
			printf(" %-20s ", pagina[j].nomeCampo);
			else
			printf(" %-10s ", pagina[j].nomeCampo);
		    if(j<objeto.qtdCampos-1)
		    	printf("|");
		}
		printf("\n");
		for(j=0; j < objeto.qtdCampos; j++){
		    printf("%s",(pagina[j].tipoCampo == 'S')? "----------------------": "------------");
		    if(j<objeto.qtdCampos-1)
		    	printf("+");
		}
		printf("\n");
	    }
	    cont++;

	    tester = 0;
            checker = 0;

	    for(j=0; j < objeto.qtdCampos*bufferpoll[p].nrec; j++){



		// CHECAGEM
		if (strcmp (pagina[j].nomeCampo, r_where->columnWhere) == 0 && checker == 0) {

			if(pagina[j].tipoCampo == 'S' && strcmp (pagina[j].valorCampo, r_where->valueWhere) == 0) {

		    		checker++;
				j -= tester;
			}

			else if(pagina[j].tipoCampo == 'I'){

		    		int *n = (int *)&pagina[j].valorCampo[0];

				if (*n == (int)*r_where->valueWhere) {

		    			checker++;
					j -= tester;
				
				}

			} else if(pagina[j].tipoCampo == 'C'){

		    		checker++;
				j -= tester;

			} else if(pagina[j].tipoCampo == 'D'){

		    		double *n = (double *)&pagina[j].valorCampo[0];

				if (*n == (double)*r_where->valueWhere) {

	    	        		checker++;
					j -= tester;

				}

			}
		}

		//////////////////////////

		if(pagina[j].tipoCampo == 'S' && checker != 0 && tester != 0)
	    		printf(" %-20s ", pagina[j].valorCampo);

		else if(pagina[j].tipoCampo == 'I' && checker != 0 && tester != 0){

	    		int *n = (int *)&pagina[j].valorCampo[0];

	    		printf(" %-10d ", *n);

		} else if(pagina[j].tipoCampo == 'C' && checker != 0 && tester != 0){

	    		printf(" %-10c ", pagina[j].valorCampo[0]);

		} else if(pagina[j].tipoCampo == 'D' && checker != 0 && tester != 0){

	    		double *n = (double *)&pagina[j].valorCampo[0];

    	        	printf(" %-10f ", *n);

		}

		if (j>=1 && ((j+1)%objeto.qtdCampos)==0 && checker == 0) {
			
			tester = -1;

		}
		

		if(j>=1 && ((j+1)%objeto.qtdCampos)==0 && checker != 0 && tester != 0) {
		    	printf("\n");
			tester = 0;
			checker = 0;
		}
		else  {
			if (checker != 0 && tester != 0) {
				printf("|");
			}
		}

		tester++;

    	    }

	    

    	    x-=bufferpoll[p++].nrec;

        }
    printf("\n(%d %s)\n\n",ntuples,(1>=ntuples)?"row": "rows");

    free(bufferpoll);

    free(esquema);
}



// Se foram especificadas colunas no *s_insert, verifica se elas existem no esquema.
/*int allColumnsExistsWhereSemProj(rc_where *r_where, table *tabela) {

	int count = 0, j = 0, count2 = 0;
	if (!r_where->columnWhere) return 0;
	if (r_where->andOr != 0 && !r_where->columnWhere2) return 0;

	table *tbl;

	tbl = tabela;


	struct fs_objects objeto;

	objeto = leObjeto(tbl->nome);

	while (j < objeto.qtdCampos) {


		if(strcmp (r_where->columnWhere, tbl->esquema->nome) == 0) {	
			
			count ++;		

		};

		if (strcmp (r_where->columnWhere2, tbl->esquema->nome) == 0) {	
			
			count2 ++;		

		};
	
		

		if (tbl->esquema->next != NULL) {
	
			tbl->esquema = tbl->esquema->next;

		};

		j++;

	
	};

	free(tbl);

	if (r_where->andOr != 0 && count != 0 && count2 != 0) {

		return 1;

	}
	
	if (r_where->andOr == 0 && count != 0) {

		return 1;

	}
	
	return 1;
					
}*/

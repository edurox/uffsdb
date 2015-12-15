#include "buffend.h"

/* Função que Imprime o resultado do where quando não tem projeção*/


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
			// Operação =
			if (r_where->oper == 1) {

				if(pagina[j].tipoCampo == 'S' && strcmp (pagina[j].valorCampo, r_where->valueWhere) == 0) {

			    		checker++;
					j -= tester;
				}

				else if(pagina[j].tipoCampo == 'I'){

			    		//pagina[j].valorCampo[0];
					
					char num[31];

					int *n = (int *)&pagina[j].valorCampo[0];


					sprintf (num, "%d", *n); 


					if (strcmp (num, r_where->valueWhere) == 0) {

			    			checker++;
						j -= tester;
				
					}

				} else if(pagina[j].tipoCampo == 'C' && strcmp (pagina[j].valorCampo, r_where->valueWhere) == 0){

			    		checker++;
					j -= tester;

				} else if(pagina[j].tipoCampo == 'D'){

					char num[31];

			    		double *n = (double *)&pagina[j].valorCampo[0];

					sprintf (num, "%lf", *n);

					if (strcmp (num, r_where->valueWhere) == 0) {

		    	        		checker++;
						j -= tester;

					}

				}
			}

			// Operação !=
			if (r_where->oper == 4) {

				if(pagina[j].tipoCampo == 'S' && strcmp (pagina[j].valorCampo, r_where->valueWhere) != 0) {

			    		checker++;
					j -= tester;
				}

				else if(pagina[j].tipoCampo == 'I'){

			    		//pagina[j].valorCampo[0];
					
					char num[31];

					int *n = (int *)&pagina[j].valorCampo[0];


					sprintf (num, "%d", *n); 


					if (strcmp (num, r_where->valueWhere) != 0) {

			    			checker++;
						j -= tester;
				
					}

				} else if(pagina[j].tipoCampo == 'C' && strcmp (pagina[j].valorCampo, r_where->valueWhere) != 0){

			    		checker++;
					j -= tester;

				} else if(pagina[j].tipoCampo == 'D'){

					char num[31];

			    		double *n = (double *)&pagina[j].valorCampo[0];

					sprintf (num, "%lf", *n);

					if (strcmp (num, r_where->valueWhere) != 0) {

		    	        		checker++;
						j -= tester;

					}

				}
			}

			// Operação >
			if (r_where->oper == 2) {

				if(pagina[j].tipoCampo == 'S' && strcmp (pagina[j].valorCampo, r_where->valueWhere) > 0) {

			    		checker++;
					j -= tester;
				}

				else if(pagina[j].tipoCampo == 'I'){

			    		//pagina[j].valorCampo[0];
					
					char num[31];

					int *n = (int *)&pagina[j].valorCampo[0];


					sprintf (num, "%d", *n); 


					if (strcmp (num, r_where->valueWhere) > 0) {

			    			checker++;
						j -= tester;
				
					}

				} else if(pagina[j].tipoCampo == 'C' && strcmp (pagina[j].valorCampo, r_where->valueWhere) > 0){

			    		checker++;
					j -= tester;

				} else if(pagina[j].tipoCampo == 'D'){

					char num[31];

			    		double *n = (double *)&pagina[j].valorCampo[0];

					sprintf (num, "%lf", *n);

					if (strcmp (num, r_where->valueWhere) > 0) {

		    	        		checker++;
						j -= tester;

					}

				}
			}

			// Operação <
			if (r_where->oper == 3) {

				if(pagina[j].tipoCampo == 'S' && strcmp (pagina[j].valorCampo, r_where->valueWhere) < 0) {

			    		checker++;
					j -= tester;
				}

				else if(pagina[j].tipoCampo == 'I'){

			    		//pagina[j].valorCampo[0];
					
					char num[31];

					int *n = (int *)&pagina[j].valorCampo[0];


					sprintf (num, "%d", *n); 


					if (strcmp (num, r_where->valueWhere) < 0) {

			    			checker++;
						j -= tester;
				
					}

				} else if(pagina[j].tipoCampo == 'C' && strcmp (pagina[j].valorCampo, r_where->valueWhere) < 0){

			    		checker++;
					j -= tester;

				} else if(pagina[j].tipoCampo == 'D'){

					char num[31];

			    		double *n = (double *)&pagina[j].valorCampo[0];

					sprintf (num, "%lf", *n);

					if (strcmp (num, r_where->valueWhere) < 0) {

		    	        		checker++;
						j -= tester;

					}

				}
			}
			// Operação =>
			if (r_where->oper == 5) {

				if(pagina[j].tipoCampo == 'S' && strcmp (pagina[j].valorCampo, r_where->valueWhere) >= 0) {

			    		checker++;
					j -= tester;
				}

				else if(pagina[j].tipoCampo == 'I'){

			    		//pagina[j].valorCampo[0];
					
					char num[31];

					int *n = (int *)&pagina[j].valorCampo[0];


					sprintf (num, "%d", *n); 


					if (strcmp (num, r_where->valueWhere) >= 0) {

			    			checker++;
						j -= tester;
				
					}

				} else if(pagina[j].tipoCampo == 'C' && strcmp (pagina[j].valorCampo, r_where->valueWhere) >= 0){

			    		checker++;
					j -= tester;

				} else if(pagina[j].tipoCampo == 'D'){

					char num[31];

			    		double *n = (double *)&pagina[j].valorCampo[0];

					sprintf (num, "%lf", *n);

					if (strcmp (num, r_where->valueWhere) >= 0) {

		    	        		checker++;
						j -= tester;

					}

				}
			}

			// Operação =<
			if (r_where->oper == 6) {

				if(pagina[j].tipoCampo == 'S' && strcmp (pagina[j].valorCampo, r_where->valueWhere) <= 0) {

			    		checker++;
					j -= tester;
				}

				else if(pagina[j].tipoCampo == 'I'){

			    		//pagina[j].valorCampo[0];
					
					char num[31];

					int *n = (int *)&pagina[j].valorCampo[0];


					sprintf (num, "%d", *n); 


					if (strcmp (num, r_where->valueWhere) <= 0) {

			    			checker++;
						j -= tester;
				
					}

				} else if(pagina[j].tipoCampo == 'C' && strcmp (pagina[j].valorCampo, r_where->valueWhere) <= 0){

			    		checker++;
					j -= tester;

				} else if(pagina[j].tipoCampo == 'D'){

					char num[31];

			    		double *n = (double *)&pagina[j].valorCampo[0];

					sprintf (num, "%lf", *n);

					if (strcmp (num, r_where->valueWhere) <= 0) {

		    	        		checker++;
						j -= tester;

					}

				}
			}
		}

		//////////////////////////

		if(pagina[j].tipoCampo == 'S' && checker != 0)
	    		printf(" %-20s ", pagina[j].valorCampo);

		else if(pagina[j].tipoCampo == 'I' && checker != 0){

	    		int *n = (int *)&pagina[j].valorCampo[0];

	    		printf(" %-10d ", *n);

		} else if(pagina[j].tipoCampo == 'C' && checker != 0){

	    		printf(" %-10c ", pagina[j].valorCampo[0]);

		} else if(pagina[j].tipoCampo == 'D' && checker != 0){

	    		double *n = (double *)&pagina[j].valorCampo[0];

    	        	printf(" %-10f ", *n);

		}

		if (j>=1 && ((j+1)%objeto.qtdCampos)==0 && checker == 0) {
			
			tester = -1;

		}
		

		if(j>=1 && ((j+1)%objeto.qtdCampos)==0 && checker != 0 && tester != 0) {
		    	printf("\n");
			tester = -1;
			checker = 0;
		}
		else  {
			if (checker != 0) {
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



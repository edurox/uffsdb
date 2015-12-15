#include "buffend.h"

/* Função que Imprime o resultado do where quando tem projeção*/


void whereComProj(rc_insert *s_insert, rc_where *r_where, char nomeTabela[], int cols) {

	

    int j,erro, x, p, cont=0, checker = 0, tester = 0, checker2 = 0, countCheck = 0, check = 0, counter = 0;
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
    int holder = 0;
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

	    tester = 0;
            checker = 0;

	    for(j=0; j < objeto.qtdCampos*bufferpoll[p].nrec; j++){

		// CHECKAGEM
		if (r_where->andOr == 0) {
			// Check se tem AND ou OR - neste caso não tem nem um dos 2
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
		}

		// CHECAGEM CASO POSSUA AND
		if (r_where->andOr == 1) {
			// Check se tem AND ou OR - neste caso AND
			if (strcmp (pagina[j].nomeCampo, r_where->columnWhere) == 0 && checker == 0) {
				// Operação =
				if (r_where->oper == 1) {

					if(pagina[j].tipoCampo == 'S' && strcmp (pagina[j].valorCampo, r_where->valueWhere) == 0) {

				    		checker++;
						if (checker2 != 0) {

							j -= tester;

						}
					}

					else if(pagina[j].tipoCampo == 'I'){

				    		//pagina[j].valorCampo[0];
					
						char num[31];

						int *n = (int *)&pagina[j].valorCampo[0];


						sprintf (num, "%d", *n); 


						if (strcmp (num, r_where->valueWhere) == 0) {

				    			checker++;
							if (checker2 != 0) {

								j -= tester;

							}
				
						}

					} else if(pagina[j].tipoCampo == 'C' && strcmp (pagina[j].valorCampo, r_where->valueWhere) == 0){

				    		checker++;
						if (checker2 != 0) {

							j -= tester;

						}

					} else if(pagina[j].tipoCampo == 'D'){

						char num[31];

				    		double *n = (double *)&pagina[j].valorCampo[0];

						sprintf (num, "%lf", *n);

						if (strcmp (num, r_where->valueWhere) == 0) {

			    	        		checker++;
							if (checker2 != 0) {

								j -= tester;

							}

						}

					}
				}

				// Operação !=
				if (r_where->oper == 4) {

					if(pagina[j].tipoCampo == 'S' && strcmp (pagina[j].valorCampo, r_where->valueWhere) != 0) {

				    		checker++;
						if (checker2 != 0) {

							j -= tester;

						}
					}

					else if(pagina[j].tipoCampo == 'I'){

				    		//pagina[j].valorCampo[0];
					
						char num[31];

						int *n = (int *)&pagina[j].valorCampo[0];


						sprintf (num, "%d", *n); 


						if (strcmp (num, r_where->valueWhere) != 0) {

				    			checker++;
							if (checker2 != 0) {

								j -= tester;

							}
				
						}

					} else if(pagina[j].tipoCampo == 'C' && strcmp (pagina[j].valorCampo, r_where->valueWhere) != 0){

				    		checker++;
						if (checker2 != 0) {

							j -= tester;

						}

					} else if(pagina[j].tipoCampo == 'D'){

						char num[31];

				    		double *n = (double *)&pagina[j].valorCampo[0];

						sprintf (num, "%lf", *n);

						if (strcmp (num, r_where->valueWhere) != 0) {

			    	        		checker++;
							if (checker2 != 0) {

								j -= tester;

							}

						}

					}
				}

				// Operação >
				if (r_where->oper == 2) {

					if(pagina[j].tipoCampo == 'S' && strcmp (pagina[j].valorCampo, r_where->valueWhere) > 0) {

				    		checker++;
						if (checker2 != 0) {

							j -= tester;

						}
					}

					else if(pagina[j].tipoCampo == 'I'){

				    		//pagina[j].valorCampo[0];
					
						char num[31];

						int *n = (int *)&pagina[j].valorCampo[0];


						sprintf (num, "%d", *n); 


						if (strcmp (num, r_where->valueWhere) > 0) {

				    			checker++;
							if (checker2 != 0) {

								j -= tester;

							}
				
						}

					} else if(pagina[j].tipoCampo == 'C' && strcmp (pagina[j].valorCampo, r_where->valueWhere) > 0){

				    		checker++;
						if (checker2 != 0) {

							j -= tester;

						}

					} else if(pagina[j].tipoCampo == 'D'){

						char num[31];

				    		double *n = (double *)&pagina[j].valorCampo[0];

						sprintf (num, "%lf", *n);

						if (strcmp (num, r_where->valueWhere) > 0) {

			    	        		checker++;
							if (checker2 != 0) {

								j -= tester;

							}

						}

					}
				}

				// Operação <
				if (r_where->oper == 3) {

					if(pagina[j].tipoCampo == 'S' && strcmp (pagina[j].valorCampo, r_where->valueWhere) < 0) {

				    		checker++;
						if (checker2 != 0) {

							j -= tester;

						}
					}

					else if(pagina[j].tipoCampo == 'I'){

				    		//pagina[j].valorCampo[0];
					
						char num[31];

						int *n = (int *)&pagina[j].valorCampo[0];


						sprintf (num, "%d", *n); 


						if (strcmp (num, r_where->valueWhere) < 0) {

				    			checker++;
							if (checker2 != 0) {

								j -= tester;

							}
				
						}

					} else if(pagina[j].tipoCampo == 'C' && strcmp (pagina[j].valorCampo, r_where->valueWhere) < 0){

				    		checker++;
						if (checker2 != 0) {

							j -= tester;

						}

					} else if(pagina[j].tipoCampo == 'D'){

						char num[31];

				    		double *n = (double *)&pagina[j].valorCampo[0];

						sprintf (num, "%lf", *n);

						if (strcmp (num, r_where->valueWhere) < 0) {

			    	        		checker++;
							if (checker2 != 0) {

								j -= tester;

							}

						}

					}
				}
				// Operação =>
				if (r_where->oper == 5) {

					if(pagina[j].tipoCampo == 'S' && strcmp (pagina[j].valorCampo, r_where->valueWhere) >= 0) {

				    		checker++;
						if (checker2 != 0) {

							j -= tester;

						}
					}

					else if(pagina[j].tipoCampo == 'I'){

				    		//pagina[j].valorCampo[0];
					
						char num[31];

						int *n = (int *)&pagina[j].valorCampo[0];


						sprintf (num, "%d", *n); 


						if (strcmp (num, r_where->valueWhere) >= 0) {

				    			checker++;
							if (checker2 != 0) {

								j -= tester;

							}
				
						}

					} else if(pagina[j].tipoCampo == 'C' && strcmp (pagina[j].valorCampo, r_where->valueWhere) >= 0){

				    		checker++;
						if (checker2 != 0) {

							j -= tester;

						}

					} else if(pagina[j].tipoCampo == 'D'){

						char num[31];

				    		double *n = (double *)&pagina[j].valorCampo[0];

						sprintf (num, "%lf", *n);

						if (strcmp (num, r_where->valueWhere) >= 0) {

			    	        		checker++;
							if (checker2 != 0) {

								j -= tester;

							}

						}

					}
				}

				// Operação =<
				if (r_where->oper == 6) {

					if(pagina[j].tipoCampo == 'S' && strcmp (pagina[j].valorCampo, r_where->valueWhere) <= 0) {

				    		checker++;
						if (checker2 != 0) {

							j -= tester;

						}
					}

					else if(pagina[j].tipoCampo == 'I'){

				    		//pagina[j].valorCampo[0];
					
						char num[31];

						int *n = (int *)&pagina[j].valorCampo[0];


						sprintf (num, "%d", *n); 


						if (strcmp (num, r_where->valueWhere) <= 0) {

				    			checker++;
							if (checker2 != 0) {

								j -= tester;

							}
				
						}

					} else if(pagina[j].tipoCampo == 'C' && strcmp (pagina[j].valorCampo, r_where->valueWhere) <= 0){

				    		checker++;
						if (checker2 != 0) {

							j -= tester;

						}

					} else if(pagina[j].tipoCampo == 'D'){

						char num[31];

				    		double *n = (double *)&pagina[j].valorCampo[0];

						sprintf (num, "%lf", *n);

						if (strcmp (num, r_where->valueWhere) <= 0) {

			    	        		checker++;
							if (checker2 != 0) {

								j -= tester;

							}

						}

					}
				}
				//printf ("- op1 %d -", checker);
			}
			// AND CHECKER 2
			if (strcmp (pagina[j].nomeCampo, r_where->columnWhere2) == 0 && checker2 == 0) {
				// Operação =
				if (r_where->oper2 == 1) {

					if(pagina[j].tipoCampo == 'S' && strcmp (pagina[j].valorCampo, r_where->valueWhere2) == 0) {

				    		checker2++;
						
						if (checker != 0) {

							j -= tester;

						}
						
					}

					else if(pagina[j].tipoCampo == 'I'){

				    		//pagina[j].valorCampo[0];
					
						char num[31];

						int *n = (int *)&pagina[j].valorCampo[0];


						sprintf (num, "%d", *n); 


						if (strcmp (num, r_where->valueWhere2) == 0) {

				    			checker2++;
							if (checker != 0) {

								j -= tester;

							}
				
						}

					} else if(pagina[j].tipoCampo == 'C' && strcmp (pagina[j].valorCampo, r_where->valueWhere2) == 0){

				    		checker2++;
						if (checker != 0) {

							j -= tester;

						}

					} else if(pagina[j].tipoCampo == 'D'){

						char num[31];

				    		double *n = (double *)&pagina[j].valorCampo[0];

						sprintf (num, "%lf", *n);

						if (strcmp (num, r_where->valueWhere2) == 0) {

			    	        		checker2++;
							if (checker != 0) {

								j -= tester;

							}

						}

					}
				}

				// Operação !=
				if (r_where->oper2 == 4) {

					if(pagina[j].tipoCampo == 'S' && strcmp (pagina[j].valorCampo, r_where->valueWhere2) != 0) {

				    		checker2++;
						if (checker != 0) {

							j -= tester;

						}
					}

					else if(pagina[j].tipoCampo == 'I'){

				    		//pagina[j].valorCampo[0];
					
						char num[31];

						int *n = (int *)&pagina[j].valorCampo[0];


						sprintf (num, "%d", *n); 


						if (strcmp (num, r_where->valueWhere2) != 0) {

				    			checker2++;
							if (checker != 0) {

								j -= tester;

							}
				
						}

					} else if(pagina[j].tipoCampo == 'C' && strcmp (pagina[j].valorCampo, r_where->valueWhere2) != 0){

				    		checker2++;
						if (checker != 0) {

							j -= tester;

						}

					} else if(pagina[j].tipoCampo == 'D'){

						char num[31];

				    		double *n = (double *)&pagina[j].valorCampo[0];

						sprintf (num, "%lf", *n);

						if (strcmp (num, r_where->valueWhere2) != 0) {

			    	        		checker2++;
							if (checker != 0) {

								j -= tester;

							}

						}

					}
				}

				// Operação >
				if (r_where->oper2 == 2) {

					if(pagina[j].tipoCampo == 'S' && strcmp (pagina[j].valorCampo, r_where->valueWhere2) > 0) {

				    		checker2++;
						if (checker != 0) {

							j -= tester;

						}
					}

					else if(pagina[j].tipoCampo == 'I'){

				    		//pagina[j].valorCampo[0];
					
						char num[31];

						int *n = (int *)&pagina[j].valorCampo[0];


						sprintf (num, "%d", *n); 


						if (strcmp (num, r_where->valueWhere2) > 0) {

				    			checker2++;
							if (checker != 0) {

								j -= tester;

							}
				
						}

					} else if(pagina[j].tipoCampo == 'C' && strcmp (pagina[j].valorCampo, r_where->valueWhere2) > 0){

				    		checker2++;
						if (checker != 0) {

							j -= tester;

						}

					} else if(pagina[j].tipoCampo == 'D'){

						char num[31];

				    		double *n = (double *)&pagina[j].valorCampo[0];

						sprintf (num, "%lf", *n);

						if (strcmp (num, r_where->valueWhere2) > 0) {

			    	        		checker2++;
							if (checker != 0) {

								j -= tester;

							}

						}

					}
				}

				// Operação <
				if (r_where->oper2 == 3) {

					if(pagina[j].tipoCampo == 'S' && strcmp (pagina[j].valorCampo, r_where->valueWhere2) < 0) {

				    		checker2++;
						if (checker != 0) {

							j -= tester;

						}
					}

					else if(pagina[j].tipoCampo == 'I'){

				    		//pagina[j].valorCampo[0];
					
						char num[31];

						int *n = (int *)&pagina[j].valorCampo[0];


						sprintf (num, "%d", *n); 


						if (strcmp (num, r_where->valueWhere2) < 0) {

				    			checker2++;
							if (checker != 0) {

								j -= tester;

							}
				
						}

					} else if(pagina[j].tipoCampo == 'C' && strcmp (pagina[j].valorCampo, r_where->valueWhere2) < 0){

				    		checker2++;
						if (checker != 0) {

							j -= tester;

						}

					} else if(pagina[j].tipoCampo == 'D'){

						char num[31];

				    		double *n = (double *)&pagina[j].valorCampo[0];

						sprintf (num, "%lf", *n);

						if (strcmp (num, r_where->valueWhere2) < 0) {

			    	        		checker2++;
							if (checker != 0) {

								j -= tester;

							}

						}

					}
				}
				// Operação =>
				if (r_where->oper2 == 5) {

					if(pagina[j].tipoCampo == 'S' && strcmp (pagina[j].valorCampo, r_where->valueWhere2) >= 0) {

				    		checker2++;
						if (checker != 0) {

							j -= tester;

						}
					}

					else if(pagina[j].tipoCampo == 'I'){

				    		//pagina[j].valorCampo[0];
					
						char num[31];

						int *n = (int *)&pagina[j].valorCampo[0];


						sprintf (num, "%d", *n); 


						if (strcmp (num, r_where->valueWhere2) >= 0) {

				    			checker2++;
							if (checker != 0) {

								j -= tester;

							}
				
						}

					} else if(pagina[j].tipoCampo == 'C' && strcmp (pagina[j].valorCampo, r_where->valueWhere2) >= 0){

				    		checker2++;
						if (checker != 0) {

							j -= tester;

						}

					} else if(pagina[j].tipoCampo == 'D'){

						char num[31];

				    		double *n = (double *)&pagina[j].valorCampo[0];

						sprintf (num, "%lf", *n);

						if (strcmp (num, r_where->valueWhere2) >= 0) {

			    	        		checker++;
							if (checker != 0) {

								j -= tester;

							}

						}

					}
				}

				// Operação =<
				if (r_where->oper2 == 6) {

					if(pagina[j].tipoCampo == 'S' && strcmp (pagina[j].valorCampo, r_where->valueWhere2) <= 0) {

				    		checker2++;
						if (checker != 0) {

							j -= tester;

						}
					}

					else if(pagina[j].tipoCampo == 'I'){

				    		//pagina[j].valorCampo[0];
					
						char num[31];

						int *n = (int *)&pagina[j].valorCampo[0];


						sprintf (num, "%d", *n); 


						if (strcmp (num, r_where->valueWhere2) <= 0) {

				    			checker2++;
							if (checker != 0) {

								j -= tester;

							}
				
						}

					} else if(pagina[j].tipoCampo == 'C' && strcmp (pagina[j].valorCampo, r_where->valueWhere2) <= 0){

				    		checker2++;
						j -= tester;

					} else if(pagina[j].tipoCampo == 'D'){

						char num[31];

				    		double *n = (double *)&pagina[j].valorCampo[0];

						sprintf (num, "%lf", *n);

						if (strcmp (num, r_where->valueWhere2) <= 0) {

			    	        		checker2++;
							if (checker != 0) {

								j -= tester;

							}

						}

					}
				}

				
			}
				

		}
		// CHECAGEM CASO POSSUA OR
		if (r_where->andOr == 2) {
			// Check se tem AND ou OR - neste caso OR
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
				//printf ("- op1 %d -", checker);
			}
			// OR CHECKER 2
			if (strcmp (pagina[j].nomeCampo, r_where->columnWhere2) == 0 && checker2 == 0) {
				// Operação =
				if (r_where->oper2 == 1) {

					if(pagina[j].tipoCampo == 'S' && strcmp (pagina[j].valorCampo, r_where->valueWhere2) == 0) {

				    		checker2++;
						
						j -= tester;
						
					}

					else if(pagina[j].tipoCampo == 'I'){

				    		//pagina[j].valorCampo[0];
					
						char num[31];

						int *n = (int *)&pagina[j].valorCampo[0];


						sprintf (num, "%d", *n); 


						if (strcmp (num, r_where->valueWhere2) == 0) {

				    			checker2++;
							j -= tester;
				
						}

					} else if(pagina[j].tipoCampo == 'C' && strcmp (pagina[j].valorCampo, r_where->valueWhere2) == 0){

				    		checker2++;
						j -= tester;

					} else if(pagina[j].tipoCampo == 'D'){

						char num[31];

				    		double *n = (double *)&pagina[j].valorCampo[0];

						sprintf (num, "%lf", *n);

						if (strcmp (num, r_where->valueWhere2) == 0) {

			    	        		checker2++;
							j -= tester;

						}

					}
				}

				// Operação !=
				if (r_where->oper2 == 4) {

					if(pagina[j].tipoCampo == 'S' && strcmp (pagina[j].valorCampo, r_where->valueWhere2) != 0) {

				    		checker2++;
						j -= tester;
					}

					else if(pagina[j].tipoCampo == 'I'){

				    		//pagina[j].valorCampo[0];
					
						char num[31];

						int *n = (int *)&pagina[j].valorCampo[0];


						sprintf (num, "%d", *n); 


						if (strcmp (num, r_where->valueWhere2) != 0) {

				    			checker2++;
							j -= tester;
				
						}

					} else if(pagina[j].tipoCampo == 'C' && strcmp (pagina[j].valorCampo, r_where->valueWhere2) != 0){

				    		checker2++;
						j -= tester;

					} else if(pagina[j].tipoCampo == 'D'){

						char num[31];

				    		double *n = (double *)&pagina[j].valorCampo[0];

						sprintf (num, "%lf", *n);

						if (strcmp (num, r_where->valueWhere2) != 0) {

			    	        		checker2++;
							j -= tester;

						}

					}
				}

				// Operação >
				if (r_where->oper2 == 2) {

					if(pagina[j].tipoCampo == 'S' && strcmp (pagina[j].valorCampo, r_where->valueWhere2) > 0) {

				    		checker2++;
						j -= tester;
					}

					else if(pagina[j].tipoCampo == 'I'){

				    		//pagina[j].valorCampo[0];
					
						char num[31];

						int *n = (int *)&pagina[j].valorCampo[0];


						sprintf (num, "%d", *n); 


						if (strcmp (num, r_where->valueWhere2) > 0) {

				    			checker2++;
							j -= tester;
				
						}

					} else if(pagina[j].tipoCampo == 'C' && strcmp (pagina[j].valorCampo, r_where->valueWhere2) > 0){

				    		checker2++;
						j -= tester;

					} else if(pagina[j].tipoCampo == 'D'){

						char num[31];

				    		double *n = (double *)&pagina[j].valorCampo[0];

						sprintf (num, "%lf", *n);

						if (strcmp (num, r_where->valueWhere2) > 0) {

			    	        		checker2++;
							j -= tester;

						}

					}
				}

				// Operação <
				if (r_where->oper2 == 3) {

					if(pagina[j].tipoCampo == 'S' && strcmp (pagina[j].valorCampo, r_where->valueWhere2) < 0) {

				    		checker2++;
						j -= tester;
					}

					else if(pagina[j].tipoCampo == 'I'){

				    		//pagina[j].valorCampo[0];
					
						char num[31];

						int *n = (int *)&pagina[j].valorCampo[0];


						sprintf (num, "%d", *n); 


						if (strcmp (num, r_where->valueWhere2) < 0) {

				    			checker2++;
							j -= tester;
				
						}

					} else if(pagina[j].tipoCampo == 'C' && strcmp (pagina[j].valorCampo, r_where->valueWhere2) < 0){

				    		checker2++;
						j -= tester;

					} else if(pagina[j].tipoCampo == 'D'){

						char num[31];

				    		double *n = (double *)&pagina[j].valorCampo[0];

						sprintf (num, "%lf", *n);

						if (strcmp (num, r_where->valueWhere2) < 0) {

			    	        		checker2++;
							j -= tester;

						}

					}
				}
				// Operação =>
				if (r_where->oper2 == 5) {

					if(pagina[j].tipoCampo == 'S' && strcmp (pagina[j].valorCampo, r_where->valueWhere2) >= 0) {

				    		checker2++;
						j -= tester;
					}

					else if(pagina[j].tipoCampo == 'I'){

				    		//pagina[j].valorCampo[0];
					
						char num[31];

						int *n = (int *)&pagina[j].valorCampo[0];


						sprintf (num, "%d", *n); 


						if (strcmp (num, r_where->valueWhere2) >= 0) {

				    			checker2++;
							j -= tester;
				
						}

					} else if(pagina[j].tipoCampo == 'C' && strcmp (pagina[j].valorCampo, r_where->valueWhere2) >= 0){

				    		checker2++;
						j -= tester;

					} else if(pagina[j].tipoCampo == 'D'){

						char num[31];

				    		double *n = (double *)&pagina[j].valorCampo[0];

						sprintf (num, "%lf", *n);

						if (strcmp (num, r_where->valueWhere2) >= 0) {

			    	        		checker++;
							j -= tester;

						}

					}
				}

				// Operação =<
				if (r_where->oper2 == 6) {

					if(pagina[j].tipoCampo == 'S' && strcmp (pagina[j].valorCampo, r_where->valueWhere2) <= 0) {

				    		checker2++;
						j -= tester;
					}

					else if(pagina[j].tipoCampo == 'I'){

				    		//pagina[j].valorCampo[0];
					
						char num[31];

						int *n = (int *)&pagina[j].valorCampo[0];


						sprintf (num, "%d", *n); 


						if (strcmp (num, r_where->valueWhere2) <= 0) {

				    			checker2++;
							j -= tester;
				
						}

					} else if(pagina[j].tipoCampo == 'C' && strcmp (pagina[j].valorCampo, r_where->valueWhere2) <= 0){

				    		checker2++;
						j -= tester;

					} else if(pagina[j].tipoCampo == 'D'){

						char num[31];

				    		double *n = (double *)&pagina[j].valorCampo[0];

						sprintf (num, "%lf", *n);

						if (strcmp (num, r_where->valueWhere2) <= 0) {

			    	        		checker2++;
							

							j -= tester;

							

						}

					}
				}

				
			}
				

		}

		//////////////////////////
		if (r_where->andOr == 0) {

		    check = 0;
		    countCheck = 0;
		    while (countCheck < cols) {

				

				if (strcmp(s_insert->columnName[countCheck], pagina[j].nomeCampo) == 0 && checker != 0) {

				    check = 1;

				}

		                 countCheck++;

		    }
								
		    if (check == 1) {
				
				//printf ("\n\n\n%d\n\n\n", counter);
			
				if(pagina[j].tipoCampo == 'S') {
			    		printf(" %-20s ", pagina[j].valorCampo);
					//counter++;
				}

				else if(pagina[j].tipoCampo == 'I'){

			    		int *n = (int *)&pagina[j].valorCampo[0];

			    		printf(" %-10d ", *n);
					//counter++;

				} else if(pagina[j].tipoCampo == 'C'){

			    		printf(" %-10c ", pagina[j].valorCampo[0]);

					//counter++;

				} else if(pagina[j].tipoCampo == 'D'){

			    		double *n = (double *)&pagina[j].valorCampo[0];

		    	        	printf(" %-10f ", *n);

					//counter++;

				}

		

				if(tester != 0 && ((counter>=1 || cols == 1) && ((counter+1)%cols)==0)) {
				    	printf("\n");
					tester = -1;
					checker = 0;
					holder++;
					//counter++;
				}
				else  {
					
					printf("|");
					
				}
				counter++;

				

				check = 0;
				countCheck = 0;


		    }
			
		    if (j>=1 && ((j+1)%objeto.qtdCampos)==0) {
			
				tester = -1;
				checker = 0;

		    }


		}
		


		if (r_where->andOr == 1) {
			
		    check = 0;
		    countCheck = 0;
		    while (countCheck < cols) {

				

				if (strcmp(s_insert->columnName[countCheck], pagina[j].nomeCampo) == 0 && checker != 0 && checker2 != 0) {

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

				}


		

				if(tester != 0 && ((counter>=1 || cols == 1) && ((counter+1)%cols)==0)) {
				    	printf("\n");
					tester = -1;
					checker = 0;
					checker2 = 0;
					holder++;
				}
				else  {
					
						printf("|");
						
			    	}
				counter++;

                    }

		    if (j>=1 && ((j+1)%objeto.qtdCampos)==0) {

				if (checker == 0 && checker2 == 0) {

					tester = -1;
					checker = 0;
					checker2 = 0;

				}
				else if (checker != 0 && checker2 == 0) {

					tester = -1;
					checker = 0;
					checker2 = 0;

				}
				else if (checker == 0 && checker2 != 0) {

					tester = -1;
					checker = 0;
					checker2 = 0;

				}

		   }
		}

		if (r_where->andOr == 2) {

		    check = 0;
		    countCheck = 0;
		    while (countCheck < cols) {

				

				if (strcmp(s_insert->columnName[countCheck], pagina[j].nomeCampo) == 0 && (checker != 0 || checker2 != 0)) {

				    check = 1;

				}

		                 countCheck++;

		    }
								
		    if (check == 1) {

			
				if(pagina[j].tipoCampo == 'S') {
			    		printf(" %-20s ", pagina[j].valorCampo);
				
				}
				else if(pagina[j].tipoCampo == 'I'){

			    		int *n = (int *)&pagina[j].valorCampo[0];

			    		printf(" %-10d ", *n);
				

				} else if(pagina[j].tipoCampo == 'C'){

			    		printf(" %-10c ", pagina[j].valorCampo[0]);
				

				} else if(pagina[j].tipoCampo == 'D'){

			    		double *n = (double *)&pagina[j].valorCampo[0];

				

		    	        	printf(" %-10f ", *n);

				}


		

				if(tester != 0 && ((counter>=1 || cols == 1) && ((counter+1)%cols)==0)) {
				    	printf("\n");
					holder++;
					tester = -1;
					checker = 0;
					checker2 = 0;
				}
				else  {
					
					printf("|");
					
				}
				counter++;
		    }
	    	    if (j>=1 && ((j+1)%objeto.qtdCampos)==0) {

				if (checker == 0 && checker2 == 0) {
		
					tester = -1;
					checker = 0;
					checker2 = 0;
				

				}
				else if (checker != 0 && checker2 == 0) {

					tester = -1;
					checker = 0;
					checker2 = 0;
					

				}
				else if (checker == 0 && checker2 != 0) {

					tester = -1;
					checker = 0;
					checker2 = 0;
					


				}

				else if (checker != 0 && checker2 != 0) {

					tester = -1;
					checker = 0;
					checker2 = 0;
					


				}

		   }

		   

		}


		tester++;

    	    }

            checker = 0;
	    checker2 = 0;

    	    x-=bufferpoll[p++].nrec;

        }

    ntuples = holder;

    printf("\n(%d %s)\n\n",ntuples,(1>=ntuples)?"row": "rows");

    free(bufferpoll);

    free(esquema);
}



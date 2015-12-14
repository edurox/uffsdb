#include "buffend.h"

/* Função que faz a PROJEÇÃO*/



// Se foram especificadas colunas no *s_insert, verifica se elas existem no esquema.
int allColumnsExistsSel(rc_insert *s_insert, table *tabela, int cols);

void selecionar(rc_insert *s_insert, int cols) {

	table *tabela = (table *)malloc(sizeof(table));
	tabela->esquema = NULL;
	memset(tabela, 0, sizeof(table));
	column *colunas = NULL;
	tp_table *esquema = NULL;
	struct fs_objects objeto;
	memset(&objeto, 0, sizeof(struct fs_objects));


	abreTabela(s_insert->objName, &objeto, &tabela->esquema); //retorna o esquema para a insere valor
	strcpylower(tabela->nome, s_insert->objName);

	if(s_insert->columnName != NULL) {
		if (allColumnsExistsSel(s_insert, tabela, cols) == cols) {
			
				
			imprime(s_insert, cols);


		}else {
			
			printf ("\n\n\nWARNING: Column not found in table.\n\n\n");

		};
	};

	//freeTp_table(&esquema, objeto.qtdCampos);
	free(esquema);
	freeColumn(colunas);
}



// Se foram especificadas colunas no *s_insert, verifica se elas existem no esquema.
int allColumnsExistsSel(rc_insert *s_insert, table *tabela, int cols) {

	int i, count = 0, j = 0;
	if (!s_insert->columnName) return 0;

	table *tbl;

	tbl = tabela;


	struct fs_objects objeto;

	objeto = leObjeto(tbl->nome);

	while (j < objeto.qtdCampos) {


		for (i = 0; i < cols; i++) {


			if (strcmp (s_insert->columnName[i], tbl->esquema->nome) == 0) {

				
				
				count ++;
				
				if (count > cols) {
					return 0;
				}

			};	
	
		};

		if (tbl->esquema->next != NULL) {
	
			tbl->esquema = tbl->esquema->next;

		}

		j++;

	
	};

	free(tbl);

	return count;

					
}

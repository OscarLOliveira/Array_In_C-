#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include<string.h>

#include "titulo.h"

void lerArquivo();				// Le o arquivo de Produtos e ja adiciona os itens no Array
void gravarArquivo();			// Persiste os produtos em um arquivo .dat
void inclusao();				// Adiciona no array os Itens
int alteracao();
void exclusao();
void consulta();
void gerarTitulo();
void ImprimirLista();
void quicksort(int first, int last);
void menu();
void abastece();
void alterarEstoque();
void venda();

typedef struct {	

	int codigo;
	char descricao[50];
	double precoCompra;
	double precoVenda;
	int qtdeEstoque;	
	
} Produto;

// Globais
Produto lista[100];
int totalProdutos = 0;


void lerArquivo() {
	
	FILE *inFile; 
    Produto produto; 

    inFile = fopen ("produtos.dat", "r"); 
    if (inFile == NULL) 
    { 
        fprintf(stderr, "\nErro com arquivo !!!\n"); 
        exit(0); 
    };
      
    while(fread(&produto, sizeof(produto), 1, inFile)) {
    	//printf ("Codigo = %d Descricao = %s Valor Compra = %f Valor Venda %lf Qtde %d\n", produto.codigo,  produto.descricao, produto.precoCompra,
		//produto.precoVenda, produto.qtdeEstoque); 
		
		lista[totalProdutos] = produto;
		totalProdutos++;
	};   
  
    printf("\n Leitura efetuada com sucesso !!!\n");
    fclose (inFile); 
    
    quicksort(0, totalProdutos-1);
};

void gravarArquivo() {
	
	if (totalProdutos <= 0) {
		printf("Nenhum Produto encontrado !!!\n");
		return;
	};
	
	FILE *outFile; 
	Produto p;
      
    outFile = fopen ("produtos.dat", "w"); 
    if (outFile == NULL) 
    { 
        fprintf(stderr, "\nErro com arquivo !!!\n"); 
        exit(0); 
    }; 
        
    int i;
    
	for (i = 0; i < totalProdutos; i++){		
		 fwrite (&lista[i], sizeof(p), 1, outFile); 
	};
    
    printf("\n Gravacao efetuada com sucesso !!!\n");
    fclose (outFile); 
};

void inclusao(){
	
	int cod;
	fflush(stdin);	
	char op;
	
	do
	{
		printf(" Digite o codigo do Produto: ");
	    scanf("%d", &cod); 	
		
		int i;
		for (i = 0; i < totalProdutos-1; i++){
			if (lista[i].codigo == cod) {
		    	printf("Codigo ja cadastrado (%s) !!!\n", lista[i].descricao);
		    	return;
			};
	  	};			
		
		lista[totalProdutos].codigo = cod;
		
		char pp[50];
	    
		printf(" Digite a Descricao do Produto:(sem espacos) ");
	    scanf("%s", &lista[totalProdutos].descricao);
		printf(" Digite o Preco de Compra do Produto: ");
	    scanf("%lf", &lista[totalProdutos].precoCompra);
		printf(" Digite o Preco de Venda do Produto: ");
	    scanf("%lf", &lista[totalProdutos].precoVenda);	
		printf(" Digite a Quantidade em estoque: ");
	    scanf("%d", &lista[totalProdutos].qtdeEstoque);		    
		
		totalProdutos++;
		   
		printf("Deseja incluir mais produtos ? ");
		scanf(" %c", &op);	
	} while(op == 'S' || op == 's');
	
/*	int i;
	for (i = 0; i < posicao; i++){
		printf("%d\n", lista[i].codigo);
	};
*/	
	//printf("%d %s %lf %lf %d", produto.codigo, produto.descricao, produto.precoCompra, produto.precoVenda, produto.qtdeEstoque);
};

int alteracao(){
	int opcao;
	int codigo;
	int indice;
	bool passei = false;
	printf(" Informe o codigo do Produto que deseja alterar: ");
	scanf(" %d", &codigo);	
	int i;
	for (i = 0; i < totalProdutos-1; i++){
		if (lista[i].codigo == codigo) {
	    	indice = i;
	    	passei = true;
	    	break;
		};
  	};	
  	
 	if (!passei) {
 		printf("Produto nao Localizado !!!\n\n");
 		menu();
		return 0;
	 };
  	
	printf("******************************************************\n");
	printf("Codigo: %d\n", lista[indice].codigo);
	printf(" --> Para Alterar Digite 1 - Descricao: %s\n", lista[indice].descricao);
	printf(" --> Para Alterar Digite 2 - Preco Compra R$: %.2f\n", (lista[indice].precoCompra));
	printf(" --> Para Alterar Digite 3 - Preco Venda R$: %.2f\n", (lista[indice].precoVenda));
	printf(" --> Para Alterar Digite 4 - Qtde Estoque: %d\n", lista[indice].qtdeEstoque);
	printf("******************************************************\n\n");	
	
	char op;
	scanf("%d", &op);  // capturar a opção selecionada
		
					switch(op) {
					       case 1:		
						   	printf("Informe a nova Descricao: ");
				    		scanf(" %s", lista[indice].descricao);		
					        break;
						   		       
					       case 2:				
							printf("Informe o novo Preco de Compra: ");
							scanf(" %f", lista[indice].precoCompra);		         
					        break;    
						   		       
					       case 3:				
							printf("Informe o novo Preco de Venda: ");
							scanf(" %f", lista[indice].precoVenda);		           
					        break;
						   		       
					       case 4:				
							printf("Informe a nova Quantidade em Estoque: ");
							scanf(" %d", lista[indice].qtdeEstoque);		         	            
					        break;
					       
					       case 5:
					           menu();
					       break;		      
					       
						   default:
						       printf("\nOpcao Invalida !!!");
						       exit(0);
			   	    }; 

	printf("Alteracao Efetuada com sucesso !!!\n\n");
};

void exclusao(){
	
	int i;
	int indice;
	int codigo;
	bool passei = false;
	
	printf("Digte o codigo do produto: ");
	scanf("%d", &codigo);
		
	for (i = 0; i < totalProdutos; i++){
		if (lista[i].codigo == codigo) {
	    	indice = i;
	    	passei = true;
	    	break;
		};
    };
    
    if (!passei) {
    	printf("Produto nao Localizado !!!\n");
    	return;
	}
	
	for (i = indice; i < totalProdutos; i++){
			lista[i] = lista[i + 1];
	};
	
	totalProdutos--;
	printf("Produto Excluido com sucesso !!!\n");
};


void consulta(){
	int opcao;
	int indice;
	int codigo;
	 	 printf("Digte o codigo do Produto: ");
		scanf(" %d", &codigo);
	
	bool passei = false;	
	int i;
	for (i = 0; i < totalProdutos-1; i++){
		if (lista[i].codigo == codigo) {
	    	indice = i;
	    	passei = true;
	    	break;
		};
  	};	
  	
 	if (!passei) {
 		printf("Produto nao Localizado !!!\n\n");
 		menu();
		return;
	};
  	
printf("******************************************************\n");
printf("Codigo: %d\n", lista[indice].codigo);
printf(" --> Para Alterar Digite 1 - Descricao: %s\n", lista[indice].descricao);
printf(" --> Para Alterar Digite 2 - Preco Compra R$: %.2f\n", (lista[indice].precoCompra));
printf(" --> Para Alterar Digite 3 - Preco Venda R$: %.2f\n", (lista[indice].precoVenda));
printf(" --> Para Alterar Digite 4 - Qtde Estoque: %d\n", lista[indice].qtdeEstoque);
printf("******************************************************\n\n");	
	
};

void gerarTitulo() {
	printf("**************************************\n");
	printf("*               Controle             *\n");
	printf("**************************************\n");	
	printf("Opcoes do Sistema:\n");
};

void ImprimirLista() {
	
	if (totalProdutos <= 0) {
		printf("Nenhum Produto encontrado !!!\n");
		return;
	};
	
	int i;
	printf("************* RELATORIO **************\n");
	for (i = 0; i < totalProdutos; i++){
			printf("Codigo: %d\n", lista[i].codigo);
			printf("Descricao: %s\n", lista[i].descricao);
			printf("Preco Compra R$: %.2f\n", (lista[i].precoCompra));
			printf("Preco Venda R$: %.2f\n", (lista[i].precoVenda));
			printf("Qtde Estoque: %d\n\n", lista[i].qtdeEstoque);	
	};
	printf("**************************************\n");	
	
};

void menu(){
		
	gerarTitulo();
	
	char op;
	printf("ITEM A: \n\t1 - Incluir\n\t2 - Alterar\n\t3 - Excluir\n\t4 - Consultar\n\t5 - Ler Arquivo\n\t6 - Gravar Arquivo\n\t7 - Relatorio de produtos\n\t8 - Sair\n");
	printf("ITEM B: \n\t9 - Alterar Estoque\n");
	printf("ITEM C: \n\t10 - Iniciar Venda\n\tDetalhamento de um Produto (esta opcao e exibida apos a venda ser concretizada)\n\nOpcao:");
	
	scanf("%d", &op);  // capturar a opção selecionada
	
	while(op != 8) {
		system ("CLS");
		switch(op) {			
			
		       case 1:				
		          inclusao(); 
		          menu();
		        break;
			   		       
		       case 2:			
		          alteracao();
		          menu();
		       break;    
			   		       
		       case 3:				
		           exclusao();
		           menu();
		       break;
			   		       
		       case 4:				
		         consulta();
				 menu();		            
		       break;
		       
		       case 5:
		           lerArquivo();
		           menu();
		       break;	
		       
		       case 6:
		           gravarArquivo();
		           menu();
		       break;
			   
		       case 7:
		           ImprimirLista();
		           menu();
		       break;	  
		       
			   case 8:
		           exit(0);
		       break;	
			   
			   case 9:
		           alterarEstoque();
		           menu();
		       break;	
			   
			   case 10:
		           venda();
		           menu();
		       break;	         
		       
			   default:
			       printf("\nOpcao Invalida !!!\n");
			       menu();
   	    }; 

  	};
};

void abastece(){
	
	FILE *fp;
   	int qtdeItens = 0;
   	
   	char nomeFile[50] = "produtos.txt";

   	fp = fopen(nomeFile, "r");		      // abrindo o arquivo em modo leitura
   	rewind(fp);						  // setando o ponteiro no inicio do arquivo
   
   	// neste While apenas obtemos a quantidade de dados do arquivo
   	char n[100];
   	while(fscanf(fp, " %s", &n) == 1) {
        qtdeItens++;
	};
	
	printf("%d", qtdeItens);

    fclose(fp);	
};

void quicksort(int first, int last) {

	int pivo, qtde, i, j;
	Produto temp;
	
	if(first < last) {	      	
		
    	pivo = last;
      	i = first;
      	j = last;

      	while(i < j) {
      		
         	while(lista[i].codigo <= lista[pivo].codigo && i < last)
            	i++;
         	while(lista[j].codigo > lista[pivo].codigo)
            	j--;
         	if(i < j) {
            	temp = lista[i];
            	lista[i] = lista[j];
            	lista[j] = temp;
         	}
      	}

    	temp = lista[pivo];
      	lista[pivo] = lista[j];
      	lista[j] = temp;

      	quicksort(first, j - 1);
      	quicksort(j + 1, last);
      	
   	}   	
   
};

void alterarEstoque(){
	
	int opcao;
	int indice;
	int codigo;
	int estoque;
	printf("Digite o codigo do Produto: ");
	scanf(" %d", &codigo);
	
	bool passei = false;	
	int i;
	for (i = 0; i < totalProdutos-1; i++){
		if (lista[i].codigo == codigo) {
	    	indice = i;
	    	passei = true;
	    	break;
		};
  	};	
  	
 	if (!passei) {
 		printf("Produto nao Localizado !!!\n\n");
 		menu();
		return;
	};
	
printf("Digite 1 para ENTRADA ou 2 para SAIDA do Estoque:\n");
scanf(" %d", &opcao);

if (opcao < 0 && opcao > 2){
	printf("Opcao Invalida !!!\n");
	return;
};

printf("******************************************************\n");
printf("Codigo: %d\n", lista[indice].codigo);
printf("Descricao: %s\n", lista[indice].descricao);
printf("Qtde Estoque: %d\n", lista[indice].qtdeEstoque);
printf("******************************************************\n\n");

printf("Informe a quantidade a ser alterada:");
scanf(" %d", &estoque);

if (opcao == 1){
	lista[i].qtdeEstoque += estoque;
}
if (opcao == 2){
	lista[i].qtdeEstoque -= estoque;
}

printf("Estoque alterado com sucesso !!!\n");

printf("******************************************************\n");
printf("Codigo: %d\n", lista[indice].codigo);
printf("Descricao: %s\n", lista[indice].descricao);
printf("Qtde Estoque: %d\n", lista[indice].qtdeEstoque);
printf("******************************************************\n\n");	
}

void venda(){
	
int codigo;
int qtdeCompra;
bool achei = false;
Produto p;

printf("Informe o codigo do Produto que deseja comprar:\n");
scanf("%d", &codigo);
int i;
for (i = 0; i < totalProdutos; i++){
	
	if (lista[i].codigo == codigo) {	
		achei = true;
		p = lista[i];
		break;
	}
}

if (!achei){
	printf("Produto nao encontrado:\n");
	return;
}

printf("Informe a Quantidade de compra:\n");
scanf(" %d", &qtdeCompra);
if (p.qtdeEstoque < qtdeCompra){
	printf("Estoque menor que a quantidade informada !!!\n");
	return;
}

p.qtdeEstoque -= qtdeCompra;
lista[i]= p;

printf("******************** PEDIDO **************************\n");
printf("Codigo: %d\n", p.codigo);
printf("Descricao: %s\n", p.descricao);
printf("Valor unitario R$: %.2f x (%d)\n", (p.precoVenda), qtdeCompra);
printf("Total da Compra R$: %.2f\n", (p.precoVenda*qtdeCompra));
printf("Total de Itens R$: %d\n", qtdeCompra);
printf("******************************************************\n\n");
	
printf("******************* DETALHAMENTO *********************\n");
printf("PRODUTO: %s\n", (p.descricao));
printf("(item i) - Preco de Compra R$: %.2f\n", p.precoCompra);
printf("(item ii) - Preco de Venda R$: %.2f\n", p.precoVenda);
printf("(item iii) - Estoque Atual: %d\n", p.qtdeEstoque);
printf("(item iv) - Total de Itens Vendidos: %d\n", qtdeCompra);
printf("(item v) - Estoque Restante: %d\n", p.qtdeEstoque);
printf("(item vi) - Valor Bruto do Estoque: %.2f\n", p.qtdeEstoque*p.precoCompra);
	
}

int main () {
	
	assinatura();
	
	menu();	
	return 0;
};

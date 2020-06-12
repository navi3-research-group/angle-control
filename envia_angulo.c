#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include<locale.h>
int dados[6]; //vetor de dados a ser enviado para o programa Arduino

HANDLE hSerial;
wchar_t port[6] = {L"COM5"}; //A porta serial do meu arduino é a COM3
int vetor[10];
void envia();
int main()

{
	setlocale(LC_ALL, "Portuguese");
	do
	{
	
	vetor[0]=201;
	system("cls");
	printf("digite qual servo deve ser movimentado:\n1- para mover o servo do eixo X:\n2- para mover o servo do eixo y:\n3- para mover ambos os servos\n0-para sair: ");
	scanf("%i",&vetor[1]);
	system("cls");
	if(vetor[1]>=0 || vetor[1]<=3)
	{
		switch(vetor[1])
		{
			case 0 : printf("você está deixando o programa... até a proxima\n\n");
			system("pause");
			break;
			case 1 :system("cls");
			do{
				printf("digite o ângulo de rotação do servo no eixo X, os ângulos estão no intervalo de 15 a 180 graus: \n\n");
				scanf("%i",&vetor[2]);
				if(vetor[2]>180 || vetor[2]<0)
				{
					printf("ângulo invalido, digite um ângulo valido \n\n");
					system("pause");
				}
				else
				{
					vetor[3]=200;
					envia();
							
				}
				
			}while(vetor[2]>180 || vetor[2]<0);
			break;
			case 2 :system("cls");
			do{
				printf("digite o ângulo de rotação do servo no eixo y, os ângulos estão no intervalo de 45 a 125 graus: \n\n");
				scanf("%i",&vetor[2]);
				if(vetor[2]>125 || vetor[2]<45)
				{
					printf("ângulo invalido, digite um ângulo valido \n\n");
					system("pause");
				}
				else
				{
					vetor[3]=200;
							envia();
				}
				
			}while(vetor[2]>125 || vetor[2]<45) ;
			break;
			case 3 : system("cls");
			do{
				printf("digite o ângulo de rotação do servo no eixo X, os ângulos estão no intervalo de 15 a 180 graus: \n\n");
				scanf("%i",&vetor[2]);
				if(vetor[2]>180 || vetor[2]<0)
				{
					printf("ângulo invalido, digite um ângulo valido \n\n");
					system("pause");
				}
				else
				{
				do{
				printf("digite o ângulo de rotação do servo no eixo y, os ângulos estão no intervalo de 45 a 125 graus: \n\n");
				scanf("%i",&vetor[3]);
				if(vetor[3]>125 || vetor[3]<45)
				{
					printf("ângulo invalido, digite um ângulo valido \n\n");
					system("pause");
				}
				else
				{
						vetor[4]=200;
							envia();
				}
				
				
					}while(vetor[3]>180 || vetor[3]<0);	
				}
			
		}while(vetor[2]>125 || vetor[2]<0);	
	
	}
	}
	else
	{
		printf("valor digitado invalido!!\n\n");
		system("pause");
	}
	/*vetor[]=200;
	envia();*/
	}while(vetor[1]!=0);
}


void envia()
{
	hSerial = CreateFile("COM5", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	
	DCB dcbSerialParams = {0};
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	GetCommState(hSerial, &dcbSerialParams);
	dcbSerialParams.BaudRate = CBR_9600;
	dcbSerialParams.ByteSize = 8;
	dcbSerialParams.StopBits = ONESTOPBIT;
	dcbSerialParams.Parity = NOPARITY;
	SetCommState(hSerial, &dcbSerialParams);
	
	COMMTIMEOUTS timeouts = {0};
	timeouts.ReadIntervalTimeout = 50;
	timeouts.ReadTotalTimeoutConstant = 50;
	timeouts.ReadTotalTimeoutMultiplier = 10;
	timeouts.WriteTotalTimeoutConstant = 50;
	timeouts.WriteTotalTimeoutMultiplier = 10;
	SetCommTimeouts(hSerial, &timeouts);   
	
	//Enviando dados para o Arduíno
	int TxBuff [1];
	unsigned int TotalBytesaEnviar = 1;
	unsigned long BytesEnviados;  
	int i;
	for(i=0; vetor[i]!=200; i++)
	{
		TxBuff[0] = vetor[i]; //pega o elemento do vetor e atribui ao vetor a ser enviado para o Arduino
		printf("%i\n", vetor[i]);
		WriteFile(hSerial, &TxBuff, TotalBytesaEnviar, &BytesEnviados, NULL); //escreve na porta serial
		sleep(1); //comando permite que o programa fique aguardando o processamento por 3 segundos
	}
		TxBuff[0] = vetor[i]; //pega o elemento do vetor e atribui ao vetor a ser enviado para o Arduino
		printf("%i\n", vetor[i]);
		WriteFile(hSerial, &TxBuff, TotalBytesaEnviar, &BytesEnviados, NULL); //escreve na porta serial
		sleep(1); //comando permite que o programa fique aguardando o processamento por 3 segundos
   	//Recebendo dados do Arduíno
	const int tamanhoDadosReceber = 25; //Define o tamanho do vetor de caracter a receber do Arduino
	char RxBuff [tamanhoDadosReceber]; 
	unsigned int TotalBytesaReceber = tamanhoDadosReceber;
	unsigned long BytesRecebidos;
	
	ReadFile(hSerial, &RxBuff, TotalBytesaReceber, &BytesRecebidos, NULL); //lê os dados enviados na porta serial
	
	//Adiciona o caracter de final de String '\0' no vetor de caracter recebido. A variável BytesRecebidos contém a quantidade caracteres recebidos
	RxBuff[BytesRecebidos]='\0';
	
	sleep(2);
	
	system("cls");
	
	printf("%s \n\n",RxBuff);
	system("pause");
	
	
	CloseHandle (hSerial); //fecha a porta serial
}




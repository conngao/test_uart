#include <stdio.h>
#include <string.h>
#include <math.h>

#define leng 50


void task4_UART(void);
float charTofloat(char str_Trans[]);
void get_Data(char str_Trans[]);

float val_Amoni = 20.256;
float val_Sulfur = 12.3456;
//data tran from stm -> esp
float NH3;
float SO2;
char Data[leng];

int main()
{
    task4_UART();
	get_Data(Data);
}

void task4_UART(void)
{	
	char str_Data_Amoni[leng];	
	char str_Data_Sulfur[leng];
	char str_Data[leng];
	for(int i=0; i<leng; i++)
	{
		str_Data_Amoni[i] = 0;
		str_Data_Sulfur[i] = 0;
		str_Data[i] = 0;
	}
	sprintf(str_Data_Amoni,"{\"Amoniac\":\"%0.2f\",", val_Amoni); 
	sprintf(str_Data_Sulfur,"\"SulfurDioxit\":\"%0.2f\"}", val_Sulfur);
	strcat(str_Data, str_Data_Amoni);
	strcat(str_Data, str_Data_Sulfur);
	strcpy(Data,str_Data);
	printf("%s",Data);
	//{"Amoniac":"20.26","SulfurDioxit":"12.35"}
}

void get_Data(char str_Trans[])
{		
	char char_Amoni[leng];
	char char_Sulfur[leng];
	char Data_Recever[leng];
	for(int i = 0; i <strlen(str_Trans); i++)
	{
		char_Amoni[i] = 0;
		char_Sulfur[i] = 0;
		Data_Recever[i] = 0;
	}
	int j, m, n, k = 0;
	for(int c=0; c<strlen(str_Trans); c++ )
	{
		if(str_Trans[c]>=0x30&&str_Trans[c]<=0x39||str_Trans[c]==0x2C||str_Trans[c]==0x2E)
		{
			Data_Recever[j] = str_Trans[c];
			j++;
		}
	}
	printf("\nData_Recever: %s",Data_Recever);

	int vitri = 0;
	for(int a = 0; a<strlen(Data_Recever); a++)
	{
		if(Data_Recever[a]==0x2C)
		{
			vitri = a;
		}
		continue;
	}

	for(int k = 0; k<vitri; k++)
	{
		char_Amoni[m] = Data_Recever[k];
		m++;
	}
	printf("\nNH3: %s",char_Amoni);

	for(int l = vitri+1; l<strlen(Data_Recever); l++)
	{
		char_Sulfur[n] = Data_Recever[l];
		n++;
	}
	printf("\nSO2: %s",char_Sulfur);
	NH3 = charTofloat(char_Amoni);
	SO2 = charTofloat(char_Sulfur);
}

float charTofloat(char chuoi[])
{
    int vitricham=0;
    float conv=0;
    for (int i = 0; i < strlen(chuoi); i++)
    {
        if (chuoi[i]=='.')
        {
            vitricham=i;
        }
    }
    for (int i = 0; i <vitricham; i++)
    {
        conv+=(chuoi[i]-48)*pow(10,vitricham-i-1);
    }

    for (int i = vitricham; i < strlen(chuoi)-1; i++)
    {
        conv+=(chuoi[i+1]-48)*pow(10,vitricham-1-i);
    }
    return conv;
}

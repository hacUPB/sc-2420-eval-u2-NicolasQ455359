#include <stdio.h>
#include <math.h> //incluyo esta libreria para que funcione pow

float calcula_IMC(float,float);  //Prototipo de la función

int main(int argc, char const *argv[])
{

    float estatura, peso, imc;
    char Nombre[30];

    printf ("Ingrese su nombre: \n");
    fgets(Nombre, 30, stdin); //lee texto de un archivo

    printf("Ingrese su peso: \n");
    scanf("%f",&peso); //lee del teclado y lo comvierte al formato

    printf("Ingrese su estatura: \n");
    scanf("%f",&estatura); //%f es float

    imc = calcula_IMC(peso, estatura); //Llama la función


    printf("%s su IMC = %f\n",Nombre,imc);
   

    printf("Sistemas Computacionales 2024\n");
    return 0;
}

float calcula_IMC(float peso,float estatura) //No lleva ;
{
    float IMC;
    //IMC = peso / estatura2
    IMC = peso / pow(estatura, 2);
    return IMC;
}
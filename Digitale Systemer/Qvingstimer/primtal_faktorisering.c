#include <stdio.h>

int primtall(int x){ //Denne funksjonen sjekker om x er et primtall
    if(x<2){
        return 0;
    }
    else{
        for(int i=2; i<x; i++){
            if(x%i==0){
                return 0;
            }
        }
        return 1;
    }
}

int main(void){
    int input_x;

    printf("Skriv inn et heltall: ");
    scanf("%d",&input_x);


    if(primtall(input_x)!=1){
        printf("%d=",input_x);
        faktoriser(input_x);
    }
    else{
        printf("\nTallet er et primtall og kan derfor ikke faktoriseres.\n");
    }
    return 0;
}

int faktoriser(int x){
    for(int i=0; i<=x; i++){//Her lå feilen. Den var "i<x" skal være "i<=x"
        if(primtall(i)==1){
            while(x%i==0){
                x /= i;
                printf("%d*",i);
            }
        }
    }
    printf("1\n");//Dette gjøres sånn at faktorene ikke skal ende (x*x*x*)
    return 0;
}

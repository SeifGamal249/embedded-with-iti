#include <stdio.h>

void main(){
    int num=0;
    int rem=0;
    int array[32]={0};
    int counter=0;
    
    printf("please enter a decimal number :");
    scanf("%d",&num);

    for (int i = 0; i < 32; i++)
    {
        rem=num%2;
        num=num/2;
        array[i]=rem;
        counter++;        
        if (num==0)
        {
            break;
        } 
    }
    
    for (int i = counter-1; i >= 0; i--)
    {
        printf("%d",array[i]);
    }
    
}
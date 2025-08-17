#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "def_header.h"
#include "header.h"
#include "def_header.h"

u16 admin_choice=0;

typedef struct ADMINE_data
{
    c8 username[20];
    u16 password;
}AD;

u16 Admin_Choice(){
    printf("please select from the following :\n");
    printf("1. Add new patient record\n");
    printf("2. Edit patient record\n");
    printf("3. Reserve a slot with the doctor\n");
    printf("4. Cancel reservation\n");
    printf("5. IF YOU WANT TO EXIT\n");

    scanf("%d",&admin_choice);
    switch (admin_choice)
    {
        case 1:
            ADD_patient();
            break;
        case 2:
            EDTI_patient();
            break;
        case 3:
            RESERVE_patient();
            break;
        case 4:
            CANCEL_reservation();
            break;
        case 5:
            return 0;
            break;
        default:
            printf("you didn't select\n");
            break;
        }
}
void main(){
    u16 choice_mode=0;
    u16 counter=0;
    AD admin1={username:"admin",password:1234};    
    while (1)
    {
        printf("*******************************************************************\n");
        printf("please select between the following : \nfor admin mode select\t1\nfor user mode select\t2\n");        
        u8 flag_1=1;
        while (flag_1)
        {    
            scanf("%d",&choice_mode);
            if ((choice_mode!=1)&&(choice_mode!=2))
            {
                printf("please enter the correct choice\n");
            }
            else
            {
                printf("*******************************************************************\n");
                printf("welcome to our program\n");
                printf("*******************************************************************\n");
                flag_1=0;
            }
        }
        
        u16 flag_2=1;
        if (choice_mode==1)
        {
            while (flag_2)
            {
                c8 admin_name_entered[20];
                u16 admin__pass_entered;
                printf("please enter the username\t");
                scanf("%s",&admin_name_entered);
                printf("please enter the password\t");
                scanf("%d",&admin__pass_entered);
                if (strcmp(admin_name_entered,admin1.username)==0&&(admin__pass_entered==admin1.password))
                {
                    printf("*******************************************************************\n");
                    printf("login successful !! ^_^\n");
                    printf("*******************************************************************\n");
                    while (Admin_Choice()!=0)
                    {
                        //loop until user choose to exit
                    }
                
                    flag_2=0;
                }
                else{
                    printf("*******************************************************************\n");
                    printf("you entered wrong username or password please try again\n");
                    counter++;
                    if (counter==3)
                    {
                        printf("*******************************************************************\n");
                        printf("you have reached your times of try\nplease try again later\n");
                        flag_2=0;
                    } 
                }  
            } 
        }
        else if (choice_mode==2)
        {
            printf("*******************************************************************\n");
            printf("welcome\nyou are now in the user window\n");
            printf("*******************************************************************\n");

            user_func();
        }
    }
    return;

}
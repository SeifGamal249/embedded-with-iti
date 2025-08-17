#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "header.h"

typedef struct ADD_patient
{
    c8 name[20];
    u16 age;
    u16 id;
    c8 gender[20];
}ADD;

typedef struct NODE_patient
{
    ADD patients;
    struct NODE_patient *next_node_pointer;
}Node;

Node *HEAD=NULL;

typedef struct available_slots
{
    u16 slot[2];
    c8 saved_slot[100];
    struct available_slots *slot_ptr_next;
    ADD data_of_patient;
}As;

As *slot_HEAD=NULL;

//As arr[5];


u16 ADD_patient(){
    u16 num=0;
    u16 id;
    u16 flag=1;
    u16 flag_search=1;
    Node *ptr=(Node*)(malloc(sizeof(Node)));
    ptr->next_node_pointer=HEAD;
    HEAD=ptr;
    printf("*******************************************************************\n");
    printf("please enter the name of the patient\t");
    scanf("%s",&(ptr->patients.name));
    printf("please enter the age of the patient\t");
    scanf("%d",&(ptr->patients.age));
    printf("please enter the id of the patient\t");
    while (flag_search)
    {
        scanf("%d",&id);
        u16 found=0;    
        Node *search_ptr;
        search_ptr=HEAD;    //make it starts from the head address

        while (search_ptr!=NULL)
        {   
            if ((search_ptr->patients.id)==(id))
            {
                printf("*******************************************************************\n");
                printf("you entered an exist id please enter another one\t");
                printf("\n*******************************************************************\n");

                found=1;
                break;
            }
            search_ptr=search_ptr->next_node_pointer;   
            /*
            changing the value of the search_ptr in each cycle to access the next address
            it must be after the if condition to check also the head(the first address he accessed)
            */
        }
        if (found==0)
        {
            ptr->patients.id=id;
            flag_search=0;
        }
        
    }

    printf("please enter the gender of the patient\t");
    scanf("%s",&(ptr->patients.gender));
    printf("*******************************************************************\n");
    printf("Do you want to cotinoue adding if yes press 1 if not press 2\t");
    scanf("%d",&num);
    printf("*******************************************************************\n");
    if (num==1)
    {
        ADD_patient();
    }
    else if(num==2)
    {
        return 1;
    }
    else 
    {
        printf("*******************************************************************\n");
        printf("you entered the wrong number\n");
        printf("*******************************************************************\n");
    }
    
}

u16 EDTI_patient(){
    u16 id=0;
    u16 choice=0;
    printf("*******************************************************************\n");
    printf("please enter the id of the patient\t");
    scanf("%d",&id);
    Node *search_id;
    search_id=HEAD;
    u16 found =0;
    
        while (search_id!=NULL)
        {
            if (id==search_id->patients.id)
            {
                static u16 new_id=0;
                c8 new_gender[20];
                u16 new_age=0;
                c8 new_name[20];
                printf("*******************************************************************\n");
                printf("what do you want to edit in the patient data:\n");
                printf("1. for editing the id\n");
                printf("2. for editing the gender\n");
                printf("3. for editing the age\n");
                printf("4. for editing the name\n");
                printf("5. for exit\n");

                scanf("%d",&choice);
                printf("*******************************************************************\n");

                switch (choice)
                {
                case 1:
                    printf("please enter the new id of the patient\t");
                    scanf("%d",&new_id);
                    search_id->patients.id=new_id;
                    break;
                case 2:
                    printf("please enter the gender of the patient\t");
                    scanf("%s", new_gender);
                    strcpy(search_id->patients.gender, new_gender);
                    break;
                case 3:
                    printf("please enter the age of the patient\t");
                    scanf("%d",&new_age);
                    search_id->patients.age=new_age;
                    break;
                case 4:
                    printf("please enter the name of the patient\t");
                    scanf("%s", new_name);
                    strcpy(search_id->patients.name, new_name);
                    break;
                case 5:
                    return 0;
                default:
                    printf("you choose wrong number\n");
                    break;
                }
                found =1;
                break;
            }
            search_id=search_id->next_node_pointer;

            }

         if(!found){
                printf("\nyou entered wrong id\n");
        }       u16 num_4_CHOICE=0;
        printf("*******************************************************************\n");
        printf("if you want to continou editing please enter 1 if not enter 2\t");
        scanf("%d",&num_4_CHOICE);
        printf("*******************************************************************\n");

        if (num_4_CHOICE==1)
        {
            EDTI_patient();
        }
        else if (num_4_CHOICE==2)
        {
            return 1;
        }
        else{
            printf("you entered wrong number\n");
        }
    }


u16 RESERVE_patient(){
    u16 choice=0;
    u16 id=0;
    u16 flag=1;
    u16 found=0;
    As *ptr=(As*)(malloc(sizeof(As)));
    ptr->slot_ptr_next=slot_HEAD;
    slot_HEAD=ptr;
    static int num_1=0;
    static int num_2=0;

    ptr->slot[0]=num_1;
    ptr->slot[1]=num_2;

    Node *ptr_4_res_pat=HEAD;
    printf("*******************************************************************\n");
    printf("hello welcome \nif you want to reserve with the doctor these are the available slots\n");
    printf("FIRST SLOT ->from 2 to 2:30 PRESS 1\n");
    printf("SECOND SLOT->from 2:30 to 3 PRESS 2\n");
    printf("THIRD SLOT ->from 3 to 3:30 PRESS 3\n");
    printf("FOURTH SLOT->from 4 to 4:30 PRESS 4\n");
    printf("FIFTH SLOT ->from 4:30 to 5 PRESS 5\n");
    printf("IF YOU WANT TO EXIT PRESS 6\n");

    scanf("%d",&choice);
    printf("*******************************************************************\n");
    printf("please enter the patients id\t");
    scanf("%d",&id);

//    while(flag)
 //   {
        while (ptr_4_res_pat!=NULL) //for checking the id exist or not
        {
            if (id==ptr_4_res_pat->patients.id)
            {
                switch (choice)
                {
                    case 1:
                        for (int i = 0; i < 2; i++)
                        {
                            if (ptr->slot[i]==0)
                            {
                                ptr->slot[i]=id;
                                strcpy(ptr->saved_slot, "->from 2 to 2:30");
                                printf("saved in slot 1\n");
                                break;
                            }
                            else if(ptr->slot[i]!=0)
                            {
                                printf("NO available slots in this time slot\n");
                            }
                        }
                        break;
                    case 2:
                        for (int i = 0; i < 2; i++)
                        {
                            if (ptr->slot[i]==0)
                            {
                                ptr->slot[i]=id;
                                strcpy(ptr->saved_slot, "->from 2:30 to 3");
                                printf("saved in slot 2\n");

                                break;
                            }
                            else if(ptr->slot[i]!=0){
                                printf("NO available slots in this time slot\n");
                            }        
                        }
                        break;
                    case 3:
                        for (int i = 0; i < 2; i++)
                        {
                            if (ptr->slot[i]==0)
                            {
                                ptr->slot[i]=id;
                                strcpy(ptr->saved_slot, "->from 4 to 4:30");
                                printf("saved in slot 3\n");

                                break;
                            }
                            else if(ptr->slot[i]!=0){
                                printf("NO available slots in this time slot\n");
                            }     
                        }
                        break;
                    case 4:
                        for (int i = 0; i < 2; i++)
                        {
                            if (ptr->slot[i]==0)
                            {
                                ptr->slot[i]=id;
                                strcpy(ptr->saved_slot, "->from 4:30 to 5");
                                printf("saved in slot 4\n");

                                break;
                            }
                            else if(ptr->slot[i]!=0){
                                printf("NO available slots in this time slot\n");
                            }        
                        }
                        break;
                    case 5:
                        for (int i = 0; i < 2; i++)
                        {
                            if (ptr->slot[i]==0)
                            {
                                ptr->slot[i]=id;
                                strcpy(ptr->saved_slot, "->from 4:30 to 5");
                                printf("saved in slot 5\n");

                                break;
                            }
                            else if(ptr->slot[i]!=0){
                                printf("NO available slots in this time slot\n");
                            }    
                        }
                        break;
                    case 6:
                        return 0;
                    default:
                        break;
                }
                found=1;
                break;
            }
            ptr_4_res_pat=ptr_4_res_pat->next_node_pointer;

        }
            if(!found){
                printf("you entered wrong id\n");
            }
            
        //}
        u16 num_4_CHOICE=0;
        printf("*******************************************************************\n");
        printf("if you want to continou reserving please enter 1 if not enter 2\t");
        scanf("%d",&num_4_CHOICE);
        printf("*******************************************************************\n");

        if (num_4_CHOICE==1)
        {
            flag=0;
            RESERVE_patient();
        }
        else if (num_4_CHOICE==2)
        {
            return 1;
        }
        else{
            printf("you entered wrong number\n");
        }
    
    }

int CANCEL_reservation(){
    u16 id=0;
    u16 flag=1;
    printf("please if you want to cancel a reservation of a patient\n");
    
    Node *cancel_res_ptr=HEAD;
    As *cancel_ptr=slot_HEAD;
    while(flag)
    {
        while (cancel_res_ptr!=0)
        {
            printf("please enter the id of the patient\n");
            scanf("%d",&id);
            if (id==cancel_res_ptr->patients.id)
            {
            
                while (cancel_ptr!=NULL)
                {
                    for (int j = 0; j < 2; j++)
                    {
                        if (cancel_ptr->slot[j]!=0)
                        {
                            cancel_ptr->slot[j]=0;
                            printf("*******************************************************************\n");
                            printf("DONE\n");
                            printf("*******************************************************************\n");
                            flag=0;
                            return 1;
                            break;
                        }
                        else{
                            printf("*******************************************************************\n");
                            printf("it is already empty slot\n");
                            printf("*******************************************************************\n");
                        }
                    }
                    cancel_ptr=cancel_ptr->slot_ptr_next;
                }
                

            }
            
            else{
                printf("you entered wrong id\n");
            }
            cancel_res_ptr=cancel_res_ptr->next_node_pointer;
            
        }
        
    }
}

u16 user_func(){
    u16 id;
    Node *User_ptr=HEAD;

    printf("*******************************************************************\n");
    printf("the reserved slots are:\n");
    As *user_slot=slot_HEAD;    
    while(user_slot!=NULL)
    {
        printf("%s\n",user_slot->saved_slot);
        user_slot=user_slot->slot_ptr_next;
    }
    printf("*******************************************************************\n");

    printf("please enter the id\t");
    scanf("%d",&id);
    printf("*******************************************************************\n");

    user_slot=slot_HEAD;    
    u16 found=0;
    while (User_ptr!=NULL)
    {
        if (id==User_ptr->patients.id)
        {
            
            printf("there is the data of the patient\n");
            printf("the patient name\t%s\n",User_ptr->patients.name);
            printf("the patient age\t\t%d\n",User_ptr->patients.age);
            printf("the patient gender\t%s\n",User_ptr->patients.gender);
            while (user_slot!=NULL)
            {
                for (int i = 0; i < 2; i++)
                {
                    if (user_slot->slot[i] == id)
                    {
                        printf("the patient reserved date %s\n",user_slot->saved_slot);
                    }                    
                }
                user_slot=user_slot->slot_ptr_next;
            }
            
            found=1;
            break;
        }

        User_ptr=User_ptr->next_node_pointer;
        
    }
    if(!found){
            printf("you entered wrong id\n");
        }
}

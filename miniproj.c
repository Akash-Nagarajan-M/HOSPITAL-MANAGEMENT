#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//DOUBLY LINKED LIST
struct doctor{
    int d_id,d_salary,d_age,d_slots;
    char d_name[30],d_contact[100],d_gender[20],d_desig[30],d_dept[30],d_doj[30],d_time[10];
    struct doctor *next,*prev;
};
//LINKED LIST
struct patient{
    int p_id,p_age;
    char p_name[30],p_gender[10],p_address[300],p_history[300];
    struct patient *next;
};
//QUEUE
struct queue{
    int a_id,t_no,qp_id,qd_id;
    char qd_name[30],qp_name[30],time[30];
    struct queue *next;
};
struct queue *front,*rear;
struct patient *pat;
struct doctor *doc;
void menu();
void blue() {
printf("\033[1;36m");
}
void reset () {
printf("\033[0m");
}
void green(){
printf("\033[1;32m");
}
void appointment();
void print_bill(int aid,int pid,int did,int tno,char *pname,char *dname,char *timings){
    green();
    printf("  \t***************************************************************\n");
    printf("  \t*\t\t  %-43s *\n","APPOINTMENT RECEIPT");
    printf("  \t*-------------------------------------------------------------*\n");
    printf("\t*\t\t    %-41s *","ABC HOSPITAL");
    printf("\n\t* %-20s \t %-28s *\n","1,ABC STREET,CD,CHE,TN.","Pincode:600023");
    printf("  \t*-------------------------------------------------------------*\n");
    printf("\t* Appointment ID:%-9d\t Token no:%-19d *\n\t* Patient id:%-6d\t\t Patient name:%-15s *\n\t* Doctor id:%-6d\t\t Doctor name:%-16s *\n",aid,tno+1,pid,pname,did,dname);
    printf("\t* Doctor timings:%-15s Bill amount:Rs.300\t      *\n",timings);
    printf("\t***************************************************************\n");
    reset();    
}
void pat_details();
struct patient* search_pat(struct patient *pat){
    struct patient *temp=pat;
    if(temp==NULL){printf("\nPatient Linked list empty\n");
    pat_details();}
    green();
    printf("\t----------------------------");
    printf("\n\t|   SEARCH PATIENT         |\n");
    printf("\t----------------------------");
    blue();
    printf("\n\t| %-20s   |","1.Search by patient id");
    printf("\n\t| %-16s |","2.Search by patient name");
    printf("\n\t| %-16s |","3.Return to patient menu");
    printf("\n\t| %-22s   |\n","4.Go to appointment");
    printf("\t----------------------------");
    reset();
    int choice;
    printf("\nEnter your choice:");
    scanf("%d",&choice);
    if(choice==1){
        int id;
        printf("\nEnter the id:");
        scanf("%d",&id);
        while(temp!=NULL && temp->p_id!=id){
            temp=temp->next;
        }
        if(temp==NULL){
            printf("\nPatient details not found\n");
            search_pat(pat);
        }
        else return temp;
    }
    else if(choice==2){
        int flag=0;
        char name[30];
        printf("\nEnter patient name:");
        scanf("%s",name);
        struct patient *temp1=NULL;
        while(temp!=NULL){
            if(!strcmp(temp->p_name,name)){
                if(flag==1){
                    printf("Patient name repeated\nUse other ways to search\n\n");
                    search_pat(pat);
                }
                flag=1;
                temp1=temp;
            }
            temp=temp->next;
        }
        if(temp1==NULL){
            printf("\nPatient details not found\n");
            search_pat(pat);
        }
        else return temp1;
    }
    else if(choice==3){
        pat_details();
    }
    else if(choice==4){
        appointment();
    }
    else{
        printf("\nEnter a correct choice\n");
        search_pat(pat);
    }
}
void modify_pat(struct patient *pat){
    struct patient *rm=search_pat(pat);
    while(1){
    printf("\nChoose the details you want to change\n1.Name\n2.Age\n3.Gender\n4.Address\n5.History\n6.All\n7.Return\n");
    int choice;
    printf("Enter your choice:");
    scanf("%d",&choice);
    switch(choice){
        case 1:
        printf("Old Name:%s\n",rm->p_name);
        printf("New name:");
        scanf("%s",rm->p_name);
        break;
        case 2:
        printf("Old Age:%d\n",rm->p_age);
        printf("New age:");
        scanf("%d",&rm->p_age);
        break;
        case 3:
        printf("Old Gender:%s\n",rm->p_gender);
        printf("New Gender:");
        scanf("%s",rm->p_gender);
        break;
        case 4:
        printf("Old Address:%s\n",rm->p_address);
        printf("New Address:");
        scanf("%s",rm->p_address);
        break;
        case 5:
        printf("Old History:%s\n",rm->p_history);
        printf("New history:");
        scanf("%s",rm->p_history);
        break;
        case 6:
        printf("Old Name:%s\n",rm->p_name);
        printf("New name:");
        scanf("%s",rm->p_name);
        printf("Old Age:%d\n",rm->p_age);
        printf("New age:");
        scanf("%d",&rm->p_age);
        printf("Old Gender:%s\n",rm->p_gender);
        printf("New Gender:");
        scanf("%s",rm->p_gender);
        printf("Old Address:%s\n",rm->p_address);
        printf("New Address:");
        scanf("%s",rm->p_address);
        printf("Old History:%s\n",rm->p_history);
        printf("New history:");
        scanf("%s",rm->p_history);
        break;
        case 7:
        pat_details();
        break;
    }
    }
}
void remove_pat(struct patient **pat){
    struct patient *rm=search_pat(*pat);
    int id=rm->p_id;
    struct patient *tmp=(*pat);
    if(tmp->next==rm){
        tmp->next=rm->next;
        (*pat)=tmp;
        free(rm);
    }
    else if(tmp==rm){
        (*pat) = rm->next; 
        free(rm);
    }
    else{
    while(tmp->next!=rm)tmp=tmp->next;
    tmp->next=rm->next;
    free(rm);}
    printf("Patient %d is deleted\n",id);
    return;
}
struct patient* add_pat(struct patient **pat,int p_id,int p_age,char *p_name,char *p_gender,char *p_address,char *p_history){
    struct patient *newpat=malloc(sizeof(struct patient));
    struct patient *temp=*pat;
    newpat->p_id=p_id,newpat->p_age=p_age;
    strcpy(newpat->p_name,p_name);
    strcpy(newpat->p_gender,p_gender);
    strcpy(newpat->p_address,p_address);
    strcpy(newpat->p_history,p_history);
    newpat->next=NULL;
    if(*pat==NULL){
        *pat=newpat;
    }
    else{
        while(temp->next!=NULL)
            temp=temp->next;
        temp->next=newpat;
    }
    return *pat;
}
void savepathelp(FILE* fp,struct patient *tmp)
{
    if(tmp!=NULL)
    {
        fprintf(fp,"%d ",tmp->p_id);
        fprintf(fp,"%s ",tmp->p_name);
        fprintf(fp,"%d ",tmp->p_age);
        fprintf(fp,"%s ",tmp->p_gender);
        fprintf(fp,"%s ",tmp->p_address);
        fprintf(fp,"%s\n",tmp->p_history);
        savepathelp(fp,tmp->next);
    }
}
void save_pat(struct patient **pat)
{
    FILE *fp;
    struct patient *tmp=*pat;
    fp=fopen("patdata.txt","w");
    savepathelp(fp,tmp);
    printf("Patient details saved into file\n");
    fclose(fp);
}
void view_pat(struct patient *pat){
    struct patient *temp=pat;
    if(pat==NULL){
        printf("\nPatient linked list is empty\n");
        return;
    }
    else{
        green();
        printf("\n\t\tPATIENT DETAILS\n");
        printf("-----------------------------------------------------------------------------------------------\n");
        printf("| %-7s | %-15s| %-7s| %-10s| %-20s| %-21s|\n","ID","NAME","AGE","GENDER","ADDRESS","HISTORY");
        printf("-----------------------------------------------------------------------------------------------\n");
        blue();
        while(temp!=NULL){
            printf("| %-7d | %-15s| %-7d| %-10s| %-20s| %-21s|\n",temp->p_id,temp->p_name,temp->p_age,temp->p_gender,temp->p_address,temp->p_history);
            temp=temp->next;
        }
        printf("-----------------------------------------------------------------------------------------------\n");
        reset();
    }
}
void viewf_pat(){
    FILE *fp;
    fp=fopen("patdata.txt","r");
    int a,b;
    char a1[30],a2[30],a3[30],a4[30];
	if(fp==NULL)
	{
		printf("\nCAN NOT OPEN FILE");
		exit(0);
	}
    green();
    printf("\n\t\tPATIENT DETAILS IN FILE\n");
    printf("-----------------------------------------------------------------------------------------------\n");
	printf("| %-7s | %-15s| %-7s| %-10s| %-20s| %-22s|\n","ID","NAME","AGE","GENDER","ADDRESS","HISTORY");
    printf("-----------------------------------------------------------------------------------------------\n");
    blue();
    while(fscanf(fp,"%d %s %d %s %s %s\n",&a,a1,&b,a2,a3,a4)!=EOF){
        printf("| %-7d | %-15s| %-7d| %-10s| %-20s| %-22s|\n",a,a1,b,a2,a3,a4);
    }
    printf("-----------------------------------------------------------------------------------------------\n");
    reset();
	fclose(fp);
}
void print_pat(struct patient *temp){
    if(temp!=NULL){
    green();
    printf("\n\t\tPATIENT DETAILS\n");
    printf("-----------------------------------------------------------------------------------------------\n");
    printf("| %-7s | %-15s| %-7s| %-10s| %-20s| %-22s|\n","ID","NAME","AGE","GENDER","ADDRESS","HISTORY");
    printf("-----------------------------------------------------------------------------------------------\n");
    blue();
    printf("| %-7d | %-15s| %-7d| %-10s| %-20s| %-22s|\n",temp->p_id,temp->p_name,temp->p_age,temp->p_gender,temp->p_address,temp->p_history);
    printf("-----------------------------------------------------------------------------------------------\n");
    reset();
    }
}
void sort_pat(struct patient **pat){
    struct patient *current = *pat, *index = NULL;  
    int p_id,p_age;
    char p_name[30],p_gender[10],p_address[300],p_history[300];
    if(*pat== NULL) {  
        return;  
    }  
    else {  
        while(current != NULL) {  
            index = current->next;  
            while(index != NULL) {  
                if(current->p_id > index->p_id){  
                    p_id= current->p_id;  
                    p_age= current->p_age;  
                    strcpy(p_name,current->p_name);
                    strcpy(p_gender,current->p_gender);
                    strcpy(p_address,current->p_address);
                    strcpy(p_history,current->p_history);
                    current->p_id = index->p_id;  
                    current->p_age=index->p_age;
                    strcpy(current->p_name,index->p_name);
                    strcpy(current->p_gender,index->p_gender);
                    strcpy(current->p_address,index->p_address);
                    strcpy(current->p_history,index->p_history);
                    index->p_id=p_id;  
                    index->p_age=p_age;
                    strcpy(index->p_name,p_name);
                    strcpy(index->p_gender,p_gender);
                    strcpy(index->p_address,p_address);
                    strcpy(index->p_history,p_history);
                }  
                index = index->next;  
            }  
            current = current->next;  
        }      
    }      
}
void pat_details(){
    while(1){
    int choice_pat;
    int p_id,p_age;
    char p_name[30],p_gender[10],p_address[300],p_history[300];
    green();
    printf("\n\t-----------------------------------------------\n");
    printf("\t|");
    printf("\t    %-33s ","PATIENT DETAILS");
    printf("|\n");
    printf("\t|---------------------------------------------|\n");
    blue();
    printf("\t|\t  %-35s |\n","1.ADD AN PATIENT");
    printf("\t|\t  %-35s |\n","2.MODIFY PATIENT DETAILS");
    printf("\t|\t  %-35s |\n","3.REMOVE PATIENT");
    printf("\t|\t  %-35s |\n","4.VIEW ALL PATIENT DETAILS");
    printf("\t|\t  %-35s |\n","5.SEARCH PATIENT");
    printf("\t|\t  %-35s |\n","6.SAVE ALL PATIENT DETAILS");
    printf("\t|\t  %-35s |\n","7.VIEW PATIENT DETAILS(FILE)");
    printf("\t|\t  %-35s |\n","8.RETURN");
    printf("\t|---------------------------------------------|\n");
    reset();
    printf("\nEnter your choice:");
    scanf("%d",&choice_pat);
    switch(choice_pat){
        case 1:
        printf("\nEnter patient id:");
        scanf("%d",&p_id);
        struct patient *temp=pat;
        while(temp!=NULL){
            if(temp->p_id==p_id){
                printf("Patient id already exists\n");
                pat_details();
            }
            temp=temp->next;
        }
        printf("Enter patient name:");
        scanf("%s",p_name);
        printf("Enter patient age:");
        scanf("%d",&p_age);
        printf("Enter patient gender:");
        scanf("%s",p_gender);
        fflush(stdin);
        printf("Enter patient address:");
        scanf("%s",p_address);
        fflush(stdin);
        printf("Enter patient history:");
        scanf("%s",p_history);
        add_pat(&pat,p_id,p_age,p_name,p_gender,p_address,p_history);
        break;
        case 2:
        modify_pat(pat);
        break;
        case 3:
        remove_pat(&pat);
        break;
        case 4:
        view_pat(pat);
        break;
        case 5:
        print_pat(search_pat(pat));       
        break;
        case 6:
        sort_pat(&pat);
        save_pat(&pat);
        break;
        case 7:
        viewf_pat();
        break;
        case 8:
        menu();
        break;
        default:
        printf("Invalid choice\n");
        break;
    }}
}
void enter_pat(){
    FILE *fp;
    fp=fopen("patdata.txt","r");
    int a,b;
    char a1[30],a2[30],a3[30],a4[30];
	if(fp==NULL)
	{
		printf("\nCAN NOT OPEN FILE");
		exit(0);
	}
    while(fscanf(fp,"%d %s %d %s %s %s\n",&a,a1,&b,a2,a3,a4)!=EOF){
        add_pat(&pat,a,b,a1,a2,a3,a4);
    }
	fclose(fp);
}
void doctor_details();
void print_doc(struct doctor *temp){
    if(temp!=NULL){
        green();
        printf("\n\tDOCTOR DETAILS\n");
        printf("------------------------------------------------------------------------------------------------------------------------------\n");
        printf("| %-6s | %-13s| %-6s| %-9s| %-7s| %-10s| %-10s| %-11s| %-11s| %-12s| %-7s|\n","ID","NAME","SLOTS","TIME","AGE","GENDER","DEPT","DESIG","DOJ","CONTACT","SALARY");
        printf("------------------------------------------------------------------------------------------------------------------------------\n");
        blue();
        printf("| %-6d | %-13s| %-6d| %-9s| %-7d| %-10s| %-10s| %-11s| %-11s| %-12s| %-7d|\n",temp->d_id,temp->d_name,temp->d_slots,temp->d_time,temp->d_age,temp->d_gender,temp->d_dept,temp->d_desig,temp->d_doj,temp->d_contact,temp->d_salary);
        printf("------------------------------------------------------------------------------------------------------------------------------\n");
        reset();
    }
}
struct doctor* search_doc(struct doctor *doc){
     struct doctor *temp=doc;
    if(temp==NULL){
        printf("\nDoctor doubly linked list empty\n");
        doctor_details();}
        green();
    printf("\t----------------------------");
    printf("\n\t|   SEARCH DOCTOR         |\n");
    printf("\t----------------------------");
    blue();
    printf("\n\t| %-20s   |","1.Search by doctor id");
    printf("\n\t| %-16s |","2.Search by doctor name");
    printf("\n\t| %-16s |","3.Return to doctor menu");
    printf("\n\t| %-22s  |\n","4.Go to appointment");
    printf("\t----------------------------");
    reset();
    int choice;
    printf("\nEnter your choice:");
    scanf("%d",&choice);
    if(choice==1){
        int id;
        printf("\nEnter the id:");
        scanf("%d",&id);
        while(temp!=NULL && temp->d_id!=id){
            temp=temp->next;
        }
        if(temp==NULL){
            printf("\nDoctor details not found\n");
            search_doc(doc);
        }
        else return temp;
    }
    else if(choice==2){
        char name[30];
        printf("\nEnter doctor name:");
        scanf("%s",name);
        int flag=0;
        struct doctor *temp1=NULL;
        while(temp!=NULL){
            if(!strcmp(temp->d_name,name)){
                if(flag==1){
                    printf("\nDoctor name repeated\nUse other ways to search\n\n");
                    search_doc(doc);
                }
                flag=1;
                temp1=temp;
            }
            temp=temp->next;
        }
        if(temp1==NULL){
            printf("\nDoctor details not found\n");
            search_doc(doc);
        }
        else{
            return temp1;
            }
    }
    else if(choice==3){
        doctor_details();
    }
    else if(choice==4){
        appointment();
    }
    else{
        printf("\nEnter a correct choice\n");
        search_doc(doc);
    }
}
struct doctor* add_doc(struct doctor **doc,int d_id,int d_salary,int d_age,int d_slots,char *d_name,char *d_contact,char *d_gender,char *d_desig,char *d_dept,char *d_doj,char *d_time){
    struct doctor *newdoc=malloc(sizeof(struct doctor));
    struct doctor *temp=*doc;
    newdoc->d_id=d_id,newdoc->d_salary=d_salary,newdoc->d_age=d_age,newdoc->d_slots=d_slots;
    fflush(stdin);
    strcpy(newdoc->d_name,d_name);
    fflush(stdin);
    strcpy(newdoc->d_contact,d_contact);
    fflush(stdin);
    strcpy(newdoc->d_gender,d_gender);
    strcpy(newdoc->d_desig,d_desig);
    strcpy(newdoc->d_dept,d_dept);
    strcpy(newdoc->d_doj,d_doj);
    strcpy(newdoc->d_time,d_time);
    newdoc->next=NULL;
    if((*doc)==NULL){
        newdoc->prev=NULL;
        (*doc)=newdoc;
    }
    else{
        while(temp->next!=NULL)
            temp=temp->next;
        temp->next=newdoc;
        newdoc->prev=temp;
    }
    return (*doc);
}
void view_doc(struct doctor *doc){
    struct doctor *temp=doc;
    if(doc==NULL){
        printf("\nDoctor doubly linked list is empty\n");
        return;
    }
    else{
        green();
        printf("\n\tDOCTOR DETAILS\n");
        printf("------------------------------------------------------------------------------------------------------------------------------\n");
        printf("| %-6s | %-13s| %-6s| %-9s| %-7s| %-10s| %-10s| %-11s| %-11s| %-12s| %-7s|\n","ID","NAME","SLOTS","TIME","AGE","GENDER","DEPT","DESIG","DOJ","CONTACT","SALARY");
        printf("------------------------------------------------------------------------------------------------------------------------------\n");
        blue();
        while(temp!=NULL){
            printf("| %-6d | %-13s| %-6d| %-9s| %-7d| %-10s| %-10s| %-11s| %-11s| %-12s| %-7d|\n",temp->d_id,temp->d_name,temp->d_slots,temp->d_time,temp->d_age,temp->d_gender,temp->d_dept,temp->d_desig,temp->d_doj,temp->d_contact,temp->d_salary);
            temp=temp->next;
        }
        printf("------------------------------------------------------------------------------------------------------------------------------\n");
        reset();
    }
}
void modify_doc(struct doctor *doc){
    struct doctor *rm=search_doc(doc);
    while(1){
    printf("\nChoose the details you want to change\n1.Name\n2.Age\n3.Salary\n4.Contact\n5.Department\n6.Designation\n");
    printf("7.Time\n8.Slots\n9.All\n10.Return\n");
    int choice;
    printf("Enter your choice:");
    scanf("%d",&choice);
    switch(choice){
        case 1:
        printf("Old Name:%s\n",rm->d_name);
        printf("New name:");
        scanf("%s",rm->d_name);
        break;
        case 2:
        printf("Old Age:%d\n",rm->d_age);
        printf("New age:");
        scanf("%d",&rm->d_age);
        break;
        case 3:
        printf("Old Salary:%d\n",rm->d_salary);
        printf("New Salary:");
        scanf("%d",&rm->d_salary);
        break;
        case 4:
        printf("Old contact:%s\n",rm->d_contact);
        printf("New contact:");
        scanf("%s",rm->d_contact);
        break;
        case 5:
        printf("Old Department:%s\n",rm->d_dept);
        printf("New department:");
        scanf("%s",rm->d_dept);
        break;
        case 6:
        printf("Old Designation:%s\n",rm->d_desig);
        printf("New designation:");
        scanf("%s",rm->d_desig);
        break;
        case 7:
        printf("Old Timings:%s\n",rm->d_time);
        printf("New timings:");
        scanf("%s",rm->d_time);
        break;
        case 8:
        printf("Old Slots:%d\n",rm->d_slots);
        printf("New Slots:");
        scanf("%d",&rm->d_slots);
        break;
        case 9:
        printf("Old Name:%s\n",rm->d_name);
        printf("New name:");
        scanf("%s",rm->d_name);
        printf("\nOld Age:%d\n",rm->d_age);
        printf("New age:");
        scanf("%d",&rm->d_age);
        printf("\nOld Salary:%d\n",rm->d_salary);
        printf("New Salary:");
        scanf("%d",&rm->d_salary);
        printf("\nOld contact:%s\n",rm->d_contact);
        printf("New contact:");
        scanf("%s",rm->d_contact);
        printf("\nOld Department:%s\n",rm->d_dept);
        printf("New department:");
        scanf("%s",rm->d_dept);
        printf("\nOld Designation:%s\n",rm->d_desig);
        printf("New designation:");
        scanf("%s",rm->d_desig);
        printf("\nOld Timings:%s\n",rm->d_time);
        printf("New timings:");
        scanf("%s",rm->d_time);
        printf("Old Slots:%d\n",rm->d_slots);
        printf("New Slots:");
        scanf("%d",&rm->d_slots);
        break;
        case 10:
        doctor_details();
        break;
    }}
}
void remove_doc(struct doctor **doc){
    struct doctor *rm=search_doc(*doc);
    int id=rm->d_id;
    if (*doc == NULL || rm == NULL)
        return;
    if (*doc == rm)
        *doc = rm->next;
    if (rm->next != NULL)
        rm->next->prev = rm->prev;
    if (rm->prev != NULL)
        rm->prev->next = rm->next;
    free(rm);
    return;
}
void sort_doc(struct doctor **doc){
    struct doctor *current = *doc, *index = NULL;  
    int d_id,d_salary,d_age,d_slots;
    char d_name[30],d_contact[100],d_gender[20],d_desig[30],d_dept[30],d_doj[30],d_time[10];
    if(*doc== NULL) {  
        return;  
    }  
    else {  
        while(current != NULL) {  
            index = current->next;  
            while(index != NULL) {  
                if(current->d_id > index->d_id){  
                    d_id= current->d_id;  
                    d_salary=current->d_salary;
                    d_age= current->d_age;  
                    d_slots=current->d_slots;
                    strcpy(d_name,current->d_name);
                    strcpy(d_gender,current->d_gender);
                    strcpy(d_contact,current->d_contact);
                    strcpy(d_desig,current->d_desig);
                    strcpy(d_dept,current->d_dept);
                    strcpy(d_doj,current->d_doj);
                    strcpy(d_time,current->d_time);
                    current->d_id = index->d_id;  
                    current->d_age=index->d_age;
                    current->d_salary=index->d_salary;
                    current->d_slots=index->d_slots;
                    strcpy(current->d_name,index->d_name);
                    strcpy(current->d_gender,index->d_gender);
                    strcpy(current->d_contact,index->d_contact);
                    strcpy(current->d_desig,index->d_desig);
                    strcpy(current->d_dept,index->d_dept);
                    strcpy(current->d_doj,index->d_doj);
                    strcpy(current->d_time,index->d_time);
                    index->d_id=d_id;  
                    index->d_salary=d_salary;
                    index->d_age=d_age;
                    index->d_slots=d_slots;
                    strcpy(index->d_name,d_name);
                    strcpy(index->d_gender,d_gender);
                    strcpy(index->d_contact,d_contact);
                    strcpy(index->d_desig,d_desig);
                    strcpy(index->d_dept,d_dept);
                    strcpy(index->d_doj,d_doj);
                    strcpy(index->d_time,d_time);
                }  
                index = index->next;  
            }  
            current = current->next;  
        }      
    }      
}
void savedochelp(FILE* fp,struct doctor *tmp)
{
    if(tmp!=NULL)
    {
        fprintf(fp,"%d %s %d %s %d %s ",tmp->d_id,tmp->d_name,tmp->d_slots,tmp->d_time,tmp->d_age,tmp->d_gender);
        fprintf(fp,"%s %s %s %s %d \n",tmp->d_dept,tmp->d_desig,tmp->d_doj,tmp->d_contact,tmp->d_salary);
        savedochelp(fp,tmp->next);
    }
}
void save_doc(struct doctor **doc)
{
    FILE *fp;
    struct doctor *tmp=*doc;
    fp=fopen("docdata.txt","w");
    savedochelp(fp, tmp);
    printf("Doctor details saved into file\n");
    fclose(fp);
}
void viewf_doc(){
    FILE *fp;
    fp=fopen("docdata.txt","r");
    if(fp==NULL)
	{
		printf("\nCAN NOT OPEN FILE");
		exit(0);
	}
	int d_id,d_salary,d_age,d_slots;
    char d_name[30],d_contact[100],d_gender[20],d_desig[30],d_dept[30],d_doj[30],d_time[10];
    green();
    printf("\n\tDOCTOR DETAILS IN FILE\n");
    printf("------------------------------------------------------------------------------------------------------------------------------\n");
	printf("| %-6s | %-13s| %-6s| %-9s| %-7s| %-10s| %-10s| %-11s| %-11s| %-12s| %-7s|\n","ID","NAME","SLOTS","TIME","AGE","GENDER","DEPT","DESIG","DOJ","CONTACT","SALARY");
    printf("------------------------------------------------------------------------------------------------------------------------------\n");
    blue();
    while(fscanf(fp,"%d %s %d %s %d %s %s %s %s %s %d\n",&d_id,d_name,&d_slots,d_time,&d_age,d_gender,d_dept,d_desig,d_doj,d_contact,&d_salary)!=EOF){
        printf("| %-6d | %-13s| %-6d| %-9s| %-7d| %-10s| %-10s| %-11s| %-11s| %-12s| %-7d|\n",d_id,d_name,d_slots,d_time,d_age,d_gender,d_dept,d_desig,d_doj,d_contact,d_salary);
    }
    printf("------------------------------------------------------------------------------------------------------------------------------\n");
    reset();
	fclose(fp);
}
void doctor_details(){
    while(1){
    int choice_doc;
    int d_id,d_salary,d_age,d_slots;
    char d_name[130],d_contact[100],d_gender[20],d_desig[30],d_dept[30],d_doj[30],d_time[10];
    green();
    printf("\n\t-----------------------------------------------\n");
    printf("\t|");
    printf("\t    %-33s ","DOCTOR DETAILS");
    printf("|\n");
    printf("\t|---------------------------------------------|\n");
    blue();
    printf("\t|\t  %-35s |\n","1.ADD AN DOCTOR");
    printf("\t|\t  %-35s |\n","2.MODIFY DOTOR DETAILS");
    printf("\t|\t  %-35s |\n","3.REMOVE DOCTOR");
    printf("\t|\t  %-35s |\n","4.VIEW ALL DOCTOR DETAILS");
    printf("\t|\t  %-35s |\n","5.SEARCH A DOCTOR");
    printf("\t|\t  %-35s |\n","6.SAVE ALL DOCTOR DETAILS");
    printf("\t|\t  %-35s |\n","7.VIEW DOCTOR DETAILS(FILE)");
    printf("\t|\t  %-35s |\n","8.RETURN");
    printf("\t|---------------------------------------------|\n");
    reset();
    printf("\nEnter your choice:");
    scanf("%d",&choice_doc);
    switch(choice_doc){
        case 1:
        printf("\nEnter doctor id:");
        scanf("%d",&d_id);
        struct doctor *temp=doc;
        while(temp!=NULL){
            if(temp->d_id==d_id){
                printf("Doctor id already exists\n");
                doctor_details();
            }
            temp=temp->next;
        }
        fflush(stdin);
        printf("Enter doctor name:");
        scanf("%s",d_name);
        printf("Enter doctor slots:");
        scanf("%d",&d_slots);
        printf("Enter doctor time:");
        scanf("%s",d_time);
        printf("Enter doctor age:");
        scanf("%d",&d_age);
        fflush(stdin);
        printf("Enter doctor gender:");
        scanf("%s",d_gender);
        printf("Enter doctor department:");
        scanf("%s",d_dept);
        printf("Enter doctor designation:");
        scanf("%s",d_desig);
        printf("Enter doctor date of joining:");
        scanf("%s",d_doj);
        fflush(stdin);
        printf("Enter doctor contact:");
        scanf("%s",d_contact);
        printf("Enter doctor salary:");
        scanf("%d",&d_salary);
        add_doc(&doc,d_id,d_salary,d_age,d_slots,d_name,d_contact,d_gender,d_desig,d_dept,d_doj,d_time);
        break;
        case 2:
        modify_doc(doc);
        break;
        case 3:
        remove_doc(&doc);
        break;
        case 4:
        view_doc(doc);
        break;
        case 5:
        search_doc(doc);
        print_doc(doc);
        break;
        case 6:
        sort_doc(&doc);
        save_doc(&doc);
        break;
        case 7:
        viewf_doc();
        break;
        case 8:
        menu();
        break;
        default:
        printf("\nEnter a valid choice\n");
        break;
    }}
}
void enter_doc(){
     FILE *fp;
    fp=fopen("docdata.txt","r");
    if(fp==NULL)
	{
		printf("\nCAN NOT OPEN FILE");
		exit(0);
	}
	int d_id,d_salary,d_age,d_slots;
    char d_name[30],d_contact[100],d_gender[20],d_desig[30],d_dept[30],d_doj[30],d_time[10];
    while(fscanf(fp,"%d %s %d %s %d %s %s %s %s %s %d\n",&d_id,d_name,&d_slots,d_time,&d_age,d_gender,d_dept,d_desig,d_doj,d_contact,&d_salary)!=EOF){
        add_doc(&doc,d_id,d_salary,d_age,d_slots,d_name,d_contact,d_gender,d_desig,d_dept,d_doj,d_time);
    }
	fclose(fp);
}
void add_queue(int a_id,int t_no,int qp_id,int qd_id,char *qd_name,char *qp_name,char *time){
    struct queue *ptr=malloc(sizeof(struct queue));
    ptr->t_no=t_no,ptr->qp_id=qp_id,ptr->qd_id=qd_id,ptr->a_id=a_id;
    strcpy(ptr->qp_name,qp_name);
    strcpy(ptr->qd_name,qd_name);
    strcpy(ptr->time,time);
    if(front == NULL)  {  
        front=ptr;  
        rear=ptr;   
        front->next=NULL;  
        rear->next=NULL;  
    }  
    else   {  
        rear->next=ptr;  
        rear=ptr;  
        rear->next=NULL;  
    }  
}
void dequeue(){  
    struct queue *ptr;  
    if(front == NULL){  
        printf("\nEmpty queue\n");  
        return;  
    }  
    else{  
        ptr = front;  
        front = front -> next;  
        printf("\nAppointment dequed\n");
        free(ptr);  
    }  
}  
void view_queue(){  
    struct queue *ptr=front;        
    if(front == NULL){  
        printf("\nEmpty queue\n");  
    }  
    else{   
        green();
        printf("\n\tAPPOINTMENT DETAILS\n");
        printf("--------------------------------------------------------------------------------------------------\n");
        printf("| %-9s | %-9s| %-9s| %-15s| %-10s| %-15s| %-15s|\n","A_ID","T_NO","P_ID","P_NAME","D_ID","D_NAME","D_TIME");
        printf("--------------------------------------------------------------------------------------------------\n");
        blue();
        while(ptr != NULL)   
        {  
            printf("| %-9d | %-9d| %-9d| %-15s| %-10d| %-15s| %-15s|\n",ptr->a_id,ptr->t_no,ptr->qp_id,ptr->qp_name,ptr->qd_id,ptr->qd_name,ptr->time);
            ptr=ptr->next;  
        }  
        printf("--------------------------------------------------------------------------------------------------\n");
        reset();
    }  
}  
void book_appointment(){
    printf("\nSelect the doctor\n");
    struct doctor *tmp=search_doc(doc);
    if(tmp->d_slots>0){
        int id=tmp->d_slots-1,a1=0;
        tmp->d_slots=id;
        printf("\nSelect the patient\n");
        struct patient *temp1=search_pat(pat);
        struct queue *ptr=front;
        while(ptr!=NULL){
            if(ptr->qd_id==tmp->d_id && ptr->qp_id==temp1->p_id)a1=1;
            ptr=ptr->next;
        }
        if(a1==0){
        int t_no,a_id,flag=0;
        if(rear==NULL)a_id=100000;
        else a_id=(rear->a_id)+1;
        ptr=front;
        while(ptr!=NULL){
            if(ptr->qd_id==tmp->d_id){
                t_no=ptr->t_no;
                flag=1;
            }
            ptr=ptr->next;
        }
        if(flag==0)t_no=0;
        add_queue(a_id,t_no+1,temp1->p_id,tmp->d_id,tmp->d_name,temp1->p_name,tmp->d_time);
        print_bill(a_id,temp1->p_id,tmp->d_id,t_no,temp1->p_name,tmp->d_name,tmp->d_time);
        }
        else{
            printf("\nPatient already booked the appointment with the doctor\n");
        }
    }
    else
        printf("Sorry no slots available\n");
}
void search_queue(){
    struct queue *ptr=front;
    if(ptr==NULL){
        printf("\nQueue is empty\n");
        appointment();
    }
    printf("\n1.Search by appointment id\n2.Search by doctor id\n3.Search by patient id\n4.Return\n");
    int choice;
    printf("\nEnter your choice:");
    scanf("%d",&choice);
    if(choice==1){
        int id,flag=0;
        printf("\nEnter the id:");
        scanf("%d",&id);
        green();
        printf("\n\tAPPOINTMENT DETAILS\n");
        printf("--------------------------------------------------------------------------------------------------\n");
        printf("| %-9s | %-9s| %-9s| %-15s| %-10s| %-15s| %-15s|\n","A_ID","T_NO","P_ID","P_NAME","D_ID","D_NAME","D_TIME");
        printf("--------------------------------------------------------------------------------------------------\n");
        blue();
        while(ptr!=NULL){
            if(ptr->a_id==id){
                printf("| %-9d | %-9d| %-9d| %-15s| %-10d| %-15s| %-15s|\n",ptr->a_id,ptr->t_no,ptr->qp_id,ptr->qp_name,ptr->qd_id,ptr->qd_name,ptr->time);
                flag=1;
            }
            ptr=ptr->next;
        }
        printf("--------------------------------------------------------------------------------------------------\n");
        reset();
        if(flag==0){
            printf("\nAppointment details not found\n\n");
            search_queue();
        }
    }
    else if(choice==2){
        int id,flag=0;
        printf("\nEnter the id:");
        scanf("%d",&id);
        green();
        printf("\n\tAPPOINTMENT DETAILS\n");
        printf("--------------------------------------------------------------------------------------------------\n");
        printf("| %-9s | %-9s| %-9s| %-15s| %-10s| %-15s| %-15s|\n","A_ID","T_NO","P_ID","P_NAME","D_ID","D_NAME","D_TIME");
        printf("--------------------------------------------------------------------------------------------------\n");
        blue();
        while(ptr!=NULL){
            if(ptr->qd_id==id){
                printf("| %-9d | %-9d| %-9d| %-15s| %-10d| %-15s| %-15s|\n",ptr->a_id,ptr->t_no,ptr->qp_id,ptr->qp_name,ptr->qd_id,ptr->qd_name,ptr->time);
                flag=1;
            }
            ptr=ptr->next;
        }
        printf("--------------------------------------------------------------------------------------------------\n");
        reset();
        if(flag==0){
            printf("\nAppointment details not found\n\n");
            search_queue();
        }
    }
    else if(choice==3){
        int id,flag=0;
        printf("\nEnter the id:");
        scanf("%d",&id);
        green();
        printf("\n\tAPPOINTMENT DETAILS\n");
        printf("--------------------------------------------------------------------------------------------------\n");
        printf("| %-9s | %-9s| %-9s| %-15s| %-10s| %-15s| %-15s|\n","A_ID","T_NO","P_ID","P_NAME","D_ID","D_NAME","D_TIME");
        printf("--------------------------------------------------------------------------------------------------\n");
        blue();
        while(ptr!=NULL){
            if(ptr->qp_id==id){
                printf("| %-9d | %-9d| %-9d| %-15s| %-10d| %-15s| %-15s|\n",ptr->a_id,ptr->t_no,ptr->qp_id,ptr->qp_name,ptr->qd_id,ptr->qd_name,ptr->time);
                flag=1;
            }
            ptr=ptr->next;
        }
        printf("--------------------------------------------------------------------------------------------------\n");
        reset();
        if(flag==0){
            printf("\nAppointment details not found\n\n");
            search_queue();
        }
    }
    else if(choice==4){
        appointment();
    }
    else{
        printf("Enter a correct choice\n");
        search_queue();
    }
}
void saveappthelp(FILE* fp,struct queue *tmp){
    if(tmp!=NULL){
        fprintf(fp,"%d %d %d %s %d %s %s\n",tmp->a_id,tmp->t_no,tmp->qp_id,tmp->qp_name,tmp->qd_id,tmp->qd_name,tmp->time);
        saveappthelp(fp,tmp->next);
    }
}
void save_appt(){
    FILE *fp;
    struct queue *tmp=front;
    fp=fopen("appointment.txt","w");
    saveappthelp(fp, tmp);
    printf("Appointment details saved into file\n");
    fclose(fp);
}
void viewf_appt(){
    FILE *fp;
    fp=fopen("appointment.txt","r");
    if(fp==NULL)
	{
		printf("\nCAN NOT OPEN FILE");
		exit(0);
	}
    int t_no,qp_id,qd_id,a_id;
    char qd_name[30],qp_name[30],time[30];
    green();
    printf("\n\tAPPOINTMENT DETAILS IN FILE\n");
    printf("--------------------------------------------------------------------------------------------------\n");
	printf("| %-9s | %-9s| %-9s| %-15s| %-10s| %-15s| %-15s|\n","A_ID","T_NO","P_ID","P_NAME","D_ID","D_NAME","D_TIME");
    printf("--------------------------------------------------------------------------------------------------\n");
    blue();
    while(fscanf(fp,"%d %d %d %s %d %s %s\n",&a_id,&t_no,&qp_id,qp_name,&qd_id,qd_name,time)!=EOF){
        printf("| %-9d | %-9d| %-9d| %-15s| %-10d| %-15s| %-15s|\n",a_id,t_no,qp_id,qp_name,qd_id,qd_name,time);
    }
    printf("--------------------------------------------------------------------------------------------------\n");
    reset();
    fclose(fp);
}
void delete_appt(){
    int id;
    printf("Enter the appointment id:");
    scanf("%d",&id);
    struct queue *ptr=front,*prev;
    if(ptr==NULL){
        printf("\nEmpty queue\n");
        return;
    }
    if (ptr!= NULL && ptr->a_id == id){
        front = ptr->next;
        free(ptr);
        printf("Appointment %d is deleted",id); 
        return;
    }
    while(ptr!=NULL && ptr->a_id!=id){
        prev=ptr;
        ptr=ptr->next;
    }
    if(ptr==NULL){
        printf("\nAppointment not found\n");
    }
    else{
        prev->next=ptr->next;
        free(ptr);
        printf("Appointment %d is deleted",id); 
    }
}
void appointment(){
    int choice;
    while(1){
        green();
        printf("\n\t-----------------------------------------------\n");
        printf("\t|");
        printf("\t    %-33s ","APPOINTMENT");
        printf("|\n");
        printf("\t|---------------------------------------------|\n");
        blue();
        printf("\t|\t  %-35s |\n","1.BOOK APPOINTMENT");
        printf("\t|\t  %-35s |\n","2.DEQUEUE APPOINTMENT");
        printf("\t|\t  %-35s |\n","3.DELETE APPOINTMENT");
        printf("\t|\t  %-35s |\n","4.VIEW APPOINTMENT");
        printf("\t|\t  %-35s |\n","5.SEARCH AN APPOINTMENT");
        printf("\t|\t  %-35s |\n","6.SAVE APPOINTMENT");
        printf("\t|\t  %-35s |\n","7.VIEW APPOINTMENT(FILE)");
        printf("\t|\t  %-35s |\n","8.RETURN");
        printf("\t|---------------------------------------------|\n");
        reset();
        printf("\nEnter your choice:");
        scanf("%d",&choice);
        switch(choice){
            case 1:
            book_appointment();
            break;
            case 2:
            dequeue();  
            break;
            case 3:
            delete_appt();
            break;
            case 4:
            view_queue();
            break;
            case 5:
            search_queue();
            break;
            case 6:
            save_appt();
            break;
            case 7:
            viewf_appt();
            break;
            case 8:
            menu();
            break;
            default:
            printf("\nEnter a valid choice\n");
            appointment();
            break;
    }}
}
void enter_appt(){
    FILE *fp=fopen("appointment.txt","r");
    if(fp==NULL)
	{
		printf("\nCAN NOT OPEN FILE");
		exit(0);
	}
    int a_id,t_no,qp_id,qd_id;
    char qd_name[30],qp_name[30],time[30];
    while(fscanf(fp,"%d %d %d %s %d %s %s\n",&a_id,&t_no,&qp_id,qp_name,&qd_id,qd_name,time)!=EOF){
        add_queue(a_id,t_no,qp_id,qd_id,qd_name,qp_name,time);
    }
    fclose(fp);
}
void menu(){
    while(1){
    int choice;
    if(pat==NULL){
        enter_pat();
    }
    if(doc==NULL){
        enter_doc();
    }
    if(front==NULL){
        enter_appt();
    }
    green();
    printf("\n\t***********************************************\n");
    printf("\t*    %-40s *\n","WELCOME TO HOSPITAL MANAGEMENT SYSTEM");
    printf("\t*---------------------------------------------*\n"); 
    printf("\t*\t    %-33s *","1.PATIENT DETAILS");
    printf("\n\t*\t    %-33s *","2.DOCTOR DETAILS");
    printf("\n\t*\t    %-33s *","3.APPOINTMENT");
    printf("\n\t*\t   %-34s *\n","-1.EXIT");
    printf("\t***********************************************\n");
    reset();
    printf("\nEnter your choice:");
    scanf("%d",&choice);
    switch(choice){
        case 1:
        pat_details();
        break;
        case 2:
        doctor_details();
        break;
        case 3:
        appointment();
        break;
        case -1:
        exit(1);
        break;
        default:
        printf("Invalid choice\n");
        break;
    }}
}
void main(){
    menu();
}
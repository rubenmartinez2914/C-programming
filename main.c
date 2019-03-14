#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node{
    struct node *prev;
    int item;
    char name[150];
    int quantity;
    struct node *next;
};

struct node * node_creation(int, char*, int);
struct node * add_list(struct node * head,int item, char *name, int quantity);
void print_list(struct node *);
int length(struct node *head);
void sort(struct node *head);
void printliststofile(struct node * head, char * outputfile);


int main(void){
    
    struct node *head;
    FILE *file;
    
    char l[150];
    char del[4]=",";
    int temp_item;
    char temp_name[100];
    int temp_quantity;
    
    
    file=fopen("items.txt", "r");
    
    if (file==NULL) {
        printf("Unable to open File\n");
    }
    
    fgets(l, sizeof(l), file);
    temp_item=atoi(strtok(l,del));
    strcpy(temp_name, strtok(NULL, del));
    temp_quantity=atoi(strtok(NULL, del));
    head = node_creation(temp_item,temp_name,temp_quantity);
    
    while (fgets(l, sizeof(l), file)) {
        temp_item=atoi(strtok(l,del));
        strcpy(temp_name, strtok(NULL, del));
        temp_quantity=atoi(strtok(NULL, del));
        head = add_list(head,temp_item,temp_name,temp_quantity);
        
        
    }
    sort(head);
    print_list(head);
    
    printliststofile(head, "output.txt");
    
}

struct node * node_creation(int item, char *name, int quantity){
    struct node * temp;
    temp = malloc(sizeof(struct node));
    temp -> item = item;
    strcpy(temp->name, name);
    temp->quantity=quantity;
   
    while (temp->next) {
        temp->next->prev=temp;
        temp=temp->next;
        
        
    }

    
    return temp;
     
}


struct node * add_list(struct node * head,int item, char *name, int quantity){
    
    struct node * t = NULL;
    
    int found=0;
    struct node *current=head;
    
    while(current != NULL)
    {
        if (item==current->item) {
            current->quantity=current->quantity+quantity;
            found=1;
            t=head;
        }
        current= current->next;
        
    }
    if(found!=1){
        
        t=node_creation(item, name, quantity);
        t->next = head;
    }
    
    
    return t;
    
}

int length(struct node *head) {
    int length = 0;
    struct node *current;
    
    for(current = head; current != NULL; current = current->next) {
        length++;
    }
    
    return length;
}


void sort(struct node *head){
    int i, j, tempitem, tempquantity;
    char tempname[150];
    struct node *current;
    struct node *next;
    int size = length(head);
    for ( i = 0 ; i < size - 1 ; i++ ) {
        current = head;
        next = head->next;
        for ( j = 1 ; j < size ; j++ ) {
            
            if ( current->item > next->item ) {
                tempitem = current->item;
                tempquantity=current->quantity;
                strcpy(tempname, current->name);
                
                current->item = next->item;
                current->quantity=next->quantity;
                strcpy(current->name,next->name);
                
                next->item = tempitem;
                next->quantity=tempquantity;
                strcpy(next->name, tempname);
            }
            current = current->next;
            next = next->next;
        }
    }
}


void print_list(struct node * head){
    
    struct node * t = head;
    
    while(t !=NULL){
        printf("%d; %s; %d;\n",t->item, t->name, t->quantity);
        t = t->next;
    }
    
}

void printliststofile(struct node * head, char * outputfile){
    
    FILE *file2;
    file2=fopen(outputfile, "w");
    if (file2==NULL) {
        printf("Unable to open File\n");
    }
    struct node * t = head;
    
    while(t !=NULL){
        fprintf(file2, "%d; %s; %d\n",t->item,t->name,t->quantity);
        t = t->next;
    }
    fclose(file2);
}


    





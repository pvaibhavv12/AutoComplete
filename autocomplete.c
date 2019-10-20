#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define A 26

typedef struct listnode{
    char data;
    struct listnode *next;
}listnode;

typedef struct list{
    listnode * head;
}list;

void insert(list *list,char data)
{
    listnode *temp = (listnode*)malloc(sizeof(listnode));
    temp->data = data;
    temp->next = list->head;
    list->head = temp; 
}

void del(list*list)
{
    if(list->head == NULL)
        return;
    listnode*temp = list->head;
    list->head = list->head->next;
    free(temp);
}

void printlist(listnode*node)
{
    if(node == NULL )
        return;
    printlist(node->next);
    printf("%c",node->data);
}   

list* create()
{
    list* temp = (list*)malloc(sizeof(list));
    temp->head = NULL;
    return temp;
}

typedef struct node{
    
    struct node* alpha[A];
    int last;

}node;

node* createnode()
{
    node* temp = (node*)malloc(sizeof(node));
    
    for(int i = 0; i < A ; i++)
            temp->alpha[i] = NULL;
    
    temp->last = 0;

    return temp;
}

void createtree(node *root ,char *s)
{
    int i = 0,index;
    node* temp = root;
    while(s[i] != '\0')
    {
        index = s[i] - 'a';
        if(temp->alpha[index] == NULL)
        {
            temp->alpha[index] = createnode();
        }

        temp = temp->alpha[index];
        i++;
    }

    temp->last = 1;

}

void print(node* root,char *s,int i,list* list)
{   
    node *temp = root;
    if(i)
    {   
        int j = 0 , index ;
        while(s[j] != '\0')
        {
            index = s[j] - 'a';
            insert(list,s[j]);
            if(temp->alpha[index] == NULL)
            {
                    printf("NO ELEMENT FOUND");
                    return;
            }
            temp = temp->alpha[index];
            j++;
        }
    }
    
    if(temp!=NULL && temp->last == 1)
    {
        
        printlist(list->head);
        printf("\n");
    }
    
    for(int j = 0; j < A ;j++)
    {
        if(temp->alpha[j] != NULL)
        {
            insert(list,(char)(j + 'a'));
            print(temp->alpha[j],s,0,list);
        }
    }
    del(list);

    
}

int main()
{   
    clock_t start,end;

    start = clock();
    
    node *root = (node*)malloc(sizeof(node));
    list * list = create();
    
    FILE *fp;
    char str[50];
    char* filename = "autocomplete.txt";
 
    fp = fopen(filename, "r");
    
    char find[50];

    while(fscanf(fp,"%[^\n]\n",str) != EOF)
	{
		createtree(root,str);
	}

    printf("Enter some starting char of word :");
    scanf("%s",str);
    print(root,str,1,list);    

    end  = clock();

    printf("%f\n",(double)(end - start )/CLOCKS_PER_SEC);
      
    
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    char data[30];
    struct Node *left,*right;

} Node;

Node *newNode(char data[30])
{
    Node *n = malloc(sizeof(Node));
    strcpy(n->data, data);
    n->left =NULL;
    n->right = NULL;
    return n;

}
Node *insert(Node *root, char data[30])
{

    if(root == NULL)
        return newNode(data);
    else if ((strcasecmp(data,root->data))<0)
        root->left = insert(root->left, data);
    else
        root->right = insert(root->right, data);
    return root;


}
char p1[30];
char p2[30];
Node *search(Node *root, char data[30])
{
    if(root == NULL)
    {
        printf("%s - Incorrect , Suggestions :%s , %s \n",data,p1,p2);
        return NULL;
    }
    else if(strcasecmp(data, root->data) == 0)
    {

        printf("%s - correct\n",data);
        return root;
    }

    else if(root->left == NULL && root->right == NULL )
    {
        printf("%s - Incorrect , Suggestions :%s , %s , %s\n",data,root->data,p1,p2);
        return ;
    }
    else if ((strcasecmp(data,root->data))<0)
    {
        strcpy(p1,root->data);
        return search(root->left, data);
    }

    else if ((strcasecmp(data,root->data))>0)
    {
        strcpy(p2,root->data);
        return search(root->right, data);
    }



}

Node * LoadDictionadry(char filename[], Node *root)
{
    FILE *f = fopen(filename,"r");
    int i=0;
    char c[30];
    char n;
    fscanf(f, "%s", c);

    if(f==NULL)
    {
        printf("file not found !\n");
        exit(1);
    }

    while((n = fgetc(f)) != EOF)
    {
        i++;

        root = insert(root, c);

        fscanf(f, "%s", c);




    }
    printf("Dictionary loaded successfully !\n");
    printf(".....................................\n");
    printf("size = %d \n",i);
    printf(".....................................\n");

    fclose(f);
    return root;

}

int max (int x, int y)
{
    if(x>y)
        return x;
    else
        return y;

}
int height (Node *root)
{
    if(root ==NULL)
        return -1;
    else
        return 1+ max(height(root->left),height(root->right));
}
int main()
{
    Node *root = NULL;
    root = LoadDictionadry("EN-US-Dictionary.txt", root);
    printf("Height = %d \n",height(root));
    printf(".....................................\n");
    printf("Enter sentence : \n");
    char line[260];
    char *token;

    scanf("%[^\n]s",line);

    token=strtok(line," ");
    while(token!='\0')
    {
        search(root, token);

        token=  strtok(NULL," ");


    }


    return 0;
}

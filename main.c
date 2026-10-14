#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//struct of Linked List.
typedef struct Equation*pos;
typedef pos Equation_List;
struct Equation
{
    char infix[200];
    char postfix[200];
    int isValid;
    int result;
    char errorMassege[200];
    pos next;
} ;
Equation_List equation=NULL;//global Linked List.
int numberOfEquation=0;//global counter.
int validated=0, converted=0, evaluated=0;
//struct of stack.
typedef struct node*ptr;
typedef ptr stack;
struct node
{
    char element;
    ptr next;
};
//struct of Tree.
typedef struct node1*ptr1;
typedef ptr1 stack1;
struct node1
{
    int element;
    ptr1 next;
};
typedef struct tree_node*tree_ptr;
struct tree_node
{
    char element[20];
    tree_ptr left;
    tree_ptr right;
};
typedef tree_ptr BST;
typedef struct tree_stack_node*treePtr;
struct tree_stack_node
{
    tree_ptr data;
    treePtr next;
};

//Prototypes
void showMenu();
void createList();
int IsEmptyList();
void insertEquation(char *);
pos getEquation(int );
void freeEquations();
void readData();
void push (stack,char);
char pop (stack);
char top(stack);
int leftBracket(char);
int rightBracket(char);
int balanced(char[],char []);
void validity();
void convert();
void evaluate();
void printInvalid();
void printExpression ();
void writeData();




//Main
int main()
{
    int choice=0;
    createList();


    while(1)
    {
        showMenu();
        if (scanf("%d",&choice)!=1) {
            if (feof(stdin)) break;
            printf("Invalid input. Enter a number.\n");
            int c; while ((c=getchar())!='\n' && c!=EOF) {}
            continue;
        }
        switch(choice)
        {
        case 1:
            readData();
            break;
        case 2:
            validity();
            break;
        case 3:
             if (!validated) { printf("Verify equations first.\n"); break; }
             convert();
            break;
        case 4:
             evaluate();
            break;
        case 5:
            printInvalid();
            break;
        case 6:
             printExpression ();
            break;
        case 7:
             writeData();
            break;
        case 8:
            printf("Thank you...\n");
            printf("Exiting...\n");
            freeEquations();
            return 0;
        default:
            printf("Invalid choice, try again.\n\n");

        }
    }

    freeEquations();
    return 0;
}
//Create Linked List.
void createList()

{
    equation=(Equation_List)malloc(sizeof(struct Equation));

    equation->next=NULL;
}
//Empty Linked List.
int IsEmptyList()

{
    return equation->next==NULL;
}
//Insert Node In Linked List.
void insertEquation(char *infix)

{
    pos temp=(pos)malloc(sizeof(struct Equation));
    strcpy(temp->infix,infix);
    temp->postfix[0]='\0';
    temp->result          = 0;
    temp->isValid         = 0;
    temp->errorMassege[0] = '\0';
    temp->next            = NULL;
    pos temp1;
    for(temp1=equation;temp1->next!=NULL;temp1=temp1->next)
        ;
    temp1->next=temp;
    numberOfEquation++;

}
//Search In Linked List.
pos getEquation(int n)
{
    pos temp=equation->next;
    for(int i=0;i<n&&temp!=NULL;i++)
        temp=temp->next;
    return temp;
}
//free Linked List.
void freeEquations() {
    pos curr = equation->next;
    while (curr != NULL) {
        pos temp = curr;
        curr     = curr->next;
        free(temp);
    }
    free(equation);
    equation         = NULL;
    numberOfEquation = 0;
}


//Show Menu.
void showMenu()
{
printf("\n========== Calculator System Menu ==========\n\n");

printf(" 1) Read data from input file\n");
printf(" 2) Verify equations correctness\n");
printf(" 3) Convert infix -> postfix\n");
printf(" 4) Evaluate postfix expressions\n");
printf(" 5) Show invalid equations\n");
printf(" 6) Expression tree operations\n");
printf(" 7) Save output to file (output.txt)\n");
printf(" 8) Exit\n");

printf("\n===========================================\n");
printf("Select an option: ");
}
//Read Data From Input File
void readData() {
    char fileName[100];
    char Line[100];
    printf("Please enter file name:\n");
    if (scanf("%99s", fileName)!=1) return;

    FILE *inputFile = fopen(fileName, "r");
    if (inputFile == NULL) {
        printf("File not found\n");
        return;
    }

    freeEquations();
    createList();
    validated=converted=evaluated=0;

    while (fgets(Line, sizeof(Line), inputFile) != NULL) {
        int size = strlen(Line);
        if (size > 0 && Line[size-1] == '\n')
            {
                 Line[size-1] = '\0';
        size--;
        }
        if (size > 0 && Line[size-1] == '\r')
            {
                Line[size-1] = '\0';
        }

        if (strlen(Line) > 0)
            insertEquation(Line);
    }

    fclose(inputFile);

    if (numberOfEquation > 0)
        printf("Successfully added %d equations.\n\n", numberOfEquation);
    else
        printf("The file is empty.\n");
}

//Empty Stack.
int IsEmpty( stack s )
{
    return (s == NULL || s->next == NULL);

}
//Return Last Element In Stack.
char top(stack s)
{
    if(!IsEmpty(s))
    return s->next->element;
    return '\0';
}
//Create Stack.
stack create()
{
    stack s=(stack)malloc(sizeof(struct node));
    if(s!=NULL)
        s->next=NULL;
    return s;

}
//Add Element to Stack.
void push (stack s,char x )
{
    ptr temp=(ptr)malloc(sizeof(struct node));
    if(temp!=NULL)
    {
        temp->element=x;
        temp->next=s->next;
        s->next=temp;

    }
}
//Remove Element From Stack.
char pop (stack s)
{
    if(IsEmpty(s))
        return '\0';
    ptr temp=s->next;
    char x=temp->element;
    s->next=temp->next;
    free(temp);
    return x;
}
//Remove All Element From Stack;
void makeEmpty (stack s)
{
    while (!IsEmpty(s))
        pop(s);
}
int Operator  (char c)
{
    return c=='+' || c=='-' || c=='*' || c=='/'||c=='%';
}
int leftBracket(char c)
{
    return  c=='(' || c=='[' || c=='{';
}
int rightBracket(char c)
{
    return  c==')' || c==']' || c=='}';
}

//Check The Bracket.
int balanced(char arr[],char errorMassege[])
{
    stack s=create();

    for (int i=0; arr[i]; i++)
    {
        if(leftBracket(arr[i]))
            push(s,arr[i]);
        else if(rightBracket(arr[i]))
        {
            if (IsEmpty(s))
            {
                sprintf(errorMassege,"'%c' has no matching opening bracket", arr[i]);
                free(s);
                return 0;
            }
            char c=pop(s);
            if ((c=='('&&arr[i]!=')')||(c=='['&&arr[i]!=']')||(c=='{'&&arr[i]!='}'))
            {
                sprintf(errorMassege,"'%c' does not match '%c'", arr[i], c);
                makeEmpty(s);
                free(s);
                return 0;
            }
        }
    }
    if(!IsEmpty(s))
    {
        ptr temp=s->next;
        char first=temp->element;
        while(temp->next!=NULL)
        {
            temp=temp->next;
            first=temp->element;

        }
        sprintf(errorMassege, "'%c' is not closed", first);
        makeEmpty(s);
        free(s);
        return 0;
    }
    makeEmpty(s);
    free(s);
    return 1;

}
//Check The Edge Case.
void validity()
{
    validated=1; converted=0; evaluated=0;

    for(int i=0; i<numberOfEquation; i++)
    {
        char *eq=getEquation(i)->infix;
        int length = strlen(eq);
        if (length == 0)
        {
            getEquation(i)->isValid = 0;
            strcpy(getEquation(i)->errorMassege, "equation is empty");
            continue;
        }
        if(!balanced(eq,getEquation(i)->errorMassege))
        {
            getEquation(i)->isValid=0;
            continue;
        }
        stack s=create();
        int valid=1;
        int type=0;
        char first[50]="";
        char end [50]="";
        type=0;
        first[0]='\0';
        end [0]='\0';
        int j=0;
        while(j<length&&valid)
        {

            char x=eq[j];

            if(isdigit(x))
            {

                char fullNumber[50]="";
                int k=0;
                while(j<length&&isdigit(eq[j]))
                {
                    if (k >= 49) { valid=0; strcpy(getEquation(i)->errorMassege,"number is too long"); break; }
                    fullNumber[k]=eq[j];
                    k++;
                    j++;
                }

                fullNumber[k]='\0';
                if(type==1||type==4)
                {
                    valid=0;
                    sprintf(getEquation(i)->errorMassege,"there is no operator between %s%s%s",first, end, fullNumber);
                }
                else
                {
                    strcpy(first,end);
                    strcpy(end,fullNumber);
                    type=1;

                }

            }
            else if(Operator(x))
            {

                char typeOperation[3]= {x,'\0'};

                if(type==0)
                {

                    valid=0;
                    sprintf(getEquation(i)->errorMassege,"equation cannot start with operator '%s'", typeOperation);
                }
                else if(type==2)
                {

                    valid=0;
                    sprintf(getEquation(i)->errorMassege,"two consecutive operators '%s%s'", end, typeOperation);
                }
                else if(type==3)
                {

                    valid=0;
                    sprintf(getEquation(i)->errorMassege,"operator '%s' right after opening bracket '%s'",typeOperation, end);
                }
                else
                {

                    strcpy(first,end);
                    end[0]=x;
                    end[1]='\0';
                    type=2;

                }
                j++;

            }
            else if(leftBracket(x))
            {

                if(type==1||type==4)
                {
                    valid=0;
                    sprintf(getEquation(i)->errorMassege,"there is no operator between %s%s%c",first, end, x);
                }
                else
                {
                    push(s,x);
                    strcpy(first,end);
                    end[0]=x;
                    end[1]='\0';
                    type=3;

                }
                j++;

            }
            else if(rightBracket(x))
            {

                if(type==3)
                {
                    valid=0;
                    sprintf(getEquation(i)->errorMassege,"empty brackets '%s%c'", end, x);
                }
                else if(type==2)
                {
                    valid=0;
                    sprintf(getEquation(i)->errorMassege, "operator '%s' before closing bracket '%c'", end, x);

                }
                else
                {
                    pop(s);
                    strcpy(first,end);
                    end[0]=x;
                    end[1]='\0';
                    type=4;
                }
                j++;
            }
            else
            {
                valid=0;
                sprintf(getEquation(i)->errorMassege, "invalid character '%c'", x);
                j++;
            }
        }
        if(valid&&type==2)
        {
            valid=0;
            sprintf(getEquation(i)->errorMassege,"equation ends with operator '%s'", end);
        }
        if(valid&&type==0)
        {
            valid=0;
            strcpy(getEquation(i)->errorMassege, "equation is empty");
        }
        makeEmpty(s);
        free(s);
        getEquation(i)->isValid=valid;
        if(valid)
        {
            strcpy(getEquation(i)->errorMassege,"valid");
        }
    }
for (int i = 0; i < numberOfEquation; i++) {

    printf("Equation No. %2d -> ", i + 1);

    if (getEquation(i)->isValid) {
        printf("valid\n");
    } else {
        printf("invalid: %s\n",getEquation(i)->errorMassege);
    }
}

}
//Check The Priority.
int topPriority(char c)
{
    if(c=='+'||c=='-')
        return 1;
    if(c=='*'||c=='/'||c=='%')
        return 2;
    return 0;
}
//Convert Infix->Postfix.
void convert()
{
    converted=1; evaluated=0;
    for(int i=0; i<numberOfEquation; i++)
    {
        if (getEquation(i)->isValid)
        {
            stack s=create();
            char *infix=getEquation(i)->infix;
            char *postfix=getEquation(i)->postfix;
            int k=0;
            for(int j=0; infix[j]!='\0'; j++)
            {
                char pos =infix[j];
                if(isdigit(pos))
                {
                    while (infix[j]!='\0'&&isdigit(infix[j]))
                    {
                        postfix[k]=infix[j];
                        k++;
                        j++;
                    }
                    postfix[k]=' ';
                    k++;
                    j--;
                }
                else if(pos=='(' || pos=='[' || pos=='{')
                    push(s,pos);
                else if(pos==')' || pos==']' || pos=='}')
                {
                    char type='\0' ;
                    if(pos==')')
                        type='(';
                    else if(pos==']')
                        type='[';
                    else
                        type='{';
                    while(!IsEmpty(s)&&top(s)!=type)
                    {
                        postfix[k]=pop(s);
                        k++;
                        postfix[k]=' ';
                        k++;

                    }
                    if (!IsEmpty(s))
                    pop(s);
                }
                else if(Operator(pos))
                {
                    while(!IsEmpty(s)&&topPriority(top(s))>=topPriority(pos))
                    {
                        postfix[k]=pop(s);
                        k++;
                        postfix[k]=' ';
                        k++;
                    }
                    push(s,pos);

                }
            }
            while(!IsEmpty(s))
            {
                postfix[k]=pop(s);
                k++;
                postfix[k]=' ';
                k++;
            }
            postfix[k]='\0';
            if(getEquation(i)->isValid)
                        printf("Equation No. %d -> %s\n", i+1,getEquation(i)->postfix);

        }
    }
}
//Add Number In Stack.
void pushNumber(stack1 s,int n)
{

    stack1 temp=malloc(sizeof(struct node1));
    temp->element=n;
    temp->next=s->next;
    s->next=temp;
}
//Remove Number From Stack.
int popNumber(stack1 s)
{

    if(s==NULL||s->next==NULL)
        return 0;
    stack1 temp=s->next;
    int n=temp->element;
    s->next=temp->next;
    free(temp);
    return n;
}
//Print Result && calculation.
void evaluate()
{
    evaluated=1;
    for(int i=0;i<numberOfEquation;i++)
    {
        if(getEquation(i)->isValid)
        {
            stack1 s=(stack1)malloc(sizeof(struct node1));
            s->next=NULL;
            char *postfix=getEquation(i)->postfix;
            int mathError=0;
            for(int j=0; postfix[j]!='\0'; j++)
            {
                if (postfix[j]==' ')
                    continue;
                if(isdigit(postfix[j]))
                {
                    int number =0;
                    while(isdigit(postfix[j]))
                    {
                        number=number*10+(postfix[j]-'0');
                        j++;
                    }
                    pushNumber(s,number);
                    j--;
                }
                else
                {
                    int number2=popNumber(s);
                    int number1=popNumber(s);
                    switch(postfix[j])
                    {
                    case '+':
                        pushNumber(s,number1+number2);
                        break;

                    case '-':
                        pushNumber(s,number1-number2);
                        break;

                    case '*':
                        pushNumber(s,number1*number2);
                        break;

                    case '/':
                        if(number2!=0)
                        pushNumber(s,number1/number2);
                        else {
                            printf("Equation No. %d -> Division by zero\n",i+1);
                            mathError=1;
                        }
                        break;
                    case '%':
                        if(number2!=0) pushNumber(s,number1%number2);
                        else {
                            printf("Equation No. %d -> Modulo by zero\n",i+1);
                            mathError=1;
                        }
                        break;
                    }
                }
            }
            if(!mathError && s->next!=NULL)
            {
               getEquation(i)->result=popNumber(s);
                printf("Equation No. %d -> %d\n", i + 1, getEquation(i)->result);
            }
            if(mathError) {
                getEquation(i)->isValid=0;
                strcpy(getEquation(i)->errorMassege,"division or modulo by zero");
            }
            while(s->next!=NULL)
                popNumber(s);
            free(s);

        }
    }
}
//Print Invalid Equation.
void printInvalid()
{
    int check=0;
    for (int i=0;i<numberOfEquation;i++)
    {
        if(getEquation(i)->isValid==0)
        {
            printf("Equation No. %d -> %s\n", i + 1, getEquation(i)->infix);
            printf("Error: %s\n",getEquation(i)->errorMassege);
            check=1;
        }
    }
    if(!check)
        printf("No invalid equations\n");
}
//Create Tree.
treePtr createTree()
{
    treePtr s = (treePtr)malloc(sizeof(struct tree_stack_node));
    s->next   = NULL;
    return s;
}
//Empty Tree.
int IsEmptyTree(treePtr s)
{
    return s->next==NULL;
}
//Add Node To Tree.
void pushTree(treePtr s,tree_ptr pos)
{
    treePtr temp =(treePtr)malloc(sizeof(struct tree_stack_node));
    temp->data=pos;
    temp->next=s->next;
    s->next=temp;
}
//Remove Node From Tree.
tree_ptr popTree(treePtr s)
{
    if(s->next==NULL)
        return 0;
    treePtr temp=s->next;
    tree_ptr x=temp->data;
    s->next=temp->next;
    free(temp);
    return x;
}
//Create Node.
BST makeNode (char *c)
{
    BST Node=(BST)malloc (sizeof(struct tree_node));
    strcpy(Node->element,c);
    Node->left=NULL;
    Node->right=NULL;
    return Node;
}
//Remove All Node From Tree.
void freeTree(BST root)
{
    if (root==NULL)
        return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);

}
//Build Tree.
BST buildTree (char *postfix)
{
    treePtr s=createTree();
    int j=0;
    while(postfix[j]!='\0')
    {
        if(postfix[j]==' ')
        {
            j++;
            continue;
        }
        if(isdigit(postfix[j]))
        {
            char fullNumber[20]="";
            int k=0;
            while (isdigit(postfix[j]))
            {
                fullNumber[k]=postfix[j];
                k++;
                j++;
            }
            fullNumber[k]='\0';
            pushTree(s,makeNode(fullNumber));

        }
        else if(Operator(postfix[j])){
            char typeOperation[2]= {postfix[j],'\0'};
            BST Node=makeNode(typeOperation);
            Node->right=popTree(s);
            Node->left=popTree(s);
            if(Node->left==NULL||Node->right==NULL)
            {
                freeTree(Node);
                return NULL;
            }
            pushTree(s,Node);
            j++;
    }
    else
        j++;
    }
    BST root=NULL;
    if(!IsEmptyTree(s))
        root=popTree(s);
    return root;
}
//inorder (Left->Root->Right).
void inorder(BST root) {
    if (root == NULL) return;

    if (root->left == NULL && root->right == NULL) {
        printf("%s", root->element);
        return;
    }

    printf("( ");
    inorder(root->left);
    printf(" %s ", root->element);
    inorder(root->right);
    printf(" )");
}
//Postorder (Left->Right->Root).
void postorder(BST root)
{
    if(root ==NULL)
        return;
    postorder(root->left);
    postorder(root->right);
    printf("%s ",root->element);
}
//Preorder (Root->Left->Right).
void preorder (BST root)
{
    if(root ==NULL)
        return;
    printf("%s ",root->element);
    preorder(root->left);
    preorder(root->right);
}
//Print All Traversal.
void printExpression ()
{
    for (int i=0;i<numberOfEquation;i++)
    {
        if(getEquation(i)->isValid)
            printf("%d. %s\n", i + 1, getEquation(i)->infix);
        else
            printf("%d. %s (invalid)\n", i + 1, getEquation(i)->infix);
    }
    int n=0;
    printf("Please enter equation number: ");
    if (scanf("%d", &n)!=1) {
        printf("Invalid number\n");
        int c; while ((c=getchar())!='\n' && c!=EOF) {}
        return;
    }
    if(n<1||n>numberOfEquation)
    {
        printf("Invalid number");
        return;

    }
    if(!getEquation(n-1)->isValid)
    {
        printf("Equation No. %d is invalid.\n", n);
        return;
    }

    BST root =buildTree(getEquation(n-1)->postfix);
    if (root==NULL)
    {
        printf("Error empty tree.\n");
        return;
    }
    printf("Inorder :");
    inorder(root);
    printf("\nPostorder  :");
    postorder(root);
    printf("\nPreorder :");
    preorder(root);
    freeTree(root);
}
//Write Data On Output File.
void writeData()
{
    FILE *f= fopen("output.txt", "w");
    if(f==NULL)
    {
        printf("Error: could not create output.txt\n");
        return;
    }
    for (int i=0;i<numberOfEquation;i++)
    {
        if (getEquation(i)->isValid) {
            fprintf(f, "Equation No. %d: %s\n",i + 1, getEquation(i)->infix);
            fprintf(f, "  Status  : valid\n");
            fprintf(f, "  Postfix : %s\n",getEquation(i)->postfix);
            fprintf(f, "  Result  : %d\n\n",getEquation(i)->result);
        } else {
            fprintf(f, "Equation No. %d: %s\n",i + 1, getEquation(i)->infix);
            fprintf(f, "  Status  : invalid - %s\n\n",getEquation(i)->errorMassege);
        }
    }
    fclose(f);
    printf("Saved to output.txt\n");
}







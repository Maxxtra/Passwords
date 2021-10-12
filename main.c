//TRECE VALGRIND PE 1 2 SI MAI MULTE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// -----------------------------------------------------------------------------

typedef struct ListNode
{
    char data;             // Stored node value
    struct ListNode *next; // link to next node
    struct ListNode *prev; // link to prev node
} ListNode;

typedef struct List
{
    ListNode *first; // link to the first node
    ListNode *last;  // link to the last node
} List;
// -----------------------------------------------------------------------------

ListNode *createNode(char data)
{
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    node->data = data;
    node->prev = NULL;
    node->next = NULL;

    return node;
}

List *createList(void)
{
    List *list = (List *)malloc(sizeof(List));
    list->first = list->last = NULL;

    return list;
}
// -----------------------------------------------------------------------------

int isEmpty(List *list)
{
    return (list == NULL) || (list->first == NULL);
}
// -----------------------------------------------------------------------------

int contains(List *list, char data)
{
    // TDOO: Cerinta 1c
    if (isEmpty(list))
        return 0;

    ListNode *iter = list->first;

    while (iter != NULL)
    {
        if (iter->data == data)
            return 1;
        iter = iter->next;
    }

    return 0;
}
// -----------------------------------------------------------------------------

int length(List *list)
{
    // Guard against young player errors
    if (list == NULL)
        return 0;

    if (isEmpty(list))
        return 0;

    int length = 0;
    ListNode *iter = list->first;

    while (iter != NULL)
    {
        length++;
        iter = iter->next;
    }

    return length;
}
// -----------------------------------------------------------------------------

void insertAt(List *list, char data, int pos)
{

    // Guard against young player errors
    if (list == NULL)
        return;

    // TODO: Cerinta 1d

    if (pos < 0)
        return;

    if (length(list) < pos)
        return;

    if (isEmpty(list))
    { //lista e vida
        ListNode *node = createNode(data);
        list->first = node;
        list->last = node;

        return;
    }

    if (pos == 0)
    { //adaugam pe prima pozitie
        ListNode *node = createNode(data);
        list->first->prev = node;
        node->next = list->first;
        list->first = node;

        return;
    }

    if (pos == length(list))
    { //adaugam pe ultima pozitie
        ListNode *node = createNode(data);
        list->last->next = node;
        node->prev = list->last;
        list->last = node;

        return;
    }

    ListNode *iter = list->first;
    ListNode *node = createNode(data);

    while (pos > 0)
    {
        iter = iter->next;
        pos--;
    }

    node->prev = iter->prev;
    node->next = iter;
    iter->prev->next = node;
    iter->prev = node;

    return;
}
// -----------------------------------------------------------------------------

void deleteOnce(List *list, ListNode *iter)
{

    // Guard against young player errors
    if (iter->prev == NULL && iter->next == NULL)
    {
        list->first = NULL;
        list->last = NULL;
        free(iter);
        return;
    }

    if (iter == list->first)
    {
        list->first = iter->next;
        list->first->prev = NULL;
        free(iter);
        return;
    }

    if (iter == list->last)
    {
        list->last = iter->prev;
        list->last->next = NULL;
        free(iter);
        return;
    }

    iter->prev->next = iter->next;
    iter->next->prev = iter->prev;
    free(iter);

    return;
}
// -----------------------------------------------------------------------------

List *destroyList(List *list)
{
    // Guard against young player errors
    if (list == NULL)
        return NULL;

    ListNode *node;

    while (list->first != NULL)
    {
        node = list->first;
        list->first = list->first->next;
        free(node);
    }

    free(list);

    return NULL;
}

void printList(List *list)
{
    FILE *f = fopen("editor.out", "w");
    ListNode *node = list->first;
    while (node != NULL)
    //printf("\nTraversal in reverse direction \n");
    {
        putc(node->data, f);
        node = node->next;
    }
    fclose(f);
}
// -----------------------------------------------------------------------------

int go_to_line(char *rest, char *comm)
{
    char *verr = comm;
    int line;
    if (rest)
        while (*verr)
        { // While there are more characters to process...
            if (isdigit(*verr) || ((*verr == '-' || *verr == '+') && isdigit(*(verr + 1))))
            {
                // Found a number
                line = strtol(verr, &verr, 15); // Read number
                //gl = 1;
            }
            else
                // Otherwise, move on to the next character.
                verr++;
        }
    return line;
}

ListNode *nth_element(List *list, const size_t thl, size_t thc)
{
    int counterl = 1, counterc = 0;
    ListNode *cap = list->first;
    while (cap != NULL && counterl != thl)
    {
        if (cap->data == '\n')
            counterl++;
        cap = cap->next;
    }
    if (thc != 0)
    {
        while (counterc != thc)
        {
            cap = cap->next;
            counterc++;
        }
    }
    return cap;
}

typedef struct StackNode
{
    char elem;
    struct StackNode *next;
} StackNode;

typedef StackNode TCelSt;
typedef StackNode *ACelSt;

typedef struct Stack
{
    StackNode *head; // Varful stivei
    long size;       // Numarul de elemente din stiva
} Stack;

typedef Stack TStiva;
typedef Stack *ASt;

Stack *createStack(void)
{
    // TODO: Cerinta 1
    Stack *stack = (Stack *)calloc(1, sizeof(Stack));
    stack->size = 0;
    stack->head = NULL;
    return stack;
}

int isStackEmpty(Stack *stack)
{
    // TODO: Cerinta 1
    if (stack == NULL)
        return 1;
    if (stack->head == NULL)
        return 1;
    return 0;
}

void push(Stack *stack, char elem)
{
    // TODO: Cerinta 1
    if (isStackEmpty(stack))
    {
        if (stack == NULL)
            stack = createStack();
        stack->size = 1;
        StackNode *node = (StackNode *)calloc(1, sizeof(StackNode));
        node->elem = elem;
        node->next = NULL;
        stack->head = node;
        return;
    }

    StackNode *node = (StackNode *)calloc(1, sizeof(StackNode));
    node->elem = elem;
    node->next = stack->head;
    stack->size++;
    stack->head = node;
    return;
}

char top(Stack *stack)
{
    return stack->head->elem;
}

void pop(Stack *stack)
{
    if (stack->head == NULL)
        return;
    StackNode *node = stack->head;
    stack->head = stack->head->next;
    free(node);
    stack->size--;
    return;
}

void destroyStack(Stack *stack)
{
    while (stack->head != NULL)
        pop(stack);
    free(stack);
    return;
}

typedef struct StackNodez
{
    char elem;
    struct StackNodez *next;
} StackNodez;

typedef StackNodez TCelStz;
typedef StackNodez *ACelStz;

typedef struct Stackz
{
    StackNodez *head; // Varful stivei
    long size;        // Numarul de elemente din stiva
} Stackz;

typedef Stackz TStivaz;
typedef Stackz *AStz;

Stackz *createStackz(void)
{
    // TODO: Cerinta 1
    Stackz *stack = (Stackz *)calloc(1, sizeof(Stackz));
    stack->size = 0;
    stack->head = NULL;
    return stack;
}

int isStackEmptyz(Stackz *stack)
{
    // TODO: Cerinta 1
    if (stack == NULL)
        return 1;
    if (stack->head == NULL)
        return 1;
    return 0;
}

void pushz(Stackz *stack, char elem)
{
    // TODO: Cerinta 1
    if (isStackEmptyz(stack))
    {
        if (stack == NULL)
            stack = createStackz();
        stack->size = 1;
        StackNodez *node = (StackNodez *)calloc(1, sizeof(StackNodez));
        node->elem = elem;
        node->next = NULL;
        stack->head = node;
        return;
    }

    StackNodez *node = (StackNodez *)calloc(1, sizeof(StackNodez));
    node->elem = elem;
    node->next = stack->head;
    stack->size++;
    stack->head = node;
    return;
}

char topz(Stackz *stack)
{
    return stack->head->elem;
}

void popz(Stackz *stack)
{
    if (stack->head == NULL)
        return;
    StackNodez *node = stack->head;
    stack->head = stack->head->next;
    free(node);
    stack->size--;
    return;
}

void destroyStackz(Stackz *stack)
{
    while (stack->head != NULL)
        popz(stack);
    free(stack);
    return;
}

int lungime(List *list)
{
    ListNode *iter = list->first;
    int l = 1;
    while (iter->next != NULL)
    {
        if (iter->data == '\n')
            l++;
        iter = iter->next;
    }
    return l;
}

static int dart[5] = {0};
char v[100];
int main()
{
    FILE *fp = fopen("editor.in", "r");
    List *list = createList();
    Stack *stack = createStack();
    Stackz *stackz = createStackz();
    char c;
    int text = 0;
    int poz = 0;
    int k = 0;
    static bool quit = 0;
    while ((c = getc(fp)) != EOF)
    {

        if (c != ':' && text % 2 == 0)
        {
            insertAt(list, c, poz);
            poz++;
            if (text != 0)
            {
                v[k] = c;
                k++;
            }
        }
        else if (c == ':')
        {

            text = 1;
            for (int i = 0; i < 3; i++)
            {
                c = getc(fp);
            }
            char *comm;
            comm = (char *)malloc(20 * sizeof(char));
            while (fgets(comm, 20, fp) != NULL)
            {
                char verify[10];
                strcpy(verify, ":");
                if (strstr(comm, verify) != NULL)
                    text++;
                if (text % 2 == 0)
                {
                    char ca = 'i';
                    push(stack, ca);
                    dart[0] = lungime(list) + 1;
                    break;
                }

                char test[100];
                char test1[15];
                //     //
                //     //
                //     //
                //     //
                //     //
                //     //
                //     //
                //     //
                //     //
                //     //
                strcpy(test, "s\n");
                if (strcmp(test, comm) == 0)
                    printList(list);
                //     //
                //     //
                //     //
                //     //
                //     //
                //     //
                //     //
                //     //
                //     //
                //     //
                strcpy(test, "q\n");
                if (strcmp(test, comm) == 0)
                {
                    quit = 1;
                    break;
                }
                //     //
                //     //
                //     //
                //     //
                //     //
                //     //
                //     //
                //     //
                //     //
                //     //
                char *rest;
                strcpy(test, "gl");
                rest = strstr(comm, test);
                if (rest)
                    dart[0] = go_to_line(rest, comm);
                //
                //
                // /
                // /
                //
                //
                //
                //
                strcpy(test, "dl ");
                strcpy(test1, "dl\n");
                if (strstr(comm, test) != NULL || strcmp(comm, test1) == 0)
                {
                    if (strlen(comm) > 4)
                    {

                        char *r;
                        r = strstr(comm, test);
                        dart[0] = go_to_line(r, comm);
                        ListNode *cursor = nth_element(list, dart[0], dart[1]);

                        while (cursor->data != '\n')
                        {
                            ListNode *aux = cursor->next;
                            deleteOnce(list, cursor);
                            cursor = aux;
                        }
                        deleteOnce(list, cursor);
                    }
                    else
                    {
                        ListNode *cursor = nth_element(list, dart[0], dart[1]);
                        while (cursor->data != '\n')
                        {
                            ListNode *aux = cursor->next;
                            deleteOnce(list, cursor);
                            cursor = aux;
                        }
                        deleteOnce(list, cursor);
                    }
                }
                //
                //
                //
                //
                //
                //
                //
                //
                strcpy(test, "gc");
                if (strstr(comm, test) != NULL)
                {
                    char splitString[15][15]; //can store 10 words of 10 characters
                    int j, cnt;
                    j = 0;
                    cnt = 0;
                    for (int i = 0; i <= (strlen(comm)); i++)
                    {
                        // if space or NULL found, assign NULL into splitStrings[cnt]
                        if (comm[i] == ' ' || comm[i] == '\n')
                        {
                            splitString[cnt][j] = '\0';
                            cnt++; //for next word
                            j = 0; //for next word, init index to 0
                        }
                        else
                        {
                            splitString[cnt][j] = comm[i];
                            j++;
                        }
                    }
                    if (cnt > 2)
                    {
                        int nr1 = 0, nr2 = 0, i;
                        for (i = 0; i < strlen(splitString[1]); i++)
                        {
                            if (isdigit(splitString[1][i]) != 0)
                            {
                                nr1 = nr1 * 10 + (splitString[1][i] - '0');
                            }
                        }
                        for (i = 0; i < strlen(splitString[2]); i++)
                        {

                            if (isdigit(splitString[2][i]) != 0)
                            {
                                nr2 = nr2 * 10 + (splitString[2][i] - '0');
                            }
                        }
                        dart[1] = nr1;
                        dart[0] = nr2;
                    }
                    else
                    {
                        int nr1 = 0, i;
                        for (i = 0; i < strlen(splitString[1]); i++)
                        {
                            if (isdigit(splitString[1][i]) != 0)
                            {
                                nr1 = nr1 * 10 + (splitString[1][i] - '0');
                            }
                        }
                        dart[1] = nr1;
                    }
                }
                //
                //
                //
                //
                //
                //
                //
                //
                //
                //
                strcpy(test, "b\n");
                if (strcmp(comm, test) == 0)
                {
                    ListNode *cursor = nth_element(list, dart[0], dart[1]);
                    deleteOnce(list, cursor);
                    dart[1]--;
                }
                //
                //
                //
                //
                //
                //
                //
                //
                //
                //

                strcpy(test1, "d\n");
                strcpy(test, "d ");
                if (strstr(comm, test) != NULL || strcmp(comm, test1) == 0)
                {
                    int del;
                    char splitString[15][15]; //can store 10 words of 10 characters
                    int j, cnt, i;
                    j = 0;
                    cnt = 0;
                    for (int i = 0; i <= (strlen(comm)); i++)
                    {
                        // if space or NULL found, assign NULL into splitStrings[cnt]
                        if (comm[i] == ' ' || comm[i] == '\n')
                        {
                            splitString[cnt][j] = '\0';
                            cnt++; //for next word
                            j = 0; //for next word, init index to 0
                        }
                        else
                        {
                            splitString[cnt][j] = comm[i];
                            j++;
                        }
                    }
                    if (cnt > 1)
                    {
                        int nr1 = 0;
                        for (i = 0; i < strlen(splitString[1]); i++)
                        {
                            if (isdigit(splitString[1][i]) != 0)
                            {
                                nr1 = nr1 * 10 + (splitString[1][i] - '0');
                            }
                        }
                        del = nr1;
                    }
                    else
                    {
                        del = 1;
                    }
                    int aux = 0;

                    while (aux != del)
                    {
                        aux++;
                        ListNode *cursor = nth_element(list, dart[0], del);
                        deleteOnce(list, cursor);
                    }
                }
                //
                //
                //
                //
                //
                //
                //
                //
                strcpy(test, "u\n");
                if (strcmp(comm, test) == 0)
                {

                    StackNode *node = stack->head;
                    if (node->elem == 'i')
                    {
                        pushz(stackz, 'u');
                        ListNode *cursor = nth_element(list, dart[0], dart[1]);
                        while (cursor->data != '\n')
                        {
                            ListNode *aux = cursor->next;
                            deleteOnce(list, cursor);
                            cursor = aux;
                        }
                        deleteOnce(list, cursor);
                        // pop(stack);
                    }
                    dart[0]--;
                }
                //
                //
                //
                //
                //
                //
                //
                strcpy(test, "r\n");
                if (strcmp(comm, test) == 0)
                {
                    ListNode *cursor = nth_element(list, dart[0], dart[1]);
                    while (cursor->data != '\n')
                        cursor = cursor->next;

                    int i;
                    i = 0;
                    while (i < strlen(v))
                    {
                        insertAt(list, v[i], length(list));
                        poz++;
                        i++;
                    }
                }
                //
                //
                //
                //
                //
                //

                if (quit == 1)
                    break;
            }
            free(comm);
        }
    }
    destroyList(list);
    destroyStack(stack);
    destroyStackz(stackz);
    fclose(fp);
    return 0;
}

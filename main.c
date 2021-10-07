#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Element_str
{
    char text[50];
    struct Element_str *next;
} Element_str;

typedef struct Cake
{
    struct Element_str *order;
    struct Taste_Stack *s_tastes;
} Cake;

typedef struct Element_cake
{
    struct Cake *cake;
    struct Element_cake *next;
} Element_cake;

typedef struct Order_Queue
{
    struct Element_str *list;
} Order_Queue;

typedef struct Taste_Stack
{
    struct Element_str *tastes;

} Taste_Stack;

typedef struct Tasting_Queue
{ // TODO
} Tasting_Queue;

Element_str *initialize_tastes()
{
    int n_taste = 7;
    char local[7][15] = {"Vanilla", "Chocolate", "Strawberry", "Orange", "Apple", "Banana", "Fudge"};
    Element_str *new_el = (Element_str *)malloc(sizeof(Element_str));
    strcpy(new_el->text, local[0]);
    int cpt = 0;
    Element_str *temp = new_el;
    while (cpt < n_taste)
    {
        temp->next = (Element_str *)malloc(sizeof(Element_str));
        strcpy(temp->text, local[cpt]);
        cpt++;
        temp = temp->next;
    }
    return new_el;
};

int len_f_orders(Order_Queue *f_orders){
    Order_Queue temp = *f_orders;
    int nb = 0;
    while(temp.list != NULL){
        nb ++;
        temp.list = temp.list->next;
    }
    return nb;
}

void display_tastes(Element_str *t)
{
    if (t->next != NULL)
    {
        printf("%s, ", t->text);
        display_tastes(t->next);
    }
    else
    {
        printf(" ø\n");
    }
}

void pass_order(char order[50], Order_Queue *f_orders){
    if (len_f_orders(f_orders)<10){
        Order_Queue *temp = f_orders;
        Element_str *new_el = malloc(sizeof(Element_str));
        strcpy(new_el->text, order);
        new_el->next = NULL;
        if (temp->list == NULL)
        {
            temp->list = new_el;
        }
        else
        {
            Element_str* pElementStr = f_orders->list;
            while(pElementStr->next != NULL){
                pElementStr = pElementStr->next;
            }
            pElementStr->next = new_el;
        }
    }
}
void pop(Order_Queue *q_orders)
{
    Order_Queue;
}

Element_str* process_order(Order_Queue* q_orders ){
    Element_str *order;
    if(q_orders->list == NULL){
        return NULL;
    } else {
        order = q_orders->list;
        q_orders->list = q_orders->list->next;
    }

    return order;
}

void print_order(Order_Queue *f_orders){
    Order_Queue temp = *f_orders;
    if (temp.list != NULL){
        while (temp.list != NULL){
            printf("%s \n",temp.list->text);
            temp.list = temp.list->next;
        }
    }
}
// Element_str *process_order(Order_Queue *q_orders){

// };

Cake *create_cake(Element_str *order)
{
    Cake *newcake = malloc(sizeof(Cake));
    newcake->order = order;
    return newcake;
};

// void build_Cake(Cake *cake, Element_str *l_tastes){

// };

// void deliver(Cake *cake, Tasting_Queue *q_tasting){

// };

// void tasting(Tasting_Queue *q_tasting, int nb_parts){

// };

int main()
{
    Element_str *l_tastes;

    l_tastes = initialize_tastes();
//    display_tastes(l_tastes);

    Order_Queue *q_orders = malloc(sizeof(Order_Queue));
    q_orders->list = NULL;

    print_order(q_orders);
    Element_str *test = process_order( q_orders );
    process_order( q_orders );
    process_order( q_orders );
    print_order(q_orders);


//
//    Cake *cake = malloc(sizeof(Cake));
//    cake = create_cake(q_orders->list);
//
//    Tasting_Queue *q_tasting;

    return 0;
}
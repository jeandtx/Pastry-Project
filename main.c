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

/*
    initialize_tastes doesn't take arguments and return a pointer to a structure Element_str: linked list. This linked list is the menu of tastes.
    To fill the menu while creating it, we needed a local variable with the data.
*/
Element_str *initialize_tastes()
{
    char local[7][15] = {"Vanilla", "Chocolate", "Strawberry", "Orange", "Apple", "Banana", "Fudge"}; // the data from the pdf
    Element_str *new_el = (Element_str *)malloc(sizeof(Element_str));
    strcpy(new_el->text, local[0]); // After creating the first element we can give him the first taste
    int cpt = 0;
    Element_str *temp = new_el;
    while (cpt < 7) // There's 7 different tastes
    {
        temp->next = (Element_str *)malloc(sizeof(Element_str));
        strcpy(temp->text, local[cpt]); // In the loop we put the local index cpt
        cpt++;
        temp = temp->next;
    }
    return new_el;
};

/* algo len_f_orders(f_order : ref to structure Order_Queue):int
return the size of a linked list made of order_queue
*/
int len_f_orders(Order_Queue *f_orders)
{
    Order_Queue temp = *f_orders;
    int nb = 0;
    while (temp.list != NULL)
    {
        nb++;
        temp.list = temp.list->next;
    }
    return nb;
}

/*pass_order(char order[50], Order_Queue *f_orders)
take a list of orders and add an order to it
*/
void pass_order(char order[50], Order_Queue *f_orders)
{
    if (len_f_orders(f_orders) < 10)
    {
        Order_Queue *temp = f_orders;
        Element_str *new_el = malloc(sizeof(Element_str)); //allocate place for the new order in the list
        strcpy(new_el->text, order);
        new_el->next = NULL;
        if (temp->list == NULL)
        {
            temp->list = new_el;    //if the list is empty fill it with new_el
        }
        else   
        {
            Element_str *pElementStr = f_orders->list;
            while (pElementStr->next != NULL)   //if not add it at the end of the list
            {
                pElementStr = pElementStr->next;
            }
            pElementStr->next = new_el;
        }
    }
}

Element_str *process_order(Order_Queue *q_orders)
{
    Element_str *order;
    if (q_orders->list == NULL)
        return NULL; //return nothing if the list is empty

    order = q_orders->list;
    q_orders->list = q_orders->list->next; //deleting the first command as its the oldest on

    return order;
}

void print_order(Order_Queue *f_orders)
{
    Order_Queue temp = *f_orders;
    if (temp.list != NULL)
    {
        while (temp.list != NULL)
        {
            printf("%s \n", temp.list->text);
            temp.list = temp.list->next;
        }
    }
}

// The function is taking an order as parameter and return an initialized cake with the right order
Cake *create_cake(Element_str *order)
{
    Cake *newcake = malloc(sizeof(Cake));
    newcake->order = order;
    newcake->s_tastes = malloc(sizeof(Taste_Stack)); // We need to allocate this variable because we will assign things in it later
    return newcake;
};

// The function is a void it act on the cake and use the menu (l_tastes) to refer but not modify it
void build_Cake(Cake *cake, Element_str *l_tastes)
{
    Cake *temp_cake = cake;
    Element_str *temp_tastes = l_tastes;
    // We need to temp because we will deal with both arguments
    int j = 0;
    while (j < strlen(temp_cake->order->text)) // While there's more tastes in the order
    {
        for (int i = 0; i < 7; i++) // For each taste
        {
            if (temp_cake->order->text[j] == temp_tastes->text[0]) // Check if this is the one on the order
            {
                temp_cake->s_tastes->tastes = malloc(sizeof(Element_str));
                strcpy(temp_cake->s_tastes->tastes->text, temp_tastes->text); // if yes add it to the cake
                // temp_cake->s_tastes->tastes = temp_cake->s_tastes->tastes->next;
                // Problem: it looks like the cake takes the first ingredient of the order but the line next is causing troubles
                j++;
            }
            else // Otherwise go to the next flavor on the menu
                temp_tastes = temp_tastes->next;
        }
        temp_tastes = l_tastes; // reset the temp because we made things with it
    }
};

// void deliver(Cake *cake, Tasting_Queue *q_tasting){

// };

// void tasting(Tasting_Queue *q_tasting, int nb_parts){

// };

int main()
{
    Element_str *l_tastes;

    l_tastes = initialize_tastes();

    Order_Queue *q_orders = malloc(sizeof(Order_Queue));
    q_orders->list = NULL;

    pass_order("AOB", q_orders);
    Cake *cake = malloc(sizeof(Cake));
    cake = create_cake(q_orders->list);

    build_Cake(cake, l_tastes);

    Tasting_Queue *q_tasting;

    return 0;
}
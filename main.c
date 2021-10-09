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
{
    struct Element_cake *queue;
} Tasting_Queue;

/*
    initialize_tastes doesn't take arguments and return a pointer to a structure Element_str: linked list. This linked list is the menu of tastes.
    To fill the menu while creating it, we needed a local variable with the data.
*/
Element_str *initialize_tastes()
{
    printf("Initialisation of the menu\n");
    char local[7][15] = {"Vanilla", "Chocolate", "Strawberry", "Orange", "Apple", "Banana", "Fudge"}; // the data from the pdf
    Element_str *new_el = (Element_str *)malloc(sizeof(Element_str));
    strcpy(new_el->text, local[0]); // After creating the first element we can give him the first taste
    int cpt = 0;
    Element_str *temp = new_el;
    printf("Available tastes:\t");
    while (cpt < 6) // There's 7 different tastes
    {
        temp->next = (Element_str *)malloc(sizeof(Element_str));
        strcpy(temp->text, local[cpt]); // In the loop we put the local index cpt
        cpt++;
        temp = temp->next;
        printf("%d. %s | ", cpt, local[cpt]);
    }
    printf("\n");
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
    printf("You passed an order for %s\n", order);
    if (len_f_orders(f_orders) < 10)
    {
        Element_str *new_el = malloc(sizeof(Element_str)); //allocate place for the new order in the list
        strcpy(new_el->text, order);
        new_el->next = NULL;
        if (f_orders->list == NULL)
        {
            f_orders->list = new_el; //if the list is empty fill it with new_el
        }
        else
        {
            Element_str *temp = f_orders->list;
            while (temp->next != NULL) //if not add it at the end of the list
            {
                temp = temp->next;
            }
            temp->next = new_el;
        }
    }
}

Element_str *process_order(Order_Queue *q_orders)
{
    printf("Order %s is in process\n", q_orders->list->text);
    Element_str *order;
    if (q_orders->list == NULL)
        return NULL; //return nothing if the list is empty

    order = q_orders->list;
    q_orders->list = q_orders->list->next; //deleting the first command as its the oldest on

    return order;
}

void print_order(Order_Queue *f_orders)
{
    printf("Wait for your time, you can see when is your turn on the queue:\n");
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
    printf("Creating the cake for order %s before cooking\n", order->text);
    Cake *newcake = malloc(sizeof(Cake));
    newcake->order = order;
    newcake->s_tastes = malloc(sizeof(Taste_Stack)); // We need to allocate this variable because we will assign things in it later
    newcake->s_tastes->tastes = malloc(sizeof(Element_str));
    return newcake;
};

// The function is a void it act on the cake and use the menu (l_tastes) to refer and check but not modify it
void build_Cake(Cake *cake, Element_str *l_tastes)
{
    printf("The chef is cooking the cake %s\n", cake->order->text);
    Element_str *temp_menu = l_tastes;                    // a temp on the menu to check all the tastes
    Element_str *temp_tastes = cake->s_tastes->tastes;    // a temp on the linked list of the cake to add tastes in the right order
    for (int j = 0; j < strlen((cake->order->text)); j++) // While there's more tastes in the order
    {
        while (cake->order->text[j] != temp_menu->text[0]) // While it didn't match with a taste from the menu !danger!->infinite loop
        {
            temp_menu = temp_menu->next;
        }
        printf("\tAdding the taste %s to the cake\n", temp_menu->text);
        Element_str *new_el = malloc(sizeof(Element_str));
        strcpy(new_el->text, temp_menu->text);
        new_el->next = cake->s_tastes->tastes;
        cake->s_tastes->tastes = new_el;
        temp_menu = l_tastes; // reset the temp because we made things with it and we need it clean
    }
    printf("Cake %s done!\n", cake->order->text);
};

void deliver(Cake *cake, Tasting_Queue *q_tasting)
{
    printf("A cake has been delivered and is ready to be tasted\n");
    Element_cake *new_el = malloc(sizeof(Element_cake));
    new_el->cake = cake;
    if (q_tasting->queue == NULL)
    {
        q_tasting->queue = new_el;
    }
    else
    {
        Element_cake *temp = q_tasting->queue;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new_el;
    }
};

void tasting(Tasting_Queue *q_tasting, int nb_parts)
{
    if (nb_parts > 0)
    {
        if ((int)q_tasting->queue->cake->s_tastes->tastes->text[0] == 0)
        {
            q_tasting->queue = q_tasting->queue->next;
            if (q_tasting->queue != NULL)
            {
                tasting(q_tasting, nb_parts);
            }
            else
            {
                return;
            }
        }
        else
        {
            Cake *cake = q_tasting->queue->cake;
            printf("You are tasting the cake %s and you just ate some %s\n", q_tasting->queue->cake->order->text, cake->s_tastes->tastes->text);
            cake->s_tastes->tastes = cake->s_tastes->tastes->next;
            tasting(q_tasting, nb_parts - 1);
        }
    }
};

int main()
{
    Element_str *l_tastes; // mandatory line

    l_tastes = initialize_tastes();

    Order_Queue *q_orders; // mandatory line
    q_orders = malloc(sizeof(Order_Queue));

    pass_order("SCOA", q_orders);
    pass_order("ABO", q_orders);

    Cake *cake = malloc(sizeof(Cake));
    cake = create_cake(process_order(q_orders));

    Cake *cake2 = malloc(sizeof(Cake));
    cake2 = create_cake(process_order(q_orders));

    build_Cake(cake, l_tastes);
    build_Cake(cake2, l_tastes);

    Tasting_Queue *q_tasting; // mandatory line
    q_tasting = malloc(sizeof(Tasting_Queue));
    deliver(cake, q_tasting);
    deliver(cake2, q_tasting);

    tasting(q_tasting, 10);

    return 0;
}
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

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
    while (cpt < 7) // There's 7 different tastes
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
    Element_str *temp = f_orders->list;
    int nb = 0;
    while (temp != NULL)
    {
        nb++;
        temp = temp->next;
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
// This function is taking the order queue and dequeue it. And return what was dequeu
{
    printf("Order %s is in process\n", q_orders->list->text);
    Element_str *order;
    if (q_orders->list == NULL)
    {
        return NULL; //return nothing if the list is empty
    }
    order = q_orders->list;
    q_orders->list = q_orders->list->next; //deleting the first command as its the oldest on
    return order;
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
    Element_str *temp_menu = l_tastes; // a temp on the menu to check all the tastes
    if (cake->order == NULL)
    {
        printf("Sorry there no place on the order queue 10 max\n");
    }
    else
    {
        for (int j = 0; j < strlen((cake->order->text)); j++) // While there's more tastes in the order
        {
            while (cake->order->text[j] != temp_menu->text[0]) // While it didn't match with a taste from the menu !danger!->infinite loop
            {
                temp_menu = temp_menu->next;
            }
            printf("\tAdding the taste %s to the cake\n", temp_menu->text);
            Element_str *new_el = malloc(sizeof(Element_str)); // Creating the new taste
            strcpy(new_el->text, temp_menu->text);
            new_el->next = cake->s_tastes->tastes;
            cake->s_tastes->tastes = new_el; // adding it to the linked list at first position
            temp_menu = l_tastes;            // reset the temp because we made things with it and we need it clean
        }
        printf("Cake %s done!\n", cake->order->text);
    }
};

void rand_order(Order_Queue *f_orders)
{
    // This function is for the Assembly Bonus
    char local[7] = {'V', 'C', 'S', 'O', 'A', 'B', 'F'};
    char order[50] = " ";
    int random;
    srand(time(NULL));
    for (int i = 0; i < 5; i++)
    { //add 5 different flavor
        random = rand() % 7;
        order[i] = local[random];
    }
    printf("\n\n%s\n\n", order);
    pass_order(order, f_orders);
}

void deliver(Cake *cake, Tasting_Queue *q_tasting)
{
    // This function take a cake and the tasting queue -> It add the cake to the tasting queue
    printf("A cake has been delivered and is ready to be tasted\n");
    Element_cake *new_el = malloc(sizeof(Element_cake));
    new_el->cake = cake;
    if (q_tasting->queue == NULL) // If the queue is empty just add the cake
    {
        q_tasting->queue = new_el;
    }
    else
    {
        Element_cake *temp = q_tasting->queue;
        while (temp->next != NULL) // Otherwise go to he end of the queue
        {
            temp = temp->next;
        }
        temp->next = new_el; // and add it
    }
};

void tasting(Tasting_Queue *q_tasting, int nb_parts)
// This function is taking the tasting queue and a numeber of parts. It dequeue, (taste), the number of parts given
// We had to consider the number of parts as the number of taste slice instead of "parts" because we didn't knew in how many parts is the cake cutted
{
    if (nb_parts > 0)
    {
        if ((int)q_tasting->queue->cake->s_tastes->tastes->text[0] == 0) // If there's no more slice in a cake go to next 
        {
            Element_cake *to_free = q_tasting->queue;
            q_tasting->queue = q_tasting->queue->next;
            free(to_free);
            if (q_tasting->queue != NULL)
                tasting(q_tasting, nb_parts);
            else // If there's no next cake in the queue you are a big greedy haha
                printf("There's no more cakes, little greedy ????????????????????????\n");
        }
        else // Other wise TASTE = dequeue the tasting queue
        {
            Cake *cake = q_tasting->queue->cake;
            printf("You are tasting the cake %s and you just ate some %s\n", q_tasting->queue->cake->order->text, cake->s_tastes->tastes->text);
            Element_str *to_free = cake->s_tastes->tastes;
            cake->s_tastes->tastes = cake->s_tastes->tastes->next; // dequeue by remooving the first one 
            free(to_free);
            tasting(q_tasting, nb_parts - 1);
        }
    }
}

void free_element_str(Element_str *l_tastes)
{
    if (l_tastes != NULL)
    {
        free_element_str(l_tastes->next);
        free(l_tastes);
    }
}

void free_q_orders(Order_Queue *q_orders)
{
    free_element_str(q_orders->list);
    free(q_orders);
}

void free_order(Element_str *order)
{
    if (order != NULL)
    {
        free_order(order->next);
        free(order);
    }
}

void free_taste_stack(Taste_Stack *taste_stack)
{
    free_element_str(taste_stack->tastes);
    free(taste_stack);
}

void free_cake(Cake *cake)
{
    free_element_str(cake->order);
    free_taste_stack(cake->s_tastes);
    free(cake);
}

void free_element_cake(Element_cake *queue)
{ 
    if (queue != NULL)
    {
        free_cake(queue->cake);
        free_element_cake(queue->next);
    }
    free(queue);
}

void free_q_tasting(Tasting_Queue *q_tasting)
{
    if (q_tasting != NULL)
    {
        free_element_cake(q_tasting->queue);
        free(q_tasting);
    }
}

void pastry()
{
    Element_str *l_tastes; // mandatory line
    l_tastes = initialize_tastes();

    Order_Queue *q_orders; // mandatory line
    q_orders = malloc(sizeof(Order_Queue));
    q_orders->list = NULL;

    Tasting_Queue *q_tasting; // mandatory line
    q_tasting = malloc(sizeof(Tasting_Queue));
    q_tasting->queue = NULL;

    int n_cakes;
    do
    {
        printf("How many cakes do you want ?\n");
        scanf("%d", &n_cakes);
    } while (n_cakes <= 0);

    for (int i = 0; i < n_cakes; i++) // For all the cakes take the order
    {
        char *cmd;
        printf("Enter the first letter of tastes you want in the cake number %d !\n", i + 1);
        scanf("%s", cmd);
        while ((strlen(cmd) >= 50))
        {
            printf("Please control your hands !\n");
            scanf("%s", cmd);
        }

        pass_order(cmd, q_orders);
    }
    for (int i = 0; i < n_cakes; i++) // For all the cakes process the order
    {
        Cake *cake = malloc(sizeof(Cake));
        cake = create_cake(process_order(q_orders));

        build_Cake(cake, l_tastes);

        deliver(cake, q_tasting);
    }
    int hungry = 1;
    int parts = 1;
    while ((q_tasting->queue != NULL) && hungry) // While you are hungry && there's cakes TASTE
    {
        printf("How many parts do you want to taste ?\n");
        scanf("%d", &parts);
        tasting(q_tasting, parts);
        printf("Are you still hungry if yes enter 1, else enter 0 ?\n");
        scanf("%d", &hungry);
        while ((hungry != 0) && (hungry != 1))
        {
            printf("Please control your hands !\n");
            scanf("%d", &hungry);
        }
    }
    free_q_orders(q_orders);
    free_element_str(l_tastes);
    free_q_tasting(q_tasting);
}

int main()
{
    pastry();
    // If you have troubles to run the code, especially on Clion, please try to run it on VScode or replit.com
    return 0;
}
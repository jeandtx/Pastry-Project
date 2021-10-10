# Pastry-Project

Dernier: October 10, 2021 11:40 AM

### Welcome in our repo!!

## The project

[Pastry Project.pdf](https://s3.us-west-2.amazonaws.com/secure.notion-static.com/d224db01-dd4b-4091-a68d-0d0b0a5def3e/Pastry_Project.pdf?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Credential=AKIAT73L2G45O3KS52Y5%2F20211010%2Fus-west-2%2Fs3%2Faws4_request&X-Amz-Date=20211010T094148Z&X-Amz-Expires=86400&X-Amz-Signature=91a8caea591f90666ab1cceb72d0a4757ec84406cf10ea2f313e2367a0e66cb0&X-Amz-SignedHeaders=host&response-content-disposition=filename%20%3D%22Pastry%2520Project.pdf%22)

The project consist of a creating a virtual pastry 🥐 🥮 .

To do so we needed some structures

```c
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
```

The client is choosing an order from the menu and the order is send in a queue. Then cakes are build by the chef and send to a tasting queue. The client can now choose how many parts he wants to taste.

## Difficulties

- It was hard to deal with structures in structures and even queues and stacks inside

## What we learned

- We learned to deal with these structures
- To finish a project in a small time with a team of 4. It need a lot of organisation and skills

## Made by
[Amaury](https://github.com/heqqqqx), [Tristan](https://github.com/StritanS), [Clément](https://github.com/sodekai) and [Jean](https://github.com/jeandtx)
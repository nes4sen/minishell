#include <stdio.h>
#include <unistd.h>

typedef struct l
{
    int a;
    int b;
    struct l *next;
}list;

void *creat()
{
    void *p = malloc(size);
    if (!p)
    {
        return (NULL);
    }
    return (p);
}
void *fill_last(void *head)
{
    while (head->next)
    {
        head = head->next;
    }
    return (head);
}
void add_back(void **head, )
{

}

int main()
{

}
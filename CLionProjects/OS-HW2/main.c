#include <stdio.h>
#include "concurrent_list.h"

int main(int argc, const char** argv)
{
    printf("Hello, World!\n");

    list* mylist = create_list();
    print_list(mylist);

    insert_value(mylist, 4);
    remove_value(mylist, 4);

    /*
    insert_value(mylist, 2);
    printf("after 1,2!\n");
    print_list(mylist);
    insert_value(mylist, 1);
    insert_value(mylist, 3);
    printf("after 3,4!\n");
    print_list(mylist);
    count_list(mylist, 1);
    remove_value(mylist, 1);
    printf("after removing!\n");
    print_list(mylist);
    count_list(mylist, 1);
    remove_value(mylist, 2);
    remove_value(mylist, 3);
    remove_value(mylist, 4);
    print_list(mylist);
     */
}
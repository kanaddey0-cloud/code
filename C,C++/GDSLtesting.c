#include <stdio.h>

#include "gdsl_list.h"

int main(){

    printf("=========== CREATE ===========\n");

    GDSL_LIST* A = gdsl_list_create();

    GDSL_LIST* B = gdsl_list_create();



    printf("\n=========== INSERT ===========\n");

    gdsl_list_insert(A, 10, -1);
    gdsl_list_insert(A, 20, -1);
    gdsl_list_insert(A, 30, -1);
    gdsl_list_insert(A, 40, 1);

    gdsl_list_view(A, 1);




    printf("\n\n=========== SIZE ===========\n");

    printf("SIZE = %ld\n",
        gdsl_list_size(A));




    printf("\n=========== GET ===========\n");

    printf("INDEX 0 = %d\n",
        gdsl_list_get(A, 0));

    printf("INDEX -1 = %d\n",
        gdsl_list_get(A, -1));




    printf("\n=========== INDEX ===========\n");

    printf("VALUE 30 INDEX = %ld\n",
        gdsl_list_index(A, 30));




    printf("\n=========== MODIFY ===========\n");

    printf("OLD VALUE = %d\n",
        gdsl_list_modify(A, 99, 1));

    gdsl_list_view(A, 1);




    printf("\n\n=========== UPDATE ===========\n");

    printf("UPDATED INDEX = %ld\n",
        gdsl_list_update(A, 99, 77, 0));

    gdsl_list_view(A, 1);




    printf("\n\n=========== DROP ===========\n");

    printf("DROP INDEX = %ld\n",
        gdsl_list_drop(A, 20));

    gdsl_list_view(A, 1);




    printf("\n\n=========== REMOVE ===========\n");

    printf("REMOVED = %d\n",
        gdsl_list_remove(A, 1));

    gdsl_list_view(A, 1);




    printf("\n\n=========== REVERSE ===========\n");

    gdsl_list_reverse(A);

    gdsl_list_view(A, 1);




    printf("\n\n=========== COPY ===========\n");

    GDSL_LIST* C = gdsl_list_copy(A);

    gdsl_list_view(C, 1);




    printf("\n\n=========== ADD ===========\n");

    gdsl_list_insert(B, 100, -1);
    gdsl_list_insert(B, 200, -1);

    gdsl_list_add(A, B);

    gdsl_list_view(A, 1);




    printf("\n\n=========== ASSIGN ===========\n");

    gdsl_list_assign(B, A);

    gdsl_list_view(B, 1);




    printf("\n\n=========== ITERATOR ===========\n");

    GDSL_LIST_ITERATOR* it =
        gdsl_list_begin(A);

    GDSL_LIST_ITERATOR* end =
        gdsl_list_end(A);

    while(
        gdsl_iterator_not_equal(it, end)
    ){

        printf("%d ",
            gdsl_iterator_get(it));

        gdsl_iterator_next(it);
    }




    printf("\n\n=========== DESTROY ===========\n");

    gdsl_iterator_destroy(it);

    gdsl_iterator_destroy(end);

    gdsl_list_destroy(A);

    gdsl_list_destroy(B);

    gdsl_list_destroy(C);

    printf("DONE\n");

    return 0;
}
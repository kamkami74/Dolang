#include "include/linked_list.h"
#include <stdio.h>
#include <assert.h>

static void test_create(){
    printf("creating linked list: ");
    t_list* l = create_list();
    assert(l);
    free(l);
    printf("done\n");
}

static t_list* test_push(int n){
    assert( n > 0 );
    printf("pushing %d variable(s) to list: ",n);
    t_list *l = NULL;
    t_var v;
    for ( int i = 0; i < n; i ++ ){ 
        assign_var(&v,VAL_INT,&i);
        list_push(&l,v,creastr("H"));
    }
    t_list* tmp = l;
    for ( int i = 0; i < n; i ++ ){ 
        assert(tmp);
        tmp = tmp->next;
    }
    printf("done\n"); return l;
}

static void test_pop(t_list** l,int n){
    assert( n > 0 );
    printf("poping %d variable(s) to list: ",n);
    t_list* tmp = *l;
    for ( int i = 0; i < n; i ++ ){
        assert(tmp);
        tmp = tmp->next;
    }

    for ( int i = 0; i < n; i ++ ){
        list_pop(l);
    }

    printf("done\n");
}

static void test_free(t_list** l){
    printf("freeing up list: ");
    free_list(l);
    printf("done\n");

}

int main(void){
    test_create();
    t_list* l = test_push(100);
    test_pop(&l,100);
    test_free(&l);
}

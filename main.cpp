#include <iostream>
using namespace std;

// stack is represented using linked list
struct stack {
    int data;
    struct stack* next;
};

// initialize stack
void init_stack(struct stack** s) {*s = NULL;}

// push item to stack
void push(struct stack** s, int x) {
    struct stack* p = (struct stack*)malloc(sizeof(*p));

    if (p == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return;
    }

    p->data = x;
    p->next = *s;
    *s = p;
}

// remove item from stack
int pop(struct stack** s) {
    int x;
    struct stack* tmp;

    x = (*s)->data;
    tmp = *s;
    (*s) = (*s)->next;
    free(tmp);

    return x;
}

// find to top item
int top(struct stack* s) {
    return (s->data);
}

// print stack
void print_stack(struct stack* s) {
    while (s) {
        cout << s->data << " ";
        s = s->next;
    }
    cout << "\n";
}

// check if stack is empty
bool check_is_empty(struct stack* s) {
    if (s == NULL) {
        return true;
    }
    return false;
}

// insert item x in sorted way recursively
void sorted_insert(struct stack** s, int x) {
    // either stack is empty or newly inserted
    // item is greater than top
    if (check_is_empty(*s) or x > top(*s)) {
        push(s, x);
        return;
    }

    // remove top item
    int tmp = pop(s);
    sorted_insert(s, x);

    // put back top item removed earlier
    push(s, tmp);
}

// sort stack
void sort_stack(struct stack** s) {
    if (!check_is_empty(*s)) {
        int x = pop(s); // remove top item

        sort_stack(s); // sort remaining stack

        sorted_insert(s, x); // push top item back in sorted stack
    }
}

int main() {
    struct stack* top;
    init_stack(&top);
    push(&top, 30);
    push(&top, -5);
    push(&top, 18);
    push(&top, 14);
    push(&top, -3);

    cout << "Stack elements before sorting:\n";
    print_stack(top);

    sort_stack(&top);
    cout << "\n";

    cout << "Stack elements after sorting:\n";
    print_stack(top);

    return 0;
}

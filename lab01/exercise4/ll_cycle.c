#include <stddef.h>
#include "ll_cycle.h"

int ll_has_cycle(node *head) {
    /* TODO: Implement ll_has_cycle */
    if (head == NULL) return 0;
    node *slow_ptr = head;
    node *fast_ptr = head;
    do {
        if ((fast_ptr = fast_ptr->next) == NULL)
            return 0;
        else if ((fast_ptr = fast_ptr->next) == NULL)
            return 0;
        else
            slow_ptr = slow_ptr->next;
    } while (fast_ptr != slow_ptr);
    return 1;
}

#include <stdio.h>
#include "cqueue.h"

void main()
{
    cqueue_t q = CQUEUE_INITIALIZER(10);
    printf("full=%d empty=%d len=%d free=%d\n",
            CQUEUE_IS_FULL(&q), CQUEUE_IS_EMPTY(&q),
            CQUEUE_LEN(&q), CQUEUE_NFREE(&q));
}

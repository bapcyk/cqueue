/**
 * @file cqueue.h
 * @defgroup cqueue Circular queue support
 * @{
 * @brief Fast circular queue support
 */
#ifndef _CQUEUE_H
#define _CQUEUE_H

/** It's possible to use another (wrapper) structure or structure with another
name for cqueue implementation. CQUEUE_STRUCT_IMPL should be defined as name
of such structure in this case before to include cqueue.h. This structure
must have members:
 - unsigned integer "size"
 - integer "rpos"
 - integer "wpos"
 - integer "rwrap"
 - integer "wwrap"
 - any other custom fields
*/
#ifdef CQUEUE_STRUCT_IMPL
typedef CQUEUE_STRUCT_IMPL cqueue_t;
#else
/// Circular queue
typedef struct cqueue_t {
    /// Capacity of queue
    unsigned int size;
    /// Reader position
    int rpos;
    /// Writer position
    int wpos;
    /// Reader wrapping flag
    unsigned char rwrap;
    /// Writer wrapping flag
    unsigned char wwrap;
} cqueue_t;

#endif

/** Initializer for circular queue structure instance. Additional args are
needs if separate implementation struct is used */
#define CQUEUE_INITIALIZER(SIZE, ...) { \
    .size = (SIZE), \
    .rpos = 0, \
    .wpos = 0, \
    .wwrap = 0, \
    .rwrap = 0, \
    __VA_ARGS__ }

/// Init. function for queue structure instance
#define CQUEUE_INIT(Q, SIZE) do { \
    (Q)->size = (SIZE); \
    (Q)->rpos = (Q)->wpos = 0; \
    (Q)->wwrap = (Q)->rwrap = 0; \
} while (0)

/// Reset circular queue into initial state
#define CQUEUE_RESET(Q) CQUEUE_INIT(Q, (Q)->size)

/// General position incrementing
#define CQUEUE_INCR(Q, PPOS, PWRAP) do { \
    *(PPOS) = *(PPOS) +1; \
    if (*(PPOS) == (Q)->size) { \
        *(PWRAP) ^= 1; \
        *(PPOS) = 0; \
    } \
} while (0)

/// Reader position (for user-side)
#define CQUEUE_RPOS(Q) ((Q)->rpos)

/// Writer position (for user-side)
#define CQUEUE_WPOS(Q) ((Q)->wpos)

/// Reader position incrementing
#define CQUEUE_INCR_R(Q) do { \
    CQUEUE_INCR(Q, &((Q)->rpos), &((Q)->rwrap)); \
} while (0)

/// Writer position incrementing
#define CQUEUE_INCR_W(Q) do { \
    CQUEUE_INCR(Q, &((Q)->wpos), &((Q)->wwrap)); \
} while (0)

/// Test of circular queue fullness
#define CQUEUE_IS_FULL(Q) \
    ((Q)->wpos == (Q)->rpos && (Q)->rwrap != (Q)->wwrap)

/// Test of circular queue emptiness
#define CQUEUE_IS_EMPTY(Q) \
    ((Q)->wpos == (Q)->rpos && (Q)->rwrap == (Q)->wwrap)

/// Number of free slots in circular queue
#define CQUEUE_NFREE(Q) \
    ((Q)->rwrap == (Q)->wwrap ? \
     ((Q)->size - (Q)->wpos + (Q)->rpos) : \
     ((Q)->rpos - (Q)->wpos))

/// Number of used slots in circular queue
#define CQUEUE_LEN(Q) \
    ((Q)->rwrap != (Q)->wwrap ? \
     ((Q)->size - (Q)->rpos + (Q)->wpos) : \
     ((Q)->wpos - (Q)->rpos))

#endif
/// @}

#pragma once

#include "subjects.h"

#include <pthread.h>

enum data_type {
    DTYPE_INVALID = 0,
    DTYPE_INT,
    DTYPE_UINT64,
    DTYPE_FLOAT,
    DTYPE_GROUP,
};

struct __subject_group {
    struct __subject **subjects;
    uint8_t            count;
};

struct __subject {
    void (*observers[MAX_OBSERVERS])(struct __subject *, void *);
    void *user_data[MAX_OBSERVERS];
    union {
        volatile int32_t        int_val;
        volatile uint64_t       uint64_val;
        volatile float          float_val;
        struct __subject_group *group;
    };
    enum data_type  dtype;
    pthread_mutex_t mutex_set;
    pthread_mutex_t mutex_subscribe;
};

struct __observer {
    struct __subject *subj;
    uint8_t           cb_id;
};

bool subject_set_int_no_notify(subject_t subj, int32_t val);
void subject_notify(subject_t subj);

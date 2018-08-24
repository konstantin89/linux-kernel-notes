#include <linux/list.h>
#include <linux/kthread.h>

#define FL_SUCCESS_CODE 0
#define FL_ERROR_CODE 1

typedef struct ListEntry
{
    //TID of the thread that added this entry into the list.
    int producer_tid;

    struct list_head list; 
} ListEntry;

typedef struct ThreadArr
{
    size_t size;
    struct task_struct** arr;

} ThreadArr;

int init_fill_list(void);

int clean_fill_list(void);

int start(int thread_count);

int print_list(void);

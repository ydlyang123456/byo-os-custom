/* BYO-OS - Kernel Heap (Simple Block Allocator) */
#include <kernel.h>

#define HEAP_START 0x400000
#define HEAP_SIZE  (4 * 1024 * 1024)
#define HEAP_END   (HEAP_START + HEAP_SIZE)

typedef struct block {
    uint32_t size;
    int free;
    struct block* next;
} block_t;

static block_t* heap_list = NULL;
static uint32_t heap_used = 0;
static uint32_t heap_allocated = 0;

void heap_init(void) {
    heap_list = (block_t*)HEAP_START;
    heap_list->size = HEAP_SIZE - sizeof(block_t);
    heap_list->free = 1;
    heap_list->next = NULL;
    heap_used = sizeof(block_t);
    heap_allocated = 0;
}

static block_t* find_free_block(uint32_t size) {
    block_t* current = heap_list;
    while (current) {
        if (current->free && current->size >= size) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void* kmalloc(size_t size) {
    if (size == 0) return NULL;
    uint32_t aligned = (size + 3) & ~3;

    block_t* block = find_free_block(aligned);
    if (!block) return NULL;

    if (block->size >= aligned + sizeof(block_t) + 16) {
        block_t* new_block = (block_t*)((uint32_t)block + sizeof(block_t) + aligned);
        new_block->size = block->size - aligned - sizeof(block_t);
        new_block->free = 1;
        new_block->next = block->next;
        block->next = new_block;
        block->size = aligned;
    }

    block->free = 0;
    heap_allocated += block->size;
    return (void*)((uint32_t)block + sizeof(block_t));
}

void kfree(void* ptr) {
    if (!ptr) return;

    block_t* block = (block_t*)((uint32_t)ptr - sizeof(block_t));
    block->free = 1;
    heap_allocated -= block->size;

    block_t* current = heap_list;
    while (current) {
        if (current->free && current->next && current->next->free) {
            current->size += sizeof(block_t) + current->next->size;
            current->next = current->next->next;
        } else {
            current = current->next;
        }
    }
}

uint32_t heap_get_used(void) {
    return heap_allocated;
}
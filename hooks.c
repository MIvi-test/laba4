#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

static void *(*real_malloc)(size_t) = NULL;
static void *(*real_calloc)(size_t, size_t) = NULL;
static void *(*real_realloc)(void *, size_t) = NULL;
static void (*real_free)(void *) = NULL;

size_t USE_MALLOC = 0;
size_t USE_REALLOC = 0;
size_t USE_CALLOC = 0;
size_t USE_FREE = 0;

// Временный буфер для calloc, чтобы избежать падения при инициализации dlsym
static char calloc_buffer[4096];
static int dlsym_in_progress = 1;

__attribute__((constructor)) void init(void) {
    dlsym_in_progress = 1;
    real_malloc = dlsym(RTLD_NEXT, "malloc");
    real_realloc = dlsym(RTLD_NEXT, "realloc");
    real_calloc = dlsym(RTLD_NEXT, "calloc");
    real_free = dlsym(RTLD_NEXT, "free");
    dlsym_in_progress = 0;
}

void *malloc(size_t size) {
    if (!real_malloc) init();
    USE_MALLOC++;
    return real_malloc(size);
}

void *realloc(void *old_ptr, size_t new_size) {
    if (!real_realloc) init();
    USE_REALLOC++;
    return real_realloc(old_ptr, new_size);
}

void *calloc(size_t nmemb, size_t size) {
    // Защита от рекурсии dlsym
    if (dlsym_in_progress || !real_calloc) {
        return calloc_buffer; // Возвращаем статическую память на время инициализации
    }
    USE_CALLOC++;
    return real_calloc(nmemb, size);
}

void free(void *ptr) {
    if (ptr == (void*)calloc_buffer) return;
    if (!real_free) init();
    USE_FREE++;
    real_free(ptr);
}

__attribute__((destructor)) void writefile(void) {
    FILE *f = fopen("memstat.txt", "w");
    if (!f) {
        fprintf(stderr, "malloc: %zu\n", USE_MALLOC);
        return;
    }
    fprintf(f, "malloc: %zu\nrealloc: %zu\ncalloc: %zu\nfree: %zu\n", 
            USE_MALLOC-2, USE_REALLOC, USE_CALLOC, USE_FREE);
    fclose(f);
}

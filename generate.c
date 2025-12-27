#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>  // For memcpy

#define GENERATIONS 1000000
#define DIMENSIONS 128

typedef float Vector[DIMENSIONS];

void generate(Vector vectors[GENERATIONS]) {
    srand((unsigned)time(NULL));
    
    const clock_t generation_start = clock();
    for (size_t i = 0; i < GENERATIONS; i++) {
        for (size_t j = 0; j < DIMENSIONS; j++) {
            vectors[i][j] = (float)rand() / RAND_MAX;  // Proper float values
        }
    }
    clock_t generation_end = clock();
    
    printf("Generation Run: %f ms\n", 
           ((double)(generation_end - generation_start)) / CLOCKS_PER_SEC * 1000);
}

int main() {
    const clock_t start = clock();
    
    // Allocate on heap to avoid stack overflow
    Vector *vectors = malloc(GENERATIONS * sizeof(Vector));
    if (!vectors) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
	generate(vectors);
    
    free(vectors);
    
    clock_t script_end = clock();
    printf("Full Script Run: %f ms\n", 
           ((double)(script_end - start)) / CLOCKS_PER_SEC * 1000);
    
    return 0;
}

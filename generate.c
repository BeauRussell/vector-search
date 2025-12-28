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

float calculate_dot(Vector v1, Vector v2, size_t size) {
	float dot = 0.0f;
	for (int i = 0; i < size; i++) {
		dot += v1[i] * v2[i];
	}
	return dot;
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
    
	clock_t start_manual_dot = clock();
	volatile float total = 0.0f;

	for (int i = 0; i < GENERATIONS - 1; i++) {
		total += calculate_dot(vectors[i], vectors[i + 1], DIMENSIONS);
	}

    clock_t manual_dot_end = clock();
    printf("Calculation Run: %f ms\n", 
           ((double)(manual_dot_end - start_manual_dot)) / CLOCKS_PER_SEC * 1000);

    free(vectors);
    
    clock_t script_end = clock();
    printf("Full Script Run: %f ms\n", 
           ((double)(script_end - start)) / CLOCKS_PER_SEC * 1000);
    
    return 0;
}

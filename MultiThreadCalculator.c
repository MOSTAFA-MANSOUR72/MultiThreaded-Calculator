#define HAVE_STRUCT_TIMESPEC
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

const int MAX_THREADS = 64;
int thread_count;
int n;
double* numbers;
double* factorial_results; // Array to store factorial results
double result;
pthread_mutex_t mutex;

void Usage(const char* prog_name);
void Read_numbers(const char* prompt, double numbers[], int n);
void Print_result(const char* title, double result);
void* Pth_add(void* rank);
void* Pth_multiply(void* rank);
void* Calculate_average(void* rank);
void* Pth_factorial(void* rank);
void Add_number(void);

int main(int argc, char* argv[]) {
    long thread;
    pthread_t* thread_handles;

    if (argc != 2) Usage(argv[0]);

    thread_count = atoi(argv[1]);
    if (thread_count <= 0 || thread_count > MAX_THREADS)
        Usage(argv[0]);

    pthread_mutex_init(&mutex, NULL);
    thread_handles = (pthread_t*)malloc(thread_count * sizeof(pthread_t));

    printf("Enter the number of elements: ");
    if (scanf_s("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid number of elements.\n");
        exit(1);
    }

    numbers = (double*)malloc(n * sizeof(double));
    factorial_results = (double*)malloc(n * sizeof(double)); // Allocate memory for results

    Read_numbers("Enter the numbers", numbers, n);

    int operation;
    while (1) {
        // User input for choosing operation
        printf("\nChoose operation:\n");
        printf("1. Add Numbers\n");
        printf("2. Multiply Numbers\n");
        printf("3. Calculate Factorial of Numbers\n");
        printf("4. Calculate Average\n");
        printf("5. Add a Number\n");
        printf("6. Exit\n");
        printf("Choose operation (1-6): ");

        if (scanf_s("%d", &operation) != 1) {
            fprintf(stderr, "Invalid operation.\n");
            continue;
        }

        // Perform chosen operation
        if (operation == 1) {
            result = 0.0; // Reset result for addition
            for (thread = 0; thread < thread_count; thread++) {
                pthread_create(&thread_handles[thread], NULL, Pth_add, (void*)thread);
            }
            for (thread = 0; thread < thread_count; thread++) {
                pthread_join(thread_handles[thread], NULL);
            }
            Print_result("The sum is", result);
        }
        else if (operation == 2) {
            result = 1.0; // Reset result for multiplication
            for (thread = 0; thread < thread_count; thread++) {
                pthread_create(&thread_handles[thread], NULL, Pth_multiply, (void*)thread);
            }
            for (thread = 0; thread < thread_count; thread++) {
                pthread_join(thread_handles[thread], NULL);
            }
            Print_result("The product is", result);
        }
        else if (operation == 3) {
            // Parallel factorial computation
            for (long thread = 0; thread < thread_count; thread++) {
                pthread_create(&thread_handles[thread], NULL, Pth_factorial, (void*)thread);
            }
            for (long thread = 0; thread < thread_count; thread++) {
                pthread_join(thread_handles[thread], NULL);
            }

            // Print factorial results
            for (int i = 0; i < n; i++) {
                printf("%.0f! = %.0f\n", numbers[i], factorial_results[i]);
            }
        }
        else if (operation == 4) {
            result = 0.0; // Reset result for summing
            for (thread = 0; thread < thread_count; thread++) {
                pthread_create(&thread_handles[thread], NULL, Calculate_average, (void*)thread);
            }
            for (thread = 0; thread < thread_count; thread++) {
                pthread_join(thread_handles[thread], NULL);
            }
            double average = result / n;
            printf("The average is: %.2f\n", average);
        }
        else if (operation == 5) {
            Add_number(); // Add a number to the list
            printf("Number added. The list now has %d numbers.\n", n);
        }
        else if (operation == 6) {
            printf("Exiting the program...\n");
            break;
        }
        else {
            printf("Invalid operation choice.\n");
        }
    }

    free(numbers);
    free(factorial_results);
    free(thread_handles);
    pthread_mutex_destroy(&mutex);

    return 0;
}

// Prints usage instructions for the program
void Usage(const char* prog_name) {
    fprintf(stderr, "usage: %s <thread_count>\n", prog_name);
    exit(0);
}

// Reads a list of numbers from user input
void Read_numbers(const char* prompt, double numbers[], int n) {
    printf("%s\n", prompt);
    for (int i = 0; i < n; i++) {
        printf("Number %d: ", i + 1);
        if (scanf_s("%lf", &numbers[i]) != 1) {
            fprintf(stderr, "Invalid input.\n");
            exit(1);
        }
    }
}

// Prints the result of an operation
void Print_result(const char* title, double result) {
    printf("%s: %.2f\n", title, result);
}

// Adds numbers in parallel (each thread adds a portion of the numbers)
void* Pth_add(void* rank) {
    long my_rank = (long)rank;
    int local_n = n / thread_count;
    int first_index = my_rank * local_n;
    int last_index = (my_rank == thread_count - 1) ? n - 1 : first_index + local_n - 1;

    double local_sum = 0.0;
    for (int i = first_index; i <= last_index; i++) {
        local_sum += numbers[i];
    }

    pthread_mutex_lock(&mutex);
    result += local_sum;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

// Multiplies numbers in parallel (each thread multiplies a portion of the numbers)
void* Pth_multiply(void* rank) {
    long my_rank = (long)rank;
    int local_n = n / thread_count;
    int first_index = my_rank * local_n;
    int last_index = (my_rank == thread_count - 1) ? n - 1 : first_index + local_n - 1;

    double local_product = 1.0;
    for (int i = first_index; i <= last_index; i++) {
        local_product *= numbers[i];
    }

    pthread_mutex_lock(&mutex);
    result *= local_product;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

// Calculates the average of numbers in parallel (each thread processes a portion of the numbers)
void* Calculate_average(void* rank) {
    long my_rank = (long)rank;
    int local_n = n / thread_count;
    int first_index = my_rank * local_n;
    int last_index = (my_rank == thread_count - 1) ? n - 1 : first_index + local_n - 1;

    double local_sum = 0.0;
    for (int i = first_index; i <= last_index; i++) {
        local_sum += numbers[i];
    }

    pthread_mutex_lock(&mutex);
    result += local_sum;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

// Calculates the factorial for numbers in parallel (each thread calculates factorial for a portion)
void* Pth_factorial(void* rank) {
    long my_rank = (long)rank;
    int local_n = n / thread_count;
    int first_index = my_rank * local_n;
    int last_index = (my_rank == thread_count - 1) ? n - 1 : first_index + local_n - 1;

    for (int i = first_index; i <= last_index; i++) {
        int num = (int)numbers[i];
        double fact = 1.0;

        for (int j = 1; j <= num; j++) {
            fact *= j;
        }

        pthread_mutex_lock(&mutex);
        factorial_results[i] = fact; // Store the result in the shared array
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

// Adds a new number to the list of numbers
void Add_number(void) {
    double new_number;
    printf("Enter the new number: ");
    if (scanf_s("%lf", &new_number) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return;
    }
    n++;
    double* temp = (double*)realloc(numbers, n * sizeof(double));
    double* temp_results = (double*)realloc(factorial_results, n * sizeof(double));

    if (temp == NULL || temp_results == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }

    numbers = temp;
    factorial_results = temp_results;
    numbers[n - 1] = new_number;
}

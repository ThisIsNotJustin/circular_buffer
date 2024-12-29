#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Buffer {
    int32_t *data;
    u_int32_t capacity;
    u_int32_t head;
    u_int32_t tail;
    u_int32_t size;
} Buffer_t;

Buffer_t* buffer_create(u_int32_t capacity);
u_int32_t buffer_enqueue(Buffer_t* b, u_int32_t item);
u_int32_t buffer_dequeue(Buffer_t* b);
u_int32_t buffer_empty(Buffer_t* b);
u_int32_t buffer_full(Buffer_t* b);
void buffer_free(Buffer_t* b);
void buffer_reset(Buffer_t* b);
void print_buffer(Buffer_t* b);

void display_menu();
u_int32_t get_input();

Buffer_t* buffer_create(u_int32_t capacity) {
    Buffer_t* circular_buffer = (Buffer_t*) malloc(sizeof(Buffer_t));
    if (circular_buffer == NULL) {
        return NULL;
    }

    circular_buffer->data = (int32_t*) malloc(capacity * sizeof(int32_t));
    if (circular_buffer->data == NULL) {
        free(circular_buffer);
        return NULL;
    }

    circular_buffer->capacity = capacity;
    circular_buffer->head = 0;
    circular_buffer->tail = 0;
    circular_buffer->size = 0;

    return circular_buffer;
}

u_int32_t buffer_enqueue(Buffer_t* b, u_int32_t item) {
    if (b == NULL || b->data == NULL || buffer_full(b) == 1) {
        return -1;
    }
    
    b->data[b->tail] = item;
    b->tail = (b->tail + 1) % b->capacity;
    b->size++;

    return 0;
}

u_int32_t buffer_dequeue(Buffer_t* b) {
    if (b == NULL || b->data == NULL || buffer_empty(b) == 1) {
        return -1;
    }

    u_int32_t item = b->data[b->head];
    b->data[b->head] = 0;
    b->head = (b->head + 1) % b->capacity;
    b->size--;

    return item;
}

u_int32_t buffer_empty(Buffer_t* b) {
    return (b != NULL && b->size == 0);
}

u_int32_t buffer_full(Buffer_t* b) {
    return (b != NULL && (b->size == b->capacity));
}

u_int32_t buffer_size(Buffer_t* b) {
    return (b != NULL) ? b->size : -1;
}

void buffer_free(Buffer_t* b) {
    if (b) {
        free(b->data);
        free(b);
    }
}

void buffer_reset(Buffer_t* b) {
    if (b && b->data) {
        memset(b->data, 0, b->capacity * sizeof(int32_t));
        b->head = 0;
        b->tail = 0;
        b->size = 0;
    }
}

int main() {
    Buffer_t* circular_buffer = buffer_create(8);
    int selected = 1;
    while (selected != 4) {
        // display menu
        display_menu();

        // get input
        selected = get_input();

        // 1 - enqueuing
        if (selected == 1) {
            printf("What number would you like to insert? \n\n");
            u_int32_t input = get_input();
            if (buffer_enqueue(circular_buffer, input) == -1) {
                printf("Buffer likely full! \n");
                getchar();
                continue;
            }

            // print_buffer(circular_buffer); visualize buffer
        // 2 - dequeuing
        } else if (selected == 2) {
            printf("Dequeuing from buffer: \n\n");
            u_int32_t item = buffer_dequeue(circular_buffer);

            if (item == -1) {
                printf("Buffer likely empty! \n");
                getchar();
                continue;
            } else {
                printf("Dequeued value: %d\n", item);
            }
        // 3 - resetting buffer
        } else if (selected == 3) {
            printf("Resetting buffer: \n\n");
            buffer_reset(circular_buffer);
        // 4 - quit program
        } else if (selected == 4) {
            printf("Exiting Circular Buffer Program \n");
            break;
        } else {
            printf("Invalid Input, Insert number between (1-4) \n");
        }
    }

    buffer_free(circular_buffer);
    return 0;
}

void display_menu() {
	printf("\n<----- CIRCULAR BUFFER ----->\n\n");
	printf("     1    Enqueue  Value\n");
	printf("     2    Dequeue Value\n");
	printf("     3    Reset Buffer\n");
    printf("     4    End Program\n");
	printf("\n<--------------------------->\n\n    ");
}

u_int32_t get_input() {
    u_int32_t input;
    while (scanf("%u", &input) != 1) {
        printf("Invalid input. \n");
        while (getchar() != '\n');
    }

    return input;
}

void print_buffer(Buffer_t* b) {
    printf("Buffer state: ");
    for (u_int32_t i = 0; i < b->capacity; i++) {
        if (i == b->head) printf("[H] ");
        if (i == b->tail) printf("[T] ");
        printf("%d ", b->data[i]);
    }
    printf("\n");
}
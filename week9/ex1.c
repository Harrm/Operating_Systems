#include <stdio.h>
#include <stdbool.h>

typedef struct {

    bool ref;
    unsigned age;
    size_t page_address;

} frame_t;

#define LEFTMOST_ONE (1u << (sizeof(unsigned) * 8 - 1))

void print_frame(int i, frame_t frame) {
    printf("|  %d  |  %d  | %#04x | %010lx |\n", i, frame.ref, frame.age, frame.page_address);
}

void update_age(frame_t* frames, size_t n) {
    for(size_t i = 0; i < n; i++) {
        frame_t* f = &frames[i];
        f->age >>= 1;
        if(f->ref) {
            f->age += LEFTMOST_ONE;
        }
        f->ref = 0;
    }
}



frame_t* search_for_page(frame_t* frames, size_t n, size_t address) {
    for(int i = 0; i < n; i++) {
        if(frames[i].page_address == address) {
            return &frames[i];
        }
    }
    return NULL;
}



size_t evict(frame_t* frames, size_t n) {
    unsigned min = LEFTMOST_ONE;
    size_t idx = 0;
    for(int i = 0; i < n; i++) {
        if(frames[i].age < min) {
            idx = i;
            min = frames[i].age;
        }
    }
    return idx;
}



int main(int argc, char** argv) {

    size_t frames_num = 0;
    if(argc > 1) {
        sscanf(argv[1], "%lu", &frames_num);
    } else {
        printf("Missing second command line argument: number of frames!\n");
    }
    char* filename = "Lab 09 input.txt";
    if(argc == 3) {
        filename = argv[2];
    }

    frame_t frames[frames_num];
    for(int i = 0; i < frames_num; i++) {
        frames[i].page_address = 0xDEADBEEF;
        frames[i].age = 0;
        frames[i].ref = 0;
    }

    FILE* f = fopen(filename, "r");
    if(!f) {
        perror("Error opening input file\n");
        return -1;
    }

    size_t page_address = 0;

    unsigned faults_num = 0;
    unsigned ref_num = 0;

    while(fscanf(f, "%lu", &page_address) != EOF) {
        frame_t* frame = search_for_page(frames, frames_num, page_address);
        if(frame != NULL) {

            frame->ref = 1;

        } else {
            size_t i = evict(frames, frames_num);
            faults_num++;
            frame_t new;
            new.page_address = page_address;
            new.ref = 1;
            new.age = 0;
            frames[i] = new;

        }
        update_age(frames, frames_num);

        ref_num++;
    }

    printf("References: %d\nFaults: %d\nRatio: %f\n", ref_num, faults_num, (double)(ref_num - faults_num) / faults_num);

    return 0;
}
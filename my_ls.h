#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

struct Node {
    char data[132];
    struct Node* next;
};

char* my_strcpy(char* ptr, char* ptr_1) {
    int index = 0;

    while (ptr_1[index] != '\0') {
        ptr[index] = ptr_1[index];
        index += 1;
    }
    ptr[index] = '\0';

    return ptr;
}

struct Node* Read_dir(struct Node* head) {
    struct dirent *de;
    DIR *dr;

    dr = opendir(".");
    if (dr == NULL) {
        printf("Could not open directory.");
        return 0;
    }

    struct Node* current;
    current = (struct Node*)malloc(sizeof(struct Node));

    int index = 1;
    while ((de = readdir(dr)) != NULL) {
        if (index == 1) {
            my_strcpy(head->data, de->d_name);

            //strcpy(head->data, de->d_name);
            head->next = current;
            index += 1;
        }
        else {
            struct Node* next;
            next = (struct Node*)malloc(sizeof(struct Node));
            my_strcpy(current->data, de->d_name);

            //strcpy(current->data, de->d_name);
            current->next = next;
            current = next;
        }
    }
    closedir(dr);

    return head;
}

int my_strlen_linked_list(struct Node* head);

struct Node* Read_dir_directory(struct Node* head, char* argv) {
    struct dirent *de;
    DIR *dr;

    dr = opendir(argv);
    if (dr == NULL) {
        printf("Could not open directory.");
        return 0;
    }

    struct Node* current = NULL;
    current = (struct Node*)malloc(sizeof(struct Node));

    int index = 1;
    while ((de = readdir(dr)) != NULL) {
        if (index == 1) {
            my_strcpy(head->data, de->d_name);

            head->next = current;
            index += 1;
        }
        else {
            struct Node* next = NULL;
            next = (struct Node*)malloc(sizeof(struct Node));
            
            my_strcpy(current->data, de->d_name);
            current->next = next;
            current = next;
        }
    }
    closedir(dr);
    
    struct Node* prev = NULL;
    int length = my_strlen_linked_list(head);
    prev = head;
    int count = 0;
    while (prev != NULL) {
        if (count == length - 1) {
            prev->next = NULL;
            break;
        }
        count += 1;
        prev = prev->next;
    }

    return head;
}

int my_strlen(char *array) {
    int length = 0;
    while (*array != '\0') {
        length += 1;
        array ++;
    }
    return length;
}

int my_strlen_linked_list(struct Node* head) {
    int length = 0;
    while (head != NULL) {
        length += 1;
        head = head->next;
    }
    length = length - 1;
    return length;
}

void print_linked_list(struct Node* head) {
    while (head != NULL) {
            printf("%s  ", head->data);
            head = head->next;
        }
        printf("\n");
}

void print_linked_list_dir(struct Node* head) {
    while (head != NULL) {
        if (*(head->data) != '.') {
            printf("%s  ", head->data);
        }
        head = head->next;
    }
    printf("\n");
}

void print_linked_list_dir_tmp(struct Node* head) {
    while (head != NULL) {
        if (*(head->data) != '.') {
            printf("%s\n", head->data);
        }
        head = head->next;
    }
    printf("\n");
}

int my_strcmp(char* ptr, char* ptr_1) {
    int count = 0;
    int length_ptr = my_strlen(ptr);
    int length_ptr_1 = my_strlen(ptr_1);

    int index = 0;
    if (length_ptr == length_ptr_1) {
        while (ptr[index] != '\0') {
            if (ptr[index] == ptr_1[index]) {
                count += 1;
            }
            index += 1;
        }
        if (count == length_ptr) {
            return count;
        } 
    }
    
    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include "my_ls.h"
#include <sys/stat.h>

struct Node* swap(struct Node* ptr, struct Node* ptr_2) {
    struct Node* temp = ptr_2->next;
    ptr_2->next = ptr;
    ptr->next = temp;

    return ptr_2;
}

struct Node* my_ls(struct Node** head) {
    struct Node** h = NULL;
    Read_dir(*head);
    h = head;

    int length = my_strlen_linked_list(*head);
    int index, index_1, swapped;

    for (index = 0; index <= length; index ++) {
        h = head;
        swapped = 0;
        for (index_1 = 0; index_1 < length - index - 1; index_1 ++) {
            struct Node* ptr = *h;
            struct Node* ptr_1 = ptr->next;

            if (*(ptr->data) > *(ptr_1->data)) {
                *h = swap(ptr, ptr_1);
                swapped = 1;
            }
            else if (*(ptr->data) == *(ptr_1->data)) {
                int length_ptr = my_strlen(ptr->data);
                int length_ptr_1 = my_strlen(ptr_1->data);

                int index_ptr = 0;
                int count = 0;
                while (index_ptr < length_ptr && index_ptr < length_ptr_1) {
                    if (ptr->data[index_ptr] > ptr_1->data[index_ptr]) {
                        *h = swap(ptr, ptr_1);
                        swapped = 1;
                        break;
                    }
                    else if (ptr->data[index_ptr] == ptr_1->data[index_ptr]) {
                        count += 1;
                    }
                    index_ptr += 1;
                }
                if (count == length_ptr_1 && length_ptr > length_ptr_1) {
                    *h = swap(ptr, ptr_1);
                    swapped = 1;
                }
            }
            h = &(*h)->next;
        }
        if (swapped == 0) {
            break;
        }
    }
    
    return *head;
}

struct Node* my_ls_t(struct Node** head) {
    struct Node** h = NULL;
    Read_dir(*head);
    struct stat buf;
    struct stat buf_1;
    
    int length = my_strlen_linked_list(*head);
    int index, index_1, swapped;

    for (index = 0; index < length; index ++) {
        h = head;
        swapped = 0;
        for (index_1 = 0; index_1 < length - index - 1; index_1 ++) {
            struct Node* ptr = *h;
            struct Node* ptr_1 = ptr->next;

            stat(ptr->data, &buf);
            stat(ptr_1->data, &buf_1);
            if (buf.st_mtim.tv_sec < buf_1.st_mtim.tv_sec) {
                *h = swap(ptr, ptr_1);
                swapped += 1;
            }
            else if (buf.st_mtim.tv_sec == buf_1.st_mtim.tv_sec) {
                if (*(ptr->data) == '.' && my_strlen(ptr->data) == 1) {
                    *h = swap(ptr, ptr_1);
                    swapped += 1;
                }
            }
            h = &(*h)->next;
        }
        if (swapped == 0) {
            break;
        }
    }

    return *head;
}

struct Node* my_ls_dir(struct Node** head, char* argv) {
    struct Node** h = NULL;
    Read_dir_directory(*head, argv);
    h = head;

    int length = my_strlen_linked_list(*head);
    int index, index_1, swapped;

    for (index = 0; index <= length; index ++) {
        h = head;
        swapped = 0;
        for (index_1 = 0; index_1 < length - index - 1; index_1 ++) {
            struct Node* ptr = *h;
            struct Node* ptr_1 = ptr->next;

            if (*(ptr->data) > *(ptr_1->data)) {
                *h = swap(ptr, ptr_1);
                swapped = 1;
            }
            else if (*(ptr->data) == *(ptr_1->data)) {
                int length_ptr = my_strlen(ptr->data);
                int length_ptr_1 = my_strlen(ptr_1->data);

                int index_ptr = 0;
                int count = 0;
                while (index_ptr < length_ptr && index_ptr < length_ptr_1) {
                    if (ptr->data[index_ptr] > ptr_1->data[index_ptr]) {
                        *h = swap(ptr, ptr_1);
                        swapped = 1;
                        break;
                    }
                    else if (ptr->data[index_ptr] == ptr_1->data[index_ptr]) {
                        count += 1;
                    }
                    index_ptr += 1;
                }
                if (count == length_ptr_1 && length_ptr > length_ptr_1) {
                    *h = swap(ptr, ptr_1);
                    swapped = 1;
                }
            }
            h = &(*h)->next;
        }
        if (swapped == 0) {
            break;
        }
    }

    return *head;
}

void print_my_ls_dir(struct Node* head, int argc, char* argv[]) {
    int count = 0;
    int count_argc = 1;
    int index_argv;
    struct Node* head_new = NULL;
    head_new = (struct Node*)malloc(sizeof(struct Node));
    
    while (head != NULL) {
        for (index_argv = 1; index_argv < argc; index_argv ++) {
            count = my_strcmp(argv[index_argv], head->data);
            if (count > 0) {
                if (argc > 2) {
                    printf("%s:\n", argv[index_argv]);
                }
                my_ls_dir(&head_new, argv[index_argv]);
                print_linked_list_dir(head_new);
                free(head_new);
                count_argc += 1;
                if (count_argc != argc && argc > 2) {
                    printf("\n");
                }
                break;
            }
        }
        if (count_argc == argc) {
            break;
        }
        head = head->next;
    }
    if (count == 0) {
        printf("No such file or directory\n");
    }
}

int main(int argc, char* argv[]) {
    struct Node* head = NULL;
    head = (struct Node*)malloc(sizeof(struct Node));

    /* my_ls -a, my_ls -t */
    char ptr_a[2] = "-a";
    char ptr_t[2] = "-t";
    char ptr_at[3] = "-at";
    char ptr_ta[3] = "-ta";
    char tmp[5] = "/tmp/";

    // my_ls
    if (argc == 1) {
        my_ls(&head);
        print_linked_list_dir(head);
    }
    // my_ls .
    else if (argv[1][0] == '.') {
        my_ls(&head);
        print_linked_list_dir(head);
    }
    // my_ls -a
    else if (my_strlen(argv[1]) == 2 && argv[1][0] == ptr_a[0] && argv[1][1] == ptr_a[1]) {
        my_ls(&head);
        print_linked_list(head);    
    }
    // my_ls -t
    else if (argc == 2 && my_strlen(argv[1]) == 2 && argv[1][0] == ptr_t[0] && argv[1][1] == ptr_t[1]) {
        my_ls_t(&head);
        print_linked_list_dir(head);
    }
    // my_ls -at
    else if (my_strlen(argv[1]) == 3 && argv[1][0] == ptr_at[0] && argv[1][1] == ptr_at[1] && argv[1][2] == ptr_at[2]) {
        my_ls_t(&head);
        print_linked_list(head);
    }
    // my_ls -ta
    else if (my_strlen(argv[1]) == 3 && argv[1][0] == ptr_ta[0] && argv[1][1] == ptr_ta[1] && argv[1][2] == ptr_ta[2]) {
        my_ls_t(&head);
        print_linked_list(head);
    }
    // my_ls -t -a
    else if (argc == 3 && my_strlen(argv[1]) == 2 && argv[1][0] == ptr_t[0] && argv[1][1] == ptr_t[1] && my_strlen(argv[2]) == 2 && argv[2][0] == ptr_a[0] && argv[2][1] == ptr_a[1]) {
        my_ls_t(&head);
        print_linked_list(head);
    }
    // my_ls /tmp/
    else if (argv[1][0] == tmp[0] && argv[1][1] == tmp[1] && argv[1][2] == tmp[2] && argv[1][3] == tmp[3] && argv[1][4] == tmp[4]) {
        my_ls_dir(&head, argv[1]);
        print_linked_list_dir_tmp(head);
    }
    // my_ls directory, file
    else {
        my_ls(&head);
        print_my_ls_dir(head, argc, argv);
    }

    free(head);
    return 0;
}
 

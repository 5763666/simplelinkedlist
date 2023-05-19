#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode {
    element data;
    struct ListNode* next;
} ListNode;

void error(char* message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

ListNode* insertNode(ListNode* head, int value, int position) {
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    p->data = value;
    p->next = NULL;

    if (position == 0) {
        p->next = head;
        return p;
    }

    ListNode* current = head;
    int count = 0;

    while (current->next != NULL && count < position - 1) {
        current = current->next;
        count++;
    }

    p->next = current->next;
    current->next = p;

    return head;
}

ListNode* deleteNode(ListNode* head, int position) {
    if (head == NULL)
        return NULL;

    ListNode* tmp = head;

    if (position == 0) {
        head = head->next;
        free(tmp);
        return head;
    }

    ListNode* previous = NULL;
    int count = 0;

    while (tmp != NULL && count < position) {
        previous = tmp;
        tmp = tmp->next;
        count++;
    }

    if (tmp == NULL)
        return head;

    previous->next = tmp->next;
    free(tmp);

    return head;
}


void printList(ListNode* head) {
    ListNode* current = head;

    if (current == NULL) {
        printf("List is empty.\n");
        return;
    }

    printf("List: ");
    while (current != NULL) {
        printf("%d-> ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    ListNode* head = NULL;
    int menu, num, position, count = 0;

    while (1) {
        printf("\nMenu\n");
        printf("(1) Insert\n");
        printf("(2) Delete\n");
        printf("(3) Print\n");
        printf("(0) Exit\n");
        printf("Enter the menu: ");
        scanf_s("%d", &menu);

        switch (menu) {
        case 1:
            printf("Enter the number and position: ");
            scanf_s("%d %d", &num, &position);
            if (count < 0 && position > 0) {
                printf("List is empty. Insert at position 0..");
                position = 0;
            }
            head = insertNode(head, num, position);
            printf("Move along the link: %d\n", count);
            break;
        case 2:
            printf("Enter the position to delete: ");
            scanf_s("%d", &position);
            head = deleteNode(head, position);
            if (count == -1)
                printf("List is empty.\n");
            else
                printf("Move along the link: %d\n", count);
            break;
        case 3:
            printList(head);
            break;
        case 0:
            printf("Exit the Program\n");
            exit(0);
        default:
            printf("Invalid Menu. Please select again.\n");
        }
    }

    return 0;
}
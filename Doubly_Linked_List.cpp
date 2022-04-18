#include <iostream>

class Node {
public:
    Node *next = nullptr;
    Node *prev = nullptr;
    int ID;
    bool created = false;

public:
    void destruct() {
        created = false;
        next = nullptr;
        prev = nullptr;
    }

    void create() {
        printf("Enter ID: ");
        if (scanf("%d", &ID) != 1) {
            printf("Invalid ID. Try again\n");
            create();
        }
        created = true;
    }

    void view() {
        if (!created)
            printf("Node is empty. Try to create()\n");
        else
            printf("%d ", ID);
    }
};

class List {
    static Node *head;
    static int counter;

public:
    void add(Node *node) {
        if (!node->created) {
            printf("Node not created\n");
            return;
        }
        if (counter == 0)
            addToEmpty(node);
        else {
            Node *temp = findID(getID());
            if (temp == nullptr) {
                printf("No nodes with specified ID in the list\n");
                return;
            } else {
                insert(node, temp);
            }
        }
        counter++;
    }

    void view() {
        if (head == nullptr) {
            printf("List is empty\n");
            return;
        }
        Node *temp = head;
        printf("List: [");
        do {
            temp->view();
            if (temp->next != nullptr)
                temp = temp->next;
            else
                break;
        } while (true);
        printf("]\n");
    }

    void remove() {
        if (head == nullptr) {
            printf("List is already empty\n");
        } else {

            Node *temp = findID(getID());
            if (temp == nullptr) {
                printf("No element with this ID\n");
                return;
            }
            if (temp->prev != nullptr && temp->next == nullptr) {
                Node *pre = temp->prev;
                pre->next = nullptr;
                temp->destruct();
                counter--;
            }    ///lewo tak prawo nie
            else if (temp->prev != nullptr && temp->next != nullptr) {
                Node *pre = temp->prev;
                Node *nex = temp->next;
                pre->next = nex;
                nex->prev = pre;
                temp->destruct();
                counter--;
            }   ///lewo tak prawo tak
            else if (temp->prev == nullptr && temp->next != nullptr) {
                Node *nex = temp->next;
                head = nex;
                nex->prev = nullptr;
                temp->destruct();
                counter--;

            }  ///lewo nie prawo tak
            else if (temp->prev == nullptr && temp->next == nullptr) {
                head = nullptr;
                temp->destruct();
                counter = 0;
            }   ///lewo nie prawo nie
        }
    }

    void sort() {
        if (head == nullptr || counter == 1)
            return;
        Node *temp = head;
        int i = 0, j = 0, p;
        for (i = 0; i < counter; i++) {
            for (j = 0; j < counter - i - 1; j++) {
                Node *n1 = returnElement(j);
                Node *n2 = returnElement(j + 1);
                if (n1 == nullptr || n2 == nullptr)
                    printf("sorting error\n");
                if (n1->ID > n2->ID) {
                    swap(n1, n2);
                }
            }
        }
    }

private:
    void swap(Node *n1, Node *n2) {
        Node n1_p;
        n1_p.next = n1->next;
        n1_p.prev = n1->prev;

        Node n2_p;
        n2_p.next = n2->next;
        n2_p.prev = n2->prev;

        if (n1->prev == nullptr && n2->next != nullptr) {
            Node *temp = n2->next;
            temp->prev = n1;
            n2->next = n1;
            n2->prev = nullptr;
            head = n2;
            n1->prev = n2;
            n1->next = temp;
        } else if (n1->prev != nullptr && n2->next == nullptr) {
            Node *temp = n1->prev;
            temp->next = n2;
            n2->prev = temp;
            n2->next = n1;
            n1->next = nullptr;
            n1->prev = n2;
        } else if (n1->prev != nullptr && n2->next != nullptr) {
            Node *temp1 = n1->prev;
            Node *temp2 = n2->next;

            temp1->next = n2;
            n2->prev = temp1;
            n2->next = n1;
            n1->prev = n2;
            n1->next = temp2;
            temp2->prev = n1;
        } else if (n1->prev == nullptr && n2->next == nullptr) {
            n2->prev = nullptr;
            n1->next = nullptr;
            n2->next = n1;
            n1->prev = n2;
        } else {
            puts("swap error");
        }


    }

    Node *returnElement(int n) {
        if (n < 0 || n > counter)
            return nullptr;
        Node *temp = head;
        for (int i = 0; i < n; i++) {
            temp = temp->next;
        }
        return temp;
    }

    void insert(Node *node, Node *found) {
        Node *temp = nullptr;
        if (found->next != nullptr)
            temp = found->next;

        found->next = node;
        node->prev = found;

        if (temp != nullptr) {
            node->next = temp;
            temp->prev = node;
        }

    }

    void addToEmpty(Node *node) {
        head = node;
    }

    int getID() {
        int id;
        printf("Find specified ID in List: ");
        if (scanf("%d", &id) != 1) {
            printf("Invalid id. Try again\n");
            id = getID();
        }
        return id;
    }

    Node *findID(int id) {
        if (head == nullptr)
            return nullptr;

        Node *temp = head;
        do {
            if (temp->ID == id)
                break;
            if (temp->next != nullptr)
                temp = temp->next;
            else break;
        } while (true);
        if (temp->ID == id)
            return temp;
        else
            return nullptr;
    }
};

int List::counter = 0;
Node *List::head = nullptr;

int main() {
    Node n[100];
    List list;
    int choice, i = 0;
    while (true) {
        printf("1 - Add element\t 2 - Remove element\n3 - view\t 4 - sort\n5 - exit\n");
        scanf("%d", &choice);
        if (choice == 1) {
            n[i].create();
            list.add(&n[i]);
            i++;
        } else if (choice == 2)
            list.remove();
        else if (choice == 3)
            list.view();
        else if (choice == 4)
            list.sort();
        else
            break;
    }

    return 0;
}
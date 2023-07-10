#ifndef INC_1_2_LIST_H
#define INC_1_2_LIST_H

template<typename T2>
class List {
public:
    T2 data;
    List<T2>* next;
    List<T2>* prev;

    List() {
        data = T2();
        next = nullptr;
        prev = nullptr;
    }

    List(T2 val) {
        data = val;
        next = nullptr;
        prev = nullptr;
    }
};

//template<typename T2>
//void initializeList(List<T2>*& head) {
//    head = nullptr;
//}

template<typename T2>
void ToList(List<T2>*& head, T2 val) {
    List<T2>* newNode = new List<T2>(val);
    if (head == nullptr) {
        head = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
}

template<typename T2>
void removeAfter(List<T2>* head, T2 val) {
    if (head == nullptr) {
        return;
    }
    List<T2>* current = head;
    while (current != nullptr && current->next != nullptr) {
        if (current->data == val) {
            List<T2>* temp = current->next;
            current->next = temp->next;
            if (temp->next != nullptr) {
                temp->next->prev = current;
            }
            delete temp;
        }
        current = current->next;
    }
}

template<typename T2>
void deleteFromList(List<T2>*& head, T2 val) {
    List<T2>* current = head;
    while (current != nullptr) {
        if (current->data == val) {
            if (current->prev != nullptr) {
                current->prev->next = current->next;
            } else {
                head = current->next;
            }
            if (current->next != nullptr) {
                current->next->prev = current->prev;
            }
            delete current;
            return;
        }
        current = current->next;
    }
}

template<typename T2>
List<T2>* search(List<T2>* head, T2 val) {
    List<T2>* current = head;
    while (current != nullptr) {
        if (current->data == val) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

template<typename T>
List<T>* mergeLists(List<T>* head1, List<T>* head2) {
    if (head1 == nullptr) {
        return head2;
    }
    if (head2 == nullptr) {
        return head1;
    }
    List<T>* current = head1;
    while (current->next != nullptr) {
        current = current->next;
    }
    current->next = head2;
    head2->prev = current;
    return head1;
}

template<typename T>
void freeMemory(List<T>*& head) {
    List<T>* current = head;
    while (current != nullptr) {
        List<T>* temp = current;
        current = current->next;
        delete temp;
    }
    head = nullptr;
}

#endif
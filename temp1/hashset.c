#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 1000
#define EMPTY -1
#define DELETED -2

typedef struct {
    int* table;
} HashSet;

int hash(int key) {
    return key % TABLE_SIZE;
}

HashSet* create_hashset() {
    HashSet* set = (HashSet*)malloc(sizeof(HashSet));
    set->table = (int*)malloc(sizeof(int) * TABLE_SIZE);
    for (int i = 0; i < TABLE_SIZE; i++) {
        set->table[i] = EMPTY;
    }
    return set;
}
int insert(HashSet* set, int shipment_id) {
    int index = hash(shipment_id);
    int start_index = index;

    while (set->table[index] != EMPTY && set->table[index] != DELETED) {
        if (set->table[index] == shipment_id) {
            return 0;
        }
        index = (index + 1) % TABLE_SIZE;
        if (index == start_index) return 0;
    }

    set->table[index] = shipment_id;
    return 1;
}

int contains(HashSet* set, int shipment_id) {
    int index = hash(shipment_id);
    int start_index = index;

    while (set->table[index] != EMPTY) {
        if (set->table[index] == shipment_id) {
            return 1;
        }
        index = (index + 1) % TABLE_SIZE;
        if (index == start_index) return 0;
    }
    return 0;
}
int delete(HashSet* set, int shipment_id) {
    int index = hash(shipment_id);
    int start_index = index;

    while (set->table[index] != EMPTY) {
        if (set->table[index] == shipment_id) {
            set->table[index] = DELETED;
            return 1;
        }
        index = (index + 1) % TABLE_SIZE;
        if (index == start_index) return 0;
    }
    return 0;
}

void free_hashset(HashSet* set) {
    free(set->table);
    free(set);
}

int main() {
    HashSet* shipmentSet = create_hashset();

    int shipments[] = { 101, 202, 303, 101, 404, 202 };
    int n = sizeof(shipments) / sizeof(shipments[0]);

    for (int i = 0; i < n; i++) {
        if (insert(shipmentSet, shipments[i])) {
            printf("Adaugat\n", shipments[i]);
        }
        else {
            printf("Procesat\n", shipments[i]);
        }
    }

    int test_id = 303;
    if (contains(shipmentSet, test_id)) {
        printf("ID gasit\n", test_id);
    }
    else {
        printf("Id-ul nu exista\n", test_id);
    }

    free_hashset(shipmentSet);
    return 0;
}

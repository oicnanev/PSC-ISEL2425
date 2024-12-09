#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct card {
	unsigned long number:50;
	unsigned long state:3;
	unsigned long hlen:8;
	char holder[];
} card_t;

typedef struct node_card {
	struct node_card *next;
	struct card *card;
} node_card_t;
typedef struct array_card {
	unsigned int ncard;
	struct card *array[];
} array_card_t;

array_card_t *list_to_array(node_card_t	*list) {
	int elems_cnt = 0;
	node_card_t *tmp = list;
	while (tmp != NULL) {
		elems_cnt += 1;
		tmp = tmp->next;
	}
	array_card_t *pcards = (array_card_t*)malloc(
		sizeof(array_card_t) + sizeof(void*)*elems_cnt
	);
	
	pcards->ncard = elems_cnt;
	for (int card_idx = 0; card_idx < elems_cnt; card_idx++) {
		pcards->array[card_idx] = list->card;
		tmp = list;
		list = list->next;
		free(tmp);
	}
		
	return pcards;
}
node_card_t *array_to_list( array_card_t *array) {
	node_card_t *list = NULL;
	for (int card_idx = array->ncard-1; card_idx >= 0; card_idx--) {
		node_card_t *pnode = (node_card_t*)malloc(sizeof(node_card_t));
		pnode->next = list;
		pnode->card = array->array[card_idx];
		list = pnode;
	}
	free(array);
	return list;
}

card_t cards[] = {
    { .number=1, .state=1, .hlen=1 },
    { .number=2, .state=1, .hlen=1 },
    { .number=3, .state=1, .hlen=1 },
    { .number=4, .state=1, .hlen=1 },
    { .number=5, .state=1, .hlen=1 },
};

struct {
    int ncard;
} test_vector[] = {
    { .ncard = 5 },
    { .ncard = 0 }
};

int main(void) {
    for (int i = 0; i < sizeof(test_vector)/sizeof(test_vector[0]); i++) {
        array_card_t *parray = (array_card_t *)malloc(sizeof(array_card_t) + sizeof(void*) * test_vector[i].ncard);
        parray->ncard = test_vector[i].ncard;
        for (int j = 0; j < parray->ncard; j++) {
            parray->array[j] = &cards[j];
        }
        array_card_t *tmp =  (array_card_t *)malloc(sizeof(array_card_t) + sizeof(void*) * test_vector[i].ncard);
        memcpy(tmp, parray, sizeof(array_card_t) + sizeof(void*) * test_vector[i].ncard);
        node_card_t *list = array_to_list(parray);
        parray = list_to_array(list);
        if (parray->ncard != tmp->ncard)
            fprintf(stderr, "[%d] - ncard field differ from original. Expected %d and returned %d\n", i, tmp->ncard, parray->ncard);
        if (memcmp(parray->array, tmp->array, sizeof(void*) * test_vector[i].ncard) != 0)
            fprintf(stderr, "[%d] - array of cards returned from list_to_array differ from original\n", i);
        free(tmp);
        free(parray);
    }
    fprintf(stderr, "Test terminated!!!\n");

    return 0;
}


#include "4a.h"
#include <stdio.h>
#include <unistd.h>
// Hier ggf. weitere Includes

/*
 * Hier könnt ihr ggf. benötigte globale Varibalen und/oder Hilfsfunktionen ablegen
 */

int pointer = 0;

int find_free_chunk(int position){
	int current = position;

	while(allocation_list[current].status != CHUNK_FREE){
		current = current + allocation_list[current].length;
		if(current >= NUM_CHUNKS){
			current = 0;
		}
		if(current == pointer){
			return -1;
		}
	}

	return current;
}

void *nf_alloc(size_t size)
{
	/*
	 * Diese Funktion sollt ihr implementieren.
	 */
	
	size_t chunk_size = size_to_chunks(size);

	if(chunk_size == 0 || chunk_size > 64){
		return NULL;
	}

	int chunk_index = find_free_chunk(pointer);

	while(chunk_index != -1){
		size_t length = allocation_list[chunk_index].length;
		if( chunk_size > length){
			// if(i < 3){
			// 	printf("Chunk index: %d\n", chunk_index);
			// 	printf("Chunk size: %d\n", chunk_size);
			// 	printf("Length: %zu\n", length);
			// 	printf("Pointer: %d\n", pointer);
			// 	i++;
			// }
			if(chunk_index + length >= NUM_CHUNKS){
				chunk_index = find_free_chunk(0);
			}
			else{
				chunk_index = find_free_chunk(chunk_index + length);
			}
		}
		else if(chunk_size == length){
			allocation_list[chunk_index].status = CHUNK_ALLOCATED;
			pointer = chunk_index + chunk_size;
			if(pointer >= NUM_CHUNKS){
				pointer = 0;
			}
			return allocation_list + chunk_index;
		}
		else{
			allocation_list[chunk_index].status = CHUNK_ALLOCATED;
			allocation_list[chunk_index].length = chunk_size;
			allocation_list[chunk_index + chunk_size].status = CHUNK_FREE;
			allocation_list[chunk_index + chunk_size].length = length - chunk_size;
			pointer = chunk_index + chunk_size;
			if(pointer >= NUM_CHUNKS){
				pointer = 0;
			}
			return allocation_list + chunk_index;
		}
	}
	
	return NULL;
}

#include "4b.h"
#include <stdio.h>

void nf_free(void *addr)
{
	// Diese Funktion sollt ihr implementieren
	mem_info *current = &allocation_list;
	int index = 0;

	if(addr == NULL){
		return;
	}

	if(addr < current || addr > (current + 63)){
		exit(255);
	}

	while(addr != current){
		current++;
		index++;
	}

	if(allocation_list[index].status == CHUNK_FREE){
		return;
	}

	extern int pointer;

	allocation_list[index].status = CHUNK_FREE;

	if(index == 0){
		size_t length = allocation_list[index].length;
		mem_info next_chunk = allocation_list[index+length];

		if(next_chunk.status == CHUNK_FREE && next_chunk.length != 0){
			allocation_list[index].length = length + next_chunk.length;
			allocation_list[index + length].length = 0;
			if(pointer == index + length){
				pointer = index;
			}
		}

	}
	else if(index + allocation_list[index].length >= NUM_CHUNKS){
		int p_index = index-1;
		size_t length = allocation_list[index].length;
		mem_info previous_chunk = allocation_list[p_index];
		while(previous_chunk.length == 0){
			p_index--;
			previous_chunk = allocation_list[p_index];
		}

		if(previous_chunk.status == CHUNK_FREE){
			allocation_list[p_index].length = allocation_list[p_index].length + length;
			allocation_list[index].length = 0;
			if(pointer == index){
				pointer = p_index;
			}
		}
	}
	else{

		size_t length = allocation_list[index].length;
		mem_info next_chunk = allocation_list[index+length];

		int p_index = index-1;
		mem_info previous_chunk = allocation_list[p_index];
		while(previous_chunk.length == 0){
			p_index--;
			previous_chunk = allocation_list[p_index];
		}

		if(previous_chunk.status == CHUNK_FREE && next_chunk.status == CHUNK_FREE){
			allocation_list[p_index].length = allocation_list[p_index].length + length + next_chunk.length;
			allocation_list[index].length = 0;
			allocation_list[index + length].length = 0;
			if(pointer == index || pointer == index + length){
				pointer = p_index;
			}
		}
		else if(previous_chunk.status == CHUNK_FREE && next_chunk.status == CHUNK_ALLOCATED){
			allocation_list[p_index].length = allocation_list[p_index].length + length;
			allocation_list[index].length = 0;
			if(pointer == index){
				pointer = p_index;
			}
		}
		else if(previous_chunk.status == CHUNK_ALLOCATED && next_chunk.status == CHUNK_FREE){
			allocation_list[index].length = length + next_chunk.length;
			allocation_list[index + length].length = 0;
			if(pointer == index + length){
				pointer = index;
			}
		}

	}

}

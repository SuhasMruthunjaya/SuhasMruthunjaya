// Does the Boolean XOR function represent a valid way to verify the integrity of a message?
// by C. Jakob, fbeit, h_da, November 2022, christian.jakob@h-da.de

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

typedef unsigned char uint8_t;

uint8_t xor_hash(char *m_ptr);

int main(void){

	char * o_msg = "Lower the rate by 1.2%! Sincerely, Christine Lagarde";
	char * m_msg = "Raise the rate by 9.5%! Sincerely, Christine Lagarde";

	printf("Length - Original Message:\t %lu, \tXOR Hash: 0x%x\n",strlen(o_msg),xor_hash(o_msg));
	printf("Length - Manipulated Message:\t %lu, \tXOR Hash: 0x%x\n",strlen(m_msg),xor_hash(m_msg));

	return 0;
}

uint8_t xor_hash(char *m_ptr){
	uint8_t xor_hash = 0;	
	while(*m_ptr){
		xor_hash ^= *m_ptr;
		m_ptr++;
	}
	return xor_hash;
}


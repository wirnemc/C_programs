//
//  main.c
//  C_memmove
//
//  Created by Irene Mateos Cañas on 10/10/18.
//  Copyright © 2018 Irene Mateos Cañas. All rights reserved.
//


// Problem under study:

/*  The memcpy() function copies n bytes from memory area src to memory area dest. The memory areas
 *   must not overlap. Let’s assume that the prototype for memcpy() is:
 *   void memcpy(void *dest, const void *src, size_t n);
 *
 *   The purpose of this exercise is to create an implementation of memcpy() that is robust to memory
 *   region overlapping. The function to implement will have the following prototype:
 *   void memmove(void *dest, const void *src, size_t n);
 */

// Cases under consideration:

/*  Case 1: src's n bytes overlaps with dest
 *  Case 2: src's n bytes doesn't overlaps with dest - empty origin
 *  Case 3: src's n bytes doesn't overlaps with dest - empty destiny
 */


// First ideas:

/*  Assumption I: size limit doesn't restricts to insert the 'n' bytes on the dest
 *              -> Check how big could n be (possible enhancement)
 *
 *  Assumption II: if pointers types are unknown:
 *  Step I:     -> Cast to a primitive type
 *              -> try to cast to a simple type to manage -> int? char?
 *              -> memory address more like a char type
 *
 *  Step III: check if there is overlapping when copying src's n bytes on dest:
 *              -> Copy src's n bytes after dest
 *              -> if dest(0 until original_dest_size) == dest (0 until desti_size-n)
 *        Step III.I -> No overlappping -> Considered as a "NULL overlapping" (same procedure as Step III.II)
 *        Step III.II -> else -> overlapping
 *
 *  Step III.II: Iterate over src
 *              -> Copy on aux array n bytes of src to be copied to dest
 *              -> If n>sizeof(src) -> stop copying
 *
 *  Step V:    Iterate over dest
 *              -> When dest[i]=='\0' -> free position
 *              -> Copy src's n bytes from i on
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void memorymove(void *dest, const void *src, size_t n){
    //Following Assumption I: memory block size is supposed to be enough
    //Following Assumption II:
    char *aux1 = (char *)src;
    char *aux2 = (char *)dest;
    
    char aux[n];
    char aux3[sizeof(aux2)+n];
    memset(aux3, 0, sizeof(aux3));
    
    //Iterate over to save n bytes of src
    for (int i=0; i<n; i++){
        aux[i]=aux1[i];
    }
    
    //Now I have on aux[n] the n bytes i want to copy on dest
    //Save on aux3 aux2 info
    for (int i=0;i<sizeof(aux2);i++){
        if (aux2[i]!='\0') {
            aux3[i]=aux2[i];
        }
    }
    
    //Copy on aux3 n bytes from aux
    int j=0;
    for (int k=0;k<sizeof(aux3);k++){
        if (aux3[k]=='\0' && j<n) {
            aux3[k]=aux[j];
            j++;
        }
    }
    
    //Copy on aux2 aux3 info and delete aux and aux3
    for (int j=0;j<sizeof(aux3);j++){
        aux2[j]=aux3[j];
    }
    
    // Once aux and aux3 has been used, this memory space could be released -> Possible enhancement
    memset(aux3, 0, sizeof(aux3));
    memset(aux,0,sizeof(aux));
    
    // Possible improvement: restriction to a maximum quantity of n bytes
    //Maximum n
    //size_t max_n = aux2 - aux1;
}

int main(int argc, const char * argv[]) {
    
    char origin[64] = "Hello";
    char destiny[64] = "Bye";
    memorymove(destiny, origin, 5);
    printf("Test 1:\n Case 1.Overlapping \n memmove origin to destiny -> \n   Result:  %s\n\n",destiny);
    
    char origin2[64] = "Chain 1";
    char destiny2[64] = "Chain 2";
    memorymove(destiny2, origin2, 3);
    printf("Test 2:\n Case 1.Overlapping \n memmove origin2 to destiny2 -> \n   Result:  %s\n\n", destiny2);
    
    char origin3[64] = "";
    char destiny3[64] = "Bye";
    memorymove(destiny3, origin3, 2);
    printf("Test 3:\n Case 2.No overlapping. Empty origin.\n memmove origin3 to destiny3 -> \n   Result:  %s\n\n",destiny3);
    
    char origin4[64] = "Chain 1";
    char destiny4[64] = "";
    memorymove(destiny4, origin4, 1);
    printf("Test 4:\n Case 3.No overlapping. Empty dest.\n memmove origin4 to destiny4 -> \n   Result:  %s\n\n", destiny4);
    
    return 0;
}


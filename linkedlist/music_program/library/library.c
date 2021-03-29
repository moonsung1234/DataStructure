
#include <stdlib.h>
#include <string.h>
#include "library.h"

Artist* artist_arr[ARRAY_SIZE];

void init() {
    int i;
    
    for(i=0; i<ARRAY_SIZE; i++) {
        artist_arr[i] = NULL;
    }
}

Artist* findArtist(char* artist) {
    Artist* p = artist_arr[0];
 
    while(p != NULL && strcmp(artist, p->name) != 0) {
        p = p->next;
    }

    return p;
}

void addSong(char* artist, char* title, char* path) {
    Artist* finded_artist = findArtist(artist);

    if(artist_arr != NULL) {

    } else {

    }
}
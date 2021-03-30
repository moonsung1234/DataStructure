
#include "library.h"

Artist* artist_arr[ARRAY_SIZE];
int song_index = 0;

void init() {
    int i;
    
    for(i=0; i<ARRAY_SIZE; i++) {
        artist_arr[i] = NULL;
    }
}

Artist* findArtist(char* artist) {
    Artist* p = artist_arr[(unsigned char) artist[0]];
 
    while(p != NULL && strcmp(artist, p->name) < 0) {
        p = p->next;
    }

    return p;
}

Artist* createArtist(char* artist) {
    Artist* created_artist = (Artist*)malloc(sizeof(Artist));
    created_artist->name = strdup(artist);
    created_artist->head = NULL;
    created_artist->next = NULL;
    created_artist->tail = NULL;

    return created_artist;
}

Artist* addArtist(char* artist) {
    Artist* created_artist = createArtist(artist);
    Artist* p = artist_arr[(unsigned char) artist[0]];   
    Artist* q = NULL;
    int i;

    while(p != NULL && strcmp(artist, p->name) < 0) {
        q = p;
        p = p->next;
    }

    if(p == NULL && q == NULL) {
        artist_arr[(unsigned char) artist[0]] = created_artist;
    
    } else if(q == NULL) {
        created_artist->next = artist_arr[(unsigned char) artist[0]];
        artist_arr[(unsigned char) artist[0]] = created_artist;
    
    } else {
        created_artist->next = p;
        q->next = created_artist;
    }

    return created_artist;
}

Song* createSong(Artist* artist, char* title, char* path) {
    Song* created_song = (Song*)malloc(sizeof(Song));
    created_song->artist = artist;
    created_song->index = song_index++;
    created_song->path = strdup(path);
    created_song->title = strdup(title);

    return created_song;
} 

void insertNode(Artist* artist, SNode* snode) {
    SNode* p = artist->head;

    while(p != NULL && strcmp(p->song->title, snode->song->title) < 0) {
        p = p->next;
    }

    if(artist->head == NULL) {
        artist->head = snode;
        artist->tail = snode;
    
    } else if(p == artist->head) {
        snode->next = artist->head;
        artist->head = snode;

    } else if(p == NULL) {
        snode->prev = artist->tail;
        artist->tail = snode;

    } else {
        snode->next = p;
        snode->prev = p->prev;
        p->prev->next = snode;
        p->prev = snode;
    }
}

SNode* createSNode(Song* song) {
    SNode* created_snode = (SNode*)malloc(sizeof(SNode));
    created_snode->next = NULL;
    created_snode->prev = NULL;
    created_snode->song = song;

    return created_snode;
}

void addSong(char* artist, char* title, char* path) {
    Artist* finded_artist = findArtist(artist);

    if(finded_artist == NULL) {
        finded_artist = addArtist(artist);
    }

    Song* created_song = createSong(finded_artist,  title, path);
    SNode* created_snode = createSNode(created_song);

    insertNode(finded_artist, created_snode);
}

void printSong(Song* song) {
    printf("%d %s %s\n", song->index, song->path, song->title);
}

void printArtist(Artist* artist) {
    printf("%s >> ", artist->name);

    SNode* snode = artist->head;

    while(snode != NULL) {
        if(snode->song != NULL) {
            printSong(snode->song);
        }

        snode = snode->next;
    }
}

void status() {
    int i;

    for(i=0; i<ARRAY_SIZE; i++) {
        Artist* p = artist_arr[i];

        while(p != NULL) {
            printArtist(p);
            
            p = p->next;
        }
    }
}

void freeAllArtist(Artist* artist) {
    SNode* snode = artist->head;

    while(snode != NULL) {
        SNode* next = snode->next;

        free(snode->song->path);
        free(snode->song->title);
        free(snode->song);
        free(snode);

        snode = next;
    }
}

void freeAll() {
    int i;

    for(i=0; i<ARRAY_SIZE; i++) {
        Artist* p = artist_arr[i];

        while(p != NULL) {
            Artist* next = p->next;

            free(p->name);
            freeAllArtist(p);
            free(p);
            
            p = next;
        }
    }
}
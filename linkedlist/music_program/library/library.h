
#ifndef LIBRARY

#define LIBRARY
#define ARRAY_SIZE 256 // 2^8

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct song Song;
typedef struct snode SNode;
typedef struct artist Artist;

struct song {
    Artist* artist;
    char* title;
    char* path;
    int index;
};

struct snode {
    SNode* next;
    SNode* prev;
    Song* song;
};

struct artist {
    char* name;
    Artist* next;
    SNode* head;
    SNode* tail;
};

void init();
void addSong(char* artist, char* title, char* path);
void status();
void freeAll();

#endif
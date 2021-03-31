
#ifndef LIBRARY

#define LIBRARY
#define ARRAY_SIZE 256 // 2^8
#define BUFFER_SIZE 200

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
void load(FILE* fp);
void _searchSong(char* artist);
void searchSong(char* artist, char* title);
void addSong(char* artist, char* title, char* path);
void printSong(Song* song);
void status();
void freeAll();

#endif
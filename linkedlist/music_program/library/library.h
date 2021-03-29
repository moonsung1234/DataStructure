
#ifndef LIBRARY

#define LIBRARY

#define ARRAY_SIZE 200

typedef struct song Song;
typedef struct s_node SNode;
typedef struct artist Artist;

struct song {
    Artist* artist;
    char* title;
    char* path;
    int index;
};

struct s_node {
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

#endif
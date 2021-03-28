
#include <stdio.h>
#include <string.h>
#include "string/string.h"
#include "library/library.h"

#define BUFFER_SIZE 200

void handleAdd() {
    char buffer[BUFFER_SIZE];
    char* artist;
    char* title;
    char* path;

    printf("Artist : ");
    readLine(buffer);

    artist = strdup(buffer);

    printf("Title : ");
    readLine(buffer);

    title = strdup(buffer);

    printf("Path : ");
    readLine(buffer);

    path = strdup(buffer);

    addSong(artist, title, path);

    printf("%s %s %s\n", artist, title, path);
}

void processCommand() {
    char buffer[BUFFER_SIZE];
    char* command;

    while(1) {
        printf("$ ");

        if(readLine(buffer) <= 0) {
            continue;
        }

        command = strtok(buffer, " ");

        if(strcmp(command, "add") == 0) {
            handleAdd();

        } else if(strcmp(command, "search") == 0) {
        
        } else if(strcmp(command, "remove") == 0) {

        } else if(strcmp(command, "status") == 0) {

        } else if(strcmp(command, "play") == 0) {

        } else if(strcmp(command, "save") == 0) {

        } else if(strcmp(command, "exit") == 0) {
            break;
        }
    }
}

void main() {
    processCommand();
}
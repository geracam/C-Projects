//
//  main.c
//  CD Database
//
//  Created by Gerardo Camarena Gomez on 12/27/14.
//  Copyright (c) 2014 Gerardo Camarena Gomez. All rights reserved.
//
// Learning how to use pointers, this is a database that takes user
// input and creates a record of CD information

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

//Initializing our data structure

struct databaseEntry
{
    char artist[40];
    char composer[40];
    char album[40];
    int trackCount;
    bool isSample;

};

// We put our global variables outside any functions

int                     numDBentries = 0;
struct  databaseEntry*     DB = NULL;              // Pointer to CDdatabase (dynamic array)

void newCommand();

void newCommand()
{
    char YN;
    
    
    if ( DB == NULL)
    {
        
        DB = malloc(sizeof(struct databaseEntry));
        if (DB == NULL)
            
        {
            
            printf("There's something not quite right");
            return;
            
        }
    }
    else
    {
        struct databaseEntry* newPointer = NULL;
        newPointer = realloc(DB, (numDBentries + 1) *sizeof(struct databaseEntry));
        
        if (newPointer == NULL) //Happens when we run out of memory
        {
            //Old pointer remains as is
            printf("Oops something went wrong");
            return;
        }
        
        DB = newPointer;
    
    }
    
    numDBentries += 1;
    
    printf("Artist:");
    scanf( "%39s", DB[ numDBentries -1].artist); // We have 39 bits bc C adds 0 at the end. (39+1 =40)
    fpurge(stdin);
    
    printf("Composer:");
    scanf( "%39s", DB[ numDBentries -1].composer);
    fpurge(stdin);
    
    printf("Album:");
    scanf( "%39s", DB[ numDBentries -1].album);
    fpurge(stdin);
    
    printf("# Tracks:");
    scanf( "%d", &DB[ numDBentries -1].trackCount);
    fpurge(stdin);
    
    printf("Sample? (yes or no?):");
    scanf( "%c", &YN);
    fpurge(stdin);
    
    DB[ numDBentries -1].isSample = (YN == 'y'|| YN == 'Y');
}

void listCommand();

void listCommand()
{
    int a=0;
    
    if (DB == NULL)
    {
        printf("No data in database!.\n");
        return;
    }
    
    while (a < numDBentries) {
        printf("Artist: %s\n" , DB[ a ].artist);
        printf("Composer: %s\n" , DB[ a ].composer);
        printf("Album: %s\n" , DB[ a ].album);
        printf("# Tracks: %d\n" , DB[ a ].trackCount);
        if (DB[ a ].isSample)
            printf("\tThis Cd is a Sample.\n");
        printf("\n");
        
        a += 1;
        
        
    }

}

void cleanup();

void cleanup(void)
{
    if (DB != NULL) //Checks to see if we have memory allocated
    {
        free(DB);
        DB = NULL;
        numDBentries = 0;
        
    }

}


int main()
{
    bool runProgram = true;
    char userInput[11];
    
    while ( runProgram == true) {
        printf( "Tell if you want NEW , LIST , or EXIT:\n> ");
        scanf("%10s", userInput);
        fpurge(stdin);
        
        if (strcmp(userInput, "NEW") == 0 )
            newCommand();
        
        else if (strcmp(userInput, "LIST") == 0)
            listCommand();
        else if (strcmp(userInput, "QUIT") == 0)
            runProgram = false;
        else
            printf( "ERROR: Unknown command \"%s\"!\n\n", userInput );
        
        
        
        }
    cleanup();
    
    return 0;
    
}

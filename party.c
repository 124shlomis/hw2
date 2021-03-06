/*

  File: party.c

  Abstract:

    Party handling implementation

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "party.h"

#define MAX_PARTY_NAME      20


/*
 * Types
 */
typedef struct _Party
{
    char Party[MAX_PARTY_NAME];
    int NumVoters;

    struct _Party* pNext;
} Party;


/*
 * Prototypes
 */
void PrintError(char* pPartyName);


/*
 * Statics
 */
static Party* PartyList = NULL;


/*

  Function: AddVote

  Abstract:

    Records the chosen party of a voter

  Parameters:

    pPartyName - The party that received the vote

  Returns: A pointer to the party name that is guaranteed to stay constant until 'FreeParties'
           is called. If the party name is illegal, we fail the operation and return NULL.

*/
char* AddVote(char* pPartyName)
{
    // checks if party name already exists, if it does, apdates NumVoters and returns
    Party* i = PartyList;
    while (i && strcmp(pPartyName, i->Party)) {
        i = i->pNext;
    }

    if (i != NULL) {
        i->NumVoters++;
        return i->Party;
    }

    // verifies the legality of the new party name
    char* pFirst_letter = strchr(pPartyName, '-');
    while (pFirst_letter++) {
        if (*pFirst_letter < 'A' || *pFirst_letter > 'Z') {
            PrintError(pPartyName);
            return NULL;
        }
        pFirst_letter = strchr(pFirst_letter, '-');
    } 
    
    // creates rhe new party
    Party* newParty = (Party*)malloc(sizeof(Party));
    if (newParty == NULL) {
        FreeParties();
        exit(-1);
    }
   
    newParty->NumVoters = 1;
    newParty->pNext = PartyList;
    PartyList = newParty;
    return  strcpy(newParty->Party, pPartyName);
}


/*

  Function: FreeParties

  Abstract:

    Frees all memory in the party database

*/
void FreeParties()
{
    while (PartyList) {
        Party* tmp = PartyList;
        PartyList = PartyList->pNext;
        free(tmp);
    }
}


/*

  Function: PrintResult

  Abstract:

    Reports the election result so far

*/
void PrintResult()
{
    Party* pParty;

    printf("Election Results\n");
    printf("Party | Num. of Voters\n");

    /*
     * Iterate the party list and print the current number of voters for each party
     */
    for (pParty = PartyList; pParty; pParty = pParty->pNext)
        printf("%s %d\n", pParty->Party, pParty->NumVoters);
    printf("\n");
}


void PrintError(char* pPartyName)
{
    printf("ERROR: '%s' is invalid\n", pPartyName);
}

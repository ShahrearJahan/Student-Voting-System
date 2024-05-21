#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Created by Shahrear Jahan
// Student ID: 212-15-4114

typedef struct {
    int candidateNumber;
    char candidateName[50];
    int votes;
} Candidate;

void printLine(int width) {
    for (int i = 0; i < width; i++) {
        printf("*");
    }
    printf("\n");
}

void printCenteredText(const char* text, int width) {
    int len = strlen(text);
    int padding = (width - len) / 2;
    printf("*%*s%s%*s*\n", padding, "", text, width - len - padding, "");
}

void electionResult(Candidate candidates[], int numCandidates, int numVoters) {
    int maxVotes = 0;
    int winnerIndex = -1;
    int tie = 0;
    int width = 50;

    for (int i = 0; i < numCandidates; i++) {
        if (candidates[i].votes > maxVotes) {
            maxVotes = candidates[i].votes;
            winnerIndex = i;
            tie = 0;
        } else if (candidates[i].votes == maxVotes) {
            tie = 1;
        }
    }

    printf("\n");
    printLine(width);
    printCenteredText("Election Result", width);
    printLine(width);

    if (tie) {
        printCenteredText("No one won the election", width);
    } else {
        printCenteredText("Congratulations to the winner!", width);
        printCenteredText(candidates[winnerIndex].candidateName, width);
    }

    printLine(width);
    printf("\n");

    // Display candidates and their votes in a box
    printLine(width);
    printCenteredText("Candidate Results", width);
    printLine(width);

    for (int i = 0; i < numCandidates; i++) {
        char result[50];
        sprintf(result, "%s: %d votes", candidates[i].candidateName, candidates[i].votes);
        printCenteredText(result, width);
    }

    printLine(width);

    // Display total voters
    char totalVotersText[50];
    sprintf(totalVotersText, "Total voters: %d", numVoters);
    printCenteredText(totalVotersText, width);
    printLine(width);

    if (!tie) {
        printf("\n");
        for (int i = 0; i < numCandidates; i++) {
            if (i != winnerIndex) {
                int wonByVote = candidates[winnerIndex].votes - candidates[i].votes;
                printf("%s won by %d votes over %s\n", candidates[winnerIndex].candidateName, wonByVote, candidates[i].candidateName);
            }
        }
    }
}

void main() {
    int numCandidates, numVoters;
    const int padding = 15;

    // Display the introductory screen
    printf("%*s\n", padding + 40, "*****************************************");
    printf("%*s\n", padding + 40, "*                                       *");
    printf("%*s\n", padding + 40, "*          Voting System                *");
    printf("%*s\n", padding + 40, "*                                       *");
    printf("%*s\n", padding + 40, "*      developed by : Shahrear Jahan    *");
    printf("%*s\n", padding + 40, "*              (212-15-4114)            *");
    printf("%*s\n", padding + 40, "*                                       *");
    printf("%*s\n", padding + 40, "*****************************************\n");

    printf("Enter the number of candidates: ");
    scanf("%d", &numCandidates);
    getchar();  // to consume the newline character after entering number

    Candidate* candidates = (Candidate*)malloc(numCandidates * sizeof(Candidate));
    for (int i = 0; i < numCandidates; i++) {
        candidates[i].candidateNumber = i + 1;
        printf("Enter the name of candidate %d: ", i + 1);
        fgets(candidates[i].candidateName, 50, stdin);
        candidates[i].candidateName[strcspn(candidates[i].candidateName, "\n")] = '\0';  // remove trailing newline
        candidates[i].votes = 0;
    }

    printf("Enter the number of voters: ");
    scanf("%d", &numVoters);

    printf("\n%*s\n", padding + 40, "*********Welcome to the Student Voting System*********");
    printf("%*s\n", padding + 40, "                   Student Election                    ");
    printf("%*s\n", padding + 40, "*******************************************************");
    for (int i = 0; i < numCandidates; i++) {
        printf("%*s%d. %-15s ", padding + 20, "", candidates[i].candidateNumber, candidates[i].candidateName);
        if ((i % 2) == 1 || i == numCandidates - 1) {
            printf("|\n");
            if (i != numCandidates - 1) {
                printf("%*s\n", padding + 40, "*******************************************************");
            }
        }
    }
    printf("%*s\n", padding + 40, "*******************************************************\n");

    for (int i = 0; i < numVoters; i++) {
        int vote;
        printf("Voter %d, please choose your candidate by number: ", i + 1);
        scanf("%d", &vote);
        if (vote > 0 && vote <= numCandidates) {
            candidates[vote - 1].votes += 1;
        } else {
            printf("Invalid candidate number. Vote not counted.\n");
        }
    }

    electionResult(candidates, numCandidates, numVoters);
    free(candidates);
}

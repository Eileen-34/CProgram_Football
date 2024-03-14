#include <stdio.h>
#include <stdlib.h>


enum BundesligaTeam {
    BayernMunich,
    BayerLeverkusen,
    FCKoeln,
    WerderBremen,
    HerthaBSC,
    BvBDortmund,
    NumTeams
};

//Structure to represent a football game
struct footballGame {
    int date;
    int month;
    int year;
    enum BundesligaTeam team1;
    enum BundesligaTeam team2;
    int goalsTeam1;
    int goalsTeam2;
    int winner; // 1 Punkte: tie(unentschieden), 3 Punkte: winner (Sieg des Team1 oder Team2)
    int pointsTeam1;
    int pointsTeam2;
};

int isValidDate(int day, int month, int year) {
    if (year < 0 || month < 1 || month > 12 || day < 1)
        return 0;

    int maxDay;

    switch (month) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            maxDay = 31;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            maxDay = 30;
            break;
        case 2:
            if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
                maxDay = 29;
            else
                maxDay = 28;
            break;
        default:
            return 0;
    }

    return day <= maxDay ? 1 : 0;
}

//Node structure for the linked list
struct Node {
    struct footballGame data;
    struct Node *next;
};

//Linked list Structure
typedef struct LinkedList {
    struct Node *head;
} LinkedList;

// Function prototypes
LinkedList *initializeList();


const char *teamNames[NumTeams] = {
        "Bayern Munich",
        "Bayer Leverkusen",
        "FC Koeln",
        "Werder Bremen",
        "Hertha BSC",
        "BvB Dortmund"
};

LinkedList *initializeList() {
    LinkedList *list = (LinkedList *) malloc(sizeof(LinkedList));
    list->head = NULL;
    return list;
}

//Function to enter match details to the list
struct footballGame enterMatch() {
    struct footballGame result;
    printf("Enter the date of a football match (DD.MM.YYYY): \n");

    while (1) {
        if (scanf("%d.%d.%d", &result.date, &result.month, &result.year) != 3 ||
            !isValidDate(result.date, result.month, result.year)) {
            printf("Invalid date. Please enter a valid date (DD.MM.YYYY): ");
        } else {
            break;
        }
    }
    printf("Enter the number of the football team 1: \n");
    printf("0: %s \n", teamNames[BayernMunich]);
    printf("1: %s \n", teamNames[BayerLeverkusen]);
    printf("2: %s \n", teamNames[FCKoeln]);
    printf("3: %s \n", teamNames[WerderBremen]);
    printf("4: %s \n", teamNames[HerthaBSC]);
    printf("5: %s \n", teamNames[BvBDortmund]);

    scanf(" %d", &result.team1);

    printf("Enter the number of the football team 2: \n");
    scanf(" %d", &result.team2);

    printf("Enter the results of a football match between Team 1 and Team 2 \n");
    printf("Team 1 goals: ");
    scanf(" %d", &result.goalsTeam1);
    printf("Team 2 goals: ");
    scanf(" %d", &result.goalsTeam2);

    // Determine the winner and assign points
    if (result.goalsTeam1 == result.goalsTeam2) {
        result.winner = 0; // Tie
        result.pointsTeam1 = 1;
        result.pointsTeam2 = 1;
    } else if (result.goalsTeam1 > result.goalsTeam2) {
        result.winner = 1; //Team1 wins
        result.pointsTeam1 = 3;
        result.pointsTeam2 = 0;
    } else {
        result.winner = 2; // Team2 wins
        result.pointsTeam1 = 0;
        result.pointsTeam2 = 3;
    }
    return result;
}

//Function to enter match scores to the list based on user input

// Function to add match result to the list
void addMatchResult(struct LinkedList *list, const struct footballGame *result) {
    struct Node *newNode = (struct Node *) malloc(sizeof(struct Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failure \n");
        exit(EXIT_FAILURE);
    }
    newNode->data = *result;
    newNode->next = list->head;
    list->head = newNode;
}

void calculateTotalPoints(const struct LinkedList *list) {
    struct Node *current = list->head;
    int totalPointsTeam1 = 0;
    int totalPointsTeam2 = 0;
    int totalMatchNumbers = 0;

    while (current != NULL) {
        totalPointsTeam1 += current->data.pointsTeam1;
        totalPointsTeam2 += current->data.pointsTeam2;
        totalMatchNumbers++;

        printf("Total Match Number: %d - Total Points: %s: %d and %s: %d \n",
               totalMatchNumbers, teamNames[current->data.team1],
               current->data.pointsTeam1,
               teamNames[current->data.team2],
               current->data.pointsTeam2);

        current = current->next;
    }
}

void printResults(const struct LinkedList *list) {
    struct Node *current = list->head;

    printf("Match results: \n");

    while (current != NULL) {
        const struct footballGame *game = &current->data;
        printf("Date: %d.%d.%d \n", game->date, game->month, game->year);
        printf("Team 1: %s \n ", teamNames[game->team1]);
        printf("Team 2: %s \n ", teamNames[game->team2]);
        printf("Goals: %s: %d --- %s: %d\n", teamNames[game->team1], game->goalsTeam1, teamNames[game->team2],
               game->goalsTeam2);

        printf("Winner: ");
        if (game->winner == 0) {
            printf("Tie");
        } else if (game->winner == 1) {
            printf("%s wins!", teamNames[game->team1]);
        } else {
            printf("%s wins!", teamNames[game->team2]);
        }

        printf("\n POINTS - %s: %d ", teamNames[game->team1], game->pointsTeam1);
        printf("\n POINTS - %s: %d ", teamNames[game->team2], game->pointsTeam2);

        current = current->next;
    }
}

// Function to check if a team has reached the winning score
int checkWinningScore(const struct LinkedList *list, int team) {
    struct Node *current = list->head;
    int totalPointsTeam1 = 0;
    int totalPointsTeam2 = 0;

    while (current != NULL) {
        totalPointsTeam1 += current->data.pointsTeam1;
        totalPointsTeam2 += current->data.pointsTeam2;
        current = current->next;
    }

    // Check if the specified team has reached the winning score of 3 points
    if (team == 1) {
        return totalPointsTeam1 >= 3;
    } else {
        return totalPointsTeam2 >= 3;
    }
}

void calculateMatchNumbers(const struct LinkedList *list) {
    struct Node *current = list->head;
    int totalMatchNumbers = 0;

    while (current != NULL) {
        totalMatchNumbers++;
        current = current->next;
    }
    printf("Total football matches played: %d\n", totalMatchNumbers);
}

//Function to display number of matches played on a date

void displayMatchesPlayedOnADate(const struct LinkedList *list) {
    int day, month, year;

    printf("Enter the date to display matches (DD.MM.YYYY): \n");

    while (1) {
        if (scanf("%d.%d.%d", &day, &month, &year) != 3 || !isValidDate(day, month, year)) {
            printf("Invalid date. Please enter a valid date (DD.MM.YYYY): ");
        } else {
            break;
        }
    }

    struct Node *current = list->head;
    int matchesOnDate = 0;

    while (current != NULL) {
        if (current->data.date == day && current->data.month == month && current->data.year == year) {
            matchesOnDate++;
        }
        current = current->next;
    }

    printf("Number of matches played on date %d.%d.%d: %d\n", day, month, year, matchesOnDate);
}

//Function to display game statistics
void displayTeamStatistics(const struct LinkedList *list) {
    struct Node *current = list->head;

    // Find the maximum team number dynamically
    int maxTeamNumber = 0;
    while (current != NULL) {
        maxTeamNumber = current->data.team1 > maxTeamNumber ? current->data.team1 : maxTeamNumber;
        maxTeamNumber = current->data.team2 > maxTeamNumber ? current->data.team2 : maxTeamNumber;
        current = current->next;
    }

    // Increment maxTeamNumber by 1 to account for zero-based indexing
    maxTeamNumber++;

    // Dynamically allocate arrays for team statistics
    int *matchesPlayed = malloc(maxTeamNumber * sizeof(int));
    int *matchesWon = malloc(maxTeamNumber * sizeof(int));
    int *matchesTied = malloc(maxTeamNumber * sizeof(int));
    int *totalPoints = malloc(maxTeamNumber * sizeof(int));

    // Reset arrays to zero
    for (int i = 0; i < maxTeamNumber; i++) {
        matchesPlayed[i] = 0;
        matchesWon[i] = 0;
        matchesTied[i] = 0;
        totalPoints[i] = 0;
    }

    // Reset current pointer to the head of the list
    current = list->head;

    // Iterate through the list of matches to calculate statistics
    while (current != NULL) {
        int team1 = current->data.team1;
        int team2 = current->data.team2;
        int winner = current->data.winner;
        int pointsTeam1 = current->data.pointsTeam1;
        int pointsTeam2 = current->data.pointsTeam2;

        // Increment matches played for both teams
        matchesPlayed[team1]++;
        matchesPlayed[team2]++;

        // Update matches won, tied, and total points for team1
        if (winner == 1) {
            matchesWon[team1]++;
            totalPoints[team1] += pointsTeam1;
            matchesTied[team2]++; // Increment matches tied for team2
        } else if (winner == 2) {
            matchesWon[team2]++;
            totalPoints[team2] += pointsTeam2;
            matchesTied[team1]++; // Increment matches tied for team1
        } else {
            // If it's a tie, increment matches tied for both teams
            matchesTied[team1]++;
            matchesTied[team2]++;
            // Add points for both teams in case of a tie
            totalPoints[team1] += pointsTeam1;
            totalPoints[team2] += pointsTeam2;
        }

        current = current->next;
    }

    // Display team statistics
    printf("Team Statistics: \n");
    for (int i = 0; i < maxTeamNumber; i++) {
        printf("Team: %s\n", teamNames[i]); // Print team name
        printf("Matches Played: %d\n", matchesPlayed[i]);
        printf("Matches Won: %d\n", matchesWon[i]);
        printf("Matches Tied: %d\n", matchesTied[i]);
        printf("Total Points: %d\n", totalPoints[i]);
        printf("\n");
    }

    // Free dynamically allocated memory
    free(matchesPlayed);
    free(matchesWon);
    free(matchesTied);
    free(totalPoints);
}

void freeList(struct Node *head) {
    struct Node *current = head;
    struct Node *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

void enterMatchScores(struct LinkedList *list) {
    //enter a match score
    struct footballGame result = enterMatch();
    addMatchResult(list, &result);

    // printf("Match Results: \n");
    //  printResults(list);

    //  calculateTotalPoints(list);

    //check for game winner
    //   if (checkWinningScore(list, 1)) {
    //      printf("%s is the winner! \n", teamNames[1]);
    //  } else if (checkWinningScore(list, 2)) {
    //       printf("%s is the winner! \n", teamNames[2]);
    //   }
}


int main() {
    LinkedList *gameResults;
    gameResults = initializeList();

    int choice;
    while (1) {
        printf("Choose one of the following options. \n");
        printf("1 - Enter a new result of a football match \n");
        printf("2 - Display all the matches played on a specific date \n");
        printf("3 - Display team statistics: how many matches are played, how many matches are won and tie, total points of a team\n");
        printf("4 - Exit the program\n");
        printf("Your choice: \n");

        scanf("%d", &choice);

        switch (choice) {
            case 1:
                enterMatchScores(gameResults);
                break;
            case 2:
                displayMatchesPlayedOnADate(gameResults);
                break;
            case 3:
                displayTeamStatistics(gameResults);
                calculateMatchNumbers(gameResults);
                calculateTotalPoints(gameResults);
                break;
            case 4:
                printf("Exiting the program. Bye!");
                freeList(gameResults->head);
                return 0;
            default:
                printf("Invalid input. Please choose a number between 1-4. \n");
        }
    }
}
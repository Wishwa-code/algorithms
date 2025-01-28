#include <cs50.h>
#include <stdio.h>
#include <string.h>


// Max number of candidates
#define MAX 4

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

void print_preferences(void) {
    // printf("Preferences:\n");
    // int index = 0;
    // for (int i = 0; i < candidate_count; i++) {
    //     for (int j = 0; j < candidate_count; j++) {
    //         printf("Preferences[%d][%d]: %i\n", i, j, preferences[i][j]);
    //         if (preferences[i][j] > 0 )
    //         {
    //             pairs[index].winner = i;
    //             pairs[index].loser = j;
    //             printf("%i %i\n",pairs[index].winner, pairs[index].loser);
    //             index++;
    //         }


    //     }
    // }

    // for (int k = 0; k<index; k++)
    // {
    //     printf("%i %i\n",pairs[k].winner, pairs[k].loser);
    // }
}

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
void add_vote(int n, int ranks[],int ranks_length);
bool creates_cycle(int winner, int loser);


int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    print_preferences();

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        //Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {

            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }
        for (int l = 0; l<candidate_count;l++)
        {
            printf("rank %i \n",ranks[l]);
        }

        record_preferences(ranks);

        print_preferences();

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    //string rank_names[ranks_length];
    for (int i=0; i<candidate_count; i++)
    {
        if(strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }

    }
    //rank_names[rank] = name;
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    int temp_ranks[] = {1,2,0};
    add_vote(candidate_count-1,ranks,candidate_count);
    return;
}

//n is ranks_length
void add_vote(int n, int ranks[], int ranks_length)
{
    if ( n <= 0 )
    {
        return ;
    }

    add_vote(n-1, ranks, ranks_length);

    for (int i = 0; i<n; i++)
    {
        printf("%i preferres over  %i\n", ranks[((ranks_length-n)-1)], ranks[(ranks_length-(i+1))] );
        // if (preferences[ranks[((ranks_length-n)-1)]][ranks[(ranks_length-(i+1))]] != 0)
        // {
        //     printf("breath check\n");
        //     preferences[ranks[((ranks_length-n)-1)]][ranks[(ranks_length-(i+1))]] = 1;
        // } else
        // {
        //     preferences[ranks[((ranks_length-n)-1)]][ranks[(ranks_length-(i+1))]]++;
        // }
        preferences[ranks[((ranks_length-n)-1)]][ranks[(ranks_length-(i+1))]]++;
        printf("preference vertor: %i \n", preferences[ranks[((ranks_length-n)-1)]][ranks[(ranks_length-(i+1))]]);
        print_preferences();
      }


}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    int index = 0;
    for (int i = 0; i < candidate_count; i++) {
        for (int j = 0; j < candidate_count; j++) {
            printf("Preferences[%d][%d]: %i\n", i, j, preferences[i][j]);
            if (preferences[i][j] > 0  && preferences[i][j] != preferences[j][i])
            {
                pairs[index].winner = i;
                pairs[index].loser = j;
                printf("selected[%d][%d]: %i\n", i, j, preferences[i][j]);
                printf("%i %i\n",pairs[index].winner, pairs[index].loser);
                index++;
            }


        }
    }

    pair_count = index; // this needs to be reduced by 1 according isntructions

    for (int k = 0; k<=index; k++)
    {
        printf("%i %i %i\n",pairs[k].winner, pairs[k].loser, pair_count);
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    pair highest;
    pair sorted[pair_count];

    for (int i = 0; i < pair_count - 1; i++) {
        // Find the index of the smallest element in the unsorted part
        int min_index = i;
        for (int j = i + 1; j < pair_count; j++) {
            if (preferences[pairs[j].winner][pairs[j].loser] > preferences[pairs[min_index].winner][pairs[min_index].loser]) {
                min_index = j;
            }
        }

        // Swap the smallest element with the first element of the unsorted part
        if (min_index != i) {
            pair temp = pairs[i];
            pairs[i] = pairs[min_index];
            pairs[min_index] = temp;
        }
    }

    for (int k = 0; k<=pair_count; k++)
    {
        printf("this one is %i %i %i\n",pairs[k].winner, pairs[k].loser, preferences[pairs[k].winner][pairs[k].loser]);
    }

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++) {
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;

        // Check if locking creates a cycle
        if (!creates_cycle(winner, loser)) {
            locked[winner][loser] = true; // Lock the pair
        }
    }

    // Optional: Print locked pairs for verification
    for (int i = 0; i < candidate_count; i++) {
        for (int j = 0; j < candidate_count; j++) {
            if (locked[i][j]) {
                printf("Locked: Candidate %d -> Candidate %d\n", i, j);
            }
        }
    }
}

bool creates_cycle(int winner, int loser) {
    // If the loser is the winner, a cycle is detected
    if (loser == winner) {
        return true;
    }

    // Iterate through all candidates to check for cycles
    for (int i = 0; i < candidate_count; i++) {
        // If there's already a lock from the loser to another candidate
        if (locked[loser][i]) {
            // Recursively check if locking the current pair creates a cycle
            if (creates_cycle(winner, i)) {
                return true;
            }
        }
    }
    return false; // No cycle found
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++) {
        bool has_incoming_edge = false;

        // Check if this candidate is locked against by any other candidate
        for (int j = 0; j < candidate_count; j++) {
            if (locked[j][i]) { // If candidate 'j' locks against candidate 'i', candidate 'i' has an incoming edge
                has_incoming_edge = true;
                break; // No need to continue checking if we found an incoming edge
            }
        }

        if (!has_incoming_edge) {
            // If this candidate has no incoming edges, they are the winner
            printf("The winner is: Candidate %s\n", candidates[i]);
            return; // Exit the function after finding the winner
        }
    }
    printf("No winner found.\n");
    //printf("%s\n",candidates[locked[0][0].winner]);
    //return;
}

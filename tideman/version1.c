#include <cs50.h>
#include <stdio.h>
#include <string.h>


// Max number of candidates
#define MAX 3

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
    printf("Preferences:\n");
    for (int i = 0; i < candidate_count; i++) {
        for (int j = 0; j < candidate_count; j++) {
            printf("Preferences[%d][%d]: %i\n", i, j, preferences[i][j]);
        }
    }
}

// Function prototypes
bool vote(int rank, string name, int ranks[], int ranks_length, string candidates_list[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
void add_vote(int n, int ranks[],int ranks_length);

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

        // Query for each rank
        // for (int j = 0; j < candidate_count; j++)
        // {
        //     string name = get_string("Rank %i: ", j + 1);

        //     if (!vote(j, name, ranks , candidate_count, candidates))
        //     {
        //         printf("Invalid vote.\n");
        //         return 3;
        //     }
        // }

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
bool vote(int rank, string name, int ranks[], int ranks_length, string candidates_list[])
{
    // TODO
    string rank_names[ranks_length];
    for (int i=0; i<ranks_length; i++)
    {
        if(strcmp(candidates_list[i], name) == 0)
        {
            rank_names[rank] = name;
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
    int temp_ranks[] = {3,2,1};
    add_vote(2,temp_ranks,3);
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
        if (preferences[ranks[((ranks_length-n)-1)]][ranks[(ranks_length-(i+1))]] != 0)
        {
            printf("breath check\n");
            preferences[ranks[((ranks_length-n)-1)]][ranks[(ranks_length-(i+1))]] = 1;
        } else
        {
            preferences[ranks[((ranks_length-n)-1)]][ranks[(ranks_length-(i+1))]]++;
        }
        printf("preference vertor: %i \n", preferences[ranks[((ranks_length-n)-1)]][ranks[(ranks_length-(i+1))]]);
        print_preferences();
      }


}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    return;
}

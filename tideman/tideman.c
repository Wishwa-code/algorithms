#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

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

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
void add_vote(int n, int ranks[], int ranks_length);
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

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {

            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }
        // for (int l = 0; l<candidate_count;l++)
        // {
        //     printf("rank %i \n",ranks[l]);
        // }

        record_preferences(ranks);

        // printf("\n");
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
    //?update ranks array with candidates arrays position of the
    //?candidate making ranks[i] = candidate_arrays[position] meaning
    //?rank[1] containes the first prefernece of the voter
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    //?adding preference for every candidate from left ro right in the ranks
    //?so if ranks array is 5, ranks(5-1) prefers over ranks (5), and ranks (5-2)
    //?preferres over both ranks rank(5-1) and ranks(5)
    //? likewise keep adding point to the left
    // int temp_ranks[] = {1,2,0};
    add_vote(candidate_count - 1, ranks, candidate_count);
    return;
}

// n is ranks_length
void add_vote(int n, int ranks[], int ranks_length)
{
    if (n <= 0)
    {
        return;
    }

    add_vote(n - 1, ranks, ranks_length);

    for (int i = 0; i < n; i++)
    {
        // printf("%i preferres over  %i\n", ranks[((ranks_length-n)-1)],
        // ranks[(ranks_length-(i+1))] );
        preferences[ranks[((ranks_length - n) - 1)]][ranks[(ranks_length - (i + 1))]]++;
        // printf("preference vector: %i \n",
        // preferences[ranks[((ranks_length-n)-1)]][ranks[(ranks_length-(i+1))]]);
        // print_preferences();
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    int index = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("Preferences[%d][%d]: %i\n", i, j, preferences[i][j]);
            //?add a pair if its only bigger from the both candidates perspectives
            //?during this process tied prefrences and pairs with 0
            //?preferences are ignored
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[index].winner = i;
                pairs[index].loser = j;
                // printf("selected[%d][%d]: %i\n", i, j, preferences[i][j]);
                // printf("%i %i\n",pairs[index].winner, pairs[index].loser);
                index++;
            }
        }
    }

    pair_count = index + 1; //! pairs[0] .. pairs[pair_count-1]

    // for (int k = 0; k<index; k++)
    // {
    //     printf("%i %i %i\n",pairs[k].winner, pairs[k].loser, pair_count-1);
    // }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    //? doing a selection sort in reverse to sort the array
    //?in descending order
    for (int i = 0; i < pair_count - 1; i++)
    {
        // Find the index of the highest pair in the unsorted part
        int min_index = i;
        for (int j = i + 1; j < pair_count; j++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] >
                preferences[pairs[min_index].winner][pairs[min_index].loser])
            {
                min_index = j;
            }
        }

        // Swap the highest pair with the first pair in the unsorted part
        if (min_index != i)
        {
            pair temp = pairs[i];
            pairs[i] = pairs[min_index];
            pairs[min_index] = temp;
        }
    }

    // for (int k = 0; k<pair_count-1; k++)
    // {
    //     printf("this one is %i %i %i\n",pairs[k].winner, pairs[k].loser,
    //     preferences[pairs[k].winner][pairs[k].loser]);
    // }

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;

        //? Check if locking creates a cycle by going each path from strongest
        //? if the same user repeats again then it is not locked
        if (!creates_cycle(winner, loser))
        {
            locked[winner][loser] = true; // Locking the pair
        }
    }

    // for (int i = 0; i < candidate_count; i++) {
    //     for (int j = 0; j < candidate_count; j++) {
    //         if (locked[i][j]) {
    //             printf("Locked: Candidate %d -> Candidate %d\n", i, j);
    //         }
    //     }
    // }
}

bool creates_cycle(int winner, int loser)
{
    // If the loser is the winner, a cycle is detected
    if (loser == winner)
    {
        return true;
    }

    // Iterate through all candidates to check for cycles
    for (int i = 0; i < candidate_count; i++)
    {
        // If there's already a lock from the loser to another candidate
        if (locked[loser][i])
        {
            // Recursively check if locking the current pair creates a cycle
            if (creates_cycle(winner, i))
            {
                return true;
            }
        }
    }
    return false; // returning when no cycle found
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        bool has_incoming_edge = false;

        //? Check if this candidate is locked against by any other candidate
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            { // If candidate 'j' locks against candidate 'i', candidate 'i' has an incoming edge
                has_incoming_edge = true;
                break; // returning when incoming edge found
            }
        }

        if (!has_incoming_edge)
        {
            //? If this candidate has no incoming edges, they are the strongest one in the start of
            //the graph
            printf("%s\n", candidates[i]);
            return;
        }
    }
    printf("No winner found.\n");
    // printf("%s\n",candidates[locked[][]);
    return;
}

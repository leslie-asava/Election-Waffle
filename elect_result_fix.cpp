#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Vote Struct
struct Vote
{
    int position_id;
    int candidate_id;
};

// Functions
int tally_votes();
void tally_position(char position[30], int array_ptr[]);
void vote_position(char position[30], int * array_ptr);
void vote_for_candidates();
char *remove_new_line(char *strbuffer);
bool authenticate_voter(int voter_id);

// The main function
int main()
{

    //vote_for_candidates();
    tally_votes();

    return 0;
}

void display_results(array)
{
	
}

int tally_votes()
{

    // Define titles
	char position_titles[3][30] = {
        "Chairman",
        "Treasurer",
        "Secretary"};
    int positions = 3;
    
    // Array to hold totals for each position
    int position_tallies[3][30] = {0};
    
    // Iterate positions
    int i;
    for (i = 0; i < positions; i++)
    {
        printf("\n\t\tTALLYING\n\t\tThis will take a sec\n");
        
		// Display candidates to choose from
        int *array_ptr = position_tallies[i];
        tally_position(position_titles[i],array_ptr);
    }
}

void tally_position(char position[30], int *array_ptr)
{
    //printf("\n\t\tPosition: %s\n\t\tCandidates\n", position);

    strcat(position, ".txt");
    printf("%s", position);

    // Variables for reading file
    char path[20] = "votes/";

    // Prepare path
    strcat(path, position);

    printf("%s", path);

    // Set up file details
    FILE *candfileptr;
    candfileptr = fopen(path, "r");

    char read_name[30];
    char read_id[30];
    int line_number = 1;
    //int candidate_votes[30] = {0};

    while (fgets(read_id, sizeof(read_id), candfileptr))
    {
        //printf("\n\t\t%d. %s", line_number, read_name);
        line_number += 1; 
        array_ptr[atoi(read_id)] ++;
    }
    
    int i = 0;
	for (i = 0; i < 4; i++)
	{
		printf("%d\n",array_ptr[i]);
	}
    

    fclose(candfileptr);
    
}

void vote_position(char position[30])
{
    printf("\n\t\tPosition: %s\n\t\tCandidates\n", position);

    strcat(position, ".txt");
    printf("%s", position);

    // Variables for reading file
    char path[20] = "candidates/";

    // Prepare path
    strcat(path, position);

    printf("%s", path);

    // Set up file details
    FILE *candfileptr;
    candfileptr = fopen(path, "r");

    char read_name[30];
    char read_id[30];
    int line_number = 1;

    while (fgets(read_name, sizeof(read_name), candfileptr))
    {
        printf("\n\t\t%d. %s", line_number, read_name);
        line_number += 1;
    }

    fclose(candfileptr);

    printf("\n\t\tType your selection: ");
    scanf("%s", read_id);

    printf("\n\t\t%s", read_id);
    
    // Change path to votes
	strcpy(path,"votes/");
	
	strcat(path, position);

    // Set up file details
    FILE *votesfileptr;
    votesfileptr = fopen(path, "a");
    
    strcat(read_id, "\n");
    
    // Append Candidate ID to file
	fprintf(votesfileptr, read_id);
	
    fclose(votesfileptr);
    
    
}

void vote_for_candidates()
{
    // Authenticate voter
    authenticate_voter(10);

    // Iterate positions
    char position_titles[3][30] = {
        "Chairman",
        "Treasurer",
        "Secretary"};
    int positions = 3;
    int i;
    for (i = 0; i < positions; i++)
    {
        printf("\n\t\tVOTING\n\t\tMake your best selections\n");
        // Display candidates to choose from
        vote_position(position_titles[i]);
    }
}

char *remove_new_line(char *strbuffer)
{
    size_t len = strlen(strbuffer);
    if (strbuffer[len - 1] == '\n')
    {
        strbuffer[len - 1] = '\0';
    }
    return strbuffer;
}

bool authenticate_voter(int voter_id)
{
    char id_str[20];
    sprintf(id_str, "%d", voter_id);

    // Set user txt file path
    char path[] = "voters/";
    char extension[] = ".txt";
    strcat(id_str, extension);
    strcat(path, id_str);

    // Get user details from file
    FILE *userfileptr;
    userfileptr = fopen(path, "r");

    char line_str[30];
    char read_name[30];
    char read_pass[30];
    int line_number = 1;

    while (fgets(line_str, sizeof(line_str), userfileptr))
    {
        if (line_number == 1)
        {
            line_number++;
            continue;
        }
        else if (line_number == 2)
        {
            strcpy(read_name, remove_new_line(line_str));
            line_number++;
        }
        else
        {
            strcpy(read_pass, remove_new_line(line_str));
        }
    }

    fclose(userfileptr);

    bool authenticated = false;

    while (!authenticated)
    {
        // Prompt
        char input_name[30];
        char input_pass[30];
        printf("\n\t\tVOTER AUTHENTICATION\n\t\tThis should take a second :)\n");
        printf("\n\t[--] Your name: ");
        scanf("%s", input_name);
        printf("\t[--] Your passphrase: ");
        scanf("%s", input_pass);

        // Determine if credentials match
        if (!strcmp(read_name, input_name) && !strcmp(read_pass, input_pass))
        {
            system("cls");
            printf("\n\t[++] Success!!!\n");
            return true;
        }
        else
        {
            system("cls");
            printf("\n\t[*#@!] No match found :(\n");
            char retry[1];
            printf("\n\t[--] Retry? [y/n]: ");
            scanf("%s", retry);
            if (!strcmp(retry, "n"))
            {
                return false;
            }
            else
            {
                system("cls");
            }
        }
    }
}

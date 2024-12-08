/*
    --- Day 2: Red-Nosed Reports ---
    Fortunately, the first location The Historians want to search isn't a long walk from the Chief Historian's office.

    While the Red-Nosed Reindeer nuclear fusion/fission plant appears to contain no sign of the Chief Historian, the engineers there run up to you as soon as they see you. Apparently, they still talk about the time Rudolph was saved through molecular synthesis from a single electron.

    They're quick to add that - since you're already here - they'd really appreciate your help analyzing some unusual data from the Red-Nosed reactor. You turn to check if The Historians are waiting for you, but they seem to have already divided into groups that are currently searching every corner of the facility. You offer to help with the unusual data.

    The unusual data (your puzzle input) consists of many reports, one report per line. Each report is a list of numbers called levels that are separated by spaces. For example:

    7 6 4 2 1
    1 2 7 8 9
    9 7 6 2 1
    1 3 2 4 5
    8 6 4 4 1
    1 3 6 7 9
    This example data contains six reports each containing five levels.

    The engineers are trying to figure out which reports are safe. The Red-Nosed reactor safety systems can only tolerate levels that are either gradually increasing or gradually decreasing. So, a report only counts as safe if both of the following are true:

    The levels are either all increasing or all decreasing.
    Any two adjacent levels differ by at least one and at most three.
    In the example above, the reports can be found safe or unsafe by checking those rules:

    7 6 4 2 1: Safe because the levels are all decreasing by 1 or 2.
    1 2 7 8 9: Unsafe because 2 7 is an increase of 5.
    9 7 6 2 1: Unsafe because 6 2 is a decrease of 4.
    1 3 2 4 5: Unsafe because 1 3 is increasing but 3 2 is decreasing.
    8 6 4 4 1: Unsafe because 4 4 is neither an increase or a decrease.
    1 3 6 7 9: Safe because the levels are all increasing by 1, 2, or 3.
    So, in this example, 2 reports are safe.

    Analyze the unusual data from the engineers. How many reports are safe?

    --- Part Two ---
    The engineers are surprised by the low number of safe reports until they realize they forgot to tell you about the Problem Dampener.

    The Problem Dampener is a reactor-mounted module that lets the reactor safety systems tolerate a single bad level in what would otherwise be a safe report. It's like the bad level never happened!

    Now, the same rules apply as before, except if removing a single level from an unsafe report would make it safe, the report instead counts as safe.

    More of the above example's reports are now safe:

    7 6 4 2 1: Safe without removing any level.
    1 2 7 8 9: Unsafe regardless of which level is removed.
    9 7 6 2 1: Unsafe regardless of which level is removed.
    1 3 2 4 5: Safe by removing the second level, 3.
    8 6 4 4 1: Safe by removing the third level, 4.
    1 3 6 7 9: Safe without removing any level.
    Thanks to the Problem Dampener, 4 reports are actually safe!

    Update your analysis by handling situations where the Problem Dampener can remove a single level from unsafe reports. How many reports are now safe?
*/
#include <stdio.h>
#include <stdlib.h>

#include "../miscellaneous/print_colors.h"

void remove_element(int* array, int index, int* num_elements);
void insert_element(int array[], int* num_elements, int index, int value);

int check_if_array_is_safe(int* array, int lengh_of_array);
int solve_with_problem_dumper(int* array, int lengh_of_array);

void read_data_and_process_input(const char* filename, int* results);

int main()
{
    int results[2];
    read_data_and_process_input("input.txt", results);

    printf(
        COLOR_GREEN "RESULT TO DAY ONE PART ONE:"COLOR_RESET" %d"COLOR_GREEN"\nRESULT TO DAY ONE PART TWO:"COLOR_RESET" %ld\n", 
        results[0], 
        results[1]
    );
}

void remove_element(int array[], int index, int* num_elements) {
    if (index < 0 || index >= *num_elements) {
        printf(COLOR_RED"Error: Index out of bounds.\n"COLOR_RESET);
        return;
    }

    for (int i = index; i < *num_elements - 1; i++) {
        array[i] = array[i + 1];
    }

    (*num_elements)--;
}

void insert_element(int array[], int* num_elements, int index, int value) 
{
    if (index < 0 || index > *num_elements) 
    {
        printf(COLOR_RED"Error: Index out of bounds.\n"COLOR_RESET);
        return;
    }

    for (int i = *num_elements; i > index; i--) 
    {
        array[i] = array[i - 1];
    }

    array[index] = value;

    (*num_elements)++;
}

void read_data_and_process_input(const char* filename, int* results)
{
    FILE* file_ptr;
    int data_line[1000];
    int num_of_elements_per_line = 0;
    char next;

    results[0] = 0;
    results[1] = 0;

    file_ptr = fopen(filename, "r");

    if(file_ptr == NULL)
    {
        printf(COLOR_RED"PROBLEM WITH FILE"COLOR_RESET);
    }
    
    while (!feof(file_ptr))
    {
        while (fscanf(file_ptr, "%d", &data_line[num_of_elements_per_line]))
        {
            num_of_elements_per_line++;
            next = fgetc(file_ptr);

            if(next == '\n' || next == EOF)
            {
                break;
            }
        }
        if(check_if_array_is_safe(data_line, num_of_elements_per_line) == 1)
        {
            results[0]++;
        }
        if(solve_with_problem_dumper(data_line, num_of_elements_per_line) == 1)
        {
            results[1]++;
        }
        num_of_elements_per_line = 0;
    }

}

int check_if_array_is_safe(int* array, int lengh_of_array)
{
    int desending = 0;

    if(array[0] > array[1])
    {
        desending = 1;
    }
    else
    {
        desending = 0;
    }
    for(int i = 0; i < lengh_of_array - 1; i++)
    {
        if(desending == 0)
        {
            if(array[i] >= array[i + 1] || abs(array[i] - array[i + 1]) > 3)
            {
                return 0;
            }
        }
        else
        {
            if(array[i] <= array[i + 1] || abs(array[i] - array[i + 1]) > 3)
            {
                return 0;
            }
        }
    }
    return 1;
}

int solve_with_problem_dumper(int* array, int lengh_of_array)
{
    int array_is_safe = 0;
    int saved_element;

    array_is_safe = check_if_array_is_safe(array, lengh_of_array);

    for(int i = 0; i < lengh_of_array && array_is_safe == 0; i++)
    {
        saved_element = array[i];
        remove_element(array, i, &lengh_of_array);
        array_is_safe = check_if_array_is_safe(array, lengh_of_array);
        if(array_is_safe == 1)
        {
            break;
        }
        insert_element(array, &lengh_of_array, i, saved_element);
    }
    return array_is_safe;
}
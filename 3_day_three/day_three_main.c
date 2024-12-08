/*
    --- Day 3: Mull It Over ---
    "Our computers are having issues, so I have no idea if we have any Chief Historians in stock! You're welcome to check the warehouse, though," says the mildly flustered shopkeeper at the North Pole Toboggan Rental Shop. The Historians head out to take a look.

    The shopkeeper turns to you. "Any chance you can see why our computers are having issues again?"

    The computer appears to be trying to run a program, but its memory (your puzzle input) is corrupted. All of the instructions have been jumbled up!

    It seems like the goal of the program is just to multiply some numbers. It does that with instructions like mul(X,Y), where X and Y are each 1-3 digit numbers. For instance, mul(44,46) multiplies 44 by 46 to get a result of 2024. Similarly, mul(123,4) would multiply 123 by 4.

    However, because the program's memory has been corrupted, there are also many invalid characters that should be ignored, even if they look like part of a mul instruction. Sequences like mul(4*, mul(6,9!, ?(12,34), or mul ( 2 , 4 ) do nothing.

    For example, consider the following section of corrupted memory:

    xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))
    Only the four highlighted sections are real mul instructions. Adding up the result of each instruction produces 161 (2*4 + 5*5 + 11*8 + 8*5).

    Scan the corrupted memory for uncorrupted mul instructions. What do you get if you add up all of the results of the multiplications?

    --- Part Two ---
    As you scan through the corrupted memory, you notice that some of the conditional statements are also still intact. If you handle some of the uncorrupted conditional statements in the program, you might be able to get an even more accurate result.

    There are two new instructions you'll need to handle:

    The do() instruction enables future mul instructions.
    The don't() instruction disables future mul instructions.
    Only the most recent do() or don't() instruction applies. At the beginning of the program, mul instructions are enabled.

    For example:

    xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))
    This corrupted memory is similar to the example from before, but this time the mul(5,5) and mul(11,8) instructions are disabled because there is a don't() instruction before them. The other mul instructions function normally, including the one at the end that gets re-enabled by a do() instruction.

    This time, the sum of the results is 48 (2*4 + 8*5).

    Handle the new instructions; what do you get if you add up all of the results of just the enabled multiplications?
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../miscellaneous/print_colors.h"

int get_input(char* input_data, const char* filename);
int solve_day_three_p1(char* input_data, int number_of_characters);
int solve_day_three_p2(char* input_data, int number_of_characters);

int main()
{
    char input_data[100000];
    int number_of_characters = 0;

    number_of_characters = get_input(input_data, "input.txt");

    printf(
        COLOR_GREEN"RESULT DAY THREE_P1: "COLOR_RESET"%d\n"COLOR_GREEN"RESULT DAY THREE_P1: "COLOR_RESET"%d\n",
        solve_day_three_p1(input_data, number_of_characters),
        solve_day_three_p2(input_data, number_of_characters)

    );
    
    return 0;
}

int get_input(char* input_data, const char* filename)
{
    FILE* file_prt;
    int number_of_characters = 0;

    file_prt = fopen(filename, "r");
    if(file_prt == NULL)
    {
        printf(COLOR_RED"PROBLEM WITH INPUT FILE"COLOR_RESET);
        return 0;
    }

    while (!feof(file_prt))
    {
        input_data[number_of_characters] = fgetc(file_prt);
        number_of_characters++;
    }
    
    for(int i = 0; i < number_of_characters; i++)
    {
        //printf("%c", input_data[i]);
    }

    return number_of_characters;
}

int solve_day_three_p1(char* input_data, int number_of_characters)
{
    /*
        look for "mul("
        if "mul(" is found look for "," check if number between mul( and , is valid
        look for ) and check if number between , and ) is valid
        calculate product and add to final sum
    */
    char* look_for = "mul(";
    char separator = ',';
    char end_of_instruction = ')';

    char check_for_beggining[5];

    int sum_of_muls = 0;
    int mul_result = 0;

    int sub_len;
    char temp[11];
    char* endptr;

    for(int i = 0; i < number_of_characters; i++)
    {
        strncpy(check_for_beggining, input_data + i, 4);
        check_for_beggining[4] = '\0';

        if(strcmp(check_for_beggining, look_for) == 0)
        {
            printf("%s + ", check_for_beggining, input_data[i + 4]);
            //look for ','
            int j = i + 4;
            while (input_data[j] != separator && j - i <= 10)
            {
                j++;
            }

            //copy resulting number and check if it represents a number
            sub_len = j - (i + 4);
            strncpy(temp, input_data + i + 4, sub_len);

            temp[sub_len] = '\0';
            long number_1 = strtol(temp, &endptr, 10);
            printf("%s", temp);

            if (*endptr == '\0') 
            {
                //look for ')'
                int q = j + 1;
                while (input_data[q] != end_of_instruction && q - j <= 10)
                {
                    q++;
                    
                    
                }
                //copy resulting number and check if it represents a number
                sub_len = q - (j + 1);
                strncpy(temp, input_data + j + 1, sub_len);
                temp[sub_len] = '\0';
                printf(" + %s", temp);

                long number_2 = strtol(temp, &endptr, 10);
                if (*endptr == '\0') 
                {
                    printf(COLOR_GREEN" -> VALID"COLOR_RESET);

                    sum_of_muls = sum_of_muls + (number_1 * number_2);
                }
                else
                {
                    printf(COLOR_RED" -> INVALID"COLOR_RESET);
                }
            } 
            else 
            {
                printf(COLOR_RED" -> INVALID"COLOR_RESET);
            }
            printf("\n");
        }
    }

    return sum_of_muls;
}

int solve_day_three_p2(char* input_data, int number_of_characters)
{
    /*
        look for "mul("
        if "mul(" is found look for "," check if number between mul( and , is valid
        look for ) and check if number between , and ) is valid
        calculate product and add to final sum

        Only do the above if there was not a don't before the mul
    */
    char* look_for_validator = "do()";
    char* look_for_invalidator = "don't()"; 

    int valid = 1;
   
    char* look_for = "mul(";
    char separator = ',';
    char end_of_instruction = ')';

    char check_for_beggining[5];
    char check_for_validator[5];
    char check_for_invalidator[8];

    int sum_of_muls = 0;
    int mul_result = 0;

    int sub_len;
    char temp[11];
    char* endptr;

    for(int i = 0; i < number_of_characters; i++)
    {
        strncpy(check_for_beggining, input_data + i, 4);
        check_for_beggining[4] = '\0';

        strncpy(check_for_validator, input_data + i, 4);
        check_for_validator[4] = '\0';

        strncpy(check_for_invalidator, input_data + i, 7);
        check_for_invalidator[7] = '\0';

        if(strcmp(check_for_invalidator, look_for_invalidator) == 0)
        {
            valid = 0;
        }
        if(strcmp(check_for_validator, look_for_validator) == 0)
        {
            valid = 1;
        }

        if(strcmp(check_for_beggining, look_for) == 0 && valid == 1)
        {
            printf("%s + ", check_for_beggining, input_data[i + 4]);
            //look for ','
            int j = i + 4;
            while (input_data[j] != separator && j - i <= 10)
            {
                j++;
            }

            //copy resulting number and check if it represents a number
            sub_len = j - (i + 4);
            strncpy(temp, input_data + i + 4, sub_len);

            temp[sub_len] = '\0';
            long number_1 = strtol(temp, &endptr, 10);
            printf("%s", temp);

            if (*endptr == '\0') 
            {
                //look for ')'
                int q = j + 1;
                while (input_data[q] != end_of_instruction && q - j <= 10)
                {
                    q++;
                    
                    
                }
                //copy resulting number and check if it represents a number
                sub_len = q - (j + 1);
                strncpy(temp, input_data + j + 1, sub_len);
                temp[sub_len] = '\0';
                printf(" + %s", temp);

                long number_2 = strtol(temp, &endptr, 10);
                if (*endptr == '\0') 
                {
                    printf(COLOR_GREEN" -> VALID"COLOR_RESET);

                    sum_of_muls = sum_of_muls + (number_1 * number_2);
                }
                else
                {
                    printf(COLOR_RED" -> INVALID"COLOR_RESET);
                }
            } 
            else 
            {
                printf(COLOR_RED" -> INVALID"COLOR_RESET);
            }
            printf("\n");
        }
    }

    return sum_of_muls;
}
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "print_colors.h"

typedef struct input_data {
    int x;
    int y;
} input_data;

int get_data(const char *filename, input_data *ret_data);
void bubbleSort(input_data* data, int size_of_data);

int solve_day_one_p1(input_data* data, int lenght_of_array);
long long solve_day_one_p2(input_data* data, int length_of_data);

int main() {
    input_data data[1000];
    int lenght_of_data = 0;
    lenght_of_data = get_data("input.txt", data);

    printf(
        COLOR_GREEN "RESULT TO DAY ONE PART ONE:"COLOR_RESET" %d"COLOR_GREEN"\nRESULT TO DAY ONE PART TWO:"COLOR_RESET" %ld\n", 
        solve_day_one_p1(data, lenght_of_data), 
        solve_day_one_p2(data, lenght_of_data)
    );

    return 0;
}

void bubbleSort(input_data* data, int lenght_of_data)
{
    int aux;
    for(int i = 0; i < lenght_of_data - 1; i++)
    {
        for(int j = i + 1; j < lenght_of_data; j++)
        {
            if(data[i].x > data[j].x)
            {
                aux = data[i].x;
                data[i].x = data[j].x;
                data[j].x = aux;
            }

            if(data[i].y > data[j].y)
            {
                aux = data[i].y;
                data[i].y = data[j].y;
                data[j].y = aux;
            }
        }
    }
}

int get_data(const char *filename, input_data *ret_data) 
{
    int ret_data_size = 0;

    FILE *file = fopen(filename, "r");
    if (file == NULL) 
    {
        perror("Error opening file");
        return 0;
    }

    while (fscanf(file, "%d %d", &ret_data[ret_data_size].x, &ret_data[ret_data_size].y) == 2) {
        ret_data_size++;
    }

    if (ferror(file)) {
        perror("Error while reading file");
    }

    fclose(file);
    return ret_data_size;
}

int solve_day_one_p1(input_data* data, int lenght_of_array)
{
    int ret_data = 0;

    bubbleSort(data, lenght_of_array);

    for (int i = 0; i < lenght_of_array; i++) 
    {
        if(data[i].x - data[i].y > 0)
        {
            ret_data = ret_data + (data[i].x - data[i].y);
        }
        else
        {
            ret_data = ret_data + (data[i].y - data[i].x);
        }
    }

    return ret_data;
}

long long solve_day_one_p2(input_data* data, int length_of_data)
{
    long long ret_data = 0;
    uint8_t data_frequency[100000] = {0};
    for(int i = 0; i < length_of_data; i++)
    {
        data_frequency[data[i].y]++;
    }
    for(int i = 0; i < length_of_data; i++)
    {
        ret_data = ret_data + (data[i].x * data_frequency[data[i].x]);
    }
    return ret_data;
}
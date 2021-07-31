/* Reads an input file with numbers, calculates the average and the maximum and
prints the findings to the standard output and to an output file
*/

#include <stdio.h>
#define MAX_DIGITS 100

/* reads the data in the data in the file passed in the first parameter
   assuming the first value is the number of integers to read into the 
   data array, populates the data array and returns the size of the data array
*/
int read_data(FILE *ptr, int data[])
{
    int size = 0, index = 0;
    fscanf(ptr, "%d", &size);

    while (fscanf(ptr, "%d", &data[index]) == 1)
        (index)++;

    return size;
}

/* calculates and returns the average of the values passed in the data array,
    identifies the maximum and returns in the max variable
 */
double average(int data[], int size, int *max)
{
    int i;
    *max = 0;
    double avg = 0.0;
    for (i = 0; i < size; i++)
    {
        avg += data[i];

        //keep track of the maximum
        if (data[i] > *max)
            *max = data[i];
    }
    return (avg / size);
}

/* prints the data count, maximum value, average and input data to the standard output 
    and the output file indicated in the first parameter
*/
void print_data(FILE *outputFile, const int d[], const int size, const int maximum, const double average)
{
    printf("\nData count: %d\nMaximum: %d\nAverage: %f\n", size, maximum, average);
    fprintf(outputFile, "\nData count: %d\nMaximum: %d\nAverage: %f\n", size, maximum, average);
    printf("\n%s:\n", "Input Data");
    fprintf(outputFile, "\n%s:\n", "Input Data");
    for (int i = 0; i < size; i++)
    {
        printf("%3d  ", d[i]);
        fprintf(outputFile, "%3d  ", d[i]);
        if ((i + 1) % 10 == 0){
            printf("\n");
            fprintf(outputFile, "\n");
        }
    }
}

int main(int argc, char **argv)
{
    FILE *ifp, *ofp;
    char *iFile = "integers.txt", *oFile = "answer-hw3";
    int data_count = 0, data[MAX_DIGITS] = {0}, max = 0;

    //if the right number of arguments is passed, overwrite the default file names
    if (argc == 3)
    {
        iFile = argv[1];
        oFile = argv[2];
    }

    //open input and output files
    ifp = fopen(iFile, "r");
    ofp = fopen(oFile, "w");

    rewind(ifp);
    data_count = read_data(ifp, data);
    double avg = average(data, data_count, &max);
    print_data(ofp, data, data_count, max, avg);

    // close external files
    fclose(ifp);
    fclose(ofp);

    return 0;
}
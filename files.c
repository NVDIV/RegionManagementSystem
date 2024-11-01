#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Region structure

struct Region {
    char name[50];
    double area;
    int population;
};

// Function prototypes

int compareByName(const void *a, const void *b);
int compareByArea(const void *a, const void *b);
int compareByPopulation(const void *a, const void *b);
void printRegion(struct Region *region);

int main() 
{
    int choice;
    FILE *file;
    struct Region region;
    struct Region *regions = NULL;
    int numRegions = 0;

    do {
        // Menu

        printf("1. Create a file\n");
        printf("2. Open an existing file and load data\n");
        printf("3. Add a new region\n");
        printf("4. Delete region(s)\n");
        printf("5. Delete the file\n");
        printf("6. Edit region(s)\n");
        printf("7. Sort regions\n");
        printf("8. Insert new region(s) into sorted file\n");
        printf("9. Display regions\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                // Create file

                file = fopen("regions.dat", "wb");
                fclose(file);
                break;
            case 2:
                // Open file

                file = fopen("regions.dat", "rb");
                if (file != NULL) 
                {
                    fseek(file, 0, SEEK_END);
                    numRegions = ftell(file) / sizeof(struct Region);
                    regions = (struct Region *)malloc(numRegions * sizeof(struct Region));
                    rewind(file);
                    fread(regions, sizeof(struct Region), numRegions, file);
                    fclose(file);
                } else 
                {
                    printf("File does not exist.\n");
                }
                break;
            case 3:
                // Add region

                file = fopen("regions.dat", "ab");
                printf("Enter region name: ");
                scanf("%s", region.name);
                printf("Enter region area: ");
                scanf("%lf", &region.area);
                printf("Enter region population: ");
                scanf("%d", &region.population);
                fwrite(&region, sizeof(struct Region), 1, file);
                fclose(file);
                break;
            case 4:
                // Delete region

                file = fopen("regions.dat", "rb");
                if (file != NULL) {
                    fseek(file, 0, SEEK_END);
                    numRegions = ftell(file) / sizeof(struct Region);
                    fclose(file);

                    // Show regions

                    printf("Current regions:\n");
                    for (int i = 0; i < numRegions; i++) 
                    {
                        printRegion(&regions[i]);
                    }

                    int deleteIndex;
                    printf("Enter the index of the region to delete (starting from 0): ");
                    scanf("%d", &deleteIndex);

                    if (deleteIndex >= 0 && deleteIndex < numRegions) 
                    {
                        // Delete region

                        file = fopen("regions.dat", "wb");
                        for (int i = 0; i < numRegions; i++) {
                            if (i != deleteIndex) {
                                fwrite(&regions[i], sizeof(struct Region), 1, file);
                            }
                        }
                        fclose(file);
                    } 
                    else 
                    {
                        printf("Invalid index.\n");
                    }
                } 
                else 
                {
                    printf("File does not exist.\n");
                }
                break;
            case 5:
                // Delete file

                if (remove("regions.dat") == 0) {
                    printf("File deleted successfully.\n");
                } else {
                    printf("Error deleting file.\n");
                }
                break;
            case 6:
                // Edit regions

                file = fopen("regions.dat", "rb");
                if (file != NULL) {
                    fseek(file, 0, SEEK_END);
                    numRegions = ftell(file) / sizeof(struct Region);
                    fclose(file);

                    // Show regions

                    printf("Current regions:\n");
                    for (int i = 0; i < numRegions; i++) 
                    {
                        printRegion(&regions[i]);
                    }

                    int editIndex;
                    printf("Enter the index of the region to edit (starting from 0): ");
                    scanf("%d", &editIndex);

                    if (editIndex >= 0 && editIndex < numRegions) 
                    {
                        // Edit region

                        printf("Enter new region name: ");
                        scanf("%s", regions[editIndex].name);
                        printf("Enter new region area: ");
                        scanf("%lf", &regions[editIndex].area);
                        printf("Enter new region population: ");
                        scanf("%d", &regions[editIndex].population);

                        // Save new array into file

                        file = fopen("regions.dat", "wb");
                        fwrite(regions, sizeof(struct Region), numRegions, file);
                        fclose(file);
                    } else {
                        printf("Invalid index.\n");
                    }
                } else {
                    printf("File does not exist.\n");
                }
                break;
            case 7:
                // Sort

                file = fopen("regions.dat", "rb");
                if (file != NULL) {
                    fseek(file, 0, SEEK_END);
                    numRegions = ftell(file) / sizeof(struct Region);
                    fclose(file);

                    // Show regions

                    printf("Current regions:\n");
                    for (int i = 0; i < numRegions; i++) {
                        printRegion(&regions[i]);
                    }

                    int sortChoice;
                    printf("Choose sorting criteria:\n");
                    printf("1. Sort by name\n2. Sort by area\n3. Sort by population\n");
                    scanf("%d", &sortChoice);

                    switch (sortChoice) {
                        case 1:
                            qsort(regions, numRegions, sizeof(struct Region), compareByName);
                            break;
                        case 2:
                            qsort(regions, numRegions, sizeof(struct Region), compareByArea);
                            break;
                        case 3:
                            qsort(regions, numRegions, sizeof(struct Region), compareByPopulation);
                            break;
                        default:
                            printf("Invalid choice.\n");
                            break;
                    }

                    // Show sorted

                    printf("Sorted regions:\n");
                    for (int i = 0; i < numRegions; i++) {
                        printRegion(&regions[i]);
                    }

                    // Save sorted array into file

                    file = fopen("regions.dat", "wb");
                    fwrite(regions, sizeof(struct Region), numRegions, file);
                    fclose(file);
                } else {
                    printf("File does not exist.\n");
                }
                break;
                case 8:
                // Insert new records into a sorted file
                file = fopen("regions.dat", "rb");
                if (file != NULL) {
                    fseek(file, 0, SEEK_END);
                    numRegions = ftell(file) / sizeof(struct Region);
                    fclose(file);

                    // Display current records
                    printf("Current regions:\n");
                    for (int i = 0; i < numRegions; i++) {
                        printRegion(&regions[i]);
                    }

                    // Enter new records
                    int numNewRegions;
                    printf("Enter the number of new regions: ");
                    scanf("%d", &numNewRegions);

                    for (int i = 0; i < numNewRegions; i++) {
                        printf("Enter new region name: ");
                        scanf("%s", region.name);
                        printf("Enter new region area: ");
                        scanf("%lf", &region.area);
                        printf("Enter new region population: ");
                        scanf("%d", &region.population);

                        // Add a new record to the sorted array
                        regions = (struct Region *)realloc(regions, (numRegions + 1) * sizeof(struct Region));
                        int insertIndex = 0;
                        while (insertIndex < numRegions && strcmp(region.name, regions[insertIndex].name) > 0) {
                            insertIndex++;
                        }

                        // Shift existing records
                        for (int j = numRegions; j > insertIndex; j--) {
                            regions[j] = regions[j - 1];
                        }

                        // Insert the new record
                        regions[insertIndex] = region;
                        numRegions++;
                    }

                    // Write the sorted array to the file
                    file = fopen("regions.dat", "wb");
                    fwrite(regions, sizeof(struct Region), numRegions, file);
                    fclose(file);
                } else {
                    printf("File does not exist.\n");
                }
                break;
            case 9:
                // Display records on the screen
                for (int i = 0; i < numRegions; i++) {
                    printRegion(&regions[i]);
                }
                break;
            case 0:
                printf("Exiting the program.\n");
                return 0;

            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }
    while (getchar() != '0');

    return 0;
}

// Compare by name

int compareByName(const void *a, const void *b) 
{
    return strcmp(((struct Region *)a)->name, ((struct Region *)b)->name);
}

// Compare by area

int compareByArea(const void *a, const void *b) 
{
    return (((struct Region *)a)->area > ((struct Region *)b)->area) - (((struct Region *)a)->area < ((struct Region *)b)->area);
}

// Compare by population

int compareByPopulation(const void *a, const void *b) 
{
    return ((struct Region *)a)->population - ((struct Region *)b)->population;
}

// Print region

void printRegion(struct Region *region) 
{
    printf("Name: %s\nArea: %.2lf sq. km\nPopulation: %d\n\n", region->name, region->area, region->population);
}
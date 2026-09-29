#include <stdio.h>

#define MAX 100
#define NAME_LENGTH 50

struct Product
{
    int id;
    char name[NAME_LENGTH];
    int weight;
};

void sortDescending(struct Product products[], int n)
{
    int i, j;
    struct Product temp;

    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (products[i].weight < products[j].weight)
            {
                temp = products[i];
                products[i] = products[j];
                products[j] = temp;
            }
        }
    }
}

int main()
{
    struct Product products[MAX];
    struct Product boxes[MAX][MAX];

    int boxUsed[MAX] = {0};
    int itemCount[MAX] = {0};

    int capacity, n;
    int i, j;
    int boxCount = 0;
    int placed;

    int totalUsed = 0;
    int totalCapacity;
    int unusedCapacity;
    float utilization;

    printf("================================================\n");
    printf("     WAREHOUSE BOX PACKAGING OPTIMIZATION\n");
    printf("================================================\n\n");

    printf("Enter box capacity (kg): ");
    scanf("%d", &capacity);

    if (capacity <= 0)
    {
        printf("Invalid box capacity.\n");
        return 0;
    }

    printf("Enter number of products: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX)
    {
        printf("Invalid number of products.\n");
        return 0;
    }

    printf("\nEnter product details:\n");

    for (i = 0; i < n; i++)
    {
        products[i].id = i + 1;

        printf("\nProduct %d name: ", i + 1);
        scanf("%s", products[i].name);

        printf("Weight (kg): ");
        scanf("%d", &products[i].weight);

        if (products[i].weight <= 0)
        {
            printf("Invalid product weight.\n");
            return 0;
        }

        if (products[i].weight > capacity)
        {
            printf("Product weight cannot exceed box capacity.\n");
            return 0;
        }
    }

   
    sortDescending(products, n);

    printf("\n================================================\n");
    printf("          GREEDY PACKING PROCESS\n");
    printf("================================================\n");

    printf("\nProducts after sorting by weight:\n");

    for (i = 0; i < n; i++)
    {
        printf("%d kg", products[i].weight);

        if (i < n - 1)
            printf(" -> ");
    }

    printf("\n\n");

   

    for (i = 0; i < n; i++)
    {
        placed = 0;

        
        for (j = 0; j < boxCount; j++)
        {
            if (boxUsed[j] + products[i].weight <= capacity)
            {
                boxes[j][itemCount[j]] = products[i];
                itemCount[j]++;

                boxUsed[j] += products[i].weight;

                printf("Step %d: %s (%d kg) -> Box %d\n",
                       i + 1,
                       products[i].name,
                       products[i].weight,
                       j + 1);

                printf("        Box %d capacity: %d / %d kg\n\n",
                       j + 1,
                       boxUsed[j],
                       capacity);

                placed = 1;
                break;
            }
        }

        
        if (placed == 0)
        {
            boxes[boxCount][0] = products[i];
            itemCount[boxCount] = 1;
            boxUsed[boxCount] = products[i].weight;

            printf("Step %d: %s (%d kg) -> NEW Box %d\n",
                   i + 1,
                   products[i].name,
                   products[i].weight,
                   boxCount + 1);

            printf("        Box %d capacity: %d / %d kg\n\n",
                   boxCount + 1,
                   boxUsed[boxCount],
                   capacity);

            boxCount++;
        }
    }

   

    printf("================================================\n");
    printf("              PACKAGING RESULT\n");
    printf("================================================\n");

    for (i = 0; i < boxCount; i++)
    {
        printf("\nBox %d\n", i + 1);
        printf("-----------------------------------------------\n");

        for (j = 0; j < itemCount[i]; j++)
        {
            printf("Product %-3d %-15s %d kg\n",
                   boxes[i][j].id,
                   boxes[i][j].name,
                   boxes[i][j].weight);
        }

        printf("-----------------------------------------------\n");
        printf("Used Capacity : %d / %d kg\n",
               boxUsed[i], capacity);

        printf("Remaining     : %d kg\n",
               capacity - boxUsed[i]);

        totalUsed += boxUsed[i];
    }

    totalCapacity = boxCount * capacity;
    unusedCapacity = totalCapacity - totalUsed;

    utilization =
        ((float)totalUsed / totalCapacity) * 100;

    printf("\n================================================\n");
    printf("                 FINAL ANALYSIS\n");
    printf("================================================\n");

    printf("Total Products    : %d\n", n);
    printf("Total Boxes Used  : %d\n", boxCount);
    printf("Total Capacity    : %d kg\n", totalCapacity);
    printf("Used Capacity     : %d kg\n", totalUsed);
    printf("Unused Capacity   : %d kg\n", unusedCapacity);
    printf("Space Utilization : %.2f%%\n", utilization);

    printf("================================================\n");

    return 0;
}
#include<stdio.h>

// Function to delete an element from the array
void deleteElement(int arr[], int *size, int index) {
    if (index < 0 || index >= *size) return;
    for (int i = index; i < *size - 1; i++) {
        arr[i] = arr[i + 1];
    }
    (*size)--;
}

// Bubble sort to sort the array in ascending order
void bubblesort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n, car = 0;
    scanf("%d", &n);
    int s[n];
    int size = n;
    
    // Input the group sizes
    for(int i = 0; i < n; i++) {
        scanf("%d", &s[i]);
    }
    
    // Sort the array to make matching easier
    bubblesort(s, size);
    
    // First pass: Match 3s with 1s
    for(int i = 0; i < size; i++) {
        if(s[i] == 3) {
            // Look for a 1 to pair with this 3
            for(int j = 0; j < size; j++) {
                if(s[j] == 1) {
                    car++;  // One taxi for this pair
                    deleteElement(s, &size, i);  // Remove the 3
                    deleteElement(s, &size, j);  // Remove the 1
                    i--;    // Adjust index after deletion
                    break;
                }
            }
        }
    }
    
    // Second pass: Match 2s with 2s
    for(int i = 0; i < size; i++) {
        if(s[i] == 2) {
            // Look for another 2 to pair with
            for(int j = i + 1; j < size; j++) {
                if(s[j] == 2) {
                    car++;  // One taxi for this pair
                    deleteElement(s, &size, j);  // Remove the second 2
                    deleteElement(s, &size, i);  // Remove the first 2
                    i--;    // Adjust index after deletion
                    break;
                }
            }
        }
    }
    
    // Third pass: Match 2s with 1s (up to two 1s)
    for(int i = 0; i < size; i++) {
        if(s[i] == 2) {
            int ones_needed = 2;  // A 2 can take up to two 1s
            // Look for 1s to pair with this 2
            for(int j = 0; j < size && ones_needed > 0; j++) {
                if(s[j] == 1) {
                    ones_needed--;
                    deleteElement(s, &size, j);  // Remove the 1
                    j--;    // Adjust index after deletion
                }
            }
            car++;  // One taxi for the 2 and whatever 1s we found
            deleteElement(s, &size, i);  // Remove the 2
            i--;    // Adjust index after deletion
        }
    }
    
    // Fourth pass: Handle remaining 1s (group them in 4s)
    int ones_remaining = 0;
    for(int i = 0; i < size; i++) {
        if(s[i] == 1) ones_remaining++;
    }
    car += ones_remaining / 4;
    if(ones_remaining % 4 != 0) car++;
    
    // Any remaining groups (4s or unmatched groups) need their own taxis
    car += size;
    
    printf("%d\n", car);
    return 0;
}
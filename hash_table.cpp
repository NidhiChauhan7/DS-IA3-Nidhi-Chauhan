
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

#define SIZE 29

int original[] = {40, 51, 62, 73, 84, 95, 9, 20, 31, 42, 53, 64};
int n = 12;

// Display Array
void display(int a[], int n) {
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;
}

// 1. Bubble Sort
void bubbleSort() {
    int a[12];
    copy(original, original + n, a);
    int comparisons = 0, swaps = 0;

    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;

        for (int j = 0; j < n - i - 1; j++) {
            comparisons++;

            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
                swaps++;
                swapped = true;
            }
        }

        if (!swapped) break;
    }

    cout << "\nBubble Sort Result:\n";
    display(a, n);
    cout << "Comparisons: " << comparisons;
    cout << "\nSwaps: " << swaps << endl;
}

// 2. Insertion Sort
void insertionSort() {
    int a[12];
    copy(original, original + n, a);
    int comparisons = 0, shifts = 0;

    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;

        while (j >= 0) {
            comparisons++;

            if (a[j] > key) {
                a[j + 1] = a[j];
                shifts++;
                j--;
            } else {
                break;
            }
        }

        a[j + 1] = key;
    }

    cout << "\nInsertion Sort Result:\n";
    display(a, n);
    cout << "Comparisons: " << comparisons;
    cout << "\nShifts: " << shifts << endl;
}

// 3. Quick Sort
int quickComparisons = 0;

int partitionArray(int a[], int low, int high) {
    int pivot = a[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        quickComparisons++;

        if (a[j] <= pivot) {
            i++;
            swap(a[i], a[j]);
        }
    }

    swap(a[i + 1], a[high]);
    return i + 1;
}

void quickSort(int a[], int low, int high) {
    if (low < high) {
        int pi = partitionArray(a, low, high);
        quickSort(a, low, pi - 1);
        quickSort(a, pi + 1, high);
    }
}

void runQuickSort() {
    int a[12];
    copy(original, original + n, a);
    quickComparisons = 0;

    quickSort(a, 0, n - 1);

    cout << "\nQuick Sort Result:\n";
    display(a, n);
    cout << "Comparisons: " << quickComparisons << endl;
}

// 4. Radix Sort
int getMax(int a[], int n) {
    int mx = a[0];

    for (int i = 1; i < n; i++)
        mx = max(mx, a[i]);

    return mx;
}

void countingSort(int a[], int n, int exp) {
    int output[12];
    int count[10] = {0};

    for (int i = 0; i < n; i++)
        count[(a[i] / exp) % 10]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        int digit = (a[i] / exp) % 10;
        output[count[digit] - 1] = a[i];
        count[digit]--;
    }

    for (int i = 0; i < n; i++)
        a[i] = output[i];
}

void radixSort() {
    int a[12];
    copy(original, original + n, a);

    int mx = getMax(a, n);

    for (int exp = 1; mx / exp > 0; exp *= 10)
        countingSort(a, n, exp);

    cout << "\nRadix Sort Result:\n";
    display(a, n);
}

// Sorted array for searching
int sortedArray[] = {
    9, 20, 31, 40, 42, 51,
    53, 62, 64, 73, 84, 95
};

// 5. Linear Search
void linearSearch() {
    int key, comparisons = 0;

    cout << "Enter element to search: ";
    cin >> key;

    for (int i = 0; i < n; i++) {
        comparisons++;

        if (sortedArray[i] == key) {
            cout << "Element found at index: " << i;
            cout << "\nComparisons: " << comparisons << endl;
            return;
        }
    }

    cout << "Element NOT FOUND";
    cout << "\nComparisons: " << comparisons << endl;
}

// 6. Binary Search
void binarySearch() {
    int key, low = 0, high = n - 1;
    int comparisons = 0;

    cout << "Enter element to search: ";
    cin >> key;

    while (low <= high) {
        int mid = (low + high) / 2;
        comparisons++;

        if (sortedArray[mid] == key) {
            cout << "Element found at index: " << mid;
            cout << "\nComparisons: " << comparisons << endl;
            return;
        }
        else if (key < sortedArray[mid]) {
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }

    cout << "Element NOT FOUND";
    cout << "\nComparisons: " << comparisons << endl;
}

// 7. Fibonacci Search
int fibonacciSearch(int a[], int n, int key) {
    int fib2 = 0;
    int fib1 = 1;
    int fib = fib2 + fib1;

    while (fib < n) {
        fib2 = fib1;
        fib1 = fib;
        fib = fib2 + fib1;
    }

    int offset = -1;

    while (fib > 1) {
        int i = min(offset + fib2, n - 1);

        if (a[i] < key) {
            fib = fib1;
            fib1 = fib2;
            fib2 = fib - fib1;
            offset = i;
        }
        else if (a[i] > key) {
            fib = fib2;
            fib1 = fib1 - fib2;
            fib2 = fib - fib1;
        }
        else {
            return i;
        }
    }

    if (fib1 && offset + 1 < n &&
        a[offset + 1] == key)
        return offset + 1;

    return -1;
}

void runFibonacciSearch() {
    int key;

    cout << "Enter element to search: ";
    cin >> key;

    int result = fibonacciSearch(sortedArray, n, key);

    if (result != -1)
        cout << "Element found at index: " << result << endl;
    else
        cout << "Element NOT FOUND" << endl;
}

// 8. Linear Probing
void linearProbing() {
    int hashTable[SIZE];

    for (int i = 0; i < SIZE; i++)
        hashTable[i] = -1;

    for (int i = 0; i < n; i++) {
        int key = original[i];
        int index = key % SIZE;

        while (hashTable[index] != -1)
            index = (index + 1) % SIZE;

        hashTable[index] = key;
    }

    cout << "\nHash Table using Linear Probing:\n";

    for (int i = 0; i < SIZE; i++) {
        cout << i << " : ";

        if (hashTable[i] == -1)
            cout << "EMPTY";
        else
            cout << hashTable[i];

        cout << endl;
    }
}

// 9. Separate Chaining
void separateChaining() {
    list<int> hashTable[SIZE];

    for (int i = 0; i < n; i++) {
        int key = original[i];
        int index = key % SIZE;

        hashTable[index].push_back(key);
    }

    cout << "\nHash Table using Separate Chaining:\n";

    for (int i = 0; i < SIZE; i++) {
        cout << i << " : ";

        if (hashTable[i].empty()) {
            cout << "EMPTY";
        }
        else {
            for (int value : hashTable[i])
                cout << value << " -> ";

            cout << "NULL";
        }

        cout << endl;
    }
}

// Main Menu
int main() {
    int choice;

    do {
        cout << "\n========== DATA STRUCTURES IA3 ==========\n";
        cout << "1. Bubble Sort\n";
        cout << "2. Insertion Sort\n";
        cout << "3. Quick Sort\n";
        cout << "4. Radix Sort\n";
        cout << "5. Linear Search\n";
        cout << "6. Binary Search\n";
        cout << "7. Fibonacci Search\n";
        cout << "8. Linear Probing\n";
        cout << "9. Separate Chaining\n";
        cout << "0. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                bubbleSort();
                break;

            case 2:
                insertionSort();
                break;

            case 3:
                runQuickSort();
                break;

            case 4:
                radixSort();
                break;

            case 5:
                linearSearch();
                break;

            case 6:
                binarySearch();
                break;

            case 7:
                runFibonacciSearch();
                break;

            case 8:
                linearProbing();
                break;

            case 9:
                separateChaining();
                break;

            case 0:
                cout << "Program terminated.\n";
                break;

            default:
                cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 0);

    return 0;
}

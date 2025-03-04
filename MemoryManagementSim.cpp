#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <ctime>

using namespace std;

int main() {
    userMemoryAllocation();
    return 0;
}

void userMemoryAllocation() {
    const int memorySize = 16 * 1024; // 16GB in MB
    const int pageSize = 160; // 160MB per page
    const int totalPages = memorySize / pageSize; // 100 pages
    vector<int> memory(totalPages, -1); // Memory pages initialized to -1 (unallocated)
    
    int startAddress = 2000;
    int processId = 1;
    srand(time(0));
    
    cout << "Process Id\tStarting Memory Address\tSize of the Process MB\tUnused Space MB\n";
    
    while (count(memory.begin(), memory.end(), -1) > 0) {
        int processPages = rand() % 30 + 1; // Random number between 1 and 30
        int processSize = processPages * 80; // Convert to MB
        int requiredPages = ceil((double)processSize / pageSize); // Pages needed
        
        // Check if enough memory is available
        int freePages = count(memory.begin(), memory.end(), -1);
        if (freePages < requiredPages) {
            break;
        }
        
        // Allocate memory
        int allocatedPages = 0;
        for (int i = 0; i < totalPages && allocatedPages < requiredPages; i++) {
            if (memory[i] == -1) {
                memory[i] = processId;
                allocatedPages++;
            }
        }
        
        // Calculate unused space
        int totalAllocatedSize = requiredPages * pageSize;
        int unusedSpace = totalAllocatedSize - processSize;
        
        // Print process information
        cout << processId << "\t\t" << startAddress << "\t\t" 
             << processSize << "\t\t" << unusedSpace << "\n";
        
        // Update start address for next process
        startAddress += totalAllocatedSize;
        processId++;
    }
}
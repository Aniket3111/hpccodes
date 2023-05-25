#include <iostream>
#include <omp.h>
#include <vector>

using namespace std;

void parallelreduction(const vector<int>& arr, int& minval, int& maxval, int& sum, double& average) {
    int n = arr.size();
    int localmin = arr[0];
    int localmax = arr[0];
    int localsum = 0;
    int numThreads;
    int threadID;

    #pragma omp parallel
    {
        numThreads = omp_get_num_threads();
        threadID = omp_get_thread_num();

        #pragma omp for reduction(min:localmin) reduction(max:localmax) reduction(+:localsum)
        for (int i = 0; i < n; i++) {
            localmin = min(localmin, arr[i]);
            localmax = max(localmax, arr[i]);
            localsum += arr[i];

            cout << "Thread " << threadID << " of " << numThreads << " threads - Processing element " << arr[i] << endl;
        }
    }

    minval = localmin;
    maxval = localmax;
    sum = localsum;
    average = static_cast<double>(localsum) / n;
}

int main() {
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    vector<int> number(n);
    cout << "Enter the elements: ";
    for (int i = 0; i < n; i++) {
        cin >> number[i];
    }

    int maxval, minval, sum;
    double average;

    parallelreduction(number, minval, maxval, sum, average);

    cout << "Minimum value: " << minval << endl;
    cout << "Maximum value: " << maxval << endl;
    cout << "Sum: " << sum << endl;
    cout << "Average: " << average << endl;

    return 0;
}

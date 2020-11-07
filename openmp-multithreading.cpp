//ilan finkelstein
//csci 375-02
//project 2

#include <iostream>
#include <cstdlib>
#include <omp.h>
#include <vector>

using namespace std;

int main() {

	//number of array elements
	int n;

	//number of threads         	 
	int total_threads;
    
	//loop index   
	int i;
    
	//number for storing sums
	int sum=0;
    
	//arrays for addition
	int* a;
	int* b;
	int* c;

	//user input for number of elements
	cout<<"Please enter the number of elements: ";
	cin>>n;

	//user input for total thread numbers
	cout<<"Please enter the number of threads: ";
	cin>>total_threads;

	//allocate spce for the arrays, as per stack overflow
	a = (int*)malloc(sizeof(int) * n);
	b = (int*)malloc(sizeof(int) * n);
	c = (int*)malloc(sizeof(int) * n);

	//initialization of vectors in ascending order
	for (i = 0; i < n; i++) {
    	a[i] = i;
    	sum+=i;
	}

	//initialization of vectors in descending order
	for (i = 0; i < n; i++) {
    	b[i] = n-i;
    	sum+=i;
	}

	//set the number of threads used by openmp, int from
	//earlier user input
	omp_set_num_threads(total_threads);

	//table headers
	printf("i\ta[i]\t+\tb[i]\t=\tc[i]\n");

	//parallel block for vector addition
	#pragma omp parallel for shared(a, b, c) private(i) schedule(static, total_threads)
    
	//for loop outide of omp parallel block for directive
	for (i = 0; i < n; i++){

   	 
    	//actual vector addition within parallel block
    	c[i] = a[i] + b[i];
   	 
    	//critical block for final sum addition to avoid data race condition
    	#pragma omp critical
    	sum+=c[i];
   	 
	//print results in a fancy table for proof of concept
	printf("%d\t%d\t\t%d\t\t%d\n", i, a[i], b[i], c[i]);
	}
    
    
	//print of critical block
	cout<<"Total: "<<sum<<"\n";
    
	//clean up memory before close
	free(a);  free(b); free(c);

	return 0;


    
}

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int extraMemoryAllocated;

void mergeSort(int pData[], int l, int r) {
    if (l <r) {
        
        int o = (l + (r - l)) / (2);

        mergeSort(pData, l, o);
        mergeSort(pData, o + 1, r);
        int* a = (int*) malloc((r - l + 1) * sizeof(int));
        extraMemoryAllocated += (r - l + 1) * sizeof(int);
        
        int i =l;
        int j =o + 1;
        int k =0;

        while ((i <=o) && (j <=r)) {
            
            if (pData[i] <pData[j]) {
                
                a[k++] =pData[i++];
                
            }
            
            else {
                
                a[k++] =pData[j++];
                
            }
            
        }

        while (i <=o) {
            
            a[k++] =pData[i++];
            
        }

        while (j <=r) {
            
            a[k++] =pData[j++];
            
        }

        memcpy(pData + l, a, k * sizeof(int));
    
        free(a);
    }
    
}
    
void insertionSort(int* pData, int n) {
    
    int i;
    int j;
    int a;
    
    for (i =1; i <n; i++) {
        
        a =pData[i];
        j =i - 1;

    

        while ((j >=0) && (pData[j] >a)) {
        
            pData[j + 1] =pData[j];
            j=j - 1;
            
        }
        
        pData[j + 1] =a;
        
    }
    
}

void bubbleSort(int* pData, int n) {

    int i;
    int j;
    
    for (i = 0; i <n-1; i++) {
    
        for (j = 0; j <(n-i)-1; j++) {
            
            if (pData[j] >pData[j+1]) {
                
                int a =pData[j];
                pData[j] =pData[j+1];
                pData[j+1] =a;
                
            }
            
        }
        
    }
    
}

void selectionSort(int* pData, int n) {
    
    int* a = (int*) malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++) {
        
        a[i] =pData[i];
        extraMemoryAllocated +=sizeof(int);
        
    }

    for (int i =0; i <n - 1; i++) {
        
        int b =i;

        for (int j =i + 1; j <n; j++) {
            
            if (a[j] <a[b]) {
                
                b =j;
                
            }
            
        }

        if (b !=i) {
            
            int c = a[i];
            a[i] = a[b];
            a[b] = c;
            
        }
        
    }

    for (int i =0; i <n; i++) {
        
        pData[i] =a[i];
        
    }

    free(a);
    
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};
	
	for (i=0;i<3;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}

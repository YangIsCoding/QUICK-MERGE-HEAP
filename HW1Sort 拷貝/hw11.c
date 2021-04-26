#include <stdio.h>
#include "sort.h"
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int Direction(char *string){
	printf("-d to sort in digit, -s to sort in string\n");
	if(strcmp(string,"-d")==0){
		printf("sort in digit!\n\n");
		return 1;
	}
	else if(strcmp(string,"-s")==0){
		printf("sort in string!\n\n");
		return 2;
	}
	else {
		printf("wrong!\n\n");
		exit(1);
		return 0;
	}
}
int Direction2(char *string){
	printf("input -q to perform QuickSort, -m to MergeSort, -h to HeapSort\n");
	if(strcmp(string,"-q")==0){
		printf("QuickSort selected\n\n");
		return 1;
	}
	else if(strcmp(string,"-m")==0){
		printf("MergeSort selected\n\n");
		return 2;
	}
	else if(strcmp(string,"-h")==0){
		printf("HeapSort selected\n\n");
		return 3;
	}
	else {
		printf("wrong!\n\n");
		exit(1);
		return 0;
	}
	
}
void swap(int *a,int *b){
	int temp=*a;
	*a=*b;
	*b=temp;
}
void DQuickSort(int *arr,int left,int right){
	int pivot, i, j;
	if(left>=right){
		return;
	}
	pivot = arr[left];
	i = left+1;
	j = right;
	
	while(1){
		while(i<=right){
			if(arr[i]>pivot){
				break;
			}
			i++;
		}	
		while(j>left){
			if(arr[j]<pivot){
				break;
			}
			j--;
		}	
	
		if(i>j){
			break;
		}	
		swap(&arr[i],&arr[j]);
	}
	swap(&arr[left],&arr[j]);
	DQuickSort(arr,left,j-1);
	DQuickSort(arr,j+1,right);
	
}
void merge(int arr[], int low, int mid, int high){
    int i, k;
    int *tmp = (int *)malloc((high-low+1)*sizeof(int));
    //申请空间，使其大小为两个
    int left_low = low;
    int left_high = mid;
    int right_low = mid + 1;
    int right_high = high;
    for(k=0; left_low<=left_high && right_low<=right_high; k++){  // 比较两个指针所指向的元素
        if(arr[left_low]<=arr[right_low]){
            tmp[k] = arr[left_low++];
        }else{
            tmp[k] = arr[right_low++];
        }
    }
    if(left_low <= left_high){  //若第一个序列有剩余，直接复制出来粘到合并序列尾
    //memcpy(tmp+k, arr+left_low, (left_high-left_low+l)*sizeof(int));
    for(i=left_low;i<=left_high;i++)
        tmp[k++] = arr[i];
    }
    if(right_low <= right_high){
    //若第二个序列有剩余，直接复制出来粘到合并序列尾
    //memcpy(tmp+k, arr+right_low, (right_high-right_low+1)*sizeof(int));
        for(i=right_low; i<=right_high; i++)
            tmp[k++] = arr[i];
    }
    for(i=0; i<high-low+1; i++)
        arr[low+i] = tmp[i];
    free(tmp);
    return;
}

void DMergeSort(int *arr,int low,int high){
	if (low < high) {
        	int mid = (low + high) / 2;
        	DMergeSort(arr, low, mid);
        	DMergeSort(arr, mid + 1, high);
        	merge(arr, low, mid, high);
    	}
}
void Swap(int *arr,int i,int j){
	int temp = arr[i];
	arr[i]=arr[j];
	arr[j] = temp;
}
void heapify(int *tree,int n,int i){
	if(i>=n){
		return;
	}
	int child1 = 2*i+1;
	int child2 = 2*i+2;
	int max = i;
	if(child1<n && tree[child1]>tree[max]){
		max = child1;
	}
	if(child2<n && tree[child2]>tree[max]){
		max = child2;
	}
	if(max!=i){
		Swap(tree,max,i);
		heapify(tree,n,max);
	}
	
}
void buildHeap(int *tree,int n){
	int lastnode = n-1;
	int parent = (lastnode-1)/2;
	int i;
	for(i = parent;i>=0;i--){
		heapify(tree,n,i);
	}
}
void DHeapSort(int *tree,int n){
	buildHeap(tree,n);
	int i;
	for(i=n-1;i>=0;i--){
		Swap(tree,i,0);
		heapify(tree,i,0);
	}
}
void digitSort(int flag2){
	struct timeval start;
	struct  timeval end;
	
	if(flag2 == 1){
		int num,cnt=0;
        	int *arr=malloc(sizeof(int)*1000000);
        	while(scanf("%d",&num)!=EOF){
			arr[cnt] = num;
			cnt++;
        	}
		unsigned  long diff;
		gettimeofday(&start,NULL);
		DQuickSort(arr,0,cnt-1);
		gettimeofday(&end,NULL);
		diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
		for(int i=0;i<cnt;i++){
			printf("%d\n",arr[i]);
		}
		printf("\nusing time:%ld\n",diff);
		free(arr);
	}
	else if(flag2 == 2){
		int num,cnt=0;
		int *arr = malloc(sizeof(int)*1000000);
		while(scanf("%d",&num)!=EOF){
			arr[cnt] = num;
			cnt++;
		
		}
		unsigned  long diff;
                gettimeofday(&start,NULL);
		DMergeSort(arr,0,cnt-1);
		gettimeofday(&end,NULL);
		diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
		for(int i=0;i<cnt;i++){
			printf("%d\n",arr[i]);
		}
		printf("\nusing time:%ld\n",diff);
		free(arr);
	}
	else if(flag2 == 3){
		int num,cnt=0;
                int *arr = malloc(sizeof(int)*1000000);
                while(scanf("%d",&num)!=EOF){
                        arr[cnt] = num;
                        cnt++;
                }
		unsigned  long diff;
                gettimeofday(&start,NULL);
		DHeapSort(arr,cnt);
		gettimeofday(&end,NULL);
                diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
		for(int i=0;i<cnt;i++){
                        printf("%d\n",arr[i]);
                }
		 printf("\nusing time:%ld\n",diff);
		free(arr);
	}
	else {
		printf("Wrong!\n");
		exit(1);
	}
}
void StringSwap(char **arg1,char **arg2){
	char *temp;
	temp = *arg1;
	*arg1 = *arg2;
	*arg2 = temp;
}
void SQuickSort(char **args,unsigned int len){
	unsigned int i, pvt=0;

    if (len <= 1)
        return;

    // swap a randomly selected value to the last node
    StringSwap(args+((unsigned int)rand() % len), args+len-1);

    // reset the pivot index to zero, then scan
    for (i=0;i<len-1;++i)
    {
        if (strcmp(args[i], args[len-1]) < 0)
            StringSwap(args+i, args+pvt++);
    }

    // move the pivot value into its place
    StringSwap(args+pvt, args+len-1);

    // and invoke on the subsequences. does NOT include the pivot-slot
    SQuickSort(args, pvt++);
    SQuickSort(args+pvt, len - pvt);
}

void Smerge(char **arr,int p,int q, int r){
	int n1 = q-p+1;
	int n2 = r-q;
		
	char *L[n1];
	char *M[n2];
	for(int k=0;k<n1;k++){
		L[k]=(char*)malloc(sizeof(char)*100);
	}
	for(int k=0;k<n2;k++){
		M[k]=(char*)malloc(sizeof(char)*100);
	}
	
	for(int i=0;i<n1;i++){
		L[i]=arr[p+i];
	}
	for(int j=0;j<n2;j++){
		M[j]=arr[q+j+1];
	}
	int i,j,k;
	i=0;j=0;k=p;
	while(i<n1 && j<n2){
		if(strcmp(L[i],M[j])<=0){
			arr[k] = L[i];
			i++;
		}
		else{
			arr[k]=M[j];
			j++;
		}
		k++;
	}
	while(i<n1){
		arr[k] = L[i];
		i++;k++;
	}
	while(j<n2){
		arr[k] = M[j];
		j++;k++;
	}
}
void SMergeSort(char **text,int low,int high){
	if (low < high) {
        	int mid = low+(high-low) / 2;
        	SMergeSort(text, low, mid);
        	SMergeSort(text, mid + 1, high);
        	Smerge(text, low, mid, high);
    	}
}
void SSwap(char **arr,int i,int j){
	char *temp = arr[i];
	arr[i]=arr[j];
	arr[j] = temp;
}
void Sheapify(char **tree,int n,int i){
	if(i>=n){
		return;
	}
	int child1 = 2*i+1;
	int child2 = 2*i+2;
	int max = i;
	if(child1<n && strcmp(tree[child1],tree[max])>0){
		max = child1;
	}
	if(child2<n && strcmp(tree[child2],tree[max])>0){
		max = child2;
	}
	if(max!=i){
		SSwap(tree,max,i);
		Sheapify(tree,n,max);
	}
	
}
void SbuildHeap(char **tree,int n){
	int lastnode = n-1;
	int parent = (lastnode-1)/2;
	int i;
	for(i = parent;i>=0;i--){
		Sheapify(tree,n,i);
	}
}
void SHeapSort(char **tree,int n){
	SbuildHeap(tree,n);
	int i;
	for(i=n-1;i>=0;i--){
		SSwap(tree,i,0);
		Sheapify(tree,i,0);
	}
}
void stringSort(int flag2){
	 struct timeval start;
        struct  timeval end;
	if(flag2 ==1){
		int cnt=0;
		char *string=malloc(sizeof(char)*101);
		char **text = malloc(sizeof(string)*1000000);
		for(int i=0;i<1000000;i++){
			text[i] = malloc(sizeof(string));
		}
		while(scanf("%s",string)!=EOF){
			strcpy(text[cnt],string);
			text[cnt][101]='\0';
			cnt++;
		}
		unsigned  long diff;
                gettimeofday(&start,NULL);
		SQuickSort(text,cnt);
		gettimeofday(&end,NULL);
                diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
		for(int i=0;i<cnt;i++){
			for(int j=0;j<100;j++){
				printf("%c",text[i][j]);
			}
			printf("\n");
		}
		printf("\nusing time:%ld\n",diff);
		free(text);
	}
	else if(flag2 == 2){
		int cnt=0;
                char *string=malloc(sizeof(char)*101);
                char **text = malloc(sizeof(string)*1000000);
                for(int i=0;i<1000000;i++){
                        text[i] = malloc(sizeof(string));
                }
                while(scanf("%s",string)!=EOF){
                        strcpy(text[cnt],string);
                        cnt++;
                }
		unsigned  long diff;
                gettimeofday(&start,NULL);
                SMergeSort(text,0,cnt-1);
		gettimeofday(&end,NULL);
                diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
                for(int i=0;i<cnt;i++){
				for(int j=0;j<100;j++){
					printf("%c",text[i][j]);
				}
			printf("\n");
                }
		printf("\nusing time:%ld\n",diff);
                free(text);
	}
	else if(flag2 == 3){
		int cnt=0;
                char *string=malloc(sizeof(char)*100);
                char **text = malloc(sizeof(string)*1000000);
                for(int i=0;i<1000000;i++){
                        text[i] = malloc(sizeof(string));
                }
                while(scanf("%s",string)!=EOF){
                        strcpy(text[cnt],string);
                        cnt++;
                }
		unsigned  long diff;
                gettimeofday(&start,NULL);
                SHeapSort(text,cnt);
		gettimeofday(&end,NULL);
                diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
                for(int i=0;i<cnt;i++){
			for(int j=0;j<100;j++){
                        	printf("%c",text[i][j]);
			}
			printf("\n");
                }
		printf("\nusing time:%ld\n",diff);
                free(text);
	}
	else{
		printf("wrong!!\n");
	}
}
int main(int argc,char **argv){
	int flag;
	flag = Direction(argv[1]);
	int flag2;
	flag2 = Direction2(argv[2]);
	if(flag==1){
		digitSort(flag2);	
	}
	else if(flag==2){
		stringSort(flag2);
	}	
}

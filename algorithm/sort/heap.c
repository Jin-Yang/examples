/**************************************************************
 ********************* Heap Sort ******************************
 * Theory:
 *     1. Produce a Max-heap or Min-heap from unordered array.
 *        Call Heapfy() from the last parent-node to root-node.
 *     2. Chose first one to ordered array.
 *     3. After STEP2, only the root is unordered, so adjust it,
 *        calling Heapfy() with root-node.
 * Performace:
 *     TIME::::BEST:O(nlogn)    WORST:O(nlogn)    AVERAGE:0(nlogn)
 *     SPACE:::WORST:O(1)
 *     IN-PLACE      UN-STABLE
 * Author:
 *     JinYang  2011-8-19
 * Others:
 *     The max-heap property is that for every node i PARENT >= I;
 *     The leaves are the nodes indexed by floor(n/2)+1 ... n.
 *     The size_t supports unsigned type in HeapSort().
 * NOTE:
 *     Some reference recommand that HeapSort_Pro() is better
 *     than HeapSort(), but we donot find difference.
 *************************************************************/
#include "Sort.h"



// The root node id is 0.
#define LEFT_0(val)	(val * 2 + 1)
#define RIGHT_0(val)	(val * 2 + 2)
#define PARENT_0(val)	((val - 1) / 2)
// The root node id is 1.
#define LEFT_1(val)	(val * 2)
#define RIGHT_1(val)	(val * 2 + 1)
#define PARENT_1(val)	(val / 2)


// adjust one element to fit Max-Heap.
static void Heapify_Pro(Element* array, unsigned int first, unsigned int last)
{
	unsigned int child, parent;
	int i;
	Element temp;

	for ( i = first; (child = LEFT_0(i)) <= last; i = child) {
#ifdef INCREASE__SORT
		if ((child + 1 <= last) && (array[child + 1] > array[child]))
#else
		if ((child + 1 <= last) && (array[child + 1] < array[child]))
#endif
			child++;
 
		// child is the larger child of i.
		temp = array[i];
		array[i] = array[child];
		array[child] = temp;
	}

	while (1) {
		parent = PARENT_0(i);
#ifdef INCREASE__SORT
		if ( parent < first || parent == i || (array[parent] > array[i]))
#else
		if ( parent < first || parent == i || (array[parent] < array[i]))
#endif
			break;
		temp = array[i];
		array[i] = array[parent];
		array[parent] = temp;

		i = parent;
	}
}

// NOTE: N should be 'int' instead of 'unsigned int'
void HeapSort_Pro(Element* array, const unsigned int N)
{
	Element temp;
	int i;

	// First, ensure heap property for array. Check from
	// the last father node to the root node.
	for(i = (N - 2) / 2; i >= 0; i--){
		Heapify_Pro(array, i, N - 1);
	}

	// Now sort by taking advantage of the fact that the
	// largest element is in array[0]. If we remove this element
	// and move it to array[N-1], that element is now in place.
	// We continue to sort by reenforcing the property on 
	// array[0 .. N-2] and then taking the next largest element
	// we will ultimately sort the array.
	for(i = N - 1; i > 0;){
		temp = array[0];
		array[0] = array[i];
		array[i] = temp;

		Heapify_Pro(array, 0, --i);
	}
}










/* Adjust the heap to max/min-heap.
 * Input:
 *    array: the array want to adjust.
 *        i: the parent node id(root_id = 0).
 *     size: the size of array, a[0], a[1] => size = 2.
 */
static void Heapify(Element* array, Size_t i, const Size_t size)
{
	Size_t child;
	Element temp;
	for (temp = array[i]; (child = LEFT_0(i)) < size; i = child) {
#ifdef INCREASE__SORT
		// In case the node is a leaf and get the larger child.
		if (((child + 1) < size) && (array[child] < array[child + 1]))
#else
		// In case the node is a leaf and get the smaller child.
		if (((child + 1) < size) && (array[child] > array[child + 1]))
#endif
			++child;
#ifdef INCREASE__SORT
		// If the larger child is bigger than father, then exchange.
		if (temp < array[child]) {
#else
		// If the smaller child is smaller than father, then exchange.
		if (temp > array[child]) {
#endif
			array[i] = array[child];
			array[child] = temp;
		} else { // OK, it's Max/Min-heap.
			break;
		}
	}
} 


// N must >= 2
void HeapSort(Element* array, const Size_t N)
{
	Element temp;
	unsigned int i;

	// First, ensure heap property for array. Check from
	// the last father node to the root node.
	i = N / 2; // Get the last father node, equal to 'floor((i-1)/2)'
	do {
		i--;
		Heapify(array, i, N);
	} while (i > 0);


	// Now sort by taking advantage of the fact that the
	// largest/smallest element is in array[0]. If we remove this
	// element and move it to array[N-1], that element is now in place.
	// We continue to sort by reenforcing the property on 
	// array[0 .. N-2] and then taking the next largest element
	// we will ultimately sort the array.
	for (i = N - 1; i > 0; i--) {
		temp = array[0];
		array[0] = array[i];
		array[i] = temp;
		Heapify(array, 0, i);
	}
}




#pragma once

#ifndef heap_sort_h
#define heap_sort_h

#include "utils.h"

template <typename T>
class heap_sort {
private:
	static void sink(T* arr, size_t k, size_t n) {
		while (2 * k <= n) {
			int j = 2 * k;
			if (j < n && less(arr, j, j + 1)) j++;
			if (!less(arr, k, j)) break;
			exchange(arr, k, j);
			k = j;
		}
	}

public:
    static void sort(T* arr) {
        int n = arr.length;

        for (int k = n / 2; k >= 1; k--)
            sink(arr, k, n);

        int k = n;
        while (k > 1) {
            exchange(arr, 1, k--);
            sink(arr, 1, k);
        }
    }

};

#endif

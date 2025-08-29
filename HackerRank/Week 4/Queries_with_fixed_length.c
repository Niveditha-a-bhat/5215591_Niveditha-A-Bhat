#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

typedef struct {
    int *tree;
    int *lazy;
    int n;
} SegmentTree;

void buildSegmentTree(SegmentTree *seg, int n) {
    seg->n = n;
    seg->tree = (int *)malloc(4 * n * sizeof(int));
    seg->lazy = (int *)malloc(4 * n * sizeof(int));
    for (int i = 0; i < 4 * n; i++) {
        seg->tree[i] = INT_MAX;
        seg->lazy[i] = INT_MAX;
    }
}

void updateRange(SegmentTree *seg, int idx, int l, int r, int ql, int qr, int val) {
    if (seg->lazy[idx] != INT_MAX) {
        seg->tree[idx] = min(seg->tree[idx], seg->lazy[idx]);
        if (l != r) {
            seg->lazy[2 * idx + 1] = min(seg->lazy[2 * idx + 1], seg->lazy[idx]);
            seg->lazy[2 * idx + 2] = min(seg->lazy[2 * idx + 2], seg->lazy[idx]);
        }
        seg->lazy[idx] = INT_MAX;
    }
    if (l > qr || r < ql) return;
    if (l >= ql && r <= qr) {
        seg->tree[idx] = min(seg->tree[idx], val);
        if (l != r) {
            seg->lazy[2 * idx + 1] = min(seg->lazy[2 * idx + 1], val);
            seg->lazy[2 * idx + 2] = min(seg->lazy[2 * idx + 2], val);
        }
        return;
    }
    int mid = (l + r) / 2;
    updateRange(seg, 2 * idx + 1, l, mid, ql, qr, val);
    updateRange(seg, 2 * idx + 2, mid + 1, r, ql, qr, val);
    seg->tree[idx] = min(seg->tree[2 * idx + 1], seg->tree[2 * idx + 2]);
}

int query(SegmentTree *seg, int idx, int l, int r, int pos) {
    if (seg->lazy[idx] != INT_MAX) {
        seg->tree[idx] = min(seg->tree[idx], seg->lazy[idx]);
        if (l != r) {
            seg->lazy[2 * idx + 1] = min(seg->lazy[2 * idx + 1], seg->lazy[idx]);
            seg->lazy[2 * idx + 2] = min(seg->lazy[2 * idx + 2], seg->lazy[idx]);
        }
        seg->lazy[idx] = INT_MAX;
    }
    if (l == r) {
        return seg->tree[idx];
    }
    int mid = (l + r) / 2;
    if (pos <= mid) {
        return query(seg, 2 * idx + 1, l, mid, pos);
    } else {
        return query(seg, 2 * idx + 2, mid + 1, r, pos);
    }
}

int* solve(int arr_count, int* arr, int queries_count, int* queries, int* result_count) {
    int n = arr_count;
    int *left = (int *)malloc(n * sizeof(int));
    int *right = (int *)malloc(n * sizeof(int));
    int *stack = (int *)malloc(n * sizeof(int));
    int top = -1;

    for (int i = 0; i < n; i++) {
        while (top >= 0 && arr[stack[top]] < arr[i]) {
            top--;
        }
        if (top == -1) {
            left[i] = -1;
        } else {
            left[i] = stack[top];
        }
        stack[++top] = i;
    }

    top = -1;
    for (int i = n - 1; i >= 0; i--) {
        while (top >= 0 && arr[stack[top]] <= arr[i]) {
            top--;
        }
        if (top == -1) {
            right[i] = n;
        } else {
            right[i] = stack[top];
        }
        stack[++top] = i;
    }

    free(stack);

    SegmentTree seg;
    buildSegmentTree(&seg, n);

    for (int i = 0; i < n; i++) {
        int len = right[i] - left[i] - 1;
        updateRange(&seg, 0, 1, n, 1, len, arr[i]);
    }

    int *res = (int *)malloc(queries_count * sizeof(int));
    for (int i = 0; i < queries_count; i++) {
        res[i] = query(&seg, 0, 1, n, queries[i]);
    }

    *result_count = queries_count;

    free(left);
    free(right);
    free(seg.tree);
    free(seg.lazy);

    return res;
}

int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    int *arr = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    int *queries = malloc(q * sizeof(int));
    for (int i = 0; i < q; i++) {
        scanf("%d", &queries[i]);
    }
    int result_count;
    int *result = solve(n, arr, q, queries, &result_count);
    for (int i = 0; i < result_count; i++) {
        printf("%d\n", result[i]);
    }
    free(arr);
    free(queries);
    free(result);
    return 0;
}
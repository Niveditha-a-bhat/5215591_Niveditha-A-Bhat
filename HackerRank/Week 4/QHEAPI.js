'use strict';

process.stdin.resume();
process.stdin.setEncoding('utf-8');
let inputString: string = '';
let inputLines: string[] = [];
let currentLine: number = 0;
process.stdin.on('data', function(inputStdin: string): void {
    inputString += inputStdin;
});

process.stdin.on('end', function(): void {
    inputLines = inputString.split('\n');
    inputString = '';
    main();
});

function readLine(): string {
    return inputLines[currentLine++];
}

function main() {
    // Enter your code here
     const q = parseInt(readLine().trim(), 10);
    const heap: number[] = [];
    const deleted = new Map<number, number>();

    const insert = (val: number) => {
        heap.push(val);
        let index = heap.length - 1;
        while (index > 0) {
            const parentIndex = Math.floor((index - 1) / 2);
            if (heap[parentIndex] <= heap[index]) break;
            [heap[parentIndex], heap[index]] = [heap[index], heap[parentIndex]];
            index = parentIndex;
        }
    };

    const removeTop = () => {
        const last = heap.pop();
        if (heap.length === 0) return;
        heap[0] = last!;
        let index = 0;
        const length = heap.length;
        while (true) {
            let leftChild = 2 * index + 1;
            let rightChild = 2 * index + 2;
            let smallest = index;
            if (leftChild < length && heap[leftChild] < heap[smallest]) {
                smallest = leftChild;
            }
            if (rightChild < length && heap[rightChild] < heap[smallest]) {
                smallest = rightChild;
            }
            if (smallest === index) break;
            [heap[index], heap[smallest]] = [heap[smallest], heap[index]];
            index = smallest;
        }
    };

    const printMin = () => {
        while (heap.length > 0) {
            const minVal = heap[0];
            if (deleted.has(minVal) && deleted.get(minVal)! > 0) {
                deleted.set(minVal, deleted.get(minVal)! - 1);
                if (deleted.get(minVal) === 0) {
                    deleted.delete(minVal);
                }
                removeTop();
            } else {
                console.log(minVal);
                break;
            }
        }
    };

    for (let i = 0; i < q; i++) {
        const parts = readLine().split(' ');
        const op = parts[0];
        if (op === '1') {
            const val = parseInt(parts[1], 10);
            insert(val);
        } else if (op === '2') {
            const val = parseInt(parts[1], 10);
            if (deleted.has(val)) {
                deleted.set(val, deleted.get(val)! + 1);
            } else {
                deleted.set(val, 1);
            }
        } else if (op === '3') {
            printMin();
        }
    }
}
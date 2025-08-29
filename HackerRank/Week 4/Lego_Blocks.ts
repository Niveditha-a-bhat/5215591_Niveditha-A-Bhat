'use strict';

import { WriteStream, createWriteStream } from "fs";
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

/*
 * Complete the 'legoBlocks' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER m
 */

function legoBlocks(n: number, m: number): number {
    // Write your code here
    const MOD = BigInt(1000000007);
    
    // Precompute F(m): number of ways to build a single row of width m
    let F: bigint[] = new Array(m+1).fill(BigInt(0));
    F[0] = BigInt(1);
    for (let i = 1; i <= m; i++) {
        F[i] = F[i-1];
        if (i >= 2) F[i] = (F[i] + F[i-2]) % MOD;
        if (i >= 3) F[i] = (F[i] + F[i-3]) % MOD;
        if (i >= 4) F[i] = (F[i] + F[i-4]) % MOD;
    }
    
    // Precompute T(m) = F(m)^n mod MOD
    let T: bigint[] = new Array(m+1);
    for (let i = 0; i <= m; i++) {
        T[i] = BigInt(1);
        let base = F[i];
        let exp = n;
        // Fast exponentiation: base^exp mod MOD
        while (exp > 0) {
            if (exp % 2 === 1) {
                T[i] = (T[i] * base) % MOD;
            }
            base = (base * base) % MOD;
            exp = Math.floor(exp / 2);
        }
    }
    
    // Precompute G(m): number of ways to build a solid wall of width m
    let G: bigint[] = new Array(m+1).fill(BigInt(0));
    G[0] = BigInt(1);
    for (let i = 1; i <= m; i++) {
        G[i] = T[i];
        let total = BigInt(0);
        for (let j = 1; j < i; j++) {
            total = (total + (G[j] * T[i - j]) % MOD) % MOD;
        }
        G[i] = (G[i] - total + MOD) % MOD;
    }
    
    return Number(G[m] % MOD);
}

// For local testing, you can simulate input
// inputLines = `4
// 2 2
// 3 2
// 2 3
// 4 4`.split('\n');
// main();

function main() {
    const ws: WriteStream = createWriteStream(process.env['OUTPUT_PATH']);

    const t: number = parseInt(readLine().trim(), 10);

    for (let tItr: number = 0; tItr < t; tItr++) {
        const firstMultipleInput: string[] = readLine().replace(/\s+$/g, '').split(' ');

        const n: number = parseInt(firstMultipleInput[0], 10);

        const m: number = parseInt(firstMultipleInput[1], 10);

        const result: number = legoBlocks(n, m);

        ws.write(result + '\n');
    }

    ws.end();
}

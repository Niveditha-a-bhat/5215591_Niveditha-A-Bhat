#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_N 100

typedef struct {
    int x, y, moves;
} Node;

int minimumMoves(int grid_count, char** grid, int startX, int startY, int goalX, int goalY) {
    int n = grid_count;
    int dist[MAX_N][MAX_N];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dist[i][j] = INT_MAX;
        }
    }
    
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    
    Node queue[MAX_N * MAX_N];
    int front = 0, rear = 0;
    
    queue[rear].x = startX;
    queue[rear].y = startY;
    queue[rear].moves = 0;
    rear++;
    dist[startX][startY] = 0;
    
    while (front < rear) {
        Node current = queue[front++];
        int x = current.x;
        int y = current.y;
        int moves = current.moves;
        
        if (x == goalX && y == goalY) {
            return moves;
        }
        
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            while (nx >= 0 && nx < n && ny >= 0 && ny < n && grid[nx][ny] != 'X') {
                if (dist[nx][ny] > moves + 1) {
                    dist[nx][ny] = moves + 1;
                    queue[rear].x = nx;
                    queue[rear].y = ny;
                    queue[rear].moves = moves + 1;
                    rear++;
                } else if (dist[nx][ny] < moves + 1) {
                    break;
                }
                nx += dx[d];
                ny += dy[d];
            }
        }
    }
    
    return dist[goalX][goalY];
}

int main() {
    int n;
    scanf("%d", &n);
    getchar();
    
    char** grid = (char**)malloc(n * sizeof(char*));
    for (int i = 0; i < n; i++) {
        grid[i] = (char*)malloc((n + 1) * sizeof(char));
        scanf("%s", grid[i]);
    }
    
    int startX, startY, goalX, goalY;
    scanf("%d %d %d %d", &startX, &startY, &goalX, &goalY);
    
    int result = minimumMoves(n, grid, startX, startY, goalX, goalY);
    printf("%d\n", result);
    
    for (int i = 0; i < n; i++) {
        free(grid[i]);
    }
    free(grid);
    
    return 0;
}
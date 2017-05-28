
#include <stdio.h>

const int MAX_SIZE = 6;
const int SUCCESS = 0;
const int FAILURE = 1; 

const int GraphA[6][7] = {
  {7, 2, -1, -1, -1, -1, -1},
  {6, 3,  4, -1, -1, -1, -1},
  {3, 0,  3, -1, -1, -1, -1},
  {9, 1,  4, -1, -1, -1, -1},
  {8, 1,  3,  5, -1, -1, -1},
  {2, 4, -1, -1, -1, -1, -1}
};

int print_graph_adjacency_list(int rows, int cols, const int graph[rows][cols]) {
  int i, j;
  for (i=0;i<rows;i++) {
    for (j=1;j<cols; j++) {
      if (graph[i][j] != -1) {
        printf("%2d", graph[i][j]);
      }
    }
    printf("\n");
  }
  return SUCCESS;
}

int push_to_queue(int val, int *queue_ptr) {
  int i;
  for (i=0; i<MAX_SIZE; i++, queue_ptr++) {
    if (*queue_ptr == -1) {
      *queue_ptr = val;
      return SUCCESS;
    }
  }
  return FAILURE;
}

int pop_from_queue(int *queue_ptr, int *res) {
  if (*queue_ptr == -1) {
    return FAILURE;
  }
  *res = *queue_ptr;
  int i;
  for (i=0; i<MAX_SIZE-1; i++, queue_ptr++) {
    *queue_ptr = *(queue_ptr + 1);
  }
  return SUCCESS;
}

int get_queue_length(int *queue_ptr, int *res) {
  int qlength = 0, i;
  for (i=0; i < MAX_SIZE; i++, queue_ptr++) {
    if (*queue_ptr != -1) {
      qlength++;
    }
  }
  *res = qlength;
  return SUCCESS;
}

int bfs(int rows, int cols, const int graph[rows][cols], int lmn, int* res) {
  // Mark all nodes as not visited
  int visited[rows];
  int i,j;
  for (i=0; i<rows; i++) {
    visited[i] = 0;
  }

  // Create queue
  int queue[rows];
  for (i=0; i<rows; i++) {
    queue[i] = -1;
  }

  // Push to queue first node in the graph
  int qlen = 0, cur_ind;
  push_to_queue(0, &queue[0]);
  get_queue_length(&queue[0], &qlen);

  // Actual BFS
  int iters = 0;
  while (qlen > 0 && iters < 20) {
    pop_from_queue(&queue[0], &cur_ind);
    int val = graph[cur_ind][0];
    visited[cur_ind] = 1;
    printf("CurInd %d ", cur_ind);
    printf("CurVal %d ", val);
    if (val == lmn) {
      *res = cur_ind;
      return SUCCESS;
    } else {
      for (j=1; j<cols; j++) {
        int node_ind = graph[cur_ind][j];
        if (node_ind != -1 && visited[node_ind] != 1) {
          printf("Chind %d ", node_ind);
          push_to_queue(graph[cur_ind][j], &queue[0]);
        }
      }
      printf("\n");
    }
    iters++;
  }
  return FAILURE;
}

int sum(int a, int b, int* res) {
  *res = a+b;
  return SUCCESS;
}

int main(int argc, char const *argv[]) {
  int c;
  int res_code = bfs(MAX_SIZE, MAX_SIZE - 1, GraphA, 3, &c);
  printf("%d\n", GraphA[2][0]);
  if (res_code == SUCCESS) {
    printf("Element index is %3d\n", c);
  } else {
    printf("There is no such Element in this graph\n");
  }
  return SUCCESS;
}

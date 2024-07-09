#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

struct Node {
    int mark;
    int prev; //1-from left; 2-from right; 3-from down; 4-from up
    struct Node * parent;
    int x;
    int y;
    double cost;
    int counter;
};

int Finder (int way, struct Node Node[], int OpenCounter) {
  int res = 0;
  double tmp1;
  int flag = 0;
  switch (way) {
    case 5://case of Random
      srand(time(NULL));
    while (1){
      res = rand() % (OpenCounter+1);
       for (int j = 0; j < OpenCounter; j++) { 
            if (Node[res].x == Node[j].x && Node[res].y == Node[j].y && Node[j].mark == 1) {
            flag = 1; 
            break;
            }
            if (Node[res].mark == 1) {
            flag = 1;
            break;
            }
          }
      if (flag == 0)
      break;
      else 
      flag = 0;
    }
    break;

    case 4://case of Depth-search
      res = OpenCounter;
      for (int i = OpenCounter; i >= 0; i--) {
          for (int j = 0; j < OpenCounter; j++) { 
            if (Node[i].x == Node[j].x && Node[i].y == Node[j].y && Node[j].mark == 1) {
            flag = 1; 
            break;
            }
            if (Node[i].mark == 1) {
            flag = 1;
            break;
            }
          }
        if (flag == 0) {
          res = i; 
          break;
          } else
          flag = 0;
      }
    break;

    case 3://case of Breadth-First search
    res = OpenCounter;
      for (int i = 0; i < OpenCounter; i++) {
          for (int j = 0; j < OpenCounter; j++) { 
            if (Node[i].x == Node[j].x && Node[i].y == Node[j].y && Node[j].mark == 1) {
            flag = 1; 
            break;
            }
            if (Node[i].mark == 1) {
            flag = 1;
            break;
            }
          }
        if ( flag == 0 ) {
          res = i;
          break;
          } else flag = 0;
      }
    break;

    case 2://case of Greedy search
    tmp1 = Node[OpenCounter].cost;
    res = OpenCounter;
      for (int i = 0; i < OpenCounter; i++) {
          for (int j = 0; j < OpenCounter; j++) { 
            if (Node[i].x == Node[j].x && Node[i].y == Node[j].y && Node[j].mark == 1) {
            flag = 1; 
            break;
            }
            if (Node[i].mark == 1) {
            flag = 1;
            break;
            }
          }
        if ( Node[i].cost <= tmp1 && flag == 0) { 
          res = i;
          tmp1 = Node[i].cost;
          }
          else flag = 0;
      }
    break;

    case 1://case of A* 
    tmp1 = Node[OpenCounter].counter + Node[OpenCounter].cost;
    res = OpenCounter;
      for (int i = 0; i < OpenCounter; i++) {
          for (int j = 0; j < OpenCounter; j++) { 
            if (Node[i].x == Node[j].x && Node[i].y == Node[j].y && Node[j].mark == 1) {
            flag = 1; 
            break;
            }
            if (Node[i].mark == 1) {
            flag = 1;
            break;
            }
          }
        if ( (Node[i].counter + Node[i].cost) <= tmp1 && flag == 0 ) {
          res = i;
          tmp1 = Node[i].counter + Node[i].cost;
          }
          else flag = 0;
      }
    break;

    default:
    return 1;
    }

    return res;
}

void OpenFunc (int x1, int y1, struct Node Node[], char ** Maze, int OpenCounter, int * OpenCounterP, int way) { 
    int tmp = Finder(way,Node,OpenCounter);
    int x = Node [tmp].x; 
    int y = Node [tmp].y;
    int g = 1; 
    struct Node * parent = &Node[tmp];
    Node [tmp].mark = 1;
    if (Maze[x][y+1] != 'X' && Node[tmp].prev != 2) {  
      *OpenCounterP+=1; 
      OpenCounter++; 
      Node[OpenCounter].x = x; 
      Node[OpenCounter].y = y+1; 
      Node[OpenCounter].mark = 0; 
      Node[OpenCounter].prev = 1; 
      Node[OpenCounter].parent = parent; 
      Node[OpenCounter].counter = Node[OpenCounter-g].counter + 1; 
      Node[OpenCounter].cost = sqrt(pow(x1 - x, 2)) + sqrt(pow(y1 - y-1, 2)); 
      g++; if (Node[OpenCounter].x == x1 && Node[OpenCounter].y == y1) return ;
    }
      if (Maze[x][y-1] != 'X' && Node[tmp].prev != 1) { 
      *OpenCounterP+=1;
      OpenCounter++;
      Node[OpenCounter].x = x;
      Node[OpenCounter].y = y-1;
      Node[OpenCounter].mark = 0;
      Node[OpenCounter].prev = 2;
      Node[OpenCounter].parent = parent;
      Node[OpenCounter].counter = Node[OpenCounter-g].counter + 1;
      Node[OpenCounter].cost = sqrt(pow(x1 - x, 2)) + sqrt(pow(y1 - y+1, 2));
      g++; if (Node[OpenCounter].x == x1 && Node[OpenCounter].y == y1) return ;
    }
      if (Maze[x+1][y] != 'X' && Node[tmp].prev != 3) { 
      *OpenCounterP+=1;
      OpenCounter++;
      Node[OpenCounter].x = x+1; 
      Node[OpenCounter].y = y;
      Node[OpenCounter].mark = 0;
      Node[OpenCounter].prev = 4;
      Node[OpenCounter].parent = parent;
      Node[OpenCounter].counter = Node[OpenCounter-g].counter + 1;
      Node[OpenCounter].cost = sqrt(pow(x1 - x-1, 2)) +sqrt(pow(y1 - y, 2));
      g++; if (Node[OpenCounter].x == x1 && Node[OpenCounter].y == y1) return ;
    }
    if (Maze[x-1][y] != 'X' && Node[tmp].prev != 4) { 
      *OpenCounterP+=1;
      OpenCounter++;
      Node[OpenCounter].x = x-1;
      Node[OpenCounter].y = y;
      Node[OpenCounter].mark = 0;
      Node[OpenCounter].prev = 3;
      Node[OpenCounter].parent = parent;
      Node[OpenCounter].counter = Node[OpenCounter-g].counter + 1;
      Node[OpenCounter].cost = sqrt(pow(x1 - x+1, 2)) + sqrt(pow(y1 - y, 2));
      g++; if (Node[OpenCounter].x == x1 && Node[OpenCounter].y == y1) return ;
    }
}

void MatrixTranslator(int rows, int cols, char ** MazeTmp, char ** Maze) { //input things from the list (those which are from user)
  int g = 0;
  for (int i = 0; i < rows; i++) { 
    for (int j = 0; j < cols; j++) { if (MazeTmp[i][j+g] == '\n') g++;
      Maze[i][j] = MazeTmp[i][j+g];
    }
  }
}

void PathReconstruction (char ** Maze, int cols, int rows, int x1, int y1, int x, int y, struct Node Node[], int res) { 
  int Path[25000][2];
  int count = 0;
  struct Node* cur = &Node[res];
  while (cur->x != x || cur->y != y) { 
    Path[count][0] = cur->x;
    Path[count][1] = cur->y; 
    count++;
    cur = cur->parent; 
  } 
  
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {

      if (i == x && j == y) {
      printf ("S");
      continue;}
      if (i == x1 && j == y1) {
      printf ("E");
      continue;}

      for (int h = 0; h < count; h++){
        if (Path[h][0] == i && Path[h][1] == j)  {
        printf ("*");
        break; 
        } else if (h == count-1)
        printf ("%c", Maze[i][j]);
      }
    }
    printf ("\n");
  }
}



int main () {   //if anything bad happens then expand repetition checker from DFS to other ways
int x,y;
int x1,y1;
FILE * file = fopen("332.txt", "r");
char ** MazeTmp = (char **)malloc(3000*sizeof(char*));
for (int r = 0; r < 3000; r++) {
  MazeTmp[r] = (char*)malloc (3000*sizeof(char)); 
}
int l = 0;
while (!feof(file)) {
    fgets(MazeTmp[l], 3000, file);
    l++;
} l--; 
printf ("Please, enter starting coordinates\n");
scanf ("%d %d", &y, &x);
printf ("Please, enter ending coordinates\n");
scanf ("%d %d", &y1, &x1);

struct Node * Node = (struct Node*)malloc(9000000*sizeof(struct Node));
  int total = 0;
  for (int i = 0; i < l-2; i++) {
      total += strlen (MazeTmp[i]);
  }
  int rows = 0;
  for (int i = 0; i < l-2; i++) {
      for (int j = 0; j < 3000; j++) {
        if (MazeTmp[i][j] == '\n') {
        rows++;
        break;
        }
      }
  }
  int cols = (total/rows) - 1;
int way;
printf("Please, enter an algorythm\n1-A*\n2-Greedy\n3-BFS\n4-DFS\n5-Random\n");
scanf("%d", &way);

char ** Maze = (char **)malloc(3000*sizeof(char*));
for (int r = 0; r < 3000; r++) {
  Maze[r] = (char*)malloc (3000*sizeof(char)); 
}

int OpenCounter = 0;
int * OpenCounterP = &OpenCounter;
MatrixTranslator(rows, cols, MazeTmp, Maze);


Node[0].x = x;
Node[0].y = y;
Node[0].mark = 0;
Node[0].prev = 0;
Node[0].cost = 0;
Node [0].counter = 0;

if (x == x1 && y == y1) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (i == x && j == y) {
        printf ("*");
        continue;
      }
      printf ("%c", Maze[i][j]);
    }
    printf ("\n");
  }
  return 0;
}
 
while (1) {
  OpenFunc(x1, y1, Node, Maze, OpenCounter, OpenCounterP, way); 
  if (Node[OpenCounter].x == x1 && Node[OpenCounter].y == y1) 
  break;
}
  PathReconstruction(Maze, cols, rows, x1, y1, x, y, Node, OpenCounter);

  return 0;
}
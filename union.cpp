/* Copyright [2019] <mituh> */
/* 7.c */
/* 荷兰国旗问题 */

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

#define MaxN 10000

int people[MaxN] = {-1};
int hobby[MaxN] = {-1};

int find(int p) {
  while (people[p] > 0) {
    p = people[p];
  }
  return p;
}

void Union(int r1, int r2) {
  if (r1 == r2) return;
  people[r1] += people[r2];
  people[r2] = r1;
}

int cmp(int a, int b) {
  return a >= b;
}

int main() {
  int N, pi, n, h;
  // fill(people.begin(), people.end(), -1);
  // fill(hobby.begin(), hobby.end(), -1);

  for (pi = 0; pi < MaxN; pi++) {
    people[pi] = -1;
    hobby[pi] = -1;
  }
  scanf("%d", &N);
  for (pi = 0; pi < N; pi++) {
    /* 从编号从0开始 */
    scanf("%d:", &n);
    while (n--) {
      scanf(" %d", &h);
      if (hobby[h] == -1) {
        hobby[h] = pi;
      } else {
        /* 发现相同兴趣爱好的人 */
        Union(find(pi), find(hobby[h]));
      }
    }
  }

  vector<int> cluster;
  int i;
  for (pi = 0; pi < N; pi++) {
    if (people[pi] < 0) {
      cluster.push_back(-people[pi]);
    }
  }

  sort(cluster.begin(), cluster.end(), cmp);
  printf("%lu\n", cluster.size());
  for (i = 0; i < cluster.size(); i++) {
    if (i != 0) printf(" ");
    printf("%d", cluster[i]);
  }
  printf("\n");
  return 0;
}


/*

8
3: 2 7 10
1: 4
2: 5 3
1: 4
1: 3
1: 4
4: 6 8 1 5
1: 4

 */

// Update
// Update
// Update
// Update
// Update
// Update
// Update
// Update
// Update
// Update
// Update
// Update
// Update
// Update
// Update
// Update
// Update
// Update
// Update
// Update
// Update
// Update
// Update
// Update
// Update
// Update
// Update
// Update

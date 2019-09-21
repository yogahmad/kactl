#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
#define f first
#define s second
#define mp make_pair

const string BLANK = "XXXXX";
const string WHITE = ".....";
const int N = 8;
const int BAWAH = 0;
const int KANAN = 1;

int n, m;
int bawah[N][N], kanan[N][N];
int grid[N][N];
int ggrid[N][N];
int no_line[N][N], revline_col[N][N], revline_row[N][N], jumlah_line(0);
int sum[N*N];

vector<pii> purut;

void cari() {
  // for(int i = 1; i <= n; i++) {
  //   for(int j = 1; j <= m; j++) {
  //     printf("%d ",ggrid[i][j]);
  //   }
  //   printf("\n");
  // }
  int cur=1e9; int solx=0, soly=0;
  int arah=BAWAH;
  int simp = 0;
  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= m; j++) {
      if (bawah[i][j] > 0) {
        int x=i+1;
        int ada=0;
        while(ggrid[x][j] >= 0) {
          ada += 1 - ggrid[x][j];
          x += 1;
        }
        if (ada > 0 && ada <= cur) {
          if (ada==cur) {
            int x = 0;
            // if (simp == bawah[i][j]) {
              x = rand()%2;
            // }
            if (x == 0) {
              simp = bawah[i][j];
              cur = ada; solx=i+1, soly=j;
              arah = BAWAH;
            }
          } else {
            simp = bawah[i][j];
            cur = ada; solx=i+1, soly=j;
            arah = BAWAH;
          }
        }
      }
      if (kanan[i][j] > 0) {
        int y=j+1;
        int ada=0;
        while(ggrid[i][y] >= 0) {
          ada += 1 - ggrid[i][y];
          y += 1;
        }
        if (ada > 0 && ada <= cur) {
          if (ada == cur) {
            int x = 0;
            // if (simp == kanan[i][j]) {
              x = rand()%2;
            // }
            if (x == 0) {
              simp = kanan[i][j];
              cur = ada; solx=i,soly=j+1;
              arah = KANAN;  
            }
          } else {
            simp = kanan[i][j];
            cur = ada; solx=i,soly=j+1;
            arah = KANAN;
          }
        }
      }
    }
  }
  
  if (cur == 1e9) return;

  if (arah == KANAN) {
    while(ggrid[solx][soly] >= 0) {
      if (ggrid[solx][soly] == 0) purut.push_back(mp(solx, soly));
      ggrid[solx][soly] = 1;
      soly += 1;
    }
  } else {
    while(ggrid[solx][soly] >= 0) {
      if (ggrid[solx][soly] == 0) purut.push_back(mp(solx, soly));
      ggrid[solx][soly] = 1;
      solx += 1;
    }
  }
  cari();
}

// solving rec
int SIZE;
vector<pii> urut;
bool sisa[N*N][10];
int ukur[N*N], sol[N][N];

void rec(int cur) {
  if (cur == SIZE) {
    for(int i = 1; i <= n; i++) {
      for(int j = 1; j <= m; j++) {
        if (j > 1) printf(" ");
        if (grid[i][j] == -1) printf("_");
        else printf("%d",sol[i][j]);
      }
      printf("\n");
    }
    exit(0);
  }
  int line1 = urut[cur].first;
  int line2 = urut[cur].second;
  int &x = sol[purut[cur].first][purut[cur].second];
  int &s1 = sum[line1];
  int &s2 = sum[line2];
  for(int i = 9; i >= 1; i--) {
    if (sisa[line1][i] && sisa[line2][i] && s1 - i >= 0 && s2 - i >= 0) {
      if (ukur[line1] == 1 && s1 - i != 0) {} 
      else if (ukur[line2] == 1 && s2 - i != 0) {}
      else {
        sisa[line1][i] = false;
        sisa[line2][i] = false;
        s1 -= i;
        s2 -= i;
        ukur[line1] -= 1;
        ukur[line2] -= 1;

        x = i;
        rec(cur + 1);

        sisa[line1][i] = true;
        sisa[line2][i] = true;
        s1 += i;
        s2 += i;
        ukur[line1] += 1;
        ukur[line2] += 1;
      }
    }
  }
}

int main() {
  srand(time(NULL));
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  memset(grid, -1, sizeof grid);
  memset(ggrid,-1, sizeof ggrid);

  cin >> n >> m;
  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= m; j++) {
      string x;
      cin >> x;
      if (x == BLANK) {
        kanan[i][j] = bawah[i][j] = grid[i][j] = -1;
      } else if (x == WHITE) {
        grid[i][j] = 0;
      } else {
        if (x[0]!='X') bawah[i][j] = ((x[0] - '0') * 10 + (x[1] - '0'));
        else bawah[i][j] = -1;
        if (x[3]!='X') kanan[i][j] = ((x[3] - '0') * 10 + (x[4] - '0')); 
        else kanan[i][j] = -1;
        grid[i][j] = -1;
      }
    }
  }

  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= m; j++) {
      ggrid[i][j] = grid[i][j];
      // printf("%d ",ggrid[i][j]);
    }
    // printf("\n");
  }
  cari();

  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= m; j++) {
      if (kanan[i][j] > 0) {
        no_line[i][j] = ++jumlah_line;
        sum[jumlah_line] = kanan[i][j];
        int x=i,y=j+1;
        while(grid[x][y] == 0) {
          revline_row[x][y] = jumlah_line;
          y++;
        }
      }
      if (bawah[i][j] > 0) {
        no_line[i][j] = ++jumlah_line;
        sum[jumlah_line] = bawah[i][j];
        int x=i+1,y=j;
        while(grid[x][y] == 0) {
          revline_col[x][y] = jumlah_line;
          x++;
        }
      }
    }
  }

  for(pii cur : purut) {
    urut.push_back(mp(revline_row[cur.f][cur.s], revline_col[cur.f][cur.s]));
    ukur[urut.back().first] += 1;
    ukur[urut.back().second] += 1;
  } 

  memset(sisa, true, sizeof sisa);
  SIZE = urut.size();
  rec(0);
  return 0;
}
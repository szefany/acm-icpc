#include <cstdio>
#include <cstring>

const char reflect[40][3] = {
  " s", "vn", "xv", "sf", "wr", "dg", "fh", "gj", "uo", "hk",
  "jl", "k;", "n,", "bm", "ip", "o ", " w", "et", "ad", "ry",
  "yi", "cb", "qe", "zc", "tu", " x", "l ", "m.", ",/", ". ",
};

char string[200];

int main() {
  char command[2];
  scanf("%s", command);
  int id = *command == 'L';

  scanf("%s", string);
  int length = strlen(string);
  for (int i = 0; i < length; ++ i) {
    int x;
    if (string[i] >= 'a' && string[i] <= 'z') x = string[i] - 'a';
    else if (string[i] == ';') x = 26;
    else if (string[i] == ',') x = 27;
    else if (string[i] == '.') x = 28;
    else x = 29;
    putchar(reflect[x][id]);
  }
  puts("");
  return 0;
} 

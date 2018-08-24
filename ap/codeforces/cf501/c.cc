
//
// Problem: https://codeforces.com/contest/1015/problem/C
// Author: montreal91
// Solved during training in 1:10
//

#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <utility>
#include <vector>

using namespace std;

typedef pair<int, int> Song;

bool song_comparator(const Song& s1, const Song& s2) {
  auto d1 = s1.first - s1.second;
  auto d2 = s2.first - s2.second;
  return d1 > d2;
}

void function(istream& in, ostream& out) {
  int number, capacity;
  in >> number >> capacity;

  vector<Song> playlist;
  for (auto i=0; i<number; i++) {
    int a, b;
    in >> a >> b;
    playlist.push_back(Song(a, b));
  }

  // First, we need to calculate sizes;
  long long uncompressed = 0, compressed = 0;
  for (auto& song : playlist) {
    uncompressed += song.first;
    compressed += song.second;
  }

  if (compressed > capacity) {
    out << -1 << endl;
    return;
  }

  sort(playlist.begin(), playlist.end(), song_comparator);

  auto total_size = uncompressed;
  auto i = 0;
  while (total_size > capacity) {
    total_size -= playlist[i].first - playlist[i].second;
    i++;
  }
  out << i << endl;
}

int main() {
  ifstream in("data/c.in");
  function(cin, cout);
  return 0;
}

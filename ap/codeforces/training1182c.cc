
//
// Problem: https://codeforces.com/contest/1182/problem/C
// Author: montreal91
// Type: training
// Time: 03:28
// Failed attempts: 0
//

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <limits>
#include <map>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

template<typename T>
void debug_print(T val, const string& label="") {
  #ifndef ONLINE_JUDGE
    string separator;
    if (label.size() == 0) {
      separator = "";
    }
    else {
      separator = " ";
    }
    cout << label << separator << val << endl;
  #endif // ONLINE_JUDGE
}

template<typename T>
void debug_print(
  const vector<T>& to_print,
  const string& separator=" ",
  const string& label=""
) {
  #ifndef ONLINE_JUDGE
    for (T p : to_print) {
      cout << p << separator;
    }
    cout << endl;
  #endif // ONLINE_JUDGE
}

bool is_vowel(char letter) {
  const string VOWELS = "aeiou";
  for (auto vowel : VOWELS) {
    if (letter == vowel) {
      return true;
    }
  }
  return false;
}

class Word {
public:

  string full_word;
  string vowels;

  Word(const string& word) : full_word(word) {
    vector<char> v;

    for (auto letter : word) {
      if (is_vowel(letter)) {
        v.push_back(letter);
      }
    }
    vowels = string(v.begin(), v.end());
    // There should be const casts to full_word and to vowels;
  }

  Word(const Word& word) :
  full_word(word.full_word),
  vowels(word.vowels) {}

  Word* operator=(const Word& word) {
    full_word = word.full_word;
    vowels = word.vowels;
    return this;
  }

  char get_last_vowel() const {
    int last = vowels.size() - 1;
    return vowels[last];
  }
};

struct WordComparator {
  bool operator()(const Word& one, const Word& two) {
    if (one.vowels.size() == two.vowels.size()) {
      return one.get_last_vowel() < two.get_last_vowel();
    }
    return one.vowels.size() < two.vowels.size();
  }
};

struct WordPair {
  Word one, two;
  bool can_be_last;

  WordPair(const Word& first, const Word& second, bool last) :
  one(first),
  two(second),
  can_be_last(last)
  {}
};

void make_good_pairs(
    const vector<Word>& words,
    int start,
    int end,
    vector<WordPair>* firsts,
    vector<WordPair>* lasts
) {
  vector<int> paired_indexes;
  vector<int> unpaired_indexes;
  for (int i=start + 1; i < end; i++) {
    if (words[i-1].get_last_vowel() == words[i].get_last_vowel()) {
      WordPair new_pair(words[i-1], words[i], true);
      lasts->push_back(new_pair);
      paired_indexes.push_back(i-1);
      paired_indexes.push_back(i);
      i++;
    }
  }

  int index = 0;

  for (int i=start; i<end; i++) {
    if (index >= paired_indexes.size()) {
      unpaired_indexes.push_back(i);
    }
    else if (i == paired_indexes[index]) {
      index++;
    }
    else {
      unpaired_indexes.push_back(i);
    }
  }
  if (unpaired_indexes.empty()) {
    return;
  }
  for (int i=0; i<unpaired_indexes.size() - 1; i+=2) {
    WordPair new_pair(
      words[unpaired_indexes[i]],
      words[unpaired_indexes[i+1]],
      false
    );
    firsts->push_back(new_pair);
  }
}

typedef pair<WordPair, WordPair> TLyric;

vector<TLyric> make_lyrics(
    const vector<WordPair>& first_pairs,
    const vector<WordPair>& last_pairs
) {
  vector<TLyric> res;
  if (first_pairs.size() >= last_pairs.size()) {
    for (int i=0; i<last_pairs.size(); i++) {
      res.push_back(TLyric(first_pairs[i], last_pairs[i]));
    }
    return res;
  }
  for (int i=0; i<first_pairs.size(); i++) {
    res.push_back(TLyric(first_pairs[i], last_pairs[i]));
  }
  for (int j=first_pairs.size(); j<last_pairs.size() - 1; j += 2) {
    res.push_back(TLyric(last_pairs[j], last_pairs[j+1]));
  }
  return res;
}

void print_lyrics(const vector<TLyric>& lyrics, ostream& out) {
  out << lyrics.size() << endl;
  for (auto& lyr : lyrics) {
    out << lyr.first.one.full_word << " " << lyr.second.one.full_word << endl;
    out << lyr.first.two.full_word << " " << lyr.second.two.full_word << endl;
  }
}

void function(istream& in, ostream& out) {
  ios::sync_with_stdio(false);
  in.tie(nullptr);

  int n;
  in >> n;

  vector<Word> words;

  for (int i=0; i<n; i++) {
    string new_word;
    in >> new_word;
    words.push_back(Word(new_word));
  }

  sort(words.begin(), words.end(), WordComparator());

  vector<WordPair> first_pairs;
  vector<WordPair> last_pairs;

  int start = 0; //, end = 0;

  for (int i=1; i < words.size(); i++) {
    if (words[i].vowels.size() > words[i-1].vowels.size()) {
      make_good_pairs(words, start, i, &first_pairs, &last_pairs);
      out << endl;
      start = i;
    }
  }
  make_good_pairs(words, start, words.size(), &first_pairs, &last_pairs);
  auto res = make_lyrics(first_pairs, last_pairs);
  print_lyrics(res, out);
}

int main() {
  #ifndef ONLINE_JUDGE
    using namespace chrono;
    auto time1 = duration_cast<milliseconds>(
      system_clock::now().time_since_epoch()
    );
  #endif // ONLINE_JUDGE

  function(cin, cout);

  #ifndef ONLINE_JUDGE
    auto time2 = duration_cast<milliseconds>(
      system_clock::now().time_since_epoch()
    );
    cout << "Time consumed: " << milliseconds(time2 - time1).count();
    cout << " ms.\n";
  #endif // ONLINE_JUDGE

  return 0;
}

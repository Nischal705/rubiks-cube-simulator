#pragma once
#include "Timer.h"
#include <climits>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
namespace fileHandler {
int N = 10; // no. of records to be read
std::vector<std::string> latestTimesArray(N);

int getPBinMS() {
  int pb_in_ms;
  ifstream infile("./pb.dat", ios::binary);
  infile.read(reinterpret_cast<char *>(&pb_in_ms), sizeof(int));
  infile.close();
  return pb_in_ms;
}

Time getPBinObject() { return getPBinMS(); }

void checkAndUpdatePB(Timer &t) {
  int new_time = t;
  if (new_time < getPBinMS()) {
    ofstream outfile("./pb.dat", ios::binary);
    outfile.write(reinterpret_cast<char *>(&new_time), sizeof(int));
    outfile.close();
  }
}

void write(Timer &t) {
  int t_in_ms = t;
  // manage PB too
  checkAndUpdatePB(t);
  // const char *new_time = t.getTime().c_str();
  ofstream outfile("./history.dat", ios::app | ios::binary);
  outfile.write(reinterpret_cast<char *>(&t_in_ms), sizeof(int));
  outfile.close();
}

void updateLatestTimesArray() {
  int t_in_ms;
  ifstream infile("./history.dat", ios::ate | ios::binary);
  // calculate no. of solves, cause it might be less than N
  int n_solves = infile.tellg() / sizeof(int);

  for (int i = 0; i < std::min(n_solves, N); i++) {
    infile.seekg(-(i + 1) * sizeof(int), ios::end);
    infile.read(reinterpret_cast<char *>(&t_in_ms), sizeof(int));
    latestTimesArray[i] = ((Time)t_in_ms).getString();
  }
}

void syncPBwithHistory() {
  int time_in_ms, pb_time_in_ms = INT_MAX;
  ifstream infile("history.dat", ios::binary);
  while (infile.read(reinterpret_cast<char *>(&time_in_ms), sizeof(int))) {
    pb_time_in_ms = std::min(pb_time_in_ms, time_in_ms);
  }
  infile.close();
  ofstream outfile("pb.dat", ios::binary);
  outfile.write(reinterpret_cast<char *>(&pb_time_in_ms), sizeof(int));
  outfile.close();
}

} // namespace fileHandler

#include "pch.h"

int main (int argc, char *argv[]) {
  google::InitGoogleLogging(argv[0]);

  LOG(INFO) << "Hello from server";
  return 0;
}

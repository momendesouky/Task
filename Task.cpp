#include <bits/stdc++.h>
using namespace std;
class EncryptionStrategy {
public:
    virtual void execute(const string& filename) = 0;
    virtual ~EncryptionStrategy() {}
};
class InMemoryStrategy : public EncryptionStrategy {
public:
    void execute(const string& filename) override {
        ifstream in(filename);
        ofstream out("inmemory_strategy.txt");
        string data, line;
        while (getline(in, line)) data += line + "\n";
        for (char& c : data) c += 1;
        out << data;
        in.close();
        out.close();
    }
};
class ChunkStrategy : public EncryptionStrategy {
public:
    void execute(const string& filename) override {
        ifstream in(filename);
        ofstream out("chunk_strategy.txt");
        string line;
        while (getline(in, line)) {
            for (char& c : line) c += 1;
            out << line << "\n";
        }
        in.close();
        out.close();
    }
};
class EncryptorContext {
private:
    EncryptionStrategy* strategy;

public:
    void setStrategy(EncryptionStrategy* s) { strategy = s; }
    void encrypt(const string& filename) {
        if (strategy) strategy->execute(filename);
    }
};
long getFileSize(const string& filename) {
  struct stat stat_buf;
  stat(filename.c_str(), &stat_buf);
  return stat_buf.st_size;
}

int main() {
  string filename = "input.txt";
  EncryptorContext context;

  if (getFileSize(filename) < 1024LL * 1024 * 1024) {
      InMemoryStrategy small;
      context.setStrategy(&small);
  } else {
      ChunkStrategy large;
      context.setStrategy(&large);
  }

  context.encrypt(filename);
  cout << "Encryption completed using Strategy Pattern.\n";
  return 0;
}
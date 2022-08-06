#pragma once

#include <ctime>
#include <ostream>
#include <string>
#include <vector>

class Bulk {
  public:
    Bulk() = default;
    ~Bulk() = default;
    void push(const std::string& cmd);
    void clear();
    size_t size() const;
    std::vector<std::string> get_cmds() const;
    std::time_t time() const;
    friend std::ostream& operator <<(std::ostream& os, const Bulk& bulk);

  private:
    std::vector<std::string> pool_{};
    std::time_t time_{};
};


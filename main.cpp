#include <string>
#include <iostream>
#include <vector>
#include <stack>

std::vector<std::string> & gen_char_swap(std::vector<std::string> & out, const std::string& in) {
  for (auto it = 0; it < in.size()-1; it++) {
    auto & cpy = out.emplace_back(in);
    std::swap(cpy[it], cpy[it+1]);
  }
  return out;
}

std::vector<std::string> & gen_missing_chars_stack(std::vector<std::string> & out, const std::string& in, size_t char_count) {
  std::stack<std::string> stack;
  stack.push(in);

  while (!stack.empty()) {
    auto str = std::move(stack.top());
    stack.pop();
    for (auto it = 0; it < str.size(); it++) {
      auto & cpy = out.emplace_back(str);
      cpy.erase(it, 1);
      if (cpy.size() - 1 > char_count)
        stack.push(cpy);
    }
  }
  return out;
}

std::vector<std::string> & gen_missing_chars(std::vector<std::string> & out, const std::string& in, size_t char_count) {
  for (auto it = 0; it < in.size(); it++) {
    auto & cpy = out.emplace_back(in);
    cpy.erase(it, 1);
    if (char_count > 1)
      gen_missing_chars(out, cpy, char_count-1);
  }
  return out;
}

template<typename T> struct PrintableVector {
  std::vector<T> const* vec;
};

template<typename T>
std::ostream& operator<<(std::ostream& s, PrintableVector<T> v) {
  for(auto const& elem : *v.vec) { s << elem << ", "; }
  return s;
}

std::vector<std::string> gen_custom_def(std::string in, size_t chars) {}
std::vector<std::string> gen_defines(std::string in, size_t chars) {}
int main() {
  std::vector<std::string> out;
  std::string in = "fecker";
  std::cout << "IN " << in << std::endl;
  std::cout << PrintableVector{&gen_char_swap(out, in)} << std::endl;
  out = {};
  std::cout << PrintableVector{&gen_missing_chars(out, in, 3)} << std::endl;
  std::cout << "stack " << in << std::endl;
  std::cout << PrintableVector{&gen_missing_chars_stack(out, in, 3)} << std::endl;

}

#include <iostream>
#include <string>

int main() {
  const int i = 2;
  switch (i) {
    case 1:
      std::cout << '1';
    case 2:  // execution starts at this case label
      std::cout << '2';
    case 3:
      std::cout << '3';
      [[fallthrough]];  // C++17 attribute to silent the warning on fallthrough
    case 5:
      std::cout << "45";
      break;  // execution of subsequent statements is terminated
    case 6:
      std::cout << '6';
  }

  std::cout << '\n';

  switch (i) {
    case 4:
      std::cout << 'a';
    default:
      std::cout << 'd';  // there are no applicable constant expressions
                         // therefore default is executed
  }

  std::cout << '\n';

  switch (i) {
    case 4:
      std::cout << 'a';  // nothing is executed
  }

  // when enumerations are used in a switch statement, many compilers
  // issue warnings if one of the enumerators is not handled
  enum color { RED, GREEN, BLUE };
  switch (RED) {
    case RED:
      std::cout << "red\n";
      break;
    case GREEN:
      std::cout << "green\n";
      break;
    case BLUE:
      std::cout << "blue\n";
      break;
  }

  // the C++17 init-statement syntax can be helpful when there is
  // no implicit conversion to integral or enumeration type
  struct Device {
    enum State { SLEEP, READY, BAD };
    auto state() const { return m_state; }

    /*...*/

   private:
    State m_state{};
  };

  switch (auto dev = Device{}; dev.state()) {
    case Device::SLEEP:
      /*...*/
      break;
    case Device::READY:
      /*...*/
      break;
    case Device::BAD:
      /*...*/
      break;
  }

  // pathological examples

  // the statement doesn't have to be a compound statement
  switch (0)
    std::cout << "this does nothing\n";

  // labels don't require a compound statement either
  switch (int n = 1) {
    case 0:
    case 1:
      std::cout << n << '\n';
  }

  char a_1 = 'a';
  std::string s_1 = "aaa";
  switch (a_1) {
    case 'a':
      std::cout << "Test char a" << std::endl;
      break;

    case 'b':
      std::cout << "Test char b" << std::endl;
      break;

    default:
      break;
  }
  /*
  double d_1 = 1.123;
  switch (d_1)
  {
  case 1:
    std::cout << "Test double a" << std::endl;
    break;

  case 2:
    std::cout << "Test double b" << std::endl;
    break;

  default:
    break;
  }
  */
  switch (2) {
    case 2: {
      int xx = 0;  // initialization
      std::cout << xx << '\n';
      break;
    }
    default:
      // compilation error: jump to default:
      // would enter the scope of 'x' without initializing it
      std::cout << "default\n";
      break;
  }
}
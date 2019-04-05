#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct Person;
struct Address;
size_t find_in_names(const std::vector<Person>& persons, const std::string& name_part);
std::vector<Person> find_person_from_city(const std::vector<Person>& haystack, const std::string& city);
std::vector<Person> read_file(const std::string& filename);
std::string rtrim(const std::string &s);
std::string caseInsensitive(std::string str);
std::ostream &operator<<(std::ostream &os, Person &p);
std::istream &operator>>(std::istream &in, Person &p);

struct Address {
  std::string street;
  int zip;
  std::string city;
};

struct Person {
  std::string name;
  std::string id;
  Address location;
};

size_t find_in_names(const std::vector<Person>& persons, const std::string& name_part) {
  size_t count = 0;
  for (const Person& c : persons) {
    if (caseInsensitive(c.name).find(caseInsensitive(name_part)) != std::string::npos) {
      count++;
    }
  }
  return count;
}

std::vector<Person> find_person_from_city(const std::vector<Person>& haystack, const std::string& city) {
  std::vector<Person> vec;
  for (const Person& c : haystack) {
    if (caseInsensitive(c.location.city) == caseInsensitive(city)) {
      vec.push_back(c);
    }
  }
  return vec;
}

std::vector<Person> read_file(const std::string& filename) {
  std::vector<Person> vec;
  std::ifstream names(filename);
  if (names.fail()) {
    std::cout << "Fail to open file\n";
    return vec;
  }
  Person temp;
  while (names.peek() != EOF) {
    names >> temp;
    vec.push_back(temp);
  }
  return vec;
}

std::string rtrim(const std::string &s) {
  size_t end = s.find_last_not_of(' ');
  return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::ostream &operator<<(std::ostream &os, Person &p) {
  os << p.name << '\n';
  os << p.id << '\n';
  os << p.location.city << '\n';
  os << p.location.street << '\n';
  os << p.location.zip << '\n';
  return os;
}

std::istream &operator>>(std::istream &in, Person &p) {
  std::string temp, temp2;
  int i, y;
  getline(in, p.name);
  getline(in, p.id);
  getline(in, temp);
  i = temp.find(',');
  y = temp.find("  ");
  p.location.street = temp.substr(0, i);
  temp2 = temp.substr(i + 1, 7);
  std::string::iterator end_pos = std::remove(temp2.begin(), temp2.end(), ' ');
  temp2.erase(end_pos, temp2.end());
  p.location.zip = stoi(temp2);
  p.location.city = rtrim(temp.substr(y + 2, -1));
  return in;
}
std::string caseInsensitive(std::string str){
  transform(str.begin(), str.end(), str.begin(), ::toupper);
  return str;
}

int main() {
  std::vector<Person> vec;
  vec = read_file("names.txt");
  int mode = 0;
  while (mode < 1 || mode > 3) {
    std::cout << "\n1 - Sök del av personnamn.\n"
                 "2 - Sök städer.\n"

                 "3 - Avsluta.\n";
    std::cin >> mode;
    switch (mode) {
    case 1: {
      std::cin.clear();
      std::cin.ignore();
      std::string str;
      std::cout << "Vilket namn vill du söka efter? ";
      std::getline(std::cin, str);
      std::cout << find_in_names(vec, str);
      mode = 0;
      continue;
    }
    case 2: {
      std::cin.clear();
      std::cin.ignore();
      std::string str;
      std::cout << "Vilket stad vill du söka efter? ";
      std::getline(std::cin, str);
      std::vector<Person> vec2;
      vec2 = find_person_from_city(vec, str);
      for (const Person &c : vec2) {
        std::cout << c.name << " " << c.location.city << '\n';
      }
      mode = 0;
      continue;
    }
    case 3:
      std::cin.clear();
      std::cin.ignore();
      std::cout << "Avslutar";
      break;
    default:
      std::cout << "Vänligen ange ett tal mellan 1 och 3 för att välja alternativ.\n";
    }
    std::cin.clear();
    std::cin.ignore();
  }
  return 0;
}
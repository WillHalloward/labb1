#include <algorithm>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

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

std::vector<Person> read_file(std::string filename);
size_t find_in_names(std::vector<Person> persons, std::string name_part);
std::vector<Person> find_person_from_city(std::vector<Person> haystack,
                                          std::string city);
std::istream &operator>>(std::istream &in, Person &p);

size_t find_in_names(std::vector<Person> persons, std::string name_part) {
  int my_count;
  my_count =
      std::count_if(persons.begin(), persons.end(), [&](const Person &s) {
        return !s.name.find(name_part);
      });
  std::cout << "Name: " << name_part << "\tcount: " << my_count << std::endl;
  return 0;
}

std::vector<Person> find_person_from_city(std::vector<Person> haystack,
                                          std::string city) {
  return haystack;
}

std::string rtrim(const std::string &s) {
  size_t end = s.find_last_not_of(' ');
  return (end == std::string::npos) ? "" : s.substr(0, end + 1);
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

std::vector<Person> read_file(const std::string filename) {
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

std::ostream &operator<<(std::ostream &os, Person &date) {
  os << date.name << '\n';
  os << date.id << '\n';
  os << date.location.city << '\n';
  os << date.location.street << '\n';
  os << date.location.zip << '\n';
  return os;
}

int main() {
  std::vector<Person> vec;
  vec = read_file("names.txt");
  for (Person c : vec) {
    std::cout << c << '\n';
  }
  find_in_names(vec, "Johan");
  find_person_from_city(vec, "test");
  return 0;
}

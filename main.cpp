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

std::ostream &operator<<(std::ostream &os, Person &date);
std::vector<Person> read_file(std::string filename);
size_t find_in_names(std::vector<Person> persons, std::string name_part);
std::vector<Person> find_person_from_city(std::vector<Person> haystack,
                                          std::string city);
std::istream &operator>>(std::istream &in, Person &p);

/*size_t find_in_names(std::vector<Person> persons, std::string name_part) {
  int my_count;
  transform(name_part.begin(), name_part.end(), name_part.begin(), ::tolower);
  my_count =
      std::count_if(persons.begin(), persons.end(), [&](const Person &s) {
      std::string str = s.name;
      transform(str.begin(), str.end(), str.begin(), ::tolower);
        return !str.find(name_part);
      });
  std::cout << "Namn: " << name_part << "\nantal: " << my_count << std::endl;
  return 0;
}*/

size_t find_in_names(std::vector<Person> persons, std::string name_part) {
  int count = 0;
  transform(name_part.begin(), name_part.end(), name_part.begin(), ::tolower);
  for (Person c : persons) {
    std::string str = c.name;
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    if (str.find(name_part) != std::string::npos) {
      count++;
    }
  }
  std::cout << count << "\n";
  return 0;
}

std::vector<Person> find_person_from_city(std::vector<Person> haystack,
                                          std::string city) {
  transform(city.begin(), city.end(), city.begin(), ::tolower);
  std::vector<Person> vec;
  for (Person c : haystack) {
    std::string str = c.location.city;
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    if (str == city) {
      vec.push_back(c);
    }
  }
  for (Person c : vec) {
    std::cout << c.name << " " << c.location.city << '\n';
  }
  return vec;
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

/*std::ostream &operator<<(std::ostream &os, Person &date) {
  os << date.name << " " << date.location.city << '\n';
  return os;
}*/

int main() {
  std::vector<Person> vec;
  vec = read_file("names.txt");
  /*for (Person c : vec) {
    std::cout << c << '\n';
  }*/
  int mode = 0;
  while (mode < 1 || mode > 3) {
    std::cout << "1 - Sök del av personnamn.\n"
                 "2 - Sök städer.\n"
                 "3 - Avsluta.\n";
    std::cin >> mode;
    switch (mode) {
    case 1: {
      std::string str;
      std::cout << "Vilket namn vill du söka efter? ";
      std::cin >> str;
      find_in_names(vec, str);
      mode = 0;
      continue;
    }
    case 2: {
      std::string str;
      std::cout << "Vilket stad vill du söka efter? ";
      std::cin >> str;
      find_person_from_city(vec, str);
      mode = 0;
      continue;
    }
    case 3:
      std::cout << "Avslutar";
      break;
    default:
      std::cout
          << "Vänligen ange ett tal mellan 1 och 3 för att välja alternativ.\n";
    }
    std::cin.clear();
    std::cin.ignore();
  }
  return 0;
}

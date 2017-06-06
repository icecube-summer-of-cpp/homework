#include <iostream>
#include <fstream>
#define age_file_name "age.txt"

inline void enable_stream_exception(std::ios& io){
  io.exceptions(std::ios_base::badbit | std::ios_base::failbit);
}

//assume that age is supposed to be an integer as a human would never say
//his age is 44.3 years
int main() {
  uint age = 0;
  {
    std::string age_string;
    int tmp_age;
    while(true){
      try {
        std::cout << "Please write your age: " << std::endl;
        std::cin >> age_string;
        tmp_age = std::stoi(age_string);
        if (tmp_age <= 0){
          std::cout << "Age needs to be bigger than 0!" << std::endl;
        }else{
          age = (unsigned int) tmp_age;
          break;
        }
      }catch (std::invalid_argument &e){
        std::cout << "Invalid input '" << age_string << "' given." << std::endl;
      }catch(std::out_of_range &e){
        std::cout << "Input was to big to be hold by an integer type!" << std::endl;
      }
    }
  }
  std::cout << "Your age as an integer is: " << age << std::endl;
  std::cout << "Writing to file " << age_file_name << std::endl;
  {//not needed, just added to show the principal of hte automatic closing of the file
    std::ofstream age_file;
    enable_stream_exception(age_file);
    //catching twice here as these are totally different error classes
    //first catch could e.g be an permission problem while the second one could be from a full hard drive
    try {
      age_file.open(age_file_name);
      
    }catch (...){
      std::cout << "Could not open " << age_file_name << " for writing." << std::endl;
      return 1;
    }
    try {
      age_file << age;
    }catch (...){
      std::cout << "Could not write to " << age_file_name << "." << std::endl;
      return 1;
    }
  }
  return 0;
}
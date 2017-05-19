//example of xml file:

//parser get low and high values from xml, finds the prime numbers between them and put them into xml between <primes> </primes>

// <?xml version="1.0" encoding="UTF-8"?>
// <root>
//   <intervals>
//     <interval>
//       <low> 100 </low>  
//       <high> 200</high>
//     </interval>
//    </intervals>
//   <primes> </primes>
// </root>


#include <iostream>
#include <regex>
#include <fstream>
#include <string>
#include <vector>
#include <utility>


class PrimeNum {
	public:
		PrimeNum() {}
		~PrimeNum() {}

		std::vector<int> is_prime(int min) {
			std::vector<int> result;
			result = prime(min, min);
			return result;
		}

		std::vector<int> is_prime(int min, int max) {
			std::vector<int> result;
			result = prime(min, max);
			return result;
		}

		std::vector<int> is_prime(std::vector<std::pair<int, int> > temp) {
			std::vector<int> result;
			for (int i = 0; i < temp.size(); i++) {
				std::vector<int> buffer = prime(temp[i].first, temp[i].second);
				for (int q = 0; q < buffer.size(); q++) {
					result.push_back(buffer[q]);
				}
			}
			return result;
		}		

		std::vector<int> prime(int min, int max) {
			int array_size = max - min + 1;
			int array[array_size];
			std::vector<int> result;
			
			for (int i = 0; i < array_size; i++) {
				array[i] = min++;
			}

			for (int i = 0, divisor = 2; i < array_size; i++) {
				if (array[i] == 0) {
					continue;
				}
				if (array[i] == 1) {
					array[i] = 0;
					continue;
				}
				for (int q = 0; q < array_size; q++) {
					if (divisor > (array[q] / 2)) {
						continue;
					}
					if (array[q] % divisor == 0) {
						array[q] = 0;
					}
				}
				if (array[i] != 0) {
					result.push_back(array[i]);
				}
				++divisor;
			}
			return result;
		}
};


class Parser {
	private:
		std::fstream file;
		std::string content_form_file;
		std::string name;
	public:
		Parser(const std::string& name) {
			this->name = name;
		}
		~Parser() {}

		void open_file() {
			file.open(name);
			if ( !file.is_open() ) {
				std::cout << "File is not opened." << std::endl;
				exit(EXIT_FAILURE);
			}
		}

		std::vector<std::pair<int, int> > start_parsing() {
			open_file();
			content_form_file = file_content();
			file.close();
			return regular_exp(content_form_file);
		}

		const std::string file_content() {
			std::string temp((std::istreambuf_iterator<char>(file)),
                 std::istreambuf_iterator<char>());
			return temp;
		}

		// parsing with regular expressions
		std::vector<std::pair<int, int> > regular_exp(std::string& content_form_file) {
			std::regex low("\\d+(?=[ ]*</low)");
			std::regex high("\\d+(?=[ ]*</high)");

			std::sregex_iterator next_low(content_form_file.begin(), content_form_file.end(), low);
			std::sregex_iterator next_high(content_form_file.begin(), content_form_file.end(), high);
			std::sregex_iterator end;

			std::vector<std::pair<int, int> > result;

			std::string::size_type sz;
			
			while (next_low != end) {
				std::smatch low_result = *next_low;
				std::smatch high_result = *next_high;
				std::pair<int, int> p;
				p = std::make_pair(std::stoi(low_result.str(), &sz), std::stoi(high_result.str(), &sz));

				result.push_back(p);

				next_low++;
				next_high++;
			}
			return result;
		}

		void add_to_file(std::vector<int> result) {
			open_file();
			std::string buff = "> ";

			for (int i = 0; i < result.size(); i++) {
				buff += std::to_string(result[i]);
				buff += " ";
			}

			file.seekg(0);
			std::regex replace_r(">.*(?=</primes>)");
			file << std::regex_replace(content_form_file, replace_r, buff);
			file.close();
		}
};

int main(int argc, char *argv[]) {
	const bool areFewParams = (argc < 2);
	if (areFewParams){
		std::cout << "Please, add file name\n";
		return 1;
	}
	const std::string input_data_file_name = argv[1];
	
	Parser p(input_data_file_name);
	PrimeNum isPrime;
	p.add_to_file(isPrime.is_prime(p.start_parsing()));


	return 0;
}

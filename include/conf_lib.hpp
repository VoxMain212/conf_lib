#include <cstddef>
#include <fstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <variant>

#define DEBUG


namespace conf_lib
{
    using config_value = std::variant<
        std::string,
        bool,
        int,
        double
    >;

    struct CONFIG 
    {
        std::unordered_map<std::string, std::unordered_map<std::string, config_value>> labels_sections;

        CONFIG() {}

        void open(std::string filename)
        {
            std::ifstream ini_file(filename);
            if (!ini_file.is_open())
            {
                throw std::runtime_error("File not exists");
            } // Если не открылся

            std::unordered_map<std::string, std::unordered_map<std::string, config_value>> temp;
            std::string current_label;
            std::string line;
            while (std::getline(ini_file, line))
            {
                size_t pos = 0;
                skip_whitespace(line, pos);

                if (pos >= line.length())
                {
                    continue;
                }

                if (line[pos] == ';') {
                    continue;
                } else if (line.empty()) {
                    continue;
                } else if (line[0] == '[') {
                    std::string new_label;
                    ++pos;
                    while (line[pos] != ']') {
                        new_label += line[pos];
                        ++pos;
                    }
                    temp[new_label] = std::unordered_map<std::string, config_value> {};
                    current_label = new_label;
                } else {
                    std::string key;
                    while ((line[pos] != ' ' && line[pos] != '=') && pos < line.length())
                    {
                        key += line[pos];
                        ++pos;
                    }
                    skip_whitespace(line, pos);
                    if (line[pos] == '=')
                    {
                        ++pos;
                        skip_whitespace(line, pos);
                    }
                    std::string value;
                    while (pos < line.length())
                    {
                        value += line[pos];
                        ++pos;
                    }
                    temp[current_label][key] = value;
                }
            }
            this->labels_sections = temp;
        }

        std::unordered_map<std::string, config_value> operator[] (std::string key)
        {
            return labels_sections[key];
        }

        private:
        void skip_whitespace(std::string &s, size_t &pos)
        {
            while (pos < s.length() && s[pos] == ' ') {++pos;};
        }
    };
}
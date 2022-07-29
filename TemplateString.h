#ifndef TEMPLATE_STR_TEMPLATE_STR_H
#define TEMPLATE_STR_TEMPLATE_STR_H


#include<map>
#include<concepts>
#include<string>



template<typename Type>
concept CharTypes = std::is_same<Type, char>::value ||
                    std::is_same<Type, wchar_t>::value ||
                    std::is_same<Type, char8_t>::value ||
                    std::is_same<Type, char16_t>::value ||
                    std::is_same<Type, char32_t>::value;


#define T_CT template<CharTypes T>


namespace tstr {




    T_CT
    class template_basic_string {

        //Constructors
    public:
        template_basic_string();
        template_basic_string(const template_basic_string<T>& other) = default;
        template_basic_string<T>& operator =(const template_basic_string<T>& other) = default;
        explicit template_basic_string(const std::basic_string<T>& pattern);
        explicit template_basic_string(const std::basic_string<T>& pattern, const std::basic_string<T>& open_delimiter, const std::basic_string<T>& close_delimiter);

        //getter and setters
        const std::basic_string<T> get_pattern() const;
        const std::map<std::basic_string<T>, std::basic_string<T>> get_arguments() const;
        const std::basic_string<T> get_substituted();
        const std::basic_string<T> get_open_delimiter();
        const std::basic_string<T> get_close_delimiter();


        void set_pattern(const std::basic_string<T>& pattern);
        void put_argument(const std::basic_string<T>& replaceable, const std::basic_string<T>& replacement);
        void put_arguments(const std::map<std::basic_string<T>, std::basic_string<T>>& arguments_);
        void set_open_delimiter(const std::basic_string<T>& open_delimiter);
        void set_close_delimiter(const std::basic_string<T>& close_delimiter);
        void set_delimiters(const std::basic_string<T>& open_delimiter, const std::basic_string<T>& close_delimiter);



        //fields
    private:
        static std::basic_string<T> default_open_delimiter, default_close_delimiter;
        std::basic_string<T> open_delimiter, close_delimiter;
        std::basic_string<T> pattern;
        std::map<std::basic_string<T>, std::basic_string<T>> arguments;
        std::basic_string<T> prepare_template();
        std::basic_string<T> validate_replaceable(const std::basic_string<T>& replaceable);


    };
}



// defined all types of strings for template_basic_string
using template_string = tstr::template_basic_string<char>;
using template_wstring = tstr::template_basic_string<wchar_t>;
using template_u8string = tstr::template_basic_string<char8_t>;
using template_u16string = tstr::template_basic_string<char16_t>;
using template_u32string = tstr::template_basic_string<char32_t>;


T_CT
std::basic_string<T> tstr::template_basic_string<T>::default_open_delimiter(reinterpret_cast<T*>(const_cast<char*>("{{")));


T_CT
std::basic_string<T> tstr::template_basic_string<T>::default_close_delimiter(reinterpret_cast<T*>(const_cast<char*>("}}")));


T_CT
tstr::template_basic_string<T>::template_basic_string(const std::basic_string<T>& pattern){
    set_pattern(pattern);
    set_delimiters(default_open_delimiter, default_close_delimiter);
}


T_CT
tstr::template_basic_string<T>::template_basic_string(const std::basic_string<T>& pattern, const std::basic_string<T>& open_delimiter, const std::basic_string<T>& close_delimiter){
    set_pattern(pattern);
    set_delimiters(open_delimiter, close_delimiter);
}
T_CT
tstr::template_basic_string<T>::template_basic_string(){
    set_delimiters(default_open_delimiter, default_close_delimiter);
}

T_CT
const std::basic_string<T> tstr::template_basic_string<T>::get_pattern() const {
    return pattern;
}


T_CT
void tstr::template_basic_string<T>::set_pattern(const std::basic_string<T>& pattern) {
    this->pattern = pattern;
}


T_CT
const std::map<std::basic_string<T>, std::basic_string<T>> tstr::template_basic_string<T>::get_arguments() const {
    return arguments;
}


T_CT
void tstr::template_basic_string<T>::put_argument(const std::basic_string<T>& replaceable, const std::basic_string<T>& replacement) {
    this->arguments.emplace(validate_replaceable(replaceable), replacement);
}


T_CT
void tstr::template_basic_string<T>::put_arguments(const std::map<std::basic_string<T>, std::basic_string<T>>& arguments_) {
    for (auto& [replaceable, replacement] : arguments_) {
        put_argument(replaceable, replacement);
    }
}

T_CT
void tstr::template_basic_string<T>::set_open_delimiter(const std::basic_string<T>& open_delimiter){
    this->open_delimiter = open_delimiter;
}

T_CT
void tstr::template_basic_string<T>::set_close_delimiter(const std::basic_string<T>& close_delimiter){
    this->close_delimiter = close_delimiter;
}
T_CT
void tstr::template_basic_string<T>::set_delimiters(const std::basic_string<T>& open_delimiter, const std::basic_string<T>& close_delimiter){
    set_open_delimiter(open_delimiter);
    set_close_delimiter(close_delimiter);
}

T_CT
const std::basic_string<T> tstr::template_basic_string<T>::get_substituted() {
    return prepare_template();
}
T_CT
const std::basic_string<T> tstr::template_basic_string<T>::get_open_delimiter(){
    return open_delimiter;
}

T_CT
const std::basic_string<T> tstr::template_basic_string<T>::get_close_delimiter(){
    return close_delimiter;
}

T_CT
std::basic_string<T> tstr::template_basic_string<T>::prepare_template() {
    std::basic_string<T> prepare = pattern;
    for (auto& [replaceable, replacement] : arguments) {
        size_t start_position = 0;
        while ((start_position = prepare.find(replaceable, start_position)) != std::string::npos) {
            prepare.replace(start_position, replaceable.length(), replacement);
            start_position += replacement.length();
        }
    }
    return prepare;
};

T_CT
std::basic_string<T> tstr::template_basic_string<T>::validate_replaceable(const std::basic_string<T>& replaceable) {
    if (replaceable.starts_with(get_open_delimiter()) && replaceable.ends_with(get_close_delimiter())) {
        return replaceable;
    }
    else {
        return get_open_delimiter() + replaceable + get_close_delimiter();
    }
};


#endif //TEMPLATE_STR_TEMPLATE_STR_H
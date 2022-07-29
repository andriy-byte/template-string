
#include <iostream>
#include <memory>
#include "TemplateString.h"

int main() {


    tstr::template_basic_string<char> ts("hello {{some}}");
    ts.put_argument("some", "world");

    std::cout << ts.get_pattern() << std::endl;
    std::cout << ts.get_substituted() << std::endl;
    std::cout << std::endl;

    tstr::template_basic_string<wchar_t> tmp(L"my name is {{name}}");

    tmp.put_argument(L"{{name}}", L"David");
    std::wcout << tmp.get_substituted() << std::endl;
    std::cout << std::endl;

    std::unique_ptr<tstr::template_basic_string<char>> temp_str_p(
            new tstr::template_basic_string<char>("I like to listen {{musical_performer}} - {{musical_composition}}"));

    temp_str_p->put_arguments({{"{{musical_performer}}", "Eels"},
                               {"musical_composition",   "Novocain For the Soul"}});

    std::cout << temp_str_p->get_pattern() << std::endl;
    std::cout << temp_str_p->get_substituted() << std::endl;
    std::cout << std::endl;

    for (auto &[key, value]: temp_str_p->get_arguments()) {
        std::cout << key << " - " << value << std::endl;
    }

    std::cout << std::endl;


    tstr::template_basic_string<wchar_t> b = tstr::template_basic_string<wchar_t>(L"next is -> **first>> ", L"**",
                                                                                  L">>");

    b.put_argument(L"first", L"hello world !!!");

    std::wcout << b.get_pattern() << std::endl;
    std::wcout << b.get_substituted();
    std::cout << std::endl << std::endl;




    // making alias for example
    using template_string = tstr::template_basic_string<char>;
    using template_wstring = tstr::template_basic_string<wchar_t>;
    using template_u8string = tstr::template_basic_string<char8_t>;
    using template_u16string = tstr::template_basic_string<char16_t>;
    using template_u32string = tstr::template_basic_string<char32_t>;


    template_string c("car model : \\ee\\");
    c.set_open_delimiter("\\");
    c.set_close_delimiter("\\");


    c.put_argument("ee", "mercedes-benz");
    std::cout << c.get_pattern() << std::endl;
    std::cout << c.get_substituted() << std::endl;
    std::cout << std::endl;

    return 0;
}

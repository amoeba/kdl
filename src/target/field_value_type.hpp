// Copyright (c) 2019-2020 Tom Hancocks
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#if !defined(KDL_FIELD_VALUE_TYPE_HPP)
#define KDL_FIELD_VALUE_TYPE_HPP

#include <string>
#include <optional>
#include <vector>
#include "parser/lexeme.hpp"

namespace kdl
{

    struct field_value_type
    {
    private:
        std::optional<lexeme> m_name;
        std::vector<lexeme> m_associated;
        bool m_is_reference;

    public:
        field_value_type(const bool reference);
        field_value_type(const lexeme name, const bool reference = false);

        auto name() const -> std::string;
        auto is_reference() const -> bool;
        auto name_lexeme() const -> std::optional<lexeme>;

        auto set_name(const lexeme name) -> void;
        auto set_is_reference(const bool reference) -> void;

        auto add_associated(const lexeme name) -> void;
        auto associated_count() const -> std::size_t;
        auto associated_at(const int i) const -> lexeme;
    };

};

#endif //KDL_FIELD_VALUE_TYPE_HPP
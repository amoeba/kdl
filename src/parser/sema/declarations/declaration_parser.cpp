// Copyright (c) 2020 Tom Hancocks
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

#include "diagnostic/fatal.hpp"
#include "parser/sema/declarations/declaration_parser.hpp"

#include <utility>
#include "parser/sema/declarations/resource_instance_parser.hpp"

// MARK: - Constructor

kdl::sema::declaration_parser::declaration_parser(kdl::sema::parser &parser, std::weak_ptr<target> target)
    : m_parser(parser), m_target(std::move(target))
{

}
// MARK: - Parser

auto kdl::sema::declaration_parser::parse() -> std::vector<kdl::build_target::resource_instance>
{
    if (m_target.expired()) {
        throw std::logic_error("Expired target found in declaration parser.");
    }
    auto target = m_target.lock();

    m_parser.ensure({ expectation(lexeme::identifier, "declare").be_true() });
    if (!m_parser.expect({ expectation(lexeme::identifier).be_true() })) {
        log::fatal_error(m_parser.peek(), 1, "Declaration type name must be an identifier.");
    }
    auto type = target->type_container_named(m_parser.read());

    std::vector<kdl::build_target::resource_instance> instances;
    m_parser.ensure({ expectation(lexeme::l_brace).be_true() });
    while (m_parser.expect({ expectation(lexeme::r_brace).be_false() })) {

        kdl::sema::resource_instance_parser parser(m_parser, type, m_target);
        if (m_parser.expect({ expectation(lexeme::identifier, "new").be_true() })) {
            parser.set_keyword("new");
        }
        else if (m_parser.expect({ expectation(lexeme::identifier, "override").be_true() })) {
            parser.set_keyword("override");
        }
        else {
            log::fatal_error(m_parser.peek(), 1, "Unexpected lexeme '" + m_parser.peek().text() + "' encountered.");
        }

        instances.emplace_back(parser.parse());
        m_parser.ensure({ expectation(lexeme::semi).be_true() });
    }
    m_parser.ensure({ expectation(lexeme::r_brace).be_true() });
    return instances;
}


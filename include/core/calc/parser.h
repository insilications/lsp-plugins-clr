/*
 * Copyright (C) 2020 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2020 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-plugins
 * Created on: 18 сент. 2019 г.
 *
 * lsp-plugins is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * lsp-plugins is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with lsp-plugins. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef CORE_CALC_PARSER_H_
#define CORE_CALC_PARSER_H_

#include <core/LSPString.h>
#include <core/calc/types.h>
#include <core/calc/evaluator.h>
#include <core/calc/Tokenizer.h>

namespace lsp
{
    namespace calc
    {
        enum expr_type_t
        {
            ET_CALC,
            ET_RESOLVE,
            ET_VALUE
        };

        typedef struct expr_t
        {
            evaluator_t     eval;       // Evaluation routine
            expr_type_t     type;       // Expression data type
            union
            {
                struct
                {
                    expr_t     *left;       // First operand (unary, binary, ternary)
                    expr_t     *right;      // Second operand (binary, ternary)
                    expr_t     *cond;       // Condition (ternary)
                } calc;

                struct
                {
                    LSPString  *name;       // Base name of variable
                    size_t      count;      // Number of additional indexes
                    expr_t    **items;      // List of additional indexes
                } resolve;

                value_t     value;          // Value
            };
        } expr_t;

        expr_t  *parse_create_expr();
        void    parse_destroy(expr_t *expr);

        status_t parse_ternary(expr_t **expr, Tokenizer *t, size_t flags);
        status_t parse_or(expr_t **expr, Tokenizer *t, size_t flags);
        status_t parse_xor(expr_t **expr, Tokenizer *t, size_t flags);
        status_t parse_and(expr_t **expr, Tokenizer *t, size_t flags);
        status_t parse_bit_or(expr_t **expr, Tokenizer *t, size_t flags);
        status_t parse_bit_xor(expr_t **expr, Tokenizer *t, size_t flags);
        status_t parse_bit_and(expr_t **expr, Tokenizer *t, size_t flags);
        status_t parse_cmp_eq(expr_t **expr, Tokenizer *t, size_t flags);
        status_t parse_cmp_rel(expr_t **expr, Tokenizer *t, size_t flags);
        status_t parse_strcat(expr_t **expr, Tokenizer *t, size_t flags);
        status_t parse_strrep(expr_t **expr, Tokenizer *t, size_t flags);
        status_t parse_addsub(expr_t **expr, Tokenizer *t, size_t flags);
        status_t parse_muldiv(expr_t **expr, Tokenizer *t, size_t flags);
        status_t parse_power(expr_t **expr, Tokenizer *t, size_t flags);
        status_t parse_not(expr_t **expr, Tokenizer *t, size_t flags);
        status_t parse_sign(expr_t **expr, Tokenizer *t, size_t flags);
        status_t parse_func(expr_t **expr, Tokenizer *t, size_t flags);
        status_t parse_primary(expr_t **expr, Tokenizer *t, size_t flags);
        status_t parse_identifier(expr_t **expr, Tokenizer *t, size_t flags);

        status_t parse_expression(expr_t **expr, Tokenizer *t, size_t flags);
    }
}

#endif /* CORE_CALC_PARSER_H_ */

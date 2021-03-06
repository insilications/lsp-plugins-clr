/*
 * Copyright (C) 2020 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2020 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-plugins
 * Created on: 5 июл. 2017 г.
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

#include <ui/ctl/ctl.h>

namespace lsp
{
    namespace ctl
    {
        const ctl_class_t CtlGrid::metadata = { "CtlGrid", &CtlWidget::metadata };

        CtlGrid::CtlGrid(CtlRegistry *src, LSPGrid *widget, ssize_t orientation): CtlWidget(src, widget)
        {
            pClass          = &metadata;
            nOrientation    = orientation;
        }

        CtlGrid::~CtlGrid()
        {
        }

        void CtlGrid::set(widget_attribute_t att, const char *value)
        {
            LSPGrid *grid       = widget_cast<LSPGrid>(pWidget);

            switch (att)
            {
                case A_ROWS:
                    if (grid != NULL)
                        PARSE_INT(value, grid->set_rows(__));
                    break;
                case A_COLS:
                    if (grid != NULL)
                        PARSE_INT(value, grid->set_columns(__));
                    break;
                case A_VSPACING:
                    if (grid != NULL)
                        PARSE_INT(value, grid->set_vspacing(__));
                    break;
                case A_HSPACING:
                    if (grid != NULL)
                        PARSE_INT(value, grid->set_hspacing(__));
                    break;
                case A_SPACING:
                    if (grid != NULL)
                        PARSE_INT(value, grid->set_spacing(__, __));
                    break;
                case A_HORIZONTAL:
                    if ((grid != NULL) && (nOrientation < 0))
                        PARSE_BOOL(value, grid->set_horizontal(__));
                    break;
                case A_VERTICAL:
                case A_TRANSPOSE:
                    if ((grid != NULL) && (nOrientation < 0))
                        PARSE_BOOL(value, grid->set_vertical(__));
                    break;
                default:
                    CtlWidget::set(att, value);
                    break;
            }
        }

        status_t CtlGrid::add(CtlWidget *child)
        {
            LSPGrid *grid       = widget_cast<LSPGrid>(pWidget);
            if (grid == NULL)
                return STATUS_BAD_STATE;

            CtlCell *cell       = ctl_cast<CtlCell>(child);
            return (cell != NULL) ?
                    grid->add(cell->widget(), cell->rows(), cell->columns()) :
                    grid->add(child->widget());
        }
    } /* namespace ctl */
} /* namespace lsp */

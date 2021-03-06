/*
 * Copyright (C) 2020 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2020 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-plugins
 * Created on: 29 сент. 2017 г.
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

#ifndef UI_TK_WIDGETS_DIALOGS_LSPMESSAGEBOX_H_
#define UI_TK_WIDGETS_DIALOGS_LSPMESSAGEBOX_H_

namespace lsp
{
    namespace tk
    {
        class LSPMessageBox: public LSPWindow
        {
            public:
                static const w_class_t metadata;

            protected:
                LSPLabel        sHeading;
                LSPLabel        sMessage;
                LSPAlign        sHeadAlign;
                LSPAlign        sMsgAlign;
                LSPBox          sVBox;
                LSPBox          sHBox;
                size_t          nMinBtnWidth;
                size_t          nMinBtnHeight;
                cvector<LSPButton> vButtons;

            public:
                explicit LSPMessageBox(LSPDisplay *dpy);
                virtual ~LSPMessageBox();

                virtual status_t init();
                virtual void destroy();

            protected:
                static status_t slot_on_button_submit(LSPWidget *sender, void *ptr, void *data);
                void do_destroy();

            public:
                inline LSPLabel        *heading_widget()    { return &sHeading; }
                inline LSPLabel        *message_widget()    { return &sMessage; }
                inline LSPLocalString  *heading()           { return sHeading.text(); }
                inline LSPLocalString  *message()           { return sMessage.text(); }
                inline bool             use_heading() const { return sHeadAlign.visible(); }
                inline bool             use_message() const { return sMsgAlign.visible(); }
                inline LSPButton       *button(size_t idx)  { return vButtons.get(idx); }
                inline size_t           buttons() const     { return vButtons.size(); }
                inline size_t           min_button_width() const    { return nMinBtnWidth; }
                inline size_t           min_button_height() const   { return nMinBtnHeight; }

            public:
                void        set_use_heading(bool use);
                void        set_use_message(bool use);

                status_t    add_button(const char *text, ui_event_handler_t handler = NULL, void *arg = NULL);
                status_t    add_button(const LSPString *text, ui_event_handler_t handler = NULL, void *arg = NULL);
                status_t    add_button(const LSPLocalString *text, ui_event_handler_t handler = NULL, void *arg = NULL);

                void        clear_buttons();

                void        set_min_button_width(size_t value);
                void        set_min_button_height(size_t value);

        };
    
    } /* namespace tk */
} /* namespace lsp */

#endif /* UI_TK_WIDGETS_DIALOGS_LSPMESSAGEBOX_H_ */

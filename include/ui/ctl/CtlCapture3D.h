/*
 * Copyright (C) 2020 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2020 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-plugins
 * Created on: 12 мая 2019 г.
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

#ifndef UI_CTL_CTLCAPTURE3D_H_
#define UI_CTL_CTLCAPTURE3D_H_

#include <core/3d/raytrace.h>

namespace lsp
{
    namespace ctl
    {
        class CtlCapture3D: public CtlWidget
        {
            public:
                static const ctl_class_t metadata;

            protected:
                class LSPCaptureColor: public LSPColor
                {
                    protected:
                        CtlCapture3D   *pCapture;
                        friend class CtlCapture3D;

                    protected:
                        virtual void    color_changed();

                    public:
                        inline LSPCaptureColor(CtlCapture3D *capture) { pCapture = capture; }
                };

            protected:
                LSPCaptureColor sXColor;
                CtlColor        sColor;
                float           fHueShift;

                room_capture_config_t sCapture;

                CtlPort        *pPosX;
                CtlPort        *pPosY;
                CtlPort        *pPosZ;
                CtlPort        *pYaw;
                CtlPort        *pPitch;
                CtlPort        *pRoll;
                CtlPort        *pSize;
                CtlPort        *pMode;
                CtlPort        *pAngle;
                CtlPort        *pDistance;

            protected:
                void            sync_capture_state();

            public:
                explicit CtlCapture3D(CtlRegistry *src, LSPCapture3D *widget);
                virtual ~CtlCapture3D();

            public:
                virtual void init();

                virtual void set(widget_attribute_t att, const char *value);

                virtual void notify(CtlPort *port);

                virtual void end();
        };
    
    } /* namespace ctl */
} /* namespace lsp */

#endif /* UI_CTL_CTLCAPTURE3D_H_ */

/*
 * Copyright (C) 2020 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2020 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-plugins
 * Created on: 26 окт. 2015 г.
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

#ifndef CORE_PLUGIN_H_
#define CORE_PLUGIN_H_

#include <dsp/dsp.h>
#include <core/types.h>
#include <core/IPort.h>
#include <core/IWrapper.h>
#include <core/ICanvas.h>
#include <core/IStateDumper.h>
#include <core/debug.h>

#include <metadata/metadata.h>

#include <data/cvector.h>

namespace lsp
{
    class plugin_t
    {
        private:
            plugin_t &operator = (const plugin_t &);

        protected:
            cvector<IPort>              vPorts;
            const plugin_metadata_t    *pMetadata;
            IWrapper                   *pWrapper;

            ssize_t                     fSampleRate;
            ssize_t                     nLatency;
            bool                        bActivated;
            bool                        bUIActive;

        public:
            explicit plugin_t(const plugin_metadata_t &mdata);
            virtual ~plugin_t();

        public:
            const plugin_metadata_t *get_metadata() const { return pMetadata;       };
            inline ssize_t get_latency() const          { return nLatency;          };
            inline void set_latency(ssize_t latency)    { nLatency = latency;       };

            inline bool add_port(IPort *port)           { return vPorts.add(port);  };
            inline IPort *port(size_t id)               { return vPorts[id];        };
            inline size_t ports_count() const           { return vPorts.size();     };

            void set_sample_rate(ssize_t sr);

            inline ssize_t get_sample_rate() const      { return fSampleRate;       };
            inline bool active() const                  { return bActivated;        };
            inline bool ui_active() const               { return bUIActive;         };

            inline IWrapper *wrapper()                  { return pWrapper;          };

            inline void activate_ui()
            {
                if (!bUIActive)
                {
                    bUIActive       = true;
                    lsp_trace("UI has been activated");
                    ui_activated();
                }
            }

            inline void deactivate_ui()
            {
                if (bUIActive)
                {
                    bUIActive       = false;
                    lsp_trace("UI has been deactivated");
                    ui_deactivated();
                }
            }

            inline void activate()
            {
                if (!bActivated)
                {
                    bActivated      = true;
                    activated();
                    pWrapper->query_display_draw();
                }
            }

            inline void deactivate()
            {
                if (bActivated)
                {
                    bActivated      = false;
                    deactivated();
                    pWrapper->query_display_draw();
                }
            }

        public:
            /** Initialize plugin
             *
             * @param wrapper plugin wrapper interface
             */
            virtual void init(IWrapper *wrapper);

            /** Update sample rate of data processing
             *
             * @param sr new sample rate
             */
            virtual void update_sample_rate(long sr);

            /** Destroy plugin state
             *
             */
            virtual void destroy();

            /** Triggered plugin activation
             *
             */
            virtual void activated();

            /** Triggered UI activation
             *
             */
            virtual void ui_activated();

            /** Triggered input port change, need to update configuration
             *
             */
            virtual void update_settings();

            /** Report current time position for plugin
             *
             * @param pos current time position
             * @return true if need to call for plugin setting update
             */
            virtual bool set_position(const position_t *pos);

            /** Process data
             *
             * @param samples number of samples to process
             */
            virtual void process(size_t samples);

            /** Draw inline display on canvas
             * This feature will not work unless E_INLINE_DISPLAY extension is
             * specified in plugin's metadata
             *
             * @param cv canvas
             * @param width maximum canvas width
             * @param height maximum canvas height
             * @return status of operation
             */
            virtual bool inline_display(ICanvas *cv, size_t width, size_t height);

            /** Triggered UI deactivation
             *
             */
            virtual void ui_deactivated();

            /** Triggered plugin deactivation
             *
             */
            virtual void deactivated();

            /**
             * Lock the KVT storage
             * @return pointer to KVT storage or NULL
             */
            virtual KVTStorage *kvt_lock();

            /**
             * Try to lock the KVT storage
             * @return pointer to KVT storage or NULL if not locked/not supported
             */
            virtual KVTStorage *kvt_trylock();

            /**
             * Release the KVT storage
             */
            virtual void kvt_release();

            /** Callback for case when plugin's state has been saved
             *
             */
            virtual void state_saved();

            /** Callback for case when plugin's state has been loaded
             *
             */
            virtual void state_loaded();

            /**
             * Dump plugin state
             * @param v state dumper
             */
            virtual void dump(IStateDumper *v) const;
    };

}

#endif /* CORE_PLUGIN_H_ */

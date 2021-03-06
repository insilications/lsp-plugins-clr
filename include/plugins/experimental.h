/*
 * Copyright (C) 2020 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2020 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-plugins
 * Created on: 11 янв. 2017 г.
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

#ifndef PLUGINS_EXPERIMENTAL_H_
#define PLUGINS_EXPERIMENTAL_H_

#include <metadata/metadata.h>
#include <metadata/plugins.h>

#include <core/plugin.h>
#include <core/filters/Filter.h>
#include <core/util/Counter.h>

namespace lsp
{
#ifndef LSP_NO_EXPERIMENTAL
    class test_plugin: public plugin_t, public test_plugin_metadata
    {
        protected:
            typedef struct osc_t
            {
                float       A0; // Initial amplitude
                float       X0; // Initial location
                float       W0; // Frequency
                float       P0; // Initial phase
                float       R0; // Reduction/Decay
            } osc_t;

        protected:
            IPort      *pIn[2];
            IPort      *pOut[2];
            IPort      *pMesh;
            IPort      *pStream;
            IPort      *pFB;
            IPort      *pGain;
            IPort      *pFileName;
            IPort      *pHeadCut;
            IPort      *pTailCut;
            IPort      *pFadeIn;
            IPort      *pFadeOut;
            IPort      *pStatus;
            IPort      *pLength;
            IPort      *pData;

            IPort      *pOutFile;
            IPort      *pOutCmd;
            IPort      *pOutStatus;
            IPort      *pOutProgress;

            float       fGain;
            bool        bFileSet;
            size_t      nPhase;
            size_t      nColorID;
            size_t      nStatus;
            size_t      nProgCurr;
            size_t      nProgLast;

            size_t      nOscPhase;
            size_t      nOscLeft;
            size_t      nRows;

            osc_t       vOsc[3];

            uint32_t    nLisCounter;        // Lissajous counter's max value
            uint32_t    nLisPhase;          // Lissajous phase
            uint32_t    nLisSteps;          // Lissajous phase step counter

            float       vBuffer[FRM_BUFFER_SIZE];
            float       vLisX[LIS_BUFFER_SIZE];
            float       vLisY[LIS_BUFFER_SIZE];
            float       vLisS[LIS_BUFFER_SIZE];

        protected:
            void        oscillate(float *dst, const osc_t *osc, float t, ssize_t n);

        public:
            explicit test_plugin();
            virtual ~test_plugin();

        public:
            virtual void init(IWrapper *wrapper);

            virtual void process(size_t samples);

            virtual void update_settings();

            virtual bool inline_display(ICanvas *cv, size_t width, size_t height);
    };

    class filter_analyzer:  public plugin_t, public filter_analyzer_metadata
    {
        protected:
            typedef struct pfilter_t
            {
                Filter              sFilter;
                filter_params_t     sFP;
                size_t              nOp;

                IPort              *pType;
                IPort              *pSlope;
                IPort              *pOp;
                IPort              *pFreqLo;
                IPort              *pFreqHi;
                IPort              *pGain;
                IPort              *pQuality;
            } pilter_;

        protected:
            IPort      *pIn;
            IPort      *pOut;
            IPort      *pGraph;
            pfilter_t   vFilters[2];
            float       vChart[MESH_POINTS*2];
            float       vTmpBuf[MESH_POINTS*2];

        public:
            explicit filter_analyzer();
            virtual ~filter_analyzer();

        public:
            virtual void init(IWrapper *wrapper);

            virtual void process(size_t samples);

            virtual void update_settings();

            void set_sample_rate(long sr);
    };
#endif
}

#endif /* INCLUDE_PLUGINS_EXPERIMENTAL_H_ */

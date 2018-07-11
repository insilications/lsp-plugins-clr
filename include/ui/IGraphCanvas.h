/*
 * IGraphCanvas.h
 *
 *  Created on: 27 нояб. 2015 г.
 *      Author: sadko
 */

#ifndef IGRAPHCANVAS_H_
#define IGRAPHCANVAS_H_

namespace lsp
{
    
    class IGraphCanvas
    {
        protected:
            size_t          nWidth;
            size_t          nHeight;
            ssize_t         nLeft;
            ssize_t         nTop;
            Color           sColor;
            IGraph         *pGraph;
            bool            bAntiAliasing;

        protected:
            void set_size(ssize_t width, ssize_t height);

        public:
            IGraphCanvas(IGraph *g);
            virtual ~IGraphCanvas();

        public:
            inline size_t  width() const    { return nWidth;            }
            inline size_t  height() const   { return nHeight;           }
            inline ssize_t left() const     { return nLeft;             }
            inline ssize_t right() const    { return nWidth + nLeft;    }
            inline ssize_t top() const      { return nTop;              }
            inline ssize_t bottom() const   { return nTop - nHeight;    }

            virtual void line(ssize_t x1, ssize_t y1, ssize_t x2, ssize_t y2);

            virtual void line(float a, float b, float c);

            virtual void set_line_width(size_t width);

            virtual void move_to(ssize_t x, ssize_t y);

            virtual void line_to(ssize_t x, ssize_t y);

            virtual void draw_lines(float *x, float *y, size_t count);

            virtual void draw_poly(float *x, float *y, size_t count, const Color &stroke, const Color &fill);

            virtual void circle(ssize_t x, ssize_t y, ssize_t r);

            virtual void radial_gradient(ssize_t x, ssize_t y, const Color &c1, const Color &c2, ssize_t r);

            virtual void stroke();

            virtual void set_color(const Color &c);

            virtual void set_color_rgb(float r, float g, float b);

            virtual void clear();

            virtual void center(size_t id, float *x, float *y);

            virtual void center(Center *c, float *x, float *y);

            virtual void out_text(ssize_t x, ssize_t y, float h_pos, float v_pos, float size, const char *text);

            virtual bool set_anti_aliasing(bool enable);
    };

} /* namespace lsp */

#endif /* IGRAPHCANVAS_H_ */
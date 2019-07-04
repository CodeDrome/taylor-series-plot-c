#include<stdio.h>
#include<math.h>

#include"svg.h"
#include"taylorseries.h"

// --------------------------------------------------------
// FUNCTION taylor_init
// --------------------------------------------------------
void taylor_sin_plot(int maxsin, int maxdegrees, int step, int width, int height, char* filename)
{
    int topmargin = 64;
    int bottommargin = 32;
    int leftmargin = 32;
    int rightmargin = 128;

    int graph_height = height - topmargin - bottommargin;
    int graph_width = width - leftmargin - rightmargin;
    double pixels_per_unit_x = (double)graph_width / (double)maxdegrees;
    double pixels_per_unit_y = (double)graph_height / ((double)maxsin * 2.0);
    double x;
    double y;
    char number_string[8];
    double yzero = topmargin + (graph_height / 2);
    double sine;
    double radians;
    int colourindex;

    char colours[6][7] = {"blue", "red", "orange", "purple", "green", "cyan"};

    // Create svg struct
    svg* psvg;
    psvg = svg_create(width, height);

    if(psvg == NULL)
    {
        puts("psvg is NULL");
    }
    else
    {
        svg_fill(psvg, "#FFFFFF");

        // header text and border lines
        svg_text(psvg, leftmargin, 38, "sans-serif", 16, "#000000", "#000000", "start", "Sines calculated with Taylor Polynomials to degree 3, 5, 7, 9 and 11");
        svg_line(psvg, "#808080", 2, leftmargin, topmargin, leftmargin, height - bottommargin);
        svg_line(psvg, "#808080", 2, leftmargin, height - bottommargin, width - rightmargin, height - bottommargin);

        // y axis indexes and values
        y = topmargin;
        for(int s = maxsin; s >= (maxsin * -1); s--)
        {
            svg_line(psvg, "#808080", 1, leftmargin - 8, y, width - rightmargin, y);

            sprintf(number_string, "%d", s);
            svg_text(psvg, 20, y + 4, "sans-serif", 12, "#000000", "#000000", "end", number_string);

            y += pixels_per_unit_y;
        }

        // x axis indexes and values
        x = leftmargin;
        for(int d = 0; d <= maxdegrees; d+= 90)
        {
            svg_line(psvg, "#808080", 1, x, topmargin, x, height - bottommargin + 8);

            sprintf(number_string, "%d", d);
            svg_text(psvg, x, height - bottommargin + 24, "sans-serif", 12, "#000000", "#000000", "middle", number_string);

            x += (pixels_per_unit_x * 90);
        }

        // key
        x = width - rightmargin + 16;
        y = topmargin + 16;
        int currdegree = 3;
        char sdegree[3];
        for(colourindex = 0; colourindex <= 5; colourindex++)
        {
            svg_circle(psvg, colours[colourindex], 0, colours[colourindex], 6, x, y);

            if(colourindex == 0)
            {
                svg_text(psvg, x + 16, y + 4, "sans-serif", 12, "#000000", "#000000", "start", "math.h sin");
            }
            else
            {
                sprintf(sdegree, "%d", currdegree);
                svg_text(psvg, x + 16, y + 4, "sans-serif", 12, "#000000", "#000000", "start", sdegree);
                currdegree += 2;
            }

            y+= 24;
        }

        if(taylor_init(11))
        {
            x = leftmargin;

            for(double degree = 0; degree <= maxdegrees; degree+= step)
            {
                radians = degree / DEGREES_IN_RADIAN;

                // C Library sin
                sine = sin(radians);

                y = yzero - (sine * pixels_per_unit_y);

                colourindex = 0;

                svg_circle(psvg, colours[colourindex], 0, colours[colourindex], 3, x, y);

                // Taylor Polynomials
                for(int poly_degree = 3; poly_degree <= 11; poly_degree+= 2)
                {
                    colourindex++;

                    sine = taylor_sin_rad(radians, poly_degree);

                    if(sine <= maxsin && sine >= (maxsin * -1))
                    {
                        y = yzero - (sine * pixels_per_unit_y);

                        svg_circle(psvg, colours[colourindex], 0, colours[colourindex], 3, x, y);
                    }
                }

                x += pixels_per_unit_x * step;
            }

            taylor_free();
        }

        svg_finalize(psvg);

        svg_save(psvg, filename);

        puts("File saved");

        svg_free(psvg);
    }
}

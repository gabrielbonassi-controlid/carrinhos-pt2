#include <cekeikon.h>
#include <cmath>
#include <omp.h>

using namespace std;

struct peak
{
    float value;
    Point position;
    int scale;
};

int main(int argc, char *argv[])
{

    omp_set_num_threads(4);

    if (argc != 4)
    {
        std::cout << "Utilização do programa:" << std::endl;
        std::cout << "fase3 video_capturado.avi quadrado.png video_localizando.avi" << std::endl;
        std::cout << "" << std::endl;

        return 0;
    }

    string video_path = argv[1];
    string quadrado_path = argv[2];
    string output_path = argv[3];

    // quadrado input
    Mat_<FLT> temp;
    le(temp, quadrado_path);

    std::vector<Mat_<FLT>> templates(10);
    double resize_factor = 1.1541;
    int final_size = 19;

    // generate resized templates
    for (int i = 0; i < 10; i++)
    {
        double multiplier = pow(resize_factor, i);
        Size new_size = Size(final_size * multiplier, final_size * multiplier);
        resize(temp, templates[i], new_size, 0, 0, INTER_AREA);
        templates[i] = somaAbsDois(dcReject(templates[i], 1.0));
    }

    // video input
    VideoCapture vi(video_path);
    float fps = vi.get(CV_CAP_PROP_FPS);
    int nc = vi.get(CV_CAP_PROP_FRAME_WIDTH);
    int nl = vi.get(CV_CAP_PROP_FRAME_HEIGHT);
    int frames = vi.get(CV_CAP_PROP_FRAME_COUNT);

    // video output
    VideoWriter vo(output_path, CV_FOURCC('X', 'V', 'I', 'D'), fps, Size(nc, nl));
    Mat_<COR> frame_int;
    Mat_<FLT> frame_float;

    int peak_count = 20;
    peak max_peak_ncc;

    std::vector<peak> peaks_ncc(peak_count), peaks_cc(peak_count);
    std::vector<Mat_<FLT>> mat_ncc(10);
    std::vector<Mat_<FLT>> mat_cc(10);

    for (int frame = 0; frame < frames; frame++)
    {
        TimePoint t1 = timePoint();

        double max_peak_cc = 0.0, threshold = 0.5;

        vi >> frame_int;

        converte(frame_int, frame_float);
        int i;
#pragma omp parallel for num_threads(5)
        for (i = 0; i < 10; i++)
        {
            mat_cc[i] = matchTemplateSame(frame_float, templates[i], CV_TM_CCORR);
            mat_ncc[i] = matchTemplateSame(frame_float, templates[i], CV_TM_CCOEFF_NORMED);
        }

        for (int n = 0; n < 10; n++)
        {
            for (int l = 0; l < mat_cc[n].rows; l++)
            {
                for (int c = 0; c < mat_cc[n].cols; c++)
                {
                    for (int m = 0; m < 20; m++)
                    {
                        if (mat_cc[n](l, c) >= peaks_cc[m].value)
                        {
                            peaks_cc[m].position = Point(c, l);
                            peaks_cc[m].value = mat_cc[n](l, c);
                            peaks_cc[m].scale = n;
                        }
                    }
                }
            }
        }

        for (int m = 0; m < 20; m++)
        {
            if (mat_ncc[peaks_cc[m].scale](peaks_cc[m].position.y, peaks_cc[m].position.x) >= max_peak_ncc.value)
            {
                max_peak_ncc.value = mat_ncc[peaks_cc[m].scale](peaks_cc[m].position.y, peaks_cc[m].position.x);
                max_peak_ncc.position = peaks_cc[m].position;
                max_peak_ncc.scale = peaks_cc[m].scale;
            }
        }

        if (max_peak_ncc.value > threshold)
        {
            Point center = max_peak_ncc.position;
            rectangle(frame_int, center - Point(templates[max_peak_ncc.scale].cols / 2, templates[max_peak_ncc.scale].rows / 2), center + Point(templates[max_peak_ncc.scale].cols / 2, templates[max_peak_ncc.scale].rows / 2), Scalar(0, 0, 255), 2);
        }

        vo << frame_int;

        TimePoint t2 = timePoint();
        double s = timeSpan(t1, t2);

        std::cout << "\rFrame rate: " << 1 / s << " fps" << flush;

        // int ch = (signed char)(waitKey(30)); // Se apertar ESC
        // if (ch == 27)
        //     break;
        // imshow("frame", frame_int);
    }
    return 0;
}
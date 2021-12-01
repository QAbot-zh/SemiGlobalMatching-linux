#include "SemiGlobalMatching.h"
#include <chrono>
using namespace std::chrono;

// opencv library
#include <opencv2/opencv.hpp>
#ifdef _DEBUG
#pragma comment(lib,"opencv_world310d.lib")
#else
#pragma comment(lib,"opencv_world310.lib")
#endif

/**
 * \brief
 * \param argv 3
 * \param argc argc[1]:锟斤拷影锟斤拷路锟斤拷 argc[2]: 锟斤拷影锟斤拷路锟斤拷 argc[3]: 锟斤拷小锟接诧拷[锟斤拷选锟斤拷默锟斤拷0] argc[4]: 锟斤拷锟斤拷硬锟絒锟斤拷选锟斤拷默锟斤拷64]
 * \param eg. ..\Data\cone\im2.png ..\Data\cone\im6.png 0 64
 * \param eg. ..\Data\Reindeer\view1.png ..\Data\Reindeer\view5.png 0 128
 * \return
 */
int main(int argv, char** argc)
{
    if (argv < 3) {
        std::cout << "锟斤拷锟斤拷锟斤拷锟劫ｏ拷锟斤拷锟斤拷锟斤拷指锟斤拷锟斤拷锟斤拷影锟斤拷路锟斤拷锟斤拷" << std::endl;
        return -1;
    }

    //锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷//
    // 锟斤拷取影锟斤拷
    std::string path_left = argc[1];
    std::string path_right = argc[2];

    cv::Mat img_left_c = cv::imread(path_left, cv::IMREAD_COLOR);
    cv::Mat img_left = cv::imread(path_left, cv::IMREAD_GRAYSCALE);
    cv::Mat img_right = cv::imread(path_right, cv::IMREAD_GRAYSCALE);

    if (img_left.data == nullptr || img_right.data == nullptr) {
        std::cout << "锟斤拷取影锟斤拷失锟杰ｏ拷" << std::endl;
        return -1;
    }
    if (img_left.rows != img_right.rows || img_left.cols != img_right.cols) {
        std::cout << "锟斤拷锟斤拷影锟斤拷叽绮灰伙拷拢锟�" << std::endl;
        return -1;
    }


    //锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷//
    const sint32 width = static_cast<uint32>(img_left.cols);
    const sint32 height = static_cast<uint32>(img_right.rows);

    // 锟斤拷锟斤拷影锟斤拷幕叶锟斤拷锟斤拷锟�
    auto bytes_left = new uint8[width * height];
    auto bytes_right = new uint8[width * height];
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            bytes_left[i * width + j] = img_left.at<uint8>(i, j);
            bytes_right[i * width + j] = img_right.at<uint8>(i, j);
        }
    }

    printf("Loading Views...Done!\n");

    // SGM匹锟斤拷锟斤拷锟斤拷锟斤拷
    SemiGlobalMatching::SGMOption sgm_option;
    // 锟桔猴拷路锟斤拷锟斤拷
    sgm_option.num_paths = 8;
    // 锟斤拷选锟接差范围
    sgm_option.min_disparity = argv < 4 ? 0 : atoi(argc[3]);
    sgm_option.max_disparity = argv < 5 ? 64 : atoi(argc[4]);
    // census锟斤拷锟斤拷锟斤拷锟斤拷
    sgm_option.census_size = SemiGlobalMatching::Census5x5;
    // 一锟斤拷锟皆硷拷锟�
    sgm_option.is_check_lr = true;
    sgm_option.lrcheck_thres = 1.0f;
    // 唯一锟斤拷约锟斤拷
    sgm_option.is_check_unique = true;
    sgm_option.uniqueness_ratio = 0.99;
    // 锟睫筹拷小锟斤拷通锟斤拷
    sgm_option.is_remove_speckles = true;
    sgm_option.min_speckle_aera = 50;
    // 锟酵凤拷锟斤拷P1锟斤拷P2
    sgm_option.p1 = 10;
    sgm_option.p2_init = 150;
    // 锟接诧拷图锟斤拷锟�
    // 锟接诧拷图锟斤拷锟侥斤拷锟斤拷锟斤拷锟斤拷煽锟斤拷锟斤拷锟斤拷锟斤拷蹋锟斤拷锟斤拷锟斤拷锟斤拷锟戒，锟斤拷锟斤拷锟叫ｏ拷锟斤拷锟斤拷锟斤拷
    sgm_option.is_fill_holes = false;

    printf("w = %d, h = %d, d = [%d,%d]\n\n", width, height, sgm_option.min_disparity, sgm_option.max_disparity);

    // 锟斤拷锟斤拷SGM匹锟斤拷锟斤拷实锟斤拷
    SemiGlobalMatching sgm;

    //锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷//
    // 锟斤拷始锟斤拷
	printf("SGM Initializing...\n");
    auto start = std::chrono::steady_clock::now();
    if (!sgm.Initialize(width, height, sgm_option)) {
        std::cout << "SGM锟斤拷始锟斤拷失锟杰ｏ拷" << std::endl;
        return -2;
    }
    auto end = std::chrono::steady_clock::now();
    auto tt = duration_cast<std::chrono::milliseconds>(end - start);
    printf("SGM Initializing Done! Timing : %lf s\n\n", tt.count() / 1000.0);

    //锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷//
    // 匹锟斤拷
	printf("SGM Matching...\n");
    start = std::chrono::steady_clock::now();
    // disparity锟斤拷锟介保锟斤拷锟斤拷锟斤拷锟截碉拷锟接诧拷锟斤拷
    auto disparity = new float32[uint32(width * height)]();
    if (!sgm.Match(bytes_left, bytes_right, disparity)) {
        std::cout << "SGM匹锟斤拷失锟杰ｏ拷" << std::endl;
        return -2;
    }
    end = std::chrono::steady_clock::now();
    tt = duration_cast<std::chrono::milliseconds>(end - start);
    printf("\nSGM Matching...Done! Timing :   %lf s\n", tt.count() / 1000.0);

    //锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷//
	// 锟斤拷示锟接诧拷图
    // 注锟解，锟斤拷锟斤拷锟斤拷撇锟斤拷锟斤拷锟絛isp_mat锟斤拷锟斤拷锟捷ｏ拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷示锟酵憋拷锟斤拷锟斤拷锟矫的★拷锟斤拷锟斤拷锟斤拷锟揭拷锟斤拷锟斤拷锟斤拷disparity锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷荩锟斤拷锟斤拷锟斤拷锟斤拷馗锟斤拷锟斤拷锟�
    cv::Mat disp_mat = cv::Mat(height, width, CV_8UC1);
    float min_disp = width, max_disp = -width;
    for (sint32 i = 0; i < height; i++) {
        for (sint32 j = 0; j < width; j++) {
            const float32 disp = disparity[i * width + j];
            if (disp != Invalid_Float) {
                min_disp = std::min(min_disp, disp);
                max_disp = std::max(max_disp, disp);
            }
        }
    }
    for (sint32 i = 0; i < height; i++) {
        for (sint32 j = 0; j < width; j++) {
            const float32 disp = disparity[i * width + j];
            if (disp == Invalid_Float) {
                disp_mat.data[i * width + j] = 0;
            }
            else {
                disp_mat.data[i * width + j] = static_cast<uchar>((disp - min_disp) / (max_disp - min_disp) * 255);
            }
        }
    }

    cv::imshow("视差图", disp_mat);
    cv::Mat disp_color;
    applyColorMap(disp_mat, disp_color, cv::COLORMAP_JET);
    cv::imshow("视差图-伪彩", disp_color);

    // 锟斤拷锟斤拷锟斤拷
    std::string disp_map_path = argc[1]; disp_map_path += ".d.png";
    std::string disp_color_map_path = argc[1]; disp_color_map_path += ".c.png";
    std::cout << disp_map_path;
    cv::imwrite(disp_map_path, disp_mat);
    cv::imwrite(disp_color_map_path, disp_color);


    cv::waitKey(0);

    //锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷//
    // 锟酵凤拷锟节达拷
    delete[] disparity;
    disparity = nullptr;
    delete[] bytes_left;
    bytes_left = nullptr;
    delete[] bytes_right;
    bytes_right = nullptr;

    // system("pause");
    return 0;
}
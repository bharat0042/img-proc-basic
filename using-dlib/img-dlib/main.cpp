#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <dlib/image_transforms.h>

#include <filesystem>
#include <iostream>
#include <exception>

namespace fs = std::experimental::filesystem;

int main()
{
    fs::path img_path{"C:/Dev/projects/ml-with-c++/data/dog.jpg"};
    dlib::array2d<dlib::rgb_pixel> img;
    dlib::load_image(img, img_path.string());

    unsigned long key;
    bool is_printable;
    dlib::image_window window(img, "Image");
    window.get_next_keypress(key, is_printable);

    dlib::array2d<dlib::rgb_pixel> img2(img.nr() / 2, img.nc() / 2);
    dlib::resize_image(img, img2, dlib::interpolate_nearest_neighbor());
    std::swap(img, img2);
    window.set_image(img);
    window.get_next_keypress(key, is_printable);

    resize_image(1.5, img);
    window.set_image(img);
    window.get_next_keypress(key, is_printable);

    extract_image_chip(img, dlib::rectangle(0, 0, img.nc() / 2, img.nr() / 2), img2);
    std::swap(img, img2);
    window.set_image(img);
    window.get_next_keypress(key, is_printable);

    img2.set_size(img.nr(), img.nc());
    transform_image(img, img2, dlib::interpolate_bilinear(),
                    dlib::point_transform_affine(dlib::identity_matrix<double>(2),
                                           dlib::vector<double, 2>(-50, -50)));
    std::swap(img, img2);
    window.set_image(img);
    window.get_next_keypress(key, is_printable);

    rotate_image(img, img2, -45, dlib::interpolate_bilinear());
    std::swap(img, img2);
    window.set_image(img);
    window.get_next_keypress(key, is_printable);


    int top = 50;
    int bottom = 20;
    int left = 150;
    int right = 5;
    img2.set_size(img.nr() + top + bottom, img.nc() + left + right);
    transform_image(
        img, img2, dlib::interpolate_bilinear(),
        dlib::point_transform_affine(dlib::identity_matrix<double>(2),
                               dlib::vector<double, 2>(-left / 2, -top / 2)));
    std::swap(img, img2);
    window.set_image(img);
    window.get_next_keypress(key, is_printable);

    dlib::array2d<dlib::bgr_pixel> img_bgr;
    assign_image(img_bgr, img);

    dlib::array2d<unsigned char> img_gray;
    assign_image(img_gray, img);
    window.set_image(img_gray);
    window.get_next_keypress(key, is_printable);

    dlib::array2d<float> img_float;
    assign_image(img_float, img);

    dlib::array2d<dlib::rgb_pixel> rgb_img(5, 5);
    assign_all_pixels(rgb_img, dlib::rgb_pixel(255, 128, 64));
    auto channel_size = static_cast<size_t>(rgb_img.nc() * rgb_img.nr());
    std::vector<unsigned char> ch1(channel_size);
    std::vector<unsigned char> ch2(channel_size);
    std::vector<unsigned char> ch3(channel_size);
    size_t i{0};
    try
    {
        for (long r = 0; r < rgb_img.nr(); ++r)
        {
            for (long c = 0; c < rgb_img.nc(); ++c)
            {
                ch1[i] = rgb_img[r][c].red;
                ch2[i] = rgb_img[r][c].green;
                ch3[i] = rgb_img[r][c].blue;
                ++i;
            }
        }
    }
    catch(const std::exception& err)
    {
        std::cerr << err.what();
    }

    return 0;
}

#include <iostream>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <Magick++.h>

using namespace std;
using namespace Magick;
namespace po = boost::program_options;
namespace fs = boost::filesystem;

bool last_file_is_directory(const vector<string> &fns) {
    return fs::is_directory(fs::path(fns.back()));
}

void clean_whiteboard_in_image_file(const fs::path &src, const fs::path &dst) {
    Image image;
    image.read(src.string());
    image.morphology(ConvolveMorphology, DoGKernel, "15,100,0");
    image.negate();
    image.normalize();
    image.blur(0.0, 1.0);
    image.channel(RGBChannels);
    image.level(0.6, 0.91, 0.1);
    image.write(dst.string());
}

int main(int argc, char **argv)
{
    InitializeMagick(*argv);

    po::options_description desc("Allowed options");
    desc.add_options()
            ("help", "Print help message")
            ("input-file", po::value< vector<string> >(), "Image file or maybe (if last) output directory")
    ;

    po::positional_options_description p;
    p.add("input-file", -1);

    po::variables_map vm;
    try {
        po::store(po::command_line_parser(argc, argv).
                  options(desc).positional(p).run(), vm);
        if (strstr(argv[0], " -")) {
#ifdef _WIN32
            po::store(po::command_line_parser(po::split_winmain(argv[0])).options(desc).run(), vm);
#else
            po::store(po::command_line_parser(po::split_unix(argv[0], " ")).options(desc).run(), vm);
#endif
        }
    } catch (po::error &e) {
        cerr << e.what() << endl;
        return 1;
    }
    po::notify(vm);

    if (vm.count("help")) {
        cout << "Usage: whiteboardcleaner option(s) file(s)" << endl;
        cout << desc;
        return 0;
    }

    if (!vm.count("input-file")) {
        cerr << "Specify at least one file, the last one might be output directory" << endl;
        return 1;
    }

    const vector<string> &input_files = vm["input-file"].as< vector<string> >();
    vector<string> regular_files;
    copy_if(input_files.begin(), input_files.end(), back_inserter(regular_files),
            [](string fn) { return fs::is_regular_file(fs::path(fn)); });

    try {
        if (input_files.size() > 1 && last_file_is_directory(input_files)) {
            fs::path out_dir(input_files.back());
            for (auto &fn: regular_files) {
                fs::path tfn = out_dir / fs::path(fn).filename();
                cout << "Processing " << fn << " to " << tfn << endl;
                clean_whiteboard_in_image_file(fs::path(fn), tfn);
            }
        } else {
            for (auto &fn: regular_files) {
                cout << "Processing " << fn << endl;
                clean_whiteboard_in_image_file(fs::path(fn), fs::path(fn));
            }
        }
    } catch (Magick::ErrorFileOpen &error) {
        cerr << "Error opening file:" << error.what() << endl;
    } catch (Magick::Exception &error) {
        cerr << "Error: " << error.what() << endl;
    }

    return 0;
}

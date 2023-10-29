#include <iostream>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>

using namespace std;
namespace po = boost::program_options;
namespace fs = boost::filesystem;


bool last_file_is_directory(const vector<string> &fns) {
    return fs::is_directory(fs::path(fns.back()));
}

int main(int argc, char **argv)
{
    po::options_description desc("Allowed options");
    desc.add_options()
            ("help", "Print help message")
            ("width,w", po::value<int>(), "Width to scale the image to")
            ("height,h", po::value<int>(),"Height to scale the image to")
            ("input-file", po::value< vector<string> >(), "Image file or maybe (if last) output directory")
    ;

    po::positional_options_description p;
    p.add("input-file", -1);

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).
              options(desc).positional(p).run(), vm);
    if (strstr(argv[0], " -")) {
#ifdef _WIN32
        po::store(po::command_line_parser(po::split_winmain(argv[0])).options(desc).run(), vm);
#else
        po::store(po::command_line_parser(po::split_unix(argv[0], " ")).options(desc).run(), vm);
#endif
    }
    po::notify(vm);

    if (vm.count("help")) {
        cout << "Usage: imagescaler option(s) file(s)" << endl;
        cout << desc;
        return 0;
    }

    int width = 0;
    int height = 0;
    if (vm.count("width") && !vm.count("height")) {
        width = vm["width"].as<int>();
        cout << "width " << width << endl;
    } else if (!vm.count("width") && vm.count("height")) {
        height = vm["height"].as<int>();
        cout << "height " << height << endl;
    } else {
        cerr << "Please specify either width or height" << endl;
        return 1;
    }

    if (!vm.count("input-file")) {
        cerr << "Specify at least one file, the last one might be output directory" << endl;
        return 1;
    }

    const vector<string> &input_files = vm["input-file"].as< vector<string> >();
    vector<string> regular_files;
    copy_if(input_files.begin(), input_files.end(), back_inserter(regular_files),
            [](string fn) { return fs::is_regular_file(fs::path(fn)); });

    if (input_files.size() > 1 && last_file_is_directory(input_files)) {
        fs::path out_dir(input_files.back());
        for (auto &fn: regular_files) {
            fs::path tfn = out_dir / fs::path(fn).filename();
            cout << fn << " " << tfn << endl;
        }
    } else {
        for (auto &fn: regular_files) {
            cout << fn << " " << fn << endl;
        }
    }

    return 0;
}

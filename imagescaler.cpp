#include <iostream>
#include <boost/program_options.hpp>

using namespace std;
namespace po = boost::program_options;

int main(int argc, char **argv)
{
    po::options_description desc("Allowed options");
    desc.add_options()
            ("help,h", "Print help message")
            ("width", po::value<int>(), "Width to scale the image to")
            ("height", po::value<int>(),"Height to scale the image to")
            ("input-file", po::value< vector<string> >(), "Image file or maybe (if last) output directory")
    ;

    po::positional_options_description p;
    p.add("input-file", -1);

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).
              options(desc).positional(p).run(), vm);
    po::notify(vm);

    if (vm.count("help")) {
        cout << "Usage: imagescaler option(s) file(s)" << endl;
        cout << desc;
        return 0;
    }

    if (!vm.count("input-file")) {
        cerr << "Specify at least one file, the last one might be output directory" << endl;
        return 1;
    }

    for (auto &fn: vm["input-file"].as< vector<string> >()) {
        cout << fn << endl;
    }

    return 0;
}

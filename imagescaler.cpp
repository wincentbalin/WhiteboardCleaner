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
    ;

    po::positional_options_description p;
    p.add("input-file", -1);

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        cout << "Usage: imagescaler option(s) file(s)" << endl;
        cout << desc;
        return 0;
    }

    return 0;
}

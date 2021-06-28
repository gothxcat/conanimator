/*
*   Console and arguments
*/

#include <stdlib.h>
#include <string>
#include <iostream>
#include <sstream>
#include <argparse/argparse.hpp>

#include <tests.hpp>

std::string help_run = gen_help_run();

argparse::ArgumentParser setup(std::string name, std::string version, std::string description) {
    argparse::ArgumentParser program(name, version);
    program.add_description(description);

    program.add_argument("-r", "--run")
		.help("run a built-in animation \u2014 use `-r help` to display options")
        .nargs(1);
    
    return program;
}

int parse(argparse::ArgumentParser *program, int argc, char **argv) {
    int ret = EXIT_SUCCESS;
    try {
        program->parse_args(argc, argv);
    } catch (const std::runtime_error &err) {
        std::cout << err.what() << std::endl;
        std::cout << *program;
        ret = EXIT_FAILURE;
    }

    return ret;
}

int process(argparse::ArgumentParser *program) {
    int ret = EXIT_SUCCESS;
    if (program->is_used("-r")) {
        auto test = program->get<std::string>("-r");
        function_map::iterator match = tests.find(test);
		if (match != tests.end()) {
			tests[test]();
		} else if (test == "help") {
            std::cout << help_run;
        } else {
            std::cout << help_run;
			ret = EXIT_FAILURE;
		}
    } else {
        std::cout << *program;
    }

    return ret;
}

std::string gen_help_run() {
    std::stringstream ss;
    ss << "animations:" << std::endl;

    for (auto itr = tests.begin(); itr != tests.cend(); itr++) {
        ss << "  " << itr->first << std::endl;
    }
    
    std::string str = ss.str();
    return str;
}

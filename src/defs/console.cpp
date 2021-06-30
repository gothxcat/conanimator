/*
*   Console and argument handlers
*/

#include <stdlib.h>
#include <string>
#include <iostream>
#include <sstream>

// Library headers
#include <argparse/argparse.hpp>

// Program headers
#include <tests.hpp>
#include <loader.hpp>

std::string help_run = gen_help_run();

// Create argparse instance, prog info and args 
argparse::ArgumentParser setup(std::string name, std::string version, std::string description) {
    argparse::ArgumentParser program(name, version);
    program.add_description(description);

    program.add_argument("-r", "--run")
		.help("run a built-in animation \u2014 use `-r help` to display options")
        .nargs(1);

    program.add_argument("-f", "--file")
		.help("run an animation from a JSON file (see example.json)")
        .nargs(1);
    
    return program;
}

/*  Parse from main args.
*   Parsers and processors take pointers to argparse instance for safer mutability */
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

// Scan used args and return exit code from called routines 
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
    } else if (program->is_used("-f")) {
        // Load and run animation from path if available 
        const int success = run_anim(program->get("-f").c_str());
        if (success != EXIT_SUCCESS) {
            std::cout << "File not readable" << std::endl;
            ret = EXIT_FAILURE;
        }
    } else {
        std::cout << *program;
    }

    return ret;
}

// Concatenate each test from the vector into a string 
std::string gen_help_run() {
    std::stringstream ss;
    ss << "animations:" << std::endl;

    for (auto itr = tests.begin(); itr != tests.cend(); itr++) {
        ss << "  " << itr->first << std::endl;
    }
    
    std::string str = ss.str();
    return str;
}
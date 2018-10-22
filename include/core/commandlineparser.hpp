#pragma once

#include "core/types.hpp"

struct CommandLineFlag
{
    String name;
    Vector<String> alias_list;
    String description;
    bool was_given;
};

struct CommandLineOption
{
    String name;
    Vector<String> alias_list;
    String description;
    String parameter_name;
    String value;
};

class CommandLineParser
{
private:
    Vector<CommandLineFlag> _flags;
    Vector<CommandLineOption> _options;
    Dictionary<String, CommandLineFlag&>  _flagDictionary;
    Dictionary<String, CommandLineOption&>  _optionDictionary;

public:
    CommandLineParser();

    CommandLineFlag& add_help_flag();
    CommandLineFlag& add_flag(String name, String description, Vector<String> alias_list);
    CommandLineOption& add_option(String name, String description, Vector<String> alias_list, String parameter_name);
    CommandLineOption& get_option(const String &name_or_alias);
    CommandLineFlag& get_flag(const String &name_or_alias);
    void parse(int argc, char* argv[]);
    void parse(Queue<String> args);
};

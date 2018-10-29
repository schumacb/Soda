#include "commandlineparser.hpp"
#include "types.hpp"

namespace soda {

CommandLineParser::CommandLineParser()
{

}

void CommandLineParser::parse(int argc, char* argv[])
{
    Queue<String> args;
    for(int i = 0; i < argc; ++i)
    {
        args.push(argv[i]);
    }
    parse(args);
}

void CommandLineParser::parse(Queue<String> args)
{
    while(args.size() > 0)
    {
        auto arg = args.front();
        args.pop();
        if(arg.starts_with("--"))
        {
            auto& option = get_option(arg);
            if(args.size() == 0) {
                throw InvalidArgumentException("The command line option " + option.name + " was given, but its parameter " + option.parameter_name + " is missing!");
            }
            option.value = args.front();
            args.pop();
        }
        if(arg.starts_with("-"))
        {
            auto& flag = get_flag(arg);
            flag.was_given = true;
        }
    }
}

CommandLineOption& CommandLineParser::get_option(const String& name_or_alias)
{
    if(!_optionDictionary.contains_key(name_or_alias))
    {
        throw InvalidArgumentException("Unknown command line option: --" + name_or_alias);
    }
    return _optionDictionary[name_or_alias];
}

CommandLineFlag& CommandLineParser::get_flag(const String &name_or_alias)
{
    if(!_flagDictionary.contains_key(name_or_alias))
    {
        throw InvalidArgumentException("Unknown command line flag: -" + name_or_alias);
    }
    return _flagDictionary[name_or_alias];
}

CommandLineFlag& CommandLineParser::add_help_flag()
{
    Vector<String> alias_list = {};
    alias_list.push_back("?");
    alias_list.push_back("h");
    return add_flag("Help", "This Message", alias_list);
}

CommandLineFlag& CommandLineParser::add_flag(String name, String description, Vector<String> alias_list)
{
    CommandLineFlag flag{ name, alias_list, description, false};
    _flagDictionary[flag.name] = flag;
    for(auto alias : flag.alias_list)
    {
        _flagAliasDictionary[alias] = flag.name;
    }
    return _flagDictionary[flag.name] = flag;
}

CommandLineOption& CommandLineParser::add_option(String name, String description, Vector<String> alias_list, String parameter_name)
{
    CommandLineOption option{name, alias_list, description, parameter_name, ""};
    _optionDictionary[option.name] = option;
    for(auto alias : option.alias_list)
    {
        _optionAliasDictionary[alias] = option.name;
    }
    return _optionDictionary[option.name] = option;
}

} // namespace soda

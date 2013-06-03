#define SASS_CONTEXT

#include <string>
#include <vector>
#include <map>
#include "kwd_arg_macros.hpp"

#ifndef SASS_MEMORY_MANAGER
#include "memory_manager.hpp"
#endif

namespace Sass {
  using namespace std;
  class AST_Node;
  class Block;

  enum Output_Style { NESTED, EXPANDED, COMPACT, COMPRESSED };

  struct Context {
    Memory_Manager<AST_Node*> mem;

    const char* source_c_str;
    vector<const char*> sources; // c-strs containing Sass file contents
    vector<string> include_paths;
    vector<pair<string, const char*> > queue; // queue of files to be parsed
    map<string, Block*> style_sheets; // map of paths to ASTs

    string       image_path; // for the image-url Sass function
    bool         source_comments;
    bool         source_maps;
    Output_Style output_style;

    KWD_ARG_SET(Data) {
      KWD_ARG(Data, const char*,     source_c_str);
      KWD_ARG(Data, string,          entry_point);
      KWD_ARG(Data, string,          image_path);
      KWD_ARG(Data, const char*,     include_paths_c_str);
      KWD_ARG(Data, const char**,    include_paths_array);
      KWD_ARG(Data, vector<string>,  include_paths);
      KWD_ARG(Data, bool,            source_comments);
      KWD_ARG(Data, bool,            source_maps);
      KWD_ARG(Data, Output_Style,    output_style);
    };

    Context(Data);
    ~Context();
    void collect_include_paths(const char* paths_str);
    void collect_include_paths(const char* paths_array[]);
    bool add_file(string path);
    void compile_string();
    void compile_file();
  };

}
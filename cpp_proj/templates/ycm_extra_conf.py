def Settings( **kwargs ):
  return {
    'flags': [ '-x', 'c++', '-std=c++20', '-Wall', '-Wextra', '-Werror', 
{% if EXTERN.wxWidgets%}
              '-D_FILE_OFFSET_BITS=64', '-DWXUSINGDLL', '-D__WXMAC__', '-D__WXOSX__','-D__WXOSX_COCOA__',
              '-I/opt/homebrew/lib/wx/include/osx_cocoa-unicode-3.2',
              '-I/opt/homebrew/include/wx-3.2',
{% endif %}
              '-I./include', 
              '-I./extern/cxxopts/include', 
              '-I./extern/fmt/include', 
              '-I./extern/spdlog/include'
            ],
  }

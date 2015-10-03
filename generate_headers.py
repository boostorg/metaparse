#!/usr/bin/python

# Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)

import sys
import argparse
import re
import os

def remove_last_dot(s):
  if s.endswith('.'):
    return s[:-1]
  else:
    return s

def remove_newline(s):
  return re.sub('[\r\n]', '', s)

def is_definition(s):
  cmd = s.strip()
  
  def_prefixes = ['#include ', 'using ', 'struct ', 'template ']
  return any([cmd.startswith(s) for s in def_prefixes]) or cmd.endswith(';')

def prefix_lines(prefix, s):
  return '\n'.join(['%s%s' % (prefix, l) for l in s.split('\n')])

def protect_metashell(s):
  if s.startswith('#include <metashell'):
    return '#ifdef __METASHELL\n%s\n#endif' % (s)
  else:
    return s

def parse_md(filename):
  sections = []
  defs = []
  current_section = ''
  in_cpp_snippet = False
  numbered_section_header = re.compile('^\[section *([0-9.]+)')
  metashell_command = re.compile('^> [^ ]')
  metashell_prompt = re.compile('^(\.\.\.|)>')
  msh_cmd = ''
  for l in open(filename, 'r'):
    if l.startswith('  '):
      ll = l[2:]
      if not in_cpp_snippet:
        in_msh_cpp_snippet = True
      if in_msh_cpp_snippet:
        if metashell_command.match(ll) or msh_cmd != '':
          cmd = metashell_prompt.sub('', remove_newline(ll))
          if msh_cmd != '':
            msh_cmd = msh_cmd + '\n'
          msh_cmd = msh_cmd + cmd
          if msh_cmd.endswith('\\'):
            msh_cmd = msh_cmd[:-1].strip() + ' '
          else:
            if not is_definition(msh_cmd):
              msh_cmd = '// query:\n%s' % (prefix_lines('//   ', msh_cmd))
            defs.append((current_section, protect_metashell(msh_cmd.strip())))
            msh_cmd = ''
        elif not in_cpp_snippet:
          in_msh_cpp_snippet = False
      in_cpp_snippet = True
    else:
      in_cpp_snippet = False
      m = numbered_section_header.match(l)
      if m:
        current_section = remove_last_dot(m.group(1)).replace('.', '_')
        sections.append(current_section)

  sections.sort(key = lambda s: [int(n) for n in s.split('_')])
  return (sections, defs)

def delete_old_headers(path):
  for f in os.listdir(path):
    if f.endswith('.hpp'):
      os.remove(os.path.join(path, f))

def gen_headers(md_filename, path):
  (sections, defs) = parse_md(md_filename)

  delete_old_headers(path)

  prev_section = ''
  for s in sections:
    prev_name = prev_section.replace('_', '.')
    with open(os.path.join(path, s + '.hpp'), 'w') as f:
      include_guard = 'BOOST_METAPARSE_GETTING_STARTED_%s_HPP' % (s)
      f.write('#ifndef %s\n' % (include_guard))
      f.write('#define %s\n' % (include_guard))
      f.write('\n')

      f.write('// Automatically generated header file\n')
      f.write('\n')

      if prev_section != '':
        f.write('// Definitions before section %s\n' % (prev_name))
        f.write('#include "%s.hpp"\n' % (prev_section))
        f.write('\n')

      f.write('// Definitions of section %s\n' % (prev_name))
      f.write('\n'.join(
        ['%s\n' % (d) for (sec, d) in defs if sec == prev_section])
      )
      f.write('\n')

      f.write('#endif\n')
      f.write('\n')
    prev_section = s

def main():
  desc = 'Generate headers with the definitions of a Getting Started guide'
  parser = argparse.ArgumentParser(description=desc)
  parser.add_argument(
    '--src',
    dest='src',
    default='doc/getting_started.qbk',
    help='The .qbk source of the Getting Started guide'
  )
  parser.add_argument(
    '--dst',
    dest='dst',
    default='example/getting_started',
    help='The target directory to generate into (all headers in that directory will be deleted!)'
  )

  args = parser.parse_args()

  gen_headers(args.src, args.dst)

if __name__ == "__main__":
  main()


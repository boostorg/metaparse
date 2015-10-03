#!/usr/bin/python

# Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)

import sys
import re

def strip_not_finished_line(s):
  s = s.strip()
  return s[:-1] if s.endswith('\\') else s

def make_copy_paste_friendly(lines):
  result = []
  for l in lines:
    if l.startswith('> '):
      result.append(l[2:])
    elif l.startswith('...> '):
      result[-1] = strip_not_finished_line(result[-1]) + l[5:].lstrip()
  return result

def files_to_write(fn):
  code_prefix = '  '

  fn_base = fn[:-4] if fn.endswith('.qbk') else fn
  files = {}

  result = []
  in_cpp_code = False
  counter = 0
  in_copy_paste_friendly_examples = False
  skip_empty_lines = False
  for l in open(sys.argv[1], 'r').readlines():
    if l.strip() != '' or not skip_empty_lines:
      skip_empty_lines = False
      if in_copy_paste_friendly_examples:
        if 'endsect' in l:
          in_copy_paste_friendly_examples = False
          result.append('\n')
          result.extend([
            '[include {0}_{1}.qbk]\n'.format(re.sub('^.*/', '', fn_base), i) \
            for i in range(0, counter)
          ])
          result.append('\n')
          result.append(l)
          in_copy_paste_friendly_examples = False
      elif '[section Copy-paste friendly code examples]' in l:
        in_copy_paste_friendly_examples = True
        result.append(l)
      elif 'copy-paste friendly version' in l:
        skip_empty_lines = True
      else:
        result.append(l)
  
        if in_cpp_code:
          if not l.startswith(code_prefix):
            in_cpp_code = False
            if len(code) > 1:
              f = '{0}_{1}'.format(fn_base, counter)
              basename_f = re.sub('^.*/', '', f)
              files['{0}.qbk'.format(f)] = \
                '[#{0}]\n\n{1}\n'.format(
                  basename_f,
                  ''.join(
                    [code_prefix + s for s in make_copy_paste_friendly(code)]
                  )
                )
              result.append(
                '[link {0} copy-paste friendly version]\n'.format(basename_f)
              )
              result.append('\n')
              counter = counter + 1
          elif \
              l.startswith(code_prefix + '> ') \
              or l.startswith(code_prefix + '...> '):
            code.append(l[len(code_prefix):])
        elif l.startswith(code_prefix):
          in_cpp_code = True
          code = [l[len(code_prefix):]]

  files[fn] = ''.join(result)
  return files

def main():
  if len(sys.argv) != 2:
    print 'Usage: {0} <filename>'.format(sys.argv[0])
    sys.exit(1)

  files = files_to_write(sys.argv[1])
  for fn in files:
    with open(fn, 'w') as f:
      f.write(files[fn])

if __name__ == "__main__":
  main()


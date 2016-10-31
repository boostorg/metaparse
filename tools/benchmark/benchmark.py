#!/usr/bin/python
"""Utility to benchmark the generated source files"""

# Copyright Abel Sinkovics (abel@sinkovics.hu) 2016.
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)

import argparse
import os
import subprocess
import json
import math
import platform
import matplotlib
import random
import re
import time
import psutil

matplotlib.use('Agg')
import matplotlib.pyplot  # pylint:disable=I0011,C0411,C0412,C0413


def benchmark_command(cmd, progress):
    """Benchmark one command execution"""
    full_cmd = '/usr/bin/time --format="%U %M" {0}'.format(cmd)
    print '{0:6.2f}% Running {1}'.format(100.0 * progress, full_cmd)
    (_, err) = subprocess.Popen(
        ['/bin/bash', '-c', full_cmd],
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE
    ).communicate('')

    values = err.strip().split(' ')
    if len(values) == 2:
        try:
            return (float(values[0]), float(values[1]))
        except:  # pylint:disable=I0011,W0702
            pass  # Handled by the code after the "if"

    print err
    raise Exception('Error during benchmarking')


def benchmark_file(
        filename, compiler, include_dirs, (progress_from, progress_to),
        iter_count):
    """Benchmark one file"""
    time_sum = 0
    mem_sum = 0
    for nth_run in xrange(0, iter_count):
        (time_spent, mem_used) = benchmark_command(
            '{0} -std=c++11 {1} -c {2}'.format(
                compiler,
                ' '.join('-I{0}'.format(i) for i in include_dirs),
                filename
            ),
            (
                progress_to * nth_run + progress_from * (iter_count - nth_run)
            ) / iter_count
        )
        os.remove(os.path.splitext(os.path.basename(filename))[0] + '.o')
        time_sum = time_sum + time_spent
        mem_sum = mem_sum + mem_used

    return {
        "time": time_sum / iter_count,
        "memory": mem_sum / (iter_count * 1024)
    }


def compiler_info(compiler):
    """Determine the name + version of the compiler"""
    (out, err) = subprocess.Popen(
        ['/bin/bash', '-c', '{0} -v'.format(compiler)],
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE
    ).communicate('')

    gcc_clang = re.compile('(gcc|clang) version ([0-9]+(\\.[0-9]+)*)')

    for line in (out + err).split('\n'):
        mtch = gcc_clang.search(line)
        if mtch:
            return mtch.group(1) + ' ' + mtch.group(2)

    return compiler


def string_char(char):
    """Turn the character into one that can be part of a filename"""
    return '_' if char in [' ', '~', '(', ')', '/', '\\'] else char


def make_filename(string):
    """Turn the string into a filename"""
    return ''.join(string_char(c) for c in string)


def files_in_dir(path, extension):
    """Enumartes the files in path with the given extension"""
    ends = '.{0}'.format(extension)
    return (f for f in os.listdir(path) if f.endswith(ends))


def format_time(seconds):
    """Format a duration"""
    minute = 60
    hour = minute * 60
    day = hour * 24
    week = day * 7

    result = []
    for name, dur in [
            ('week', week), ('day', day), ('hour', hour),
            ('minute', minute), ('second', 1)
    ]:
        if seconds > dur:
            value = seconds // dur
            result.append(
                '{0} {1}{2}'.format(int(value), name, 's' if value > 1 else '')
            )
            seconds = seconds % dur
    return ' '.join(result)


def benchmark(src_dir, compiler, include_dirs, iter_count):
    """Do the benchrmarking"""

    files = list(files_in_dir(src_dir, 'cpp'))
    random.shuffle(files)

    started_at = time.time()
    result = {}
    for filename in files:
        progress = len(result)
        result[filename] = benchmark_file(
            os.path.join(src_dir, filename),
            compiler,
            include_dirs,
            (float(progress) / len(files), float(progress + 1) / len(files)),
            iter_count
        )
        elapsed = time.time() - started_at
        total = float(len(files) * elapsed) / len(result)
        print 'Elapsed time: {0}, Remaining time: {1}'.format(
            format_time(elapsed),
            format_time(total - elapsed)
        )
    return result


def plot(values, mode_names, title, (xlabel, ylabel), out_file):
    """Plot a diagram"""
    matplotlib.pyplot.clf()
    for mode, mode_name in mode_names.iteritems():
        vals = values[mode]
        matplotlib.pyplot.plot(
            [x for x, _ in vals],
            [y for _, y in vals],
            label=mode_name
        )
    matplotlib.pyplot.title(title)
    matplotlib.pyplot.xlabel(xlabel)
    matplotlib.pyplot.ylabel(ylabel)
    if len(mode_names) > 1:
        matplotlib.pyplot.legend()
    matplotlib.pyplot.savefig(out_file)


def mkdir_p(path):
    """mkdir -p path"""
    try:
        os.makedirs(path)
    except OSError:
        pass


def configs_in(src_dir):
    """Enumerate all configs in src_dir"""
    for filename in files_in_dir(src_dir, 'json'):
        with open(os.path.join(src_dir, filename), 'rb') as in_f:
            yield json.load(in_f)


def byte_to_gb(byte):
    """Convert bytes to GB"""
    return byte / (1024.0 * 1024 * 1024)


def plot_diagrams(results, configs, compiler, out_dir):
    """Plot all diagrams specified by the configs"""
    display_name = {
        'time': 'Compilation time (s)',
        'memory': 'Compiler memory usage (MB)',
    }

    compiler_fn = make_filename(compiler)
    total = psutil.virtual_memory().total  # pylint:disable=I0011,E1101
    memory = int(math.ceil(byte_to_gb(total)))

    for config in configs:
        out_prefix = '{0}_{1}'.format(config['name'], compiler_fn)
        for measured in ['time', 'memory']:
            files = config['files']
            mpts = sorted(int(k) for k in files.keys())
            plot(
                {
                    m: [(x, results[files[str(x)][m]][measured]) for x in mpts]
                    for m in config['modes'].keys()
                },
                config['modes'],
                display_name[measured],
                (config['x_axis_label'], display_name[measured]),
                os.path.join(
                    out_dir,
                    'images',
                    '{0}_{1}.png'.format(out_prefix, measured)
                )
            )
        with open(
            os.path.join(out_dir, '{0}.qbk'.format(out_prefix)),
            'wb'
        ) as out_f:
            qbk_content = """{0}
Measured on a {2} host with {3} GB memory. Compiler used: {4}.

[$images/metaparse/{1}_time.png [width 70%]]
[$images/metaparse/{1}_memory.png [width 70%]]
""".format(config['desc'], out_prefix, platform.platform(), memory, compiler)
            out_f.write(qbk_content)


def main():
    """The main function of the script"""
    desc = 'Benchmark the files generated by generate.py'
    parser = argparse.ArgumentParser(description=desc)
    parser.add_argument(
        '--src',
        dest='src_dir',
        default='generated',
        help='The directory containing the sources to benchmark'
    )
    parser.add_argument(
        '--out',
        dest='out_dir',
        default='../../doc',
        help='The output directory'
    )
    parser.add_argument(
        '--include',
        dest='include',
        default='include',
        help='The directory containing the headeres for the benchmark'
    )
    parser.add_argument(
        '--boost_headers',
        dest='boost_headers',
        default='../../../..',
        help='The directory containing the Boost headers (the boost directory)'
    )
    parser.add_argument(
        '--compiler',
        dest='compiler',
        default='g++',
        help='The compiler to do the benchmark with'
    )
    parser.add_argument(
        '--repeat_count',
        dest='repeat_count',
        type=int,
        default=5,
        help='How many times a measurement should be repeated.'
    )

    args = parser.parse_args()

    compiler = compiler_info(args.compiler)
    results = benchmark(
        args.src_dir,
        args.compiler,
        [args.include, args.boost_headers],
        args.repeat_count
    )

    plot_diagrams(results, configs_in(args.src_dir), compiler, args.out_dir)


if __name__ == '__main__':
    main()

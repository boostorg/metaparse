#!/bin/bash

for svg in *.svg
do
  rsvg-convert -o ../$(echo $svg | sed 's/\.svg/\.png/') -f png $svg
done

for md in *.md
do
  ./gen_toc -i $md -o - -t pandoc_html \
    | pandoc --from markdown --to html -c style.css -o ../$(echo $md | sed 's/\.md/\.html/')
done


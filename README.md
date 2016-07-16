# Lasagna_PDF

A tool to conbine PDF files like

- [original PDF1](https://github.com/nukazuka/Lasagna_PDF/blob/master/sample/sample1.pdf)
- [original PDF2](https://github.com/nukazuka/Lasagna_PDF/blob/master/sample/sample2.pdf)
- [original PDF3](https://github.com/nukazuka/Lasagna_PDF/blob/master/sample/sample3.pdf)
- [original PDF4](https://github.com/nukazuka/Lasagna_PDF/blob/master/sample/sample4.pdf)

- [output][https://github.com/nukazuka/Lasagna_PDF/blob/master/sample/output.pdf]

It looks like lasagna, isn't it?

## All you need is...

This tool is actually just a wrapper of pdfjam.

- [pdfjam](http://www2.warwick.ac.uk/fac/sci/statistics/staff/academic-research/firth/software/pdfjam/)
   - if you have already installed [TeX Live](http://www.tug.org/texlive/), it should be enough
- [pdfinfo](https://poppler.freedesktop.org/)

## Installation

You can:

- install using make, default installed directory is ~/bin
- set PATH

## Usage

Usage: lpdf  [OPTIONS] FILE1 FILE2 ...
 | Options         | Description                           |
 | :-------------- | :------------------------------------ |
 | -a, --all       | all pages will be processed           |
 | -e, --end       | specify the end page                  |
 | -h, --help      | show this guide                       |
 | -l, --landscape | landscape mode                        |
 | --nup, --matrix | configuration of page, default is 1x1 |
 | -o, --output    | A name of output file                 |
 | -s, --start     | specifiy the beginning page           |

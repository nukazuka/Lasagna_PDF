bin_dir=~/bin

all:
	cd src; make
	ln -s -f ${PWD}/src/Lasagna_PDF_transposition $(bin_dir)
	ln -s -f ${PWD}/lpdf.sh $(bin_dir)/lpdf

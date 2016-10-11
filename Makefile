bin_dir=~/bin

all:
	cd src; make
	install -s ${PWD}/src/Lasagna_PDF_transposition $(bin_dir)
	ln -s -f ${PWD}/lpdf.sh $(bin_dir)/lpdf

clean:
	cd src; make clean
